#define OUTPUT_ENABLE 3
#define LATCH_ENABLE 2
#define SR_CLOCK 1
#define SR_DATA 0

byte brightness = 100;

void updateShiftRegister(byte value) {
  digitalWrite(LATCH_ENABLE, LOW);
  digitalWrite(OUTPUT_ENABLE, HIGH);
  shiftOut(SR_DATA, SR_CLOCK, MSBFIRST, value);
  digitalWrite(LATCH_ENABLE, HIGH);
  analogWrite(OUTPUT_ENABLE, brightness);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(OUTPUT_ENABLE, OUTPUT);
  pinMode(LATCH_ENABLE, OUTPUT);
  pinMode(SR_CLOCK, OUTPUT);
  pinMode(SR_DATA, OUTPUT);
  digitalWrite(SR_CLOCK, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  /*
  for (int i = 0; i < 8; i++) {
    byte value = 1 << i;
    updateShiftRegister(value);
    delay(100);
  }
  for (int i = 7; i >= 0; i--) {
    byte value = 1 << i;
    updateShiftRegister(value);
    delay(100);
  }
  */
  byte value = random(255);
  updateShiftRegister(value);
  delay(100);
}
