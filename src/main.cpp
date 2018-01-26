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

  device.setup();
  device.configure(cfg);

  web.configure(cfg);
}

void loop() {
  unsigned long loop_time = millis();
  device.loop(loop_time);
  web.loop();
}
