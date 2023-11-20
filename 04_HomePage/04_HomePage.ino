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
  Данная модофикация подключает 
    - редирект с корневой страницы на Hello страницу, 
    - которая в свою очередь содержит кнопку и тест
    - другой вариант , - страница Page тоже кастомно написана
    - третий вариант, - добавление в портал своей страницы, ссылающейся на штатный сервер и не наследующий каких либо стилей

*/

#define FIRMWARE_VERSION  "0.4.2-dev"
// расцветка коричневая (теплая, ламповая) https://hieromon.github.io/AutoConnect/colorized.html
#define AUTOCONNECT_MENUCOLOR_TEXT        "#e6e6fa"
#define AUTOCONNECT_MENUCOLOR_BACKGROUND  "#3e2723"
#define AUTOCONNECT_MENUCOLOR_ACTIVE      "#4e342e"

// локализация https://hieromon.github.io/AutoConnect/adexterior.html#make-different-menu-labels
#define AUTOCONNECT_MENULABEL_CONFIGNEW   "Настройка новой AP"
#define AUTOCONNECT_MENULABEL_OPENSSIDS   "Открыть SSIDs"
#define AUTOCONNECT_MENULABEL_DISCONNECT  "Отключиться"
#define AUTOCONNECT_MENULABEL_RESET       "Перезагрузка!"
#define AUTOCONNECT_MENULABEL_UPDATE      "OTA обновление"
#define AUTOCONNECT_MENULABEL_HOME        "Home"
#define AUTOCONNECT_MENULABEL_DEVINFO     "Инфо"
#define AUTOCONNECT_BUTTONLABEL_RESET     "Перезагрузить"
#define AUTOCONNECT_BUTTONLABEL_UPDATE    "Обновить"

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

WiFiWebServer  Server;          // Replace with WebServer for ESP32
AutoConnect       Portal(Server);

#include "my_events.h"
#include "custom_pages.h"

AutoConnectConfig Config;

const char* fw_ver = FIRMWARE_VERSION;

void setup() {
  delay(1000);
  Serial.begin(115200);
  
  // Добавлена конфигурация для автоматического реконнекта коннекта к порталу
  Config.title = String(fw_ver) + String("!");
  //Config.beginTimeout = 5000;     // Timeout sets to 5[s]
  Config.autoReconnect = true;    // Attempt automatic reconnection.
  Config.reconnectInterval = 6;   // Seek interval time is 180[s].
  Config.autoReset = false;       // Not reset the module even by intentional disconnection using AutoConnect menu.
  Config.retainPortal = true;     // Keep the captive portal open.
  
  // OTA update можно включать обвновление по кнопке, как это описано тут https://hieromon.github.io/AutoConnect/otabrowser.html
  Config.ota = AC_OTA_BUILTIN;
  Config.otaExtraCaption = fw_ver; // можно видеть версию обновления на странице

  // Присоединяем главную страницу
  joinPages(Portal);
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
