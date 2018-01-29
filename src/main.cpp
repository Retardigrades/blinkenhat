#include <Arduino.h>

#include <Config.h>
#include <LEDDevice.h>
#include <WifiHandler.h>
#include <WebServer.h>


Config cfg;
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

  cfg.onReconf([&](const Config& new_cfg){ device.configure(new_cfg); });
}

void loop() {
  unsigned long loop_time = millis();
  device.loop(loop_time);
  web.loop();
}
