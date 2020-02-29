/*
 * teensyMediaKeys firmware
 * This code is primarily based off of the Teensyduino
 * MediaButtons example code. 
 * All connected buttons are active low so we can use 
 * the built in pullup resistors in the TeensyLC. This 
 * also reduces the part count.
 */

// For easy key press detection
#include <Bounce.h>

// button definitions
#define PLAY_PIN 23
#define FORWARD_PIN 19
#define BACK_PIN 20
#define VOL_UP_PIN 21
#define VOL_DOWN_PIN 18

#define GENERAL_PIN 22

// Shift register definitions
#define OUTPUT_ENABLE 3
#define LATCH_ENABLE 2
#define SR_CLOCK 1
#define SR_DATA 0

// Create bounce objects for each of the buttons
Bounce playButton = Bounce(PLAY_PIN, 10); // 10 ms debounce time
Bounce forwardButton = Bounce(FORWARD_PIN, 10); // 10 ms debounce time
Bounce backButton = Bounce(BACK_PIN, 10); // 10 ms debounce time
Bounce volUpButton = Bounce(VOL_UP_PIN, 10); // 10 ms debounce time
Bounce volDownButton = Bounce(VOL_DOWN_PIN, 10); // 10 ms debounce time

Bounce generalButton = Bounce(GENERAL_PIN, 10);

// brightness of the LEDs
byte brightness = 240;
const byte BRIGHTNESS_STEP = 40;

void setup() {
  // set the button pins as input with a pullup 
  pinMode(PLAY_PIN, INPUT_PULLUP);
  pinMode(FORWARD_PIN, INPUT_PULLUP);
  pinMode(BACK_PIN, INPUT_PULLUP);
  pinMode(VOL_UP_PIN, INPUT_PULLUP);
  pinMode(VOL_DOWN_PIN, INPUT_PULLUP);
  pinMode(GENERAL_PIN, INPUT_PULLUP);

  // set the shift register pins as outputs
  pinMode(OUTPUT_ENABLE, OUTPUT);
  pinMode(LATCH_ENABLE, OUTPUT);
  pinMode(SR_CLOCK, OUTPUT);
  pinMode(SR_DATA, OUTPUT);
  digitalWrite(SR_CLOCK, LOW);
  updateShiftRegister(63);
} //setup()

void loop() {
  // check the status of the buttons
  playButton.update();
  forwardButton.update();
  backButton.update();
  volUpButton.update();
  volDownButton.update();
  generalButton.update();
  
  // check for the falling edge, the represents the key down event since the buttons are active low
  if (playButton.fallingEdge()) {
    Keyboard.press(KEY_MEDIA_PLAY_PAUSE);
    Keyboard.release(KEY_MEDIA_PLAY_PAUSE);
  }

  if (forwardButton.fallingEdge()) {
    Keyboard.press(KEY_MEDIA_NEXT_TRACK);
    Keyboard.release(KEY_MEDIA_NEXT_TRACK);
  }

  if (backButton.fallingEdge()) {
    Keyboard.press(KEY_MEDIA_PREV_TRACK);
    Keyboard.release(KEY_MEDIA_PREV_TRACK);
  }

  if (volUpButton.fallingEdge()) {
    Keyboard.press(KEY_MEDIA_VOLUME_INC);
    Keyboard.release(KEY_MEDIA_VOLUME_INC);
  }

  if (volDownButton.fallingEdge()) {
    Keyboard.press(KEY_MEDIA_VOLUME_DEC);
    Keyboard.release(KEY_MEDIA_VOLUME_DEC);
  }

  if (generalButton.fallingEdge()) {
    if (brightness > (0 + BRIGHTNESS_STEP)) {
      brightness -= BRIGHTNESS_STEP;
    } else {
      brightness = 240;
    }
    updateShiftRegister(63);
  }

} // loop()

void updateShiftRegister(byte value) {
  digitalWrite(LATCH_ENABLE, LOW);
  digitalWrite(OUTPUT_ENABLE, HIGH);
  shiftOut(SR_DATA, SR_CLOCK, MSBFIRST, value);
  digitalWrite(LATCH_ENABLE, HIGH);
  analogWrite(OUTPUT_ENABLE, brightness);
}
