M5StackFaces
============

* Author: Lennart Hennigs (https://www.lennarthennigs.de)
* Copyright (C) 2020 Lennart Hennigs.
* Released under the MIT license.


Description
-----------

This class is for the M5Stack Faces [Encoder Module](https://m5stack.com/products/encoder-module). 
It allows you to detect encoder interactions (clicks and rotation) and control the built-in LEDs.

- It offers callback functions for handling the encoder events.
- You can define a number-range for the encoder and a starting value.
- You can also define the "speed" of the encoder by setting the steps-per-click.
- Since the encode module has a led ring with 12 leds, the class also offer a function to set the color for each.

- **Note:** For the class to work, you need to call the `loop()` member function in your sketch's `loop()` function. See the example for more details.
- **Note:** The firmware of the Encode Module triggers the leds on each detected click. This is something which this library cannot disable/fix.


How to Use
----------

These are the constructor and the member functions the library provides:


```
M5FacesEncoder (int lower_bound = INT16_MIN , int upper_bound = INT16_MAX , int inital_pos = 0, int steps_per_click = 1);

void setStepsPerClick (int steps);
int getStepsPerClick() const;

int getPosition() const;
void setPosition (int p = 0, bool fireCallback = true);

byte getDirection() const;
String directionToString( byte direction) const;

bool isPressed() const;
unsigned long wasPressedFor() const;

void setChangedHandler (CallbackFunction f);
void setRightRotationHandler (CallbackFunction f);
void setLeftRotationHandler (CallbackFunction f);
void setUpperOverflowHandler (CallbackFunction f);
void setLowerOverflowHandler (CallbackFunction f);

void setClickHandler (CallbackFunction f);
void setPressedHandler (CallbackFunction f);
void setReleasedHandler (CallbackFunction f);

void setLed(int i, long rgb);
void setLed(int i, byte r, byte g, byte b);

void loop();
``` 
    

Installation
------------
Open the Arduino IDE choose "Sketch > Include Library" and search for "Button2". 
Or download the ZIP archive (https://github.com/lennarthennigs/Button2/zipball/master), and choose "Sketch > Include Library > Add .ZIP Library..." and select the downloaded file.


License
-------

MIT License

Copyright (c) 2020 Lennart Hennigs

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
