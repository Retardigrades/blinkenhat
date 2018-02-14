//
// Created by jan on 25.01.18.
//

#include "EffectStack.h"

#include "EDot.h"
#include "ERainbow.h"
#include "ETwinkle.h"

Effect *EffectStack::createEffect(const HatConfig::EffectCfg &cfg) {
  if (cfg.type() == F("rainbow")) {
    Effect *fx = new ERainbow();
    fx->config(cfg.config());
    return fx;
  }
  if (cfg.type() == F("dot")) {
    Effect *fx = new EDot();
    fx->config(cfg.config());
    return fx;
  }
  if (cfg.type() == F("twinkle")) {
    Effect *fx = new ETwinkle();
    fx->config(cfg.config());
    return fx;
  }
  return nullptr;
}

void EffectStack::configure(const HatConfig::ChannelCfg &cfg) {
  for (auto item : effects) {
    delete item;
  }
  effects.clear();

  cfg.for_each_fx([&](const HatConfig::EffectCfg &fx_cfg) {
    Effect *fx = createEffect(fx_cfg);
    if (fx) {
      effects.emplace_front(fx);
    }
  });
}
