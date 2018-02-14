#pragma once

#include <bitset>
#include <forward_list>

#include "Effect.h"

class ETwinkle : public Effect {

  using OccupiedSet = std::bitset<MAX_LEDS>;

  class Light;

  enum Color { WHITE = 0, UNIHUE = 1, DYNAMIC = 2 };

public:
  ETwinkle()
      : count(3), speed(3000), fade(500), color_mode(WHITE), hue(0),
        apply_to(1), coeff(1.0f) {}

  void update(LEDBand &band, unsigned long time) override;
  void restart() override;
  void config(const ConfigWrapper &cfg) override;

  ~ETwinkle();

private:
  void resetLight(Light &light, unsigned long time, uint8_t num_leds);
  static ETwinkle::Color mapCfg(uint8_t mode) {
    switch (mode) {
    case 1:
      return ETwinkle::UNIHUE;
    case 2:
      return ETwinkle::DYNAMIC;
    default:
      return ETwinkle::WHITE;
    }
  }

  uint8_t count;
  unsigned long speed;
  unsigned long fade;
  Color color_mode;
  uint8_t hue;
  uint8_t apply_to;
  float coeff;

  OccupiedSet occupied;
  std::forward_list<Light *> lights;
};
