# Schematic analysis (source: supplied screenshot)

## What is visible

The design includes an Arduino Uno (ARD1), a bridge rectifier (BR1), an RC/voltage-divider sensing network (R1 = 1 MΩ, R2 = 10 kΩ, C1 = 10 µF), an adjustable AC test source (V1) with R3 = 10 kΩ, R4 = 10 kΩ and RV1 = 10 kΩ, two transformers (TR1 and TR2, both marked `TRAN-2P5S`), the ULN2003A (U1), five visible 5 V relays (RL2 through RL6), two red indicators (D1 and D2), three AC voltmeters, and a virtual terminal.

The rectifier network appears connected to Arduino A0. Several Arduino digital outputs connect to the ULN2003A input side, driving relay coils. Transformer labels on the right include 150, 180, 210, 240, 270, and 300; they imply distinct nominal input/tap ranges but the exact electrical topology and transformer turns ratios are not recoverable from one image.

Texts near the indicators suggest `For greater than 325 (out of order)` and `For less than 135`, but these exact thresholds and polarity were not validated against code. The visible 150–300 labels should not be interpreted as confirmed switching thresholds.

## Important uncertainties

- Five relay symbols exist but six nominal voltage labels are visible. No complete relay-to-tap truth table can be proved from the image.
- The image does not establish the true calibration factor, RMS measurement approach, transformer turns ratios, or relay contact ratings.
- The original firmware, working Proteus `.pdsprj`/`.dsn` project, verified physical PCB, original serial output, and experiment logs were **not provided**.
- The reconstruction uses Arduino D2–D6 for five hypothetical relay channels; do not assume these match the exact pins in the photographed circuit.
- LEDs are assigned to D9/D10 as a new firmware convention, not an asserted original pin map.
- The bridge appears connected to AC circuit nodes. Directly replicating that with live AC mains would be hazardous. A galvanically isolated sensing scheme, properly protected power stage, and qualified engineering review are necessary.
- The ULN2003A is a *low-side coil driver*, not a relay-contact isolation device. Coil supply, common ground, flyback path, and coil current must be explicitly verified.

## Reproduction status

The PNG is the *original source screenshot*. `firmware/` and `scripts/` are newly written reference reconstructions, not original archived assets. There is no native Proteus project in this repository.
