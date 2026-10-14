# Arduino-Based Automatic Voltage Stabilizer

**Project period:** December 2023  
**Project type:** Embedded Systems · Power Electronics · Circuit Simulation  
**Tools:** Proteus Design Suite, Arduino IDE  
**Technologies:** Arduino Uno, C/C++, Voltage Sensing, ULN2003A, Electromechanical Relays, Transformer Tap Switching

![Complete Proteus circuit of my Arduino-based automatic voltage stabilizer](assets/original-proteus-schematic.png)

## About my project

I designed, programmed, and simulated an **Arduino-based automatic voltage stabilizer** as an embedded-systems and power-electronics project. My goal was to develop a system that could respond automatically to changes in AC input voltage and select an appropriate transformer tap to keep the output closer to a desired voltage level.

Instead of manually changing transformer connections, I used an **Arduino Uno** to monitor the input through a voltage-sensing circuit and control a set of **5 V relays** through a **ULN2003A relay-driver IC**. I assembled the circuit in **Proteus**, developed Arduino control logic, and repeatedly tested and adjusted the simulation until the voltage-sensing and switching behavior worked together.

This project gave me hands-on experience in connecting three parts of an engineering system: **analog voltage measurement, microcontroller programming, and electromechanical switching**.

## My contributions

I worked on the design, integration, programming, testing, and troubleshooting of the project. My work included:

- **Circuit design in Proteus:** Built the full simulation schematic, placing and connecting the Arduino Uno, sensing circuit, relays, transformer models, indicators, and virtual instruments.
- **Voltage measurement:** Set up an AC-to-DC sensing stage so the Arduino could read a conditioned analog signal representing changes in the input voltage.
- **Arduino programming:** Developed the control approach that reads the analog input, decides which voltage range is active, and issues the required relay-control signals.
- **Driver and relay integration:** Connected Arduino digital outputs to the ULN2003A relay driver and used the relays to select transformer connections.
- **Simulation and debugging:** Tested the system with different simulated input voltages; investigated wiring, measurement, and switching behavior; and iterated on the circuit and code.
- **Output observation:** Used Proteus AC voltmeters, LEDs, and a virtual serial terminal to check how the circuit responded.

## Why I built it

AC supply voltage is not always constant. A **low input voltage** can leave equipment operating below its intended level, while a **high input voltage** may expose equipment to excessive voltage. I wanted to demonstrate an automatic system that makes a correction without requiring someone to manually switch the transformer taps.

The main idea was simple: **measure the incoming voltage → decide which transformer connection is appropriate → activate the corresponding relay → observe the output**.

## How the system works

```text
          Simulated AC input
                  |
                  v
       Bridge rectifier + filter
         + voltage divider
                  |
                  v
          Arduino Uno (A0)
                  |
                  v
          Voltage evaluation
        and tap-selection logic
                  |
                  v
       Arduino digital outputs
                  |
                  v
         ULN2003A relay driver
                  |
                  v
            Relay bank
                  |
                  v
        Transformer tap selection
                  |
                  v
         Regulated AC output
                  |
                  v
          Proteus AC voltmeter
```

### 1. Measuring the incoming voltage

I used a voltage-sensing section containing **BR1**, **R1**, **R2**, and **C1**. The bridge rectifier converts the sensed AC waveform into a rectified signal. The resistors form a divider, and the capacitor smooths the measured signal. This provides an analog value that the Arduino can sample at **A0**.

In the schematic, the sensing section uses **R1 = 1 MΩ, R2 = 10 kΩ, and C1 = 10 µF**. I also included a **VSINE simulation source** and adjustable resistance to explore input-voltage variation in Proteus.

### 2. Processing the reading in Arduino code

I programmed the Arduino-based controller to interpret voltage changes and select a suitable switching state. The controller's central job is to convert an analog measurement into a decision about which transformer tap should be connected.

For example, if the measured supply is low, the controller should select a connection that **increases the effective output voltage**. If the input is high, it should select a connection that **reduces the effective output voltage**. Around the intended operating voltage, it should choose a normal connection rather than changing relays unnecessarily.

### 3. Switching the transformer connections

The Arduino cannot directly supply the current needed by the relay coils. I used the **ULN2003A** as an interface between the Arduino digital outputs and the relay bank. The relay contacts perform the transformer-tap switching, while the microcontroller determines when and which switching command to issue.

The schematic contains **five 5 V relays (RL2–RL6)** and transformer models marked **TR1** and **TR2**, with voltage labels including **150 V, 180 V, 210 V, 240 V, 270 V, and 300 V**. These voltage labels show the range of supply conditions considered in the design.

### 4. Checking the result

I used the Proteus voltmeters to view AC voltage values and the indicators and virtual terminal to observe controller behavior. This let me test the complete sequence—from input-voltage change to relay selection and resulting transformer output—without building a mains-connected prototype.

## Circuit components

| Component | Schematic reference | Purpose |
| --- | --- | --- |
| Arduino Uno | ARD1 | Reads sensor values and controls switching |
| Bridge rectifier | BR1 | Rectifies the sensed AC signal |
| Resistors | R1: 1 MΩ, R2: 10 kΩ | Conditions the sensing voltage |
| Capacitor | C1: 10 µF | Smooths the sensed voltage |
| Simulated source and adjustment | V1, R3, R4, RV1 | Simulates and varies an AC input signal |
| Relay driver | U1: ULN2003A | Interfaces Arduino outputs with relay coils |
| Five relays | RL2–RL6, 5 V | Select transformer switching paths |
| Transformers | TR1, TR2 | Provide selectable transformer connections |
| Status indicators | D1, D2 | Show controller status |
| AC voltmeters | Proteus instruments | Observe simulated AC voltage |
| Virtual terminal | Proteus instrument | Inspect serial/status output |

## My development process

### Phase 1 — Planning the control system

I began by separating the design into three blocks: a **voltage-sensing section**, an **Arduino decision-making section**, and a **transformer/relay-switching section**. This approach helped me understand how the circuit should respond to different voltage levels.

### Phase 2 — Building the Proteus circuit

I created the schematic in Proteus, added the Arduino Uno and individual components, and connected the analog sensing stage to the controller. I wired the Arduino outputs to the ULN2003A and the relay coils, then integrated the transformer models, status LEDs, and measurement instruments.

### Phase 3 — Programming the controller

I worked with Arduino code to read the sensed analog voltage and control the relay outputs. An important part of this work was making sure the software decisions matched the physical switching connections represented in the Proteus schematic.

### Phase 4 — Trial, error, and troubleshooting

Getting the sensing, code, relay activation, and transformer selection to operate as a single system took repeated testing. I checked simulated input conditions, observed instrument readings, and refined the design when the switching behavior did not match what I expected. Working through these problems was one of the most valuable parts of the project.

### Phase 5 — Testing the automatic regulation behavior

Once the integrated Proteus simulation was working, I tested how the stabilizer reacted when the simulated supply moved into lower and higher voltage ranges. The controller switched relay paths to select a transformer connection intended to compensate for the change. I used the output-voltage instruments to check the correction behavior.

## Voltage regulation principle

The aim of a tap-switching stabilizer is to keep the AC output close to a nominal target despite variations at the input. Transformer taps change the effective turns ratio, so different connections produce different output voltages for the same input.

The relationship is approximately:

\[
\frac{V_{out}}{V_{in}} \approx \frac{N_{out}}{N_{in}}
\]

where \(V_{in}\) and \(V_{out}\) are input and output voltage and \(N_{in}\) and \(N_{out}\) are the effective turns on the chosen transformer connection. The actual output depends on the transformer configuration and load.

| Input condition | Intended controller response | Why |
| --- | --- | --- |
| Supply falls below target range | Select a step-up connection | Raise the output toward its target |
| Supply is near the desired range | Select a suitable nominal connection | Avoid unnecessary correction |
| Supply rises above target range | Select a step-down connection | Reduce the output toward its target |
| Supply exceeds the intended working range | Use a protective/fault state | Avoid inappropriate switching |

The diagram also includes status indications referring to very low and very high voltage conditions.

## Skills and experience gained

Through this project, I developed practical experience in **Proteus circuit simulation, Arduino C/C++ programming, analog sensing, digital control, relay drivers, transformer tap selection, circuit integration, and iterative debugging**. More importantly, I learned how to take a circuit idea, implement its control logic, and refine the combined system through simulation until it behaved as intended.

## Project files

```text
voltage-stabilizer-arduino/
├── README.md
├── assets/
│   ├── original-proteus-schematic.png
│   └── original-project-description.png
├── firmware/VoltageStabilizer/
│   └── VoltageStabilizer.ino
├── hardware/
│   └── bill-of-materials.csv
├── docs/
│   ├── schematic-analysis.md
│   ├── control-algorithm.md
│   ├── safety-and-validation.md
│   └── github-upload-guide.md
├── scripts/
│   ├── control_model.py
│   └── demo.py
├── tests/
│   └── test_control_model.py
└── LICENSE
```

**Code in this repository:** The original project was designed and programmed in 2023. The included `VoltageStabilizer.ino` is a later documented implementation of the control concept; it is not a recovered copy of my original 2023 sketch. The Python model and tests are additional supporting examples.

## Project outcome

I completed a Proteus-based Arduino voltage stabilizer simulation that combined **input-voltage sensing, software-controlled relay selection, transformer connections, and output-voltage monitoring**. After multiple rounds of testing and troubleshooting, I was able to demonstrate automatic switching in response to input-voltage changes. This project strengthened my interest in **embedded control systems, automation, and power-electronics applications**.

> **Hardware safety:** This repository documents a Proteus simulation. Any real AC-voltage implementation requires proper isolation, correctly rated protection and switching equipment, and qualified electrical review. Do not connect mains AC directly to an Arduino analog input.
