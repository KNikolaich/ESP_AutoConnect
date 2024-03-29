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
    Автоматическую отправку данных на сайт ThingSpeak


*/

#include "definitions.h"

void onConnect(IPAddress& ipaddr) {
  Serial.print("WiFi connected with ");
  Serial.print(WiFi.SSID());
  Serial.print(", IP:");
  Serial.println(ipaddr.toString());
}

void setup() {
  delay(1000);
  // отключаем прием сигналов по сериальному порту, т.к. нужен ещё хотя бы один пин для работы
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY); 
  
  // Добавлена конфигурация для автоматического реконнекта коннекта к порталу
  Config.title = String(FIRMWARE_VERSION) + String("!");
  //Config.beginTimeout = 5000;     // Timeout sets to 5[s]
  Config.autoReconnect = true;    // Attempt automatic reconnection.
  Config.reconnectInterval = 6;   // Seek interval time is 180[s].
  Config.autoReset = false;       // Not reset the module even by intentional disconnection using AutoConnect menu.
  Config.retainPortal = true;     // Keep the captive portal open.
  
  // OTA update можно включать обвновление по кнопке, как это описано тут https://hieromon.github.io/AutoConnect/otabrowser.html
  //Config.ota = AC_OTA_BUILTIN;
  Config.otaExtraCaption = FIRMWARE_VERSION; // можно видеть версию обновления на странице OTA

  // Присоединяем главную страницу
  joinPages(Portal);
  // конфигурируем портал
  Portal.config(Config);

  Portal.onConnect(onConnect);    // Если коннект случился, выполняем метод, как реакцию на событие
  Portal.begin();
  Sensors_setup();
  SetupThingSpeak();
  SetupSsd1306();
  TelegramSetup();
}

void loop() {
    if (WiFi.status() == WL_CONNECTED) {
    // тут пишем код, который может выполняться в случае нормального коннекта
  }
  else {
    // тут пишем код, который может выполняться в случае отсутсвия коннекта
  }
  Ds18b20_read();
  Analog_read();
  SendToTS();
  Portal.handleClient();
  Ssd1306Handle();
  TelegaLoop();
  delay(1);
}