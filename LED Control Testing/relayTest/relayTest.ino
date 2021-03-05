/**
 * Alex Knowlton
 * 11/17/2020
 *
 * This sketch is a test for a simple relay setup. The relay is wired like
 * normal for any arduino PWM device.
 */

int RELAY = 2;

void setup()
{
  pinMode(RELAY, OUTPUT);
}

void loop()
{
  digitalWrite(RELAY, HIGH);
  delay(500);
  digitalWrite(RELAY, LOW);
  delay(500);
}
