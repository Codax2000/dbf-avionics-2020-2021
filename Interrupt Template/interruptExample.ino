/**
 * Alex Knowlton
 * 2/6/2021
 * This file contains a template for using the enableInterrupt library with
 * arduino to read a PWM signal. This is an asynchronous approach that emphasizes speed with a
 * small loss in precision. This assumes that the input pin can read PWM,
 * which is standard on most Arduino boards.
 */

#include <EnableInterrupt.h>

// These go together, for every extra input channel, there should be an input pin and an index
// The index is used in flagging which channels have changed in the arrays below
#define RC_NUM_CHANNELS  1
#define RC_CH1  0
#define RC_INPUT A0

// Define output pins for using interrupt values
#define OUTPUT_1 = 1

// arrays for interrupt flags and timing
uint16_t rc_values[RC_NUM_CHANNELS];
uint32_t rc_start[RC_NUM_CHANNELS];
volatile uint16_t rc_shared[RC_NUM_CHANNELS];

// parameter for time management of airspeed reading
int mod_count = 0;


// runs once when Arduino is turned on
void setup() {

  // set interrupt pins to input mode
  pinMode(RC_INPUT, INPUT);

  // establish interrupts - connect input to a service routine that
  // will execute on a change in the specified pin
  enableInterrupt(RC_INPUT, calc_ch1, CHANGE);

  // attach servos and define output pins here if necessary
  pinMode(OUTPUT_1, OUTPUT);

}


void loop() {
  // read rc values
  rc_read_and_store_values();
  
  // access pwm inputs using rc_values, which stores the PWM timing of each channel
  // for example, here is a call that will turn the output to high if the deflection
  // of the input is over 1700 microseconds

}


void rc_read_and_store_values() {
  noInterrupts();
  memcpy(rc_values, (const void *)rc_shared, sizeof(rc_shared));
  interrupts();
}


// Interrupt service routines go here
// these update the fields with times, shortened to a generic call so we don't have
// to deal with callbacks or anything weird
void calc_ch1() { calc_input(RC_CH1, RC_CH1_INPUT); }


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