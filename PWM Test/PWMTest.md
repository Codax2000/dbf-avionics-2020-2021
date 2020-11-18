# PWM Wiring Test

The purpose of this test was to see whether we could send signals to the
sensor using only 1 signal wire and no ground wire.

## Methodology

This was done using 2 Arduino uno boards, one sending an alternating PWM
signal and one reading it and alternating an LED between on and off based
on that signal. Everything between the boards was isolated except for 1
signal wire.

## Results

The test was successful. The LED alternated between on and off, although PWM
reading accuracy was inconclusive. This shouldn't matter to the eventual result,
since we only have to distinguish between 2 signals and control the LEDs based
on that 1 signal.
