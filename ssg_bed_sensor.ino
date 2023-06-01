#include "motion.h"
#include <SoftwareSerial.h>

Motion motion = Motion();
SoftwareSerial mySerial(10, 11);

bool is_insleep = false;

void setup() {
  motion.setDataPin(2);
  motion.setDuration(10000);

  Serial.begin(9600);
  mySerial.begin(9600);

  mySerial.write("AT");
}

void loop() {
  if (Serial.available()) {
    while (Serial.available()) {
      mySerial.write(Serial.read());
    }
  }

  if (mySerial.available()) {
    while (mySerial.available()) {
      Serial.write(mySerial.read());
    }
  }

  delay(100);

  motion.update();

  
  if (is_insleep != motion.isInSleep()) {
    // 값이 변할 때만 송신
    is_insleep = motion.isInSleep();
    if (motion.isInSleep()) {
      mySerial.print("INSLEEP=TRUE");
      Serial.println("[transmitted] insleep: true");
    } else {
      mySerial.print("INSLEEP=FALSE");
      Serial.println("[transmitted] insleep: false");
    }
  }

  if (motion.isMotion()) {
    Serial.println("[info] moving: true");
  } else {
    Serial.println("[info] moving: false");
  }

  delay(1000);
}