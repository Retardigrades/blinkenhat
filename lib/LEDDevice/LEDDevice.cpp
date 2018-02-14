//
// Created by jan on 26.01.18.
//

#include "LEDDevice.h"

static const uint8_t maxLEDs = MAX_LEDS;
static CRGBArray<maxLEDs * 2> led_arr;

void LEDDevice::setup() {
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<WS2811_PORTA, 2>(led_arr, maxLEDs)
      .setCorrection(TypicalLEDStrip);

  // We do not use dithering for now.
  FastLED.setDither(0);
}

LEDDevice::LEDDevice()
    : brightness(50), frame_time(1000 / 30), last_update(0),
      bands({nullptr, nullptr}) {}

void LEDDevice::recreateChannel(const Channel &channel,
                                const HatConfig::ChannelCfg &c_cfg) {
  int idx = int(channel);

  uint8_t num_leds = c_cfg.getOption("leds", uint8_t(70));
  float gamma = c_cfg.getOption("gamma", 1.0f);

  if (bands[idx]) {
    delete bands[idx];
  }

  bands[idx] =
      new LEDBand(led_arr((idx * maxLEDs), ((idx * maxLEDs) + num_leds - 1)),
                  num_leds, gamma);
}

void LEDDevice::configure(const HatConfig &cfg) {
  const ConfigWrapper root(cfg.device());

  brightness = root.getOption(F("brightness"), uint8_t(50));
  frame_time = 1000 / root.getOption(F("framerate"), 30U);

  // set master brightness control
  FastLED.setBrightness(brightness);

  forEachChannel([&](const Channel &channel) {
    const HatConfig::ChannelCfg ccfg(cfg.channel(channel));
    effects[int(channel)].configure(ccfg);

    recreateChannel(channel, ccfg);
  });
}

void LEDDevice::loop(unsigned long time) {
  unsigned long elapsed = time - last_update;

  if (elapsed >= frame_time) {

    forEachChannel([&](const Channel &channel) {
      LEDBand *band = bands[int(channel)];
      EffectStack &effect = effects[int(channel)];

      band->blankLeds();
      effect.loop(*band, time);
      band->applyGamma();
    });

    last_update = millis();

    yield();
    FastLED.show();
    delayMicroseconds(50);
  }
}
