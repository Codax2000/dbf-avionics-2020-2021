/**
 * Alex Knowlton
 * 11/17/2020
 *
 * This is the code for a simple MOSFET circuit. See LED Control Testing.md
 * for link to circuit diagram. Turns an LED on and off every half second.
 *
 * Note: LED pin must have ~PWM next to it on the board
 */

int LED_PIN = A3;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
}

void loop()
{
  analogWrite(LED_PIN, 255);
  delay(500);
  analogWrite(LED_PIN, 0);
  delay(500);
}