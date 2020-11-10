# dbf-avionics-2020-2021
Repo for the Arduino code for the plane this year. This will be primarily focused on the sensor, again running based on interrupts. Control 3 relays using 1 board and 1 signal wire. Written in C++ for Arduino

## Style Guide
Some things to keep in mind when writing code:
 - Factor out as much as possible into functions to avoid redundancy.
 - Use camelCase for your variables and functions.
 - Use SCREAMING_CASE for variables.
 - If you can, make your naming and your code readable without comments. Comments aren't taboo, but they should only be necessary as a last resource (every time you have to explain your code, you've failed to make it readable enough). Exceptions include: function comments, pseudocode, and commenting blocks of variables.

## Approach
We are trying to take in 1 signal and based on that signal, decide which of three LED's should be turned on via relay. We are using Arduino (so C++), and may move to an Attiny85 if we can to save weight.
All necessary libraries will be uploaded in this repo.

*Let's do this!*
