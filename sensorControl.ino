/**
 * Alex Knowlton et. al
 * 11/9/2020
 * DBF 2020-2021
 * Main code for sensor board. Used to control 3 LEDs and read 1 PWM input line.
 */

// import libraries
// variable for interrupt data
// variables for servos/relays

void setup()
{
  // set output pins
  // set input pins

  // establish interrupt

  // attach servos/relays
}

void loop()
{
  rc_read_values();

  signal = (int)(rc_input[0]);

  // logic to decide which pin to output on based on PWM signal
}