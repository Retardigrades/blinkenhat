#pragma once
#include "Effect.h"

class EDot : public Effect {
public:
  EDot()
      : width(0), count(1), start_hue(0), apply_to(3), coeff(1.0f),
        start_time(0), duration(0) {}

  void update(LEDBand &band, unsigned long time) override;
  void restart() override { start_time = millis(); }
  void config(const ConfigWrapper &cfg) override;

private:
  unsigned int width;
  unsigned int count;
  uint8_t start_hue;
  uint8_t apply_to;
  float coeff;
  unsigned long start_time;
  unsigned int duration;
  unsigned int color_duration;
};
