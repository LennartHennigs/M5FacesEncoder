/////////////////////////////////////////////////////////////////

#include "M5Stack.h"
#include "M5FacesEncoder.h"

/////////////////////////////////////////////////////////////////

// sets range from -20 to 20, starting point to 10, and 2 steps per turn
M5FacesEncoder encoder;

/////////////////////////////////////////////////////////////////

void setup() {
  M5.begin(true, false, true);
  M5.Power.begin();
  M5.Speaker.mute();

  Serial.begin(9600);
  while(!Serial) {
    delay(20);
  }
  Serial.println("");
  Serial.println("");
  Serial.println("Rotary Encoder Test");

  M5.Lcd.begin();
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.clear();
  M5.Lcd.print("Rotary Encoder Test");

  showLedAnimation();

  if (encoder.begin(-20, 20, 10, 2)) {
    encoder.setPressedHandler(pressed);
    encoder.setClickHandler(click);
    encoder.setReleasedHandler(released);

    encoder.setChangedHandler(rotate);
    encoder.setLeftRotationHandler(showDirection);
    encoder.setRightRotationHandler(showDirection);
    encoder.setUpperOverflowHandler(theEnd);
    encoder.setLowerOverflowHandler(theEnd);
  } else {
    M5.Lcd.println("");
    M5.Lcd.println("");
    M5.Lcd.println("no encoder found");
  }
}

void loop() {
  encoder.loop();
  dacWrite(25, 0);
}

/////////////////////////////////////////////////////////////////

void showLedAnimation() {
for (int i=0; i < 12; i++) {
    encoder.setLed(i, 0x00ff00);
    delay(20);
  }
  for (int i=12; i >= 0; i--) {
    encoder.setLed(i, 0);
    delay(20);
  }

}

/////////////////////////////////////////////////////////////////

void rotate(M5FacesEncoder& e) {
  M5.Lcd.setCursor(0, 60);
  M5.Lcd.fillRect(0, 60, 320, 20, 0);
  M5.Lcd.print("position: ");
  M5.Lcd.print(e.getPosition());
}

/////////////////////////////////////////////////////////////////

void click(M5FacesEncoder& e) {
  M5.Lcd.fillRect(0, 80, 320, 20, 0);
  M5.Lcd.setCursor(0, 80);
  M5.Lcd.print("clicked: ");
  M5.Lcd.print(e.wasPressedFor());
  M5.Lcd.print(" ms");
}

/////////////////////////////////////////////////////////////////

void pressed(M5FacesEncoder& e) {
  M5.Lcd.setCursor(0, 100);
  M5.Lcd.println("pressed");
}

/////////////////////////////////////////////////////////////////

void released(M5FacesEncoder& e) {
  M5.Lcd.fillRect(0, 100, 320, 20, 0);
}

/////////////////////////////////////////////////////////////////

void theEnd(M5FacesEncoder& e) {
  M5.Lcd.fillRect(0, 100, 320, 20, 0);
  M5.Lcd.setCursor(0, 100);
  M5.Lcd.println("end reached");
  delay(100);
  M5.Lcd.fillRect(0, 100, 320, 20, 0);
}

/////////////////////////////////////////////////////////////////

// on left or right rotation
void showDirection(M5FacesEncoder& e) {
  M5.Lcd.setCursor(0, 40);
  M5.Lcd.print(e.directionToString(e.getDirection()));
  delay(100);
  M5.Lcd.fillRect(0, 40, 320, 20, 0);
}

/////////////////////////////////////////////////////////////////