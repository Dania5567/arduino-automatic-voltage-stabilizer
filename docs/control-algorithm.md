# Reconstructed control algorithm

This document describes newly developed example logic, **not recovered original 2023 firmware**.

1. Sample an isolated, conditioned DC representation of input voltage on A0.
2. Convert Arduino ADC counts to an estimated AC RMS input voltage. The scale and offset are **illustrative placeholders**, and cannot be used without calibration.
3. Filter the estimate using an exponential moving average (alpha 0.15).
4. Reject out-of-range readings (illustrative 140–285 V guard band).
5. Pick the reference tap with the smallest predicted deviation from 230 V among 150, 180, 210, 240, and 270 V.
6. Apply a 6 V switching improvement threshold, a 3-second minimum hold, and a 150 ms break-before-make interval. Trigger an immediate fault for unsupported input.
7. Send measurement and tap state to Serial at 9600 baud, approximately once per second.

The output estimate uses `predicted_out = input_v * 230 / tap_v`, a **hypothetical ideal-ratio model**. This formula is not confirmed for the transformers in the screenshot and excludes losses, regulation, loading, winding configuration, and switching transients.

**Critical**: `ENABLE_OUTPUTS = false` in the Arduino sketch, leaving actual relay outputs off. Turning it on does not make the device safe. The sensing network, relay contact topology, interlocks, and electrical protection require independent validation before hardware trials.

## Demonstration truth table (illustrative, not measured)

| Hypothetical input (V) | Selected reference tap (V) | Calculated output (V) |
| ---: | ---: | ---: |
| 150 | 150 | 230 |
| 180 | 180 | 230 |
| 210 | 210 | 230 |
| 240 | 240 | 230 |
| 270 | 270 | 230 |
| 300 | None | Not supported by this five-channel reference design |

These examples test the computation, not the electrical performance.
