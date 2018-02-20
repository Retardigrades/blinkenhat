#include <ESP8266WiFi.h>
#include <user_interface.h>
#include <array>

#include "WifiHandler.h"

const byte DNS_PORT = 53;

void WifiHandler::configure(const HatConfig &cfg) {
  ConfigWrapper dcfg = cfg.device();

  sta_ssid = dcfg.getOption(F("sta_ssid"), String());
  sta_passwd = dcfg.getOption(F("sta_passwd"), String());

  ap_ssid = dcfg.getOption(F("ap_ssid"), String());
  ap_passwd = dcfg.getOption(F("ap_passwd"), String());

  timeout = dcfg.getOption(F("ap_timeout"), 0U);
}


struct ChannelStat {
  uint8_t channel;
  uint8_t count;

  ChannelStat(uint8_t channel) : channel(channel), count(0) {}
  bool operator<(const ChannelStat& other) { return count < other.count; }
};


bool WifiHandler::connect() {
  last_client = millis();

  if (sta_ssid.length() > 0 && sta_passwd.length() > 0) {
    WiFi.mode(WIFI_STA);
    WiFi.begin(sta_ssid.c_str(), sta_passwd.c_str());

    for (int i = 0; i < 100; ++i) {
      if (WiFi.status() == WL_CONNECTED) {
        Serial.printf("connected after %dms\n", i * 50);
        Serial.println(WiFi.localIP());
        return true;
      }
      delay(50);
    }
  }

  if (ap_ssid.length() > 0 && ap_passwd.length() > 0) {

    int channel = 1;

    uint8_t scan_results = 0;

    // find channel with min networks.
    if ((scan_results = WiFi.scanNetworks()) > 0) {

      std::array<ChannelStat, 4> stats{{1, 5, 9, 13}};
      for (uint8_t idx = 0; idx < scan_results; ++idx) {
        int current = WiFi.channel(idx);
        for (auto& stat : stats) {
          if (stat.channel == current) {
            stat.count ++;
            break;
          }
        }
      }

      const auto& minCh = std::min_element(stats.begin(), stats.end());
      channel = minCh->channel;

#ifdef DEBUG_ESP_WIFI
      Serial.println("Channel stats:");
      for (const auto& stat : stats) {
        Serial.printf("  %02d: %d\n", stat.channel, stat.count);
      }
      Serial.printf("Selected channel: %d", channel);
#endif
    }

    WiFi.mode(WIFI_AP);

    WiFi.softAP((ap_ssid + String(ESP.getChipId(), HEX)).c_str(),
                ap_passwd.c_str(),
                channel);

    delay(500);
    Serial.println(WiFi.softAPIP());

    dnsServer.setTTL(300);
    dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
    dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());

    return true;
  }

  return false;
}
