#include "motion.h"
#include "serial.h"

Motion *motion;
SerialHandler *serial_handler;

void setup() {
  SoftwareSerialBuilder *builder;
  SoftwareSerial *serial;

  motion = new Motion();
  motion->setDataPin(2);
  motion->setDuration(10000);

  builder = new SoftwareSerialBuilder();
  builder->setRxPin(3);
  builder->setTxPin(4);
  builder->setBaudRate(9600);

  // serial = builder->buildAndListen();

  serial = new SoftwareSerial(3, 4);

  serial_handler = new SerialHandler(serial);

  Serial.begin(9600);
}

void loop() {
  motion->update();

  if (motion->isInSleep()) {
    serial_handler->transmit("INSLEEP=TRUE");
    Serial.println("[transmitted] insleep: true");
  } else {
    serial_handler->transmit("INSLEEP=FALSE");
    Serial.println("[transmitted] insleep: false");
  }

  if (motion->isMotion()) {
    Serial.println("[transmitted] moving: true");
  } else {
    Serial.println("[transmitted] moving: false");
  }

  delay(200);

  if (Serial.available()) {
    while (Serial.available()) {
      serial_handler->transmit(Serial.read());
    }
  }
}