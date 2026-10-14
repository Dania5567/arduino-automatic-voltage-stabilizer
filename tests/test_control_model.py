"""Tests of the conceptual tap selection model, not tests of real equipment."""
from pathlib import Path
import sys
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'scripts'))
from control_model import choose_tap, predicted_output

def test_nearest_rated_tap():
    for v in (150, 180, 210, 240, 270):
        assert choose_tap(v) == v

def test_out_of_bounds():
    assert choose_tap(100) is None
    assert choose_tap(330) is None

def test_unimplemented_300v_path():
    assert choose_tap(300) is None

def test_reference_prediction():
    assert predicted_output(240, 240) == 230

def test_hysteresis_avoids_switching_for_small_gain():
    assert choose_tap(194, current_tap=180) == 180

import unittest
class ControlModelTests(unittest.TestCase):
    def test_nearest(self): test_nearest_rated_tap()
    def test_out_of_bounds(self): test_out_of_bounds()
    def test_unimplemented(self): test_unimplemented_300v_path()
    def test_prediction(self): test_reference_prediction()
    def test_hysteresis(self): test_hysteresis_avoids_switching_for_small_gain()
