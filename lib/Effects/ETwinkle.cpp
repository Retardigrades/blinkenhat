#include "ETwinkle.h"

class ETwinkle::Light {
public:
  Light() : timestamp(0), position(0), hue(0) {}

  unsigned long timestamp;
  uint8_t position;
  uint8_t hue;
};

void ETwinkle::update(LEDBand &band, unsigned long time) {
  int leds = band.getLEDCount() / (apply_to == 4 ? 1 : 2);
  unsigned long show_time = fade * 2;

  for (auto lp : lights) {
    Light &light = *lp;
    unsigned long elapsed = time - light.timestamp;

    // Not yet to show
    if (elapsed < speed) {
      continue;
    }

    // Already faded out
    if (elapsed > (speed + show_time)) {
      resetLight(light, time, leds);
      continue;
    }

    float amount = 0;

    float progress = float(elapsed - (speed + fade)) / float(fade);
    float brightness = (-1.0f * (progress * progress)) + 1.0f;

    CHSV actual(light.hue, (color_mode == WHITE ? 0 : 255),
                uint8_t(255.0f * (coeff * brightness)));

    if (apply_to & 0x01)
      band.upperLeds()[light.position] += actual;
    if (apply_to & 0x02)
      band.lowerLeds()[light.position] += actual;
    if (apply_to == 0x04) {
      band.allLeds()[light.position] += actual;
    }
  }
}

void ETwinkle::resetLight(Light &light, unsigned long time, uint8_t num_leds) {
  light.hue = (color_mode == DYNAMIC ? random8() : hue);

  occupied.set(light.position, false);

  do {
    light.position = random8(num_leds);
  } while (occupied[light.position]);

  occupied.set(light.position, true);

  long offset = long((float(speed) / 300.0f) * float(int(random8(200)) - 100));
  light.timestamp = time + offset;
}

void ETwinkle::restart() {
  for (auto light : lights) {
    delete light;
  }
  lights.clear();

  occupied.reset();

  unsigned now = millis();
  unsigned offset = speed / count;

  for (int idx = 0; idx < count; ++idx) {
    lights.emplace_front(new Light());
    resetLight(*(lights.front()), now - (idx * offset), MAX_LEDS);
  }
}

void ETwinkle::config(const ConfigWrapper &cfg) {
  count = cfg.getOption(F("count"), 1U);
  speed = cfg.getOption(F("speed"), 10U);
  fade = cfg.getOption(F("fade"), 10U);
  color_mode = mapCfg(cfg.getOption(F("color_mode"), 0U));
  hue = cfg.getOption(F("hue"), uint8_t(0));
  apply_to = cfg.getOption(F("apply"), uint8_t(3));
  coeff = cfg.getOption(F("coeff"), 1.0f);

  restart();
}

ETwinkle::~ETwinkle() {
  for (auto light : lights) {
    delete light;
  }
}
