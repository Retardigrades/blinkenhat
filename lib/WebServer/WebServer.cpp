
#include "WebServer.h"
#include "index.h"

#ifndef FW_VERSION
#define FW_VERSION unknown
#endif

#define X_QUOTE(x) #x
#define QUOTE(x) X_QUOTE(x)

const char PROGMEM TEXT_PLAIN[] = "text/plain";
const char PROGMEM APPLICATION_JSON[] = "application/json";

static String strResult(const bool inp) {
  return (inp ? F("true") : F("false"));
}

void WebServer::configure(HatConfig &config) {

  /*
   * GET /
   */
  web.on(F("/"), HTTP_GET, [this]() {
    web.sendHeader(F("Content-Encoding"), F("deflate"));
    web.setContentLength(index_html_len);
    web.send(200, F("text/html"), "");
    web.sendContent_P(index_html, index_html_len);
  });

  /*
   * GET /firmware
   */
  web.on(F("/firmware"), HTTP_GET, [this]() {
    web.send(200, FPSTR(APPLICATION_JSON),
             F("{\"version\": \"" QUOTE(FW_VERSION) "\"}"));
  });

  /*
   * POST /firmware
   */
  web.on(
      F("/firmware"), HTTP_POST,
      [this]() {
        web.sendHeader(F("Connection"), F("close"));

        if (Update.hasError()) {
          web.send_P(
              200, TEXT_PLAIN,
              PSTR("Update failed. You may need to reflash the device."));
        } else {
          web.sendHeader(F("Refresh"), F("20; URL=/"));
          web.send_P(200, TEXT_PLAIN,
                     PSTR("Update successful.\n\nDevice will reboot and try "
                          "to reconnect in 20 seconds."));
        }
        delay(1000);
        WiFi.disconnect(true);
        delay(500);
        ESP.restart();
      },
      [this]() {
        HTTPUpload &upload = web.upload();
        if (upload.status == UPLOAD_FILE_START) {
          Serial.setDebugOutput(true);

          Serial.print(F("Update: "));
          Serial.println(upload.filename.c_str());
          uint32_t maxSketchSpace =
              (ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000;
          if (!Update.begin(maxSketchSpace)) { // start with max available size
            Update.printError(Serial);
          }
        } else if (upload.status == UPLOAD_FILE_WRITE) {
          if (Update.write(upload.buf, upload.currentSize) !=
              upload.currentSize) {
            Update.printError(Serial);
          }
        } else if (upload.status == UPLOAD_FILE_END) {
          if (Update.end(
                  true)) { // true to set the size to the current progress
            Serial.print(F("Update Success: "));
            Serial.print(upload.totalSize);
            Serial.print(F("\nRebooting...\n"));
          } else {
            Update.printError(Serial);
          }
          Serial.setDebugOutput(false);
        }
        yield();
      });

  /*
   * GET /config
   */
  web.on(F("/config"), HTTP_GET, [&]() {
    web.send(200, FPSTR(APPLICATION_JSON), config.currentConfig());
  });

  /*
   * POST /config
   */
  web.on(F("/config"), HTTP_POST, [&]() {
    bool success = web.args() == 1 && config.saveNewConfig(web.arg(0));
    if (success) {
      config.load();
    }
    web.send(200, FPSTR(APPLICATION_JSON), strResult(success));
  });

  /*
   * DELETE /config
   */
  web.on(F("/config"), HTTP_DELETE, [&]() {
    config.removeConfig();
    config.load();
    web.send(200, FPSTR(APPLICATION_JSON), strResult(true));
  });

  web.begin();
}
