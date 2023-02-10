/*
  GetStarted.ino, Example for the AutoConnect library.
  Copyright (c) 2020, Hieromon Ikasamo
  https://github.com/Hieromon/AutoConnect

  This software is released under the MIT License.
  https://opensource.org/licenses/MIT

  This example was get from 
  https://hieromon.github.io/AutoConnect/gettingstarted.html
*/
/*
  Для простейшего подключения к вайфаю достаточно вот такого кода. 
  После заливки данного скетча мы получаем из коробки уже очень не мало, - 
    * точка доступа, поднятая на вашей ESP 
          login     esp8266ap 
          password  12345678
    * после подключения wifi точка доступа и логин к ней сохраняются в энергонезависимой памяти и выводится в Монитор порта, 
        в моем пример это адрес 192.168.1.142 далее имеем:
    * интерфейс отображающий параметры подключения по адресу http://192.168.1.142/_ac
    * возможность сконфигурировать ещё подключения к точкам доступа по адресу http://192.168.1.142/_ac/config
    * при переходе на домашнюю страницу Возвращаем текст, из нашего примера  "Hello, world"

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

ESP8266WebServer Server;          // Replace with WebServer for ESP32
AutoConnect      Portal(Server);

void rootPage() {
  char content[] = "Hello, world";
  Server.send(200, "text/plain", content);
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();

  Server.on("/", rootPage);
  if (Portal.begin()) {
    Serial.println("WiFi connected: " + WiFi.localIP().toString());
  }
}

void loop() {
    Portal.handleClient();
}