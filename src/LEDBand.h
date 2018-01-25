#pragma once

#define FASTLED_ESP8266_D1_PIN_ORDER
#define FASTLED_ALLOW_INTERRUPTS 0

#include <FastLED.h>
#include "Config.h"


class LEDBand {
public:
  LEDBand(const Channel channel, const uint8_t numLEDs, const uint8_t framerate);

  void update();
  void config(const Config::ChannelCfg& cfg);

  uint8_t getLEDCount(void) const { return numLEDs; }

  CRGBSet allLeds() { return leds; }
  CRGBSet upperLeds() { return leds(0, (numLEDs / 2) - 1); }
  CRGBSet lowerLeds() { return CRGBSet(leds.leds, numLEDs - 1, (numLEDs / 2)); }

  void blankLeds() { leds = CRGB::Black; }


private:
  CRGBSet leds;
  uint8_t numLEDs;
  float gamma;

  unsigned int wait;
  unsigned long last_update;
};

void setupLEDs(uint8_t brightness);