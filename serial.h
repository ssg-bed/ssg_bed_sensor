#ifndef _SSG_BED_LIBRARY__SERIAL_H    // Put these two lines at the top of your file.
#define _SSG_BED_LIBRARY__SERIAL_H

#include <SoftwareSerial.h>


class SoftwareSerialBuilder {
private:
  unsigned char rx_pin;
  unsigned char tx_pin;
  unsigned long baud_rate;

public:
  SoftwareSerialBuilder *setRxPin(unsigned char value) {
    rx_pin = value;
    return this;
  }

  SoftwareSerialBuilder *setTxPin(unsigned char value) {
    tx_pin = value;
    return this;
  }

  SoftwareSerialBuilder *setBaudRate(unsigned long value) {
    baud_rate = value;
    return this;
  }

  SoftwareSerial *buildAndListen() {
    SoftwareSerial *ss = new SoftwareSerial(rx_pin, tx_pin);
    ss->begin(baud_rate);
    ss->listen();
    return ss;
  }
};


class SerialHandler {
private:
  SoftwareSerial *serial;

  char buffer[1024];
  unsigned int buffer_size = 1024;

public:
  SerialHandler(SoftwareSerial *s) {
    serial = s;
  }

  char *receive() {
    int i;
    if (!serial->available()) {
      i = 0;
      while (serial->available() && i < (buffer_size-1)) {
        buffer[i++] = serial->read();
      }
      buffer[i] = '\0';
    } else {
      buffer[0] = '\0';
    }
    return buffer;
  }

  void transmit(const char *msg) {
    serial->write(msg);
  }

  void transmit(const char c) {
    serial->write(c);
  }
};

#endif