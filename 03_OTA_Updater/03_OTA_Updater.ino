/*
  GetStarted.ino, Example for the AutoConnect library.
  Copyright (c) 2020, Hieromon Ikasamo
  https://github.com/Hieromon/AutoConnect

  This software is released under the MIT License.
  https://opensource.org/licenses/MIT

  This example was get from 
  https://hieromon.github.io/AutoConnect/otabrowser.html
*/
/*
  Для простейшего подключения к вайфаю достаточно вот такого кода. 
  Так же тут есть возможность обновления по воздуху, т.е. без подключения к USB порту ПК. 
  После заливки данного скетча мы получаем из коробки уже очень не мало, - 
    * точка доступа, поднятая на вашей ESP 
          login     esp8266ap 
          password  12345678
    * Добавлен конфиг для реконнекта к вайфаю и сообщения о подключении в случае, если оно случилось
  В принципе, файл OTA_update.h можно не использовать. Потому что во время обновления активно светится светодиод на борту.
*/

// To properly include the suitable header files to the target platform.
#if defined(ARDUINO_ARCH_ESP8266)
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
using WiFiWebServer = ESP8266WebServer;
#elif defined(ARDUINO_ARCH_ESP32)
#include <WiFi.h>
#include <WebServer.h>
using WiFiWebServer = WebServer;
#endif
#include <AutoConnect.h>

#include "my_events.h"
#include "ota_update.h"

ESP8266WebServer  Server;          // Replace with WebServer for ESP32
AutoConnect       Portal(Server);
AutoConnectConfig Config;

void rootPage() {
  char content[] = "Hello, world";
  Server.send(200, "text/plain", content);
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();


  Server.on("/", rootPage);

  // Добавлена конфигурация для автоматического реконнекта коннекта к порталу
  Config.title = "03 OTA Update by WiFi";
  //Config.beginTimeout = 5000;     // Timeout sets to 5[s]
  Config.autoReconnect = true;    // Attempt automatic reconnection.
  Config.reconnectInterval = 6;   // Seek interval time is 180[s].
  Config.autoReset = false;       // Not reset the module even by intentional disconnection using AutoConnect menu.
  Config.retainPortal = true;     // Keep the captive portal open.
  
  // OTA update
  Config.ota = AC_OTA_BUILTIN;
  // установки реакций на события обновления, - без этого можно обойтись
  setupPortalOta(Portal);

  // конфигурируем портал
  Portal.config(Config);

  Portal.onConnect(onConnect);    // Если коннект случился, выполняем метод, как реакцию на событие
  Portal.begin();
}

void loop() {
    if (WiFi.status() == WL_CONNECTED) {
    // тут пишем код, который может выполняться в случае нормального коннекта
  }
  else {
    // тут пишем код, который может выполняться в случае отсутсвия коннекта
  }

    Portal.handleClient();
}