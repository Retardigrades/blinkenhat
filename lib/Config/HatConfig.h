//
// Created by jan on 24.01.18.
//

#ifndef BLINKENHAT_CONFIG_H
#define BLINKENHAT_CONFIG_H

#include <forward_list>
#include <functional>

#include <WString.h>

#include <ArduinoJson.h>

enum class Channel { A = 0, B = 1 };

using ChannelConsumer = std::function<void(const Channel &channel)>;

inline void forEachChannel(const ChannelConsumer &cb) {
  cb(Channel::A);
  cb(Channel::B);
}

class ConfigWrapper {

public:
  ConfigWrapper(const JsonObject *cfg) : cfg(cfg) {}

  template <typename Tkey, typename Tvalue>
  Tvalue getOption(const Tkey &key, const Tvalue &dflt) const {
    if (cfg->containsKey(key)) {
      return cfg->get<Tvalue>(key);
    }
    return dflt;
  }

  virtual ~ConfigWrapper() = default;

protected:
  const JsonObject *cfg;
};

class HatConfig {
public:
  using ReconfCb = std::function<void(const HatConfig &)>;

  class EffectCfg : ConfigWrapper {
  public:
    EffectCfg(JsonObject &root) : ConfigWrapper(&root) {}
    String type() const;
    ConfigWrapper config() const;
  };

  class ChannelCfg : public ConfigWrapper {
  public:
    using EffectConsumer = std::function<void(const EffectCfg &)>;

    ChannelCfg(JsonObject &root) : ConfigWrapper(&root) {}
    ConfigWrapper for_each_fx(const EffectConsumer &cb) const;
  };

  HatConfig();

  bool saveNewConfig(const String &new_config) const;
  void removeConfig() const;
  void load();
  String currentConfig() const;

  void onReconf(const ReconfCb &cb) { reconf_cb.emplace_front(cb); }

  ConfigWrapper device() const { return ConfigWrapper(root); }

  ChannelCfg channel(const Channel &channel) const;

private:
  DynamicJsonBuffer buff;
  JsonObject *root;
  std::forward_list<ReconfCb> reconf_cb;
};

#endif // BLINKENHAT_CONFIG_H
