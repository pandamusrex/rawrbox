# RAWRBOX

RAWRBOX is a Teensy 4.1 based four track MIDI controller for live performance. Rawr.

## Setup

You'll need

- the Arduino IDE
- the Teensy Loader https://www.pjrc.com/teensy/loader.html

- In the Arduino IDE, click File > Preferences. In "Additional boards manager URLs", paste this URL

https://www.pjrc.com/teensy/package_teensy_index.json

- In the main Arduino IDE window, open the Boards Manager by clicking the left-side board icon, search for "teensy", and click "Install".

## Hardware

- Teensy 4.1 600 MHz Cortex-M7 Microcontroller
- SparkFun COM-28380: https://www.sparkfun.com/color-320x240-touchscreen-3-2-inch-ili9341-controller.html

## Libraries

- https://github.com/PaulStoffregen/ILI9341_t3
- https://github.com/PaulStoffregen/XPT2046_Touchscreen
