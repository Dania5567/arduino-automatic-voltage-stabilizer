"""Generate illustrative data; NOT original lab or Proteus measurements."""
import csv
from pathlib import Path
from control_model import choose_tap, predicted_output
output = Path(__file__).resolve().parents[1] / 'assets' / 'illustrative-sweep.csv'
with output.open('w', newline='') as f:
    writer = csv.writer(f)
    writer.writerow(['input_voltage_v', 'selected_reference_tap_v', 'predicted_output_voltage_v', 'status'])
    for voltage in range(120, 331, 5):
        tap = choose_tap(voltage)
        writer.writerow([voltage, tap or '', round(predicted_output(voltage, tap), 2) if tap else '', 'REFERENCE_ONLY' if tap else 'NO_SUPPORTED_TAP'])
print(f'Wrote illustrative model: {output}')
