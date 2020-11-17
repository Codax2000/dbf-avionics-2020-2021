/* This program is for an ATtiny85. It receives one pwm signal and sends out a
 * constant pwm signal from one of three pins (used to toggle one of three leds 
 * in this case).
 * 
 * The odd constants part with *Port[] configures the ATtiny to send fast
 * pwm signals from output pins 0, 1, and 4. This is necessary because
 * only pins 0 and 1 are pwm-capable without this special config.
 * 
 * PWM config code from http://www.technoblogy.com/show?LE0
 * Interrupt code stolen from Alex's DBF 2019-20 code
 *
 *
 *  Pins for ATtiny85
 *   - Numbers in the box are the physical locations of
 *     the pins on the chip, NOT THE VALUES IN SOFTWARE
 *   - Labels outside the box are the pin names in software. Ex:
 *     pinMode(2, OUTPUT) sets Pin 2 (A1) as an output pin, NOT Pin 3
 *   
 *              ATtiny85
 *              --------
 *  Reset      | 1    8 | VCC (1.8-5.5V)
 *  Pin 3 (A3) | 2    7 | Pin 2 (A1)
 *  Pin 4 (A2) | 3    6 | Pin 1
 *  GND        | 4    5 | Pin 0
 *              --------
 */
 
#include <EnableInterrupt.h>

// PWM INPUT PIN
const uint8_t RC_IN = 2;

// INTERRUPT VARIABLES
uint32_t rc_start;
uint16_t rc_value; // microseconds

// returns signal N if { SIG_N-1 < X < SIG_N } where X is received pwm signal (us)
const int SIGNAL_1 = 700;
const int SIGNAL_2 = 1400;
const int SIGNAL_3 = 2000; // unnecessary, but nice to have

// ATtiny85 OUTPUT VARIABLES
const int Pin[] = {0, 1, 4}; // led 1, 2, 3
const int LED_1 = 0;
const int LED_2 = 2;
const int LED_3 = 1;
volatile uint8_t* Port[] = {&OCR0A, &OCR0B, &OCR1B}; // pwms

// tracks which led should turn on
uint8_t led;


void setup() {

  pinMode(RC_IN, INPUT);
  enableInterrupt(RC_IN, calc_input, CHANGE);

  // setup for led PWMs
  pinMode(Pin[LED_1], OUTPUT);
  pinMode(Pin[LED_2], OUTPUT);
  pinMode(Pin[LED_3], OUTPUT);
  // Configure counter/timer0 for fast PWM on PB0 and PB1
  TCCR0A = 3<<COM0A0 | 3<<COM0B0 | 3<<WGM00;
  TCCR0B = 0<<WGM02 | 3<<CS00; // Optional; already set
  // Configure counter/timer1 for fast PWM on PB4
  GTCCR = 1<<PWM1B | 3<<COM1B0;
  TCCR1 = 3<<COM1A0 | 7<<CS10;
  
}


const int INTENSITY = 128; // 0-255 value for how bright leds are
void loop() {
  for (int i = 0; i < 3; i++) {
    if (i == led) {        // turn on correct led
      pwmWrite(i, INTENSITY);
    } else {               // turn off all other leds
      pwmWrite(i, 0);
    }
  }
}


// Replaces analogWrite, but usage is the same
// intensity is 0-255; 255 is full brightness
void pwmWrite (int led, int intensity) {
  *Port[led] = 255 - intensity;
}


// generic Interrupt Service Routine - thank you Alex
// Tracks time starting from when signal rises to when it falls,
// then sets rc_value to that interval in microseconds and says
// which led to turn on
void calc_input() {
  if (digitalRead(RC_IN) == HIGH) {
    rc_start = micros();
  } else {
    uint16_t rc_compare = (uint16_t)(micros() - rc_start);
    rc_value = rc_compare;
    if (rc_value < 200 || rc_compare > 2200) { // no pwm signal
      led = -1; // all off
    } else if (rc_value < SIGNAL_1) {
      led = LED_1;
    } else if (rc_value < SIGNAL_2) {
      led = LED_2;
    } else { // rc_value < SIGNAL_3
      led = LED_3;
    }
  }
}
