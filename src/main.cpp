#include <Arduino.h>

#include <HatConfig.h>
#include <LEDDevice.h>
#include <WebServer.h>
#include <WifiHandler.h>

HatConfig cfg;
WifiHandler wifihandler;
LEDDevice device;
WebServer web;

void setup() {
  Serial.begin(115200);
  Serial.println("setup");
  Serial.println(int(Channel::A));

  cfg.load();

  wifihandler.configure(cfg);
  wifihandler.connect();

  device.setup();
  device.configure(cfg);

  web.configure(cfg);

  cfg.onReconf([&](const HatConfig &new_cfg) { device.configure(new_cfg); });
  Serial.println(ESP.getChipId(), HEX);
}

void loop() {
  unsigned long loop_time = millis();
  // if (!wifihandler.isConnected()) {
  device.loop(loop_time);
  //}
  wifihandler.loop();
  web.loop();
}
