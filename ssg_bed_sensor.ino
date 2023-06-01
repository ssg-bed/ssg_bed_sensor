#include "motion.h"

Motion motion = Motion();

void setup() {
  Serial.begin(9600);

  motion.setDataPin(2);
  motion.setDuration(10000);

  // LED Settings
  pinMode(3, OUTPUT);
  pinMode(8, OUTPUT);
}

void loop() {
  motion.update();

  digitalWrite(3, !motion.isInSleep());
  digitalWrite(8, motion.isMotion());
}