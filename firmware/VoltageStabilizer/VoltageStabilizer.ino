/*
 * Voltage Stabilizer — RECONSTRUCTED demonstration firmware (2026)
 * Based on a photographed December 2023 project, NOT recovered original code.
 *
 * BENCH / SIMULATION ONLY. NEVER attach mains to an Arduino input.
 * Requires isolated and conditioned voltage sensing, calibrated before use.
 * ENABLE_OUTPUTS defaults false: all relays remain de-energized.
 * A five-relay reference topology is assumed, and MUST be adapted/validated
 * against an actual switching design before any physical relay connection.
 */
#include <Arduino.h>
#include <math.h>

namespace Config {
  constexpr bool ENABLE_OUTPUTS = false;    // SAFETY INTERLOCK: simulation review first
  constexpr uint8_t SENSOR_PIN = A0;
  constexpr uint8_t RELAY_PINS[5] = {2, 3, 4, 5, 6};
  constexpr uint8_t LED_HEALTHY = 9;
  constexpr uint8_t LED_FAULT = 10;
  constexpr float ADC_REFERENCE_V = 5.0f;
  // Placeholders; must calibrate against an isolated AC sensing circuit.
  constexpr float VOLTS_PER_ADC_VOLT = 75.0f;
  constexpr float SENSOR_OFFSET_V = 0.0f;
  constexpr float FILTER_ALPHA = 0.15f;
  constexpr float NOMINAL_OUTPUT_V = 230.0f;
  constexpr float MIN_INPUT_V = 140.0f;
  constexpr float MAX_INPUT_V = 285.0f;
  constexpr float MAX_PREDICTED_ERROR_V = 35.0f;
  constexpr float HYSTERESIS_IMPROVEMENT_V = 6.0f;
  constexpr unsigned long SAMPLE_MS = 100;
  constexpr unsigned long MIN_HOLD_MS = 3000;
  constexpr unsigned long BREAK_MS = 150;
}

// Image shows 150/180/210/240/270/300 labels but only five relay symbols.
// This demonstration uses five of those labels. The 300 V path is unimplemented.
constexpr float TAP_RATINGS_V[5] = {150, 180, 210, 240, 270};
float filteredInputV = NAN;
int8_t activeTap = -1;
int8_t pendingTap = -1;
unsigned long lastSampleMs = 0;
unsigned long lastChangeMs = 0;
unsigned long breakStartedMs = 0;
bool isBreaking = false;

void allRelaysOff() {
  for (uint8_t i = 0; i < 5; ++i) digitalWrite(Config::RELAY_PINS[i], LOW);
}

// REFERENCE MODEL ONLY: assumes a hypothetical output = input * 230 / tap.
// No transformer ratio or tap-to-relay mapping is recoverable from screenshot.
float predictedOutput(float inputV, uint8_t tapIndex) {
  return inputV * Config::NOMINAL_OUTPUT_V / TAP_RATINGS_V[tapIndex];
}

int8_t desiredTap(float inputV) {
  if (!isfinite(inputV) || inputV < Config::MIN_INPUT_V || inputV > Config::MAX_INPUT_V) return -1;
  int8_t best = -1;
  float bestError = 1e9f;
  for (uint8_t i = 0; i < 5; ++i) {
    float error = fabsf(predictedOutput(inputV, i) - Config::NOMINAL_OUTPUT_V);
    if (error < bestError) { bestError = error; best = i; }
  }
  if (bestError > Config::MAX_PREDICTED_ERROR_V) return -1;
  if (activeTap >= 0 && best != activeTap) {
    float currentError = fabsf(predictedOutput(inputV, activeTap) - Config::NOMINAL_OUTPUT_V);
    if (currentError - bestError < Config::HYSTERESIS_IMPROVEMENT_V) return activeTap;
  }
  return best;
}

void publishStatus(float volts, int8_t selected) {
  Serial.print(F("measured_input_v=")); Serial.print(volts, 1);
  Serial.print(F(" requested_tap="));
  if (selected < 0) Serial.print(F("FAULT"));
  else Serial.print(TAP_RATINGS_V[selected], 0);
  Serial.print(F(" active_tap="));
  if (activeTap < 0) Serial.print(F("NONE"));
  else Serial.print(TAP_RATINGS_V[activeTap], 0);
  Serial.print(F(" outputs_enabled="));
  Serial.println(Config::ENABLE_OUTPUTS ? F("yes") : F("no"));
}

void setup() {
  Serial.begin(9600);
  for (uint8_t i = 0; i < 5; ++i) {
    digitalWrite(Config::RELAY_PINS[i], LOW);
    pinMode(Config::RELAY_PINS[i], OUTPUT);
  }
  pinMode(Config::LED_HEALTHY, OUTPUT);
  pinMode(Config::LED_FAULT, OUTPUT);
  allRelaysOff();
  digitalWrite(Config::LED_FAULT, HIGH);
  Serial.println(F("RECONSTRUCTED VOLTAGE STABILIZER / SIMULATION ONLY"));
  Serial.println(F("Uncalibrated placeholder conversion; relay outputs disabled by default."));
}

void loop() {
  const unsigned long now = millis();
  if (isBreaking && (now - breakStartedMs >= Config::BREAK_MS)) {
    isBreaking = false;
    if (Config::ENABLE_OUTPUTS && pendingTap >= 0) {
      digitalWrite(Config::RELAY_PINS[pendingTap], HIGH); // ULN2003 input active HIGH
      activeTap = pendingTap;
    } else activeTap = -1;
    pendingTap = -1;
    lastChangeMs = now;
  }
  if (now - lastSampleMs < Config::SAMPLE_MS) return;
  lastSampleMs = now;
  int raw = analogRead(Config::SENSOR_PIN);
  const float sensorV = raw * Config::ADC_REFERENCE_V / 1023.0f;
  const float inputV = sensorV * Config::VOLTS_PER_ADC_VOLT + Config::SENSOR_OFFSET_V;
  if (!isfinite(filteredInputV)) filteredInputV = inputV;
  else filteredInputV += Config::FILTER_ALPHA * (inputV - filteredInputV);

  int8_t candidate = desiredTap(filteredInputV);
  // Fault: release outputs without waiting for minimum hold interval.
  if (candidate < 0) {
    allRelaysOff(); activeTap = -1; pendingTap = -1; isBreaking = false;
  } else if (Config::ENABLE_OUTPUTS && !isBreaking && candidate != activeTap &&
             (activeTap < 0 || now - lastChangeMs >= Config::MIN_HOLD_MS)) {
    allRelaysOff(); activeTap = -1;
    pendingTap = candidate;
    isBreaking = true;
    breakStartedMs = now;
  }
  const bool healthy = candidate >= 0;
  digitalWrite(Config::LED_HEALTHY, healthy ? HIGH : LOW);
  digitalWrite(Config::LED_FAULT, healthy ? LOW : HIGH);
  static uint8_t reportCount = 0;
  if (++reportCount >= 10) { reportCount = 0; publishStatus(filteredInputV, candidate); }
}
