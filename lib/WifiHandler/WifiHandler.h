#ifndef BLINKENHAT_WIFIHANDLER_H
#define BLINKENHAT_WIFIHANDLER_H
#include <ESP8266WiFi.h>

#include <DNSServer.h>
#include <HatConfig.h>

class WifiHandler {
public:
  void configure(const HatConfig &cfg);
  bool connect();

  bool isConnected() { return (WiFi.softAPgetStationNum() > 0); }
  void loop() {
    // Serial.printf("Stations connected = %d\n", WiFi.softAPgetStationNum());
    dnsServer.processNextRequest();
    // .. disconnect after timeout
    // use softAPgetStationNum to check if clients connected.
  }

private:
  String sta_ssid;
  String sta_passwd;

  String ap_ssid;
  String ap_passwd;

  unsigned long timeout;
  unsigned long last_client;

  DNSServer dnsServer;
};

#endif // BLINKENHAT_WIFIHANDLER_H
