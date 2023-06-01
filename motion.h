#ifndef _SSG_BED_LIBRARY__MOTION_H    // Put these two lines at the top of your file.
#define _SSG_BED_LIBRARY__MOTION_H

class Motion {
private:
  unsigned long now;

  bool is_motion = false;
  bool is_insleep = false;

  unsigned long motion_started_at = 0;
  unsigned long motion_continued_at = 0;

  unsigned char data_pin = 0;
  unsigned long duration_factor_ms = 0;

  bool isMotionContinuable() {
    return (motion_continued_at + duration_factor_ms) >= now;
  }

  void handleMotionStart() {
    if (is_motion && !isMotionContinuable()) {
      motion_started_at = now;
      motion_continued_at = now;
    }
  }

  bool isIgnorable() {
    return (now - motion_started_at)  < duration_factor_ms;
  }

  void handleMotionContinue() {
    if (is_motion && isMotionContinuable()) {
      motion_continued_at = now;
      is_insleep = isIgnorable();
    }
  }

  void handleMotionEnd() {
    if (!is_motion && !isMotionContinuable()) {
      is_insleep = true;
    }
  }

public:
  void setDuration(unsigned long ms) {
    duration_factor_ms = ms;
  }

  void setDataPin(unsigned char pin) {
    data_pin = pin;
    pinMode(pin, INPUT);
  }

  void update() {
    now = millis();
    is_motion = digitalRead(data_pin);

    handleMotionStart();
    handleMotionContinue();
    handleMotionEnd();
  }

  bool isMotion() {
    return is_motion;
  }

  bool isInSleep() {
    return is_insleep;
  }
};

#endif