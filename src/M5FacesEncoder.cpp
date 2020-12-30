/////////////////////////////////////////////////////////////////

#include "M5FacesEncoder.h"

/////////////////////////////////////////////////////////////////
M5FacesEncoder::M5FacesEncoder() {
  
}
/////////////////////////////////////////////////////////////////

bool M5FacesEncoder::begin(int lower_bound /* = INT16_MIN */, int upper_bound /* = INT16_MAX */, int inital_pos /* = 0 */, int steps_per_click /* = 1 */) {
  if(isPresent()) {
    this->lower_bound = (lower_bound < upper_bound) ? lower_bound : upper_bound;
    this->upper_bound = (lower_bound < upper_bound) ? upper_bound: lower_bound;
    setStepsPerClick(steps_per_click);
    loop();
    setPosition(inital_pos, false);
    return true;
  } else {
    return false;
  }
}

/////////////////////////////////////////////////////////////////

bool M5FacesEncoder::isPresent() {
  Wire.begin();
  Wire.beginTransmission(ENCODER_I2C_ADDR);
  is_present = (Wire.endTransmission() == 0);
  return is_present;
}

/////////////////////////////////////////////////////////////////

void M5FacesEncoder::setClickHandler(CallbackFunction f) {
  click_cb = f;
}

/////////////////////////////////////////////////////////////////

void M5FacesEncoder::setPressedHandler(CallbackFunction f) {
  pressed_cb = f; 
}

/////////////////////////////////////////////////////////////////

void M5FacesEncoder::setReleasedHandler(CallbackFunction f) {
  released_cb = f; 
}

/////////////////////////////////////////////////////////////////

void M5FacesEncoder::setChangedHandler(CallbackFunction f) {
  change_cb = f;
}

/////////////////////////////////////////////////////////////////

void M5FacesEncoder::setRightRotationHandler(CallbackFunction f) {
  right_cb = f;
}

/////////////////////////////////////////////////////////////////

void M5FacesEncoder::setLeftRotationHandler(CallbackFunction f) {
  left_cb = f;
}

/////////////////////////////////////////////////////////////////

void M5FacesEncoder::setUpperOverflowHandler(CallbackFunction f) {
  upper_cb = f;
}

/////////////////////////////////////////////////////////////////

void M5FacesEncoder::setLowerOverflowHandler(CallbackFunction f) {
  lower_cb = f;
}

/////////////////////////////////////////////////////////////////

void M5FacesEncoder::setStepsPerClick(int steps) {
  steps_per_click = (steps < 1) ? 1 : steps;
}

/////////////////////////////////////////////////////////////////

int M5FacesEncoder::getStepsPerClick() const {
  return steps_per_click;
}


/////////////////////////////////////////////////////////////////

void M5FacesEncoder::setPosition(int p /* = 0 */, bool fireCallback /* = true */) {
  if (p > upper_bound) {
    last_position = upper_bound /* * steps_per_click */;
  } else {
    last_position = ((lower_bound > p) ? lower_bound : p) /* * steps_per_click */;
  }

  if (position != last_position) {
    position = last_position;
    if (fireCallback && change_cb != NULL) change_cb (*this);
  }
  direction = 0;
}

/////////////////////////////////////////////////////////////////

byte M5FacesEncoder::getDirection() const {
  return direction;
}

/////////////////////////////////////////////////////////////////

String M5FacesEncoder::directionToString(byte direction) const {
  if (direction == ENCODER_LEFT) {
    return "LEFT";
  } else {
    return "RIGHT";
  }
}

/////////////////////////////////////////////////////////////////

int M5FacesEncoder::getPosition() const {
  return position;
}

/////////////////////////////////////////////////////////////////

boolean M5FacesEncoder::isPressed() const {
  return (state != 0);
}

/////////////////////////////////////////////////////////////////

unsigned long M5FacesEncoder::wasPressedFor() const {
  return down_time_ms;
}

/////////////////////////////////////////////////////////////////

void M5FacesEncoder::loop() {
  if (is_present) {
    Wire.requestFrom(ENCODER_I2C_ADDR, 3);
    if (Wire.available()) {   
       
      // get rotary value
      int increment = Wire.read(); 
      position += ((increment > 127) ? (256 - increment) * -1 : increment) * steps_per_click;
    }

    if (position >= lower_bound && position <= upper_bound) {
      if (position != last_position) {
        if (position > last_position) {
          direction = ENCODER_RIGHT;
          if (right_cb != NULL) right_cb (*this);
        } else {
          direction = ENCODER_LEFT;
          if (left_cb != NULL) left_cb (*this);
        }
        if (change_cb != NULL) change_cb (*this);
        last_position = position;
      }
    } else {
        if (position < lower_bound && lower_cb != NULL) lower_cb (*this);
        if (position > upper_bound && upper_cb != NULL) upper_cb (*this);
        position = last_position;
      }
      
      // read button state
      prev_state = state;
      state = Wire.read();
      unsigned long now = millis();
      // is button pressed?  
      if (state == PRESSED) {
        if (prev_state == NOT_PRESSED) {
          down_time_ms = 0;
          down_ms = now;
          pressed_triggered = false;
        } else if (!pressed_triggered && (now > down_ms + debounce_time_ms)) {
          pressed_triggered = true;
          if (pressed_cb != NULL) pressed_cb (*this);
        }
      // is the button released?
      } else if (state == NOT_PRESSED && prev_state == PRESSED && pressed_triggered) {
        pressed_triggered = false;
        down_time_ms = now - down_ms;

        // is it beyond debounce time?
        if (down_time_ms >= debounce_time_ms) {
          if (released_cb != NULL) released_cb (*this);
          if (click_cb != NULL) click_cb (*this);
      } 
    }
  }
}

/////////////////////////////////////////////////////////////////

void M5FacesEncoder::setLed(int i, long rgb) {
  byte r=(byte)(rgb>>16);
  byte g=(byte)(rgb>>8);
  byte b=(byte)(rgb);
  setLed(i, r, g, b);
}

/////////////////////////////////////////////////////////////////

void M5FacesEncoder::setLed(int i, byte r, byte g, byte b) {
    Wire.beginTransmission(ENCODER_I2C_ADDR);
    Wire.write(i);
    Wire.write(r);
    Wire.write(g);
    Wire.write(b);
    Wire.endTransmission();
}

/////////////////////////////////////////////////////////////////
