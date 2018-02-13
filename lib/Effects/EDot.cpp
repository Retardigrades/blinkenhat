#include "EDot.h"

void EDot::update(LEDBand &band, unsigned long time) {
  int max = band.getLEDCount()/2;

  unsigned int dot_offset = max/count;
  uint8_t hue = start_hue;
  float hue_coeff = 0.0f;

  if (0.0f < color_duration) {
    hue = uint8_t(255.0f*float((time - start_time)%color_duration)/color_duration);
    hue_coeff = float(duration)/float(color_duration)*(255.0f/float(max));
  }

  unsigned int elapsed = (time - start_time)%duration;
  float center = (float(elapsed*max)/float(duration)) + float(max);
  int head = int(ceilf(center));
  int tail = int(floorf(center)) - width;

  unsigned int pos;
  unsigned int off = 0;
  do {
    pos = (tail + off++);
    float center_distance = fabsf(center - pos);

    float local_coeff = (pos==head
                         ? 1.0f - center_distance
                         : 1.0f - fminf(1.0f, center_distance/float(width)));
    unsigned int actual_hue = (pos==head ? hue : hue - uint8_t(hue_coeff*center_distance));
    uint8_t brightness = uint8_t((255.0f*coeff) * local_coeff*local_coeff);
    for (int i = 0; i < count; ++i) {
      unsigned int actual_off = dot_offset*i;
      CHSV color(uint8_t((actual_hue + uint8_t(float(actual_off)*hue_coeff))%255),
                 255, brightness);
      unsigned int idx = (pos + actual_off)%max;
      if (apply_to & 0x01)
        band.upperLeds()[idx] += (color);
      if (apply_to & 0x02)
        band.lowerLeds()[idx] += (color);
    }
  } while (pos!=head);
}

void EDot::config(const ConfigWrapper &cfg) {
  width = cfg.getOption(F("len"), 10U);
  duration = cfg.getOption(F("speed"), 10U);
  color_duration = cfg.getOption(F("color_speed"), 15U);
  count = cfg.getOption(F("count"), 1U);
  start_hue = cfg.getOption(F("hue"), uint8_t(0));
  apply_to = cfg.getOption(F("apply"), uint8_t(3));
  coeff = cfg.getOption(F("coeff"), 1.0f);

  restart();
}
