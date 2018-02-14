#include "ERainbow.h"

static void _rainbow(const CRGBSet &leds,
                     uint8_t initialhue,
                     uint8_t val) {
  CHSV hsv;
  hsv.hue = initialhue;
  hsv.val = val;
  hsv.sat = 240;
  for (auto &led : leds) {
    led += hsv;
    hsv.hue++;
  }
}

void ERainbow::update(LEDBand &band, unsigned long time) {
  uint8_t hue = uint8_t(255.0f * (float((time - start_time) % speed) / float(speed)));

  if (apply_to & 0x01)
    _rainbow(band.upperLeds(), hue, value);
  if (apply_to & 0x02)
    _rainbow(band.lowerLeds(), hue, value);
  if (apply_to == 0x04)
    _rainbow(band.allLeds(), hue, value);
}

void ERainbow::config(const ConfigWrapper &cfg) {
  speed = cfg.getOption(F("speed"), 10);
  apply_to = cfg.getOption(F("apply"), uint8_t(3));
  value = uint8_t(255.0f * cfg.getOption(F("coeff"), 1.0f));
  restart();
}

void ERainbow::restart() {
  start_time = millis();
}
