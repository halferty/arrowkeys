#include <Keyboard.h>
// Put arduino pins in an array for easy reordering
int keyPins[] = {
  10, 9, 8, 7, 6, 5, 4, 3, 2
};
// Keycodes that will be emitted over USB when the button on this pin (by index in keyPins above) is pressed
char keyCodes[] = {
  KEY_LEFT_ARROW, KEY_DOWN_ARROW, KEY_RIGHT_ARROW, 0, KEY_UP_ARROW, KEY_PAGE_DOWN, 0, KEY_PAGE_UP, 0
};
// Current key values
int pinValues[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0
};
// Key value before current loop iteration
int prevPinValues[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0
};
// Keep track of how many loop iterations have passed since a key was pressed, to add debouncing
int pinChangeTimers[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0
};
// Debounce amount
int PIN_CHANGE_COOLDOWN = 50;

void setup() {
  for (int i = 0; i < 9; i++) {
    pinMode(keyPins[i], INPUT_PULLUP);
  }
  Keyboard.begin();
}
void loop() {
  for (int i = 0; i < 9; i++) {
    prevPinValues[i] = pinValues[i];
    pinValues[i] = !digitalRead(keyPins[i]);
    if (pinChangeTimers[i] > PIN_CHANGE_COOLDOWN) {
      pinChangeTimers[i] = -1;
    } else if (pinChangeTimers[i] != -1) {
      pinChangeTimers[i]++;
    }
    if (pinChangeTimers[i] == -1 && pinValues[i] != prevPinValues[i]) {
      if (pinValues[i]) {
        // Pin went down
        Keyboard.press(keyCodes[i]);
        pinChangeTimers[i] = 0;
      } else {
        // Pin went up
        Keyboard.release(keyCodes[i]);
        pinChangeTimers[i] = 0;
      }
    }
  }
}
