//
// Created by jan on 26.01.18.
//

#ifndef BLINKENHAT_LEDDEVICE_H
#define BLINKENHAT_LEDDEVICE_H

#include <EffectStack.h>
#include <HatConfig.h>
#include <LEDBand.h>

class LEDDevice {
public:
  LEDDevice();

  void setup();
  void configure(const HatConfig &cfg);

  void loop(unsigned long time);

private:
  void recreateChannel(const Channel &channel,
                       const HatConfig::ChannelCfg &ccfg);

  uint8_t brightness;
  unsigned int frame_time;

  unsigned long last_update;

  LEDBand *bands[2];
  EffectStack effects[2];
};

#endif // BLINKENHAT_LEDDEVICE_H
