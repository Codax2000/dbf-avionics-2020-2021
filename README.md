# dbf-avionics-2020-2021

Repo for the Arduino code for the plane this year. This will be primarily focused on the sensor, again running based on interrupts. Control 3 relays using 1 board and 1 signal wire. Written in C++ for Arduino

## Approach

We are trying to take in 1 signal and based on that signal, decide which of three LED's should be turned on via relay or mosfet. We are using Arduino (so C++), and may move to an Attiny85 if we can to save weight. There is not a copy of the EnableInterrupt library here, since it isn't ours, but it can be downloaded from [GreyGnome's Github page](https://github.com/GreyGnome/EnableInterrupt). There is also a generic interrupt-driven piece of code here. Most of it is boilerplate and can be copied and pasted. Unfortunately, this makes large blocks of code that seem redundant, so it's not ideal. We may resort to making an encapsulating object in the future, but this will do for now, since it will not need to be scaled dramatically.

_Let's do this!_

## Style Guide

Some things to keep in mind when writing code that might make it more readable:

- Factor out as much as possible into functions to avoid redundancy.
- Use `camelCase` for your variables and functions.
- Use `SCREAMING_CASE` for global constants.
- If you can, make your naming and your code readable without comments. Comments aren't taboo, but they should only be necessary as a last resource (every time you have to explain your code, you've failed to make it readable enough). Exceptions include: function comments, pseudocode, and commenting blocks of variables.
- keep lines of code under 80 characters if possible.
- keep 2 spaces between functions, 1 space between blocks of variables.

We will be using GitHub this year for version control and collaboration. Commit to the development branch, not to the main one, and please document what you do before committing changes.

## Results Folder

Keep track of your testing in the results folder. For every piece of code you write, especially for proof-of-concept code or wiring testing,
write a new `.md` or `.txt` file summarizing what you found. Also, drop any pictures or videos you took into a folder with the code you write, if you
can. If you're not sure what markdown is, it's great and easy to learn! It's just a way of marking text so that it shows up
with specific formatting. If you don't know, just write a text file, that's fine.
