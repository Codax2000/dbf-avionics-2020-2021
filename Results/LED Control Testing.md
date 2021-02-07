# LED Control Testing

This test is to explore controlling high-wattage devices using relays and
MOSFETs. This includes 3 sketches:

1. Code a single MOSFET
2. Code a single relay
3. Wire 3 high-power LEDs in parallel, each with a relay

## Relay Test

Successful. Writing to a relay is simple, requiring only a call to
digitalWrite(), without a PWM signal.

## MOSFET Test

This was a helpful resource when learning how to wire the MOSFET:
[Controlling a DC motor with Arduino](https://enricosimonetti.com/control-a-motor-speed-with-arduino/)

The test wasn't successful, and we weren't able to control the low-power LED
using a MOSFET.

## High-power LED Test

Using three 3.3 Ohm resistors, a 9V battery, and a 10W LED, we were able to use
a relay to successfully control a high-power device using arduino.
