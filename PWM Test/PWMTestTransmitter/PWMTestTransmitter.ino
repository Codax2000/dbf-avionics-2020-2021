/**
 * Alex Knowlton
 * 11/16/2020
 * Program part 1 of 2 to test whether we need a ground wire or not.
 *
 * This program sends an alternating PWM signal of 2000 to 1000,
 * alternating every half second *
 */

#include <Servo.h>

Servo output;

void setup()
{
  output.attach(9);
}

void loop()
{
  output.writeMicroseconds(2000);
  delay(500);
  output.writeMicroseconds(1000);
  delay(500);
}
