/**
 * Alex Knowlton
 * 2/12/2021
 * 
 * This file contains the code for the sensor microcontroller. It assumes one input
 * and three output pins, defined at the top of the file.
 */

#include <EnableInterrupt.h>

// These go together, for every extra input channel, there should be an input pin and an index
// The index is used in flagging which channels have changed in the arrays below
#define RC_NUM_CHANNELS 1
#define RC_CH1 0
#define RC_INPUT A0

// Define array of output pins for using interrupt values
const uint8_t ledPins[] = {1, 2, 3}; // output pin for led 1, 2, 3 respectively

// arrays for interrupt flags and timing
uint16_t rc_values[RC_NUM_CHANNELS];
uint32_t rc_start[RC_NUM_CHANNELS];
volatile uint16_t rc_shared[RC_NUM_CHANNELS];

// consider using an array of booleans, this is due to not knowing much in C++
uint8_t leds[3];

void setup() {

  // set interrupt pins to input mode
  pinMode(RC_INPUT, INPUT);

  // establish interrupts - connect input to a service routine that
  // will execute on a change in the specified pin
  enableInterrupt(RC_INPUT, calc_ch1, CHANGE);

  // attach servos and define output pins here if necessary
  for (int i = 0; i < 3; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  // initialize booleans to false
  for (int i = 0; i < 3; i++) {
    leds[i] = 0;
  }
}


void loop() {
  // read rc values
  rc_read_and_store_values();
  clearLeds(); // set all leds to 0
  if (rc_values[0] > 1600) { // if PWM signal is high, run LEDs
    // run LED program
    uint32_t time = micros();
    int remainder = int(time / 1000000) % 3;
    leds[remainder] = 1; // only set correct led to 1
  }

  lightUp(); // turn on all leds set to 1
}

// set all leds to false
void clearLeds() {
  for (int i = 0; i < 3; i++) {
    leds[i] = 0;
  }
}

// turn on all leds that are set to 1
void lightUp() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledPins[i], leds[i]); //digitalWrite LOW if led[i] == 0, else HIGH
  }
}


void rc_read_and_store_values() {
  noInterrupts();
  memcpy(rc_values, (const void *)rc_shared, sizeof(rc_shared));
  interrupts();
}


// Interrupt service routines go here
// these update the fields with times, shortened to a generic call so we don't have
// to deal with callbacks or anything weird
void calc_ch1() { calc_input(RC_CH1, RC_INPUT); }


// generic Interrupt Service Routine
void calc_input(uint8_t channel, uint8_t input_pin) {
  // if the input is high, start timing
  if (digitalRead(input_pin) == HIGH) {
    rc_start[channel] = micros();
  } else {
    // if it is low, record the time so we can use it as a PWM signal
    uint16_t rc_compare = (uint16_t)(micros() - rc_start[channel]);
    rc_shared[channel] = rc_compare;
  }
}
