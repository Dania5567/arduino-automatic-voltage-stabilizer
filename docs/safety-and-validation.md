# Electrical safety and validation plan

**This GitHub repository is for documentation, control-algorithm learning, and low-voltage isolated simulation. It is not a build-ready mains stabilizer.** Household AC can injure or kill. A photo of a Proteus circuit is insufficient to certify isolation, clearances, tap topology, or protective devices.

## Safer validation path

1. **Software only:** run reference-model tests and inspect example CSV. All output data are mathematical predictions, not real measurements.
2. **Proteus low-voltage controls:** recreate sensor data with an artificial 0–5 V DC waveform into A0 and indicator-only relay substitutes; confirm digital logic without mains.
3. **Calibration research:** select a **galvanically isolated** voltage transducer or isolated transformer sensing solution; determine true RMS transfer function and calibration using qualified equipment/personnel.
4. **Protection design review:** qualified engineer verifies power isolation, tap configurations, mutually exclusive contacts, relay voltage and current deratings, coil driver currents, snubbers, fusing, surge protection, enclosures, thermal management, earthing, and emergency disconnect.
5. **Only after formal review:** perform any energized testing using a properly rated isolated and current-limited laboratory setup with appropriate procedures.

## What cannot be concluded from the screenshot

No verified hardware output ripple, closed-loop accuracy, voltage correction span, efficiency, switching speed, component endurance, device service life, or real load test results are available. Do not list them as measured achievements.
