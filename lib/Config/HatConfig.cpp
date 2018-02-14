//
// Created by jan on 24.01.18.
//

#include <FS.h>

#include "HatConfig.h"
#include "default.h"

const char PROGMEM FILENAME[] = "/config.json";

HatConfig::HatConfig() : buff(), root(nullptr) { SPIFFS.begin(); }

void HatConfig::load() {
  buff.clear();
  root = nullptr;

  if (SPIFFS.exists(FPSTR(FILENAME))) {
    File file = SPIFFS.open(FPSTR(FILENAME), "r");
    if (file) {
      JsonObject &parsed = buff.parseObject(file);
      if (parsed.success()) {
        root = &parsed;
      }
      file.close();
    }
  }

  if (!root) {
    JsonObject &parsed = buff.parse(F(DEFAULT_CONFIG));

    if (parsed.success()) {
      root = &parsed;
    }
  }

  for (auto &cb : reconf_cb) {
    cb(*this);
  }
}

bool HatConfig::saveNewConfig(const String &new_config) const {
  DynamicJsonBuffer tmp_buff;
  JsonObject &tmp_conf = tmp_buff.parseObject(new_config);

  if (!tmp_conf.success()) {
    return false;
  }

  File file = SPIFFS.open(FPSTR(FILENAME), "w");
  if (file) {
    tmp_conf.printTo(file);
    file.close();
    return true;
  }

  return false;
}

void HatConfig::removeConfig() const {
  if (SPIFFS.exists(FPSTR(FILENAME))) {
    SPIFFS.remove(FPSTR(FILENAME));
  }
}

String HatConfig::currentConfig() const {
  String output;
  root->printTo(output);
  return output;
}

HatConfig::ChannelCfg HatConfig::channel(const Channel &channel) const {
  return ChannelCfg(
      root->get<JsonObject &>(F("channels"))
          .get<JsonObject &>((channel == Channel::A ? F("A") : F("B"))));
}

String HatConfig::EffectCfg::type() const { return cfg->get<String>(F("typ")); }

ConfigWrapper HatConfig::EffectCfg::config() const {
  return ConfigWrapper(&(cfg->get<JsonObject &>(F("cfg"))));
}

ConfigWrapper HatConfig::ChannelCfg::for_each_fx(
    const std::function<void(const HatConfig::EffectCfg &)> &cb) const {
  for (auto fx : cfg->get<JsonArray &>(F("effects"))) {
    cb(EffectCfg(fx.as<JsonObject &>()));
  }
}
