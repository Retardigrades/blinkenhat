#pragma once

#define FASTLED_ESP8266_D1_PIN_ORDER
#define FASTLED_ALLOW_INTERRUPTS 0

#ifndef MAX_LEDS
#define MAX_LEDS 100
#endif

#include <FastLED.h>
#include <HatConfig.h>

class LEDBand {
public:
  LEDBand(const CRGBSet &leds, uint8_t num_leds, float gamma);

  uint8_t getLEDCount() const { return numLEDs; }

  CRGBSet allLeds() { return leds; }
  CRGBSet upperLeds() { return leds(0, (numLEDs / 2) - 1); }
  CRGBSet lowerLeds() { return CRGBSet(leds.leds, numLEDs - 1, (numLEDs / 2)); }

  void blankLeds() { leds = CRGB::Black; }
  void applyGamma() {
    if (1.0f != gamma) {
      allLeds().napplyGamma_video(gamma);
    }
  }

private:
  CRGBSet leds;
  uint8_t numLEDs;
  float gamma;
};
