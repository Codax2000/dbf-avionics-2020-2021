/**
 * Alex Knowlton
 * 11/16/2020
 * Program 2 of 2 to test signal processing - do we need a ground
 * wire with the signal?
 * 
 * This program reads input sent from the source and controls an LED
 * based on that input
 */

int INPUT_PIN = 8;
int LED_PIN = 9;
int CUTOFF = 1500;

int reading;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(INPUT_PIN, INPUT);
  Serial.begin(9600);
}

void loop()
{
  // don't use this reading method in production, used here for convenience
  reading = pulseIn(INPUT_PIN, HIGH);
  if (reading < CUTOFF || reading > 3000)
  {
    digitalWrite(LED_PIN, LOW);
  }
  else
  {
    digitalWrite(LED_PIN, HIGH);
  }
  Serial.println(reading);
}
