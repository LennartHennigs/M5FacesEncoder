/////////////////////////////////////////////////////////////////
/*
  Arduino Library for reading encoder values from the M5Stack Facees.
  Copyright 2020 Lennart Hennigs
*/
/////////////////////////////////////////////////////////////////
#pragma once

#ifndef M5FacesEncoder_h
#define M5FacesEncoder_h

/////////////////////////////////////////////////////////////////

#include <Arduino.h>
#include <Wire.h>

/////////////////////////////////////////////////////////////////

#define ENCODER_RIGHT       1
#define ENCODER_LEFT        255

#define PRESSED             0
#define NOT_PRESSED         1
#define ENCODER_I2C_ADDR    0x5e

/////////////////////////////////////////////////////////////////


class M5FacesEncoder {
 protected:
    bool encoder_found = false;
    int position, last_position, lower_bound, upper_bound;
    byte direction;
    byte state;
    byte prev_state;
    int steps_per_click = 1;
    bool pressed_triggered = false;
    unsigned long down_time_ms = 0;
    unsigned long down_ms = 0;
    unsigned long debounce_time_ms = 50;

    typedef void (*CallbackFunction) (M5FacesEncoder&);
    
    CallbackFunction change_cb = NULL;
    CallbackFunction right_cb = NULL;
    CallbackFunction left_cb = NULL;
    CallbackFunction lower_cb = NULL;
    CallbackFunction upper_cb = NULL;

    CallbackFunction pressed_cb = NULL;
    CallbackFunction released_cb = NULL;
    CallbackFunction click_cb = NULL;

  public:
    M5FacesEncoder(int lower_bound = INT16_MIN , int upper_bound = INT16_MAX , int inital_pos = 0, int steps_per_click = 1);

    void setStepsPerClick(int steps);
    int getStepsPerClick() const;
    int getPosition() const;
    void setPosition(int p = 0, bool fireCallback = true);
    byte getDirection() const;
    String directionToString(byte direction) const;
    bool isPressed() const;
    unsigned long wasPressedFor() const;

    void setChangedHandler(CallbackFunction f);
    void setRightRotationHandler(CallbackFunction f);
    void setLeftRotationHandler(CallbackFunction f);
    void setUpperOverflowHandler(CallbackFunction f);
    void setLowerOverflowHandler(CallbackFunction f);

    void setClickHandler(CallbackFunction f);
    void setPressedHandler(CallbackFunction f);
    void setReleasedHandler(CallbackFunction f);

    void setLed(int i, String rgb);
    void setLed(int i, long rgb);
    void setLed(int i, byte r, byte g, byte b);

    void loop();
};
/////////////////////////////////////////////////////////////////
#endif
///////////////////////////////////////////////////////////////// 