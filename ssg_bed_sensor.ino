#include <Wire.h>
#include <SoftwareSerial.h>

#include "motion.h"

#define PIN_LED 4
#define PIN_PIR 5
#define WIRE_ADDR 8

Motion motion = Motion();

void setup() {
  motion.setDataPin(PIN_PIR);
  motion.setDuration(10000);

  Wire.begin();
  Serial.begin(9600);

  pinMode(PIN_LED, OUTPUT);
}


void loop() {
  motion.update();

  Wire.beginTransmission(WIRE_ADDR);
  Wire.write("INSLEEP=");
  Wire.write(motion.isInSleep() ? "TRUE" : "FALSE");
  Wire.endTransmission();

  digitalWrite(PIN_LED, motion.isMotion());

  Serial.print("Motion:");
  Serial.print(motion.isMotion());
  Serial.print(" Sleep:");
  Serial.println(motion.isInSleep());

  delay(1000);
}