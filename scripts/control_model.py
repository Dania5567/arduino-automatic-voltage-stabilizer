"""Transparent reference maths for the reconstructed Arduino algorithm.

WARNING: tap labels and transfer model are assumptions, not measured results.
"""
from math import isfinite
TAPS = (150, 180, 210, 240, 270)
NOMINAL = 230.0

def predicted_output(input_voltage, tap_voltage):
    return input_voltage * NOMINAL / tap_voltage

def choose_tap(input_voltage, current_tap=None):
    if not isfinite(input_voltage) or not 140 <= input_voltage <= 285:
        return None
    best = min(TAPS, key=lambda tap: abs(predicted_output(input_voltage, tap) - NOMINAL))
    best_error = abs(predicted_output(input_voltage, best) - NOMINAL)
    if best_error > 35:
        return None
    if current_tap in TAPS and current_tap != best:
        current_error = abs(predicted_output(input_voltage, current_tap) - NOMINAL)
        if current_error - best_error < 6:
            return current_tap
    return best
