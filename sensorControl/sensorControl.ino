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

// Define output pins for using interrupt values
#define OUTPUT_GREEN 1
#define OUTPUT_ORANGE 2
#define OUTPUT_RED 3

// arrays for interrupt flags and timing
uint16_t rc_values[RC_NUM_CHANNELS];
uint32_t rc_start[RC_NUM_CHANNELS];
volatile uint16_t rc_shared[RC_NUM_CHANNELS];

// consider using an array of booleans, this is due to not knowing much in C++
boolean green_led;
boolean orange_led;
boolean red_led;

void setup() {

  // set interrupt pins to input mode
  pinMode(RC_INPUT, INPUT);

  // establish interrupts - connect input to a service routine that
  // will execute on a change in the specified pin
  enableInterrupt(RC_INPUT, calc_ch1, CHANGE);

  // attach servos and define output pins here if necessary
  pinMode(OUTPUT_GREEN, OUTPUT);
  pinMode(OUTPUT_RED, OUTPUT);
  pinMode(OUTPUT_ORANGE, OUTPUT);

  // initialize booleans to false
  green_led = false;
  orange_led = false;
  red_led = false;
}


void loop() {
  // read rc values
  rc_read_and_store_values();
  
  if (rc_values[0] > 1600) { // if PWM signal is high, run LEDs
    // run LED program
    uint32_t time = micros();
    int remainder = int(time / 1000000) % 3;
    if (remainder == 0) {
      if (!green_led) {
        digitalWrite(OUTPUT_GREEN, HIGH);
        digitalWrite(OUTPUT_RED, LOW);
        red_led = false;
        green_led = true;
      }
    } else if (remainder == 1) {
      if (!orange_led) {
        digitalWrite(OUTPUT_ORANGE, HIGH);
        digitalWrite(OUTPUT_GREEN, LOW);
        orange_led = true;
        green_led = false;
      }
    } else {
      if (!red_led) {
        digitalWrite(OUTPUT_RED, HIGH);
        digitalWrite(OUTPUT_ORANGE, LOW);
        orange_led = false;
        red_led = true;
      }
    }
  } else { // all leds off, booleans set to false
    digitalWrite(OUTPUT_GREEN, LOW);
    digitalWrite(OUTPUT_ORANGE, LOW);
    digitalWrite(OUTPUT_RED, LOW);
    green_led = false;
    orange_led = false;
    red_led = false;
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
