#include <ESP8266WiFi.h>
#include <user_interface.h>

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
    WiFi.mode(WIFI_AP);

    WiFi.softAP((ap_ssid + String(ESP.getChipId(), HEX)).c_str(),
                ap_passwd.c_str());

    delay(500);
    Serial.println(WiFi.softAPIP());

    dnsServer.setTTL(300);
    dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
    dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());

    return true;
  }

  return false;
}
