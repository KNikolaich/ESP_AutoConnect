/* Тут определяем константы и глобальные переменные
*/
#define FIRMWARE_VERSION  "0.7.6 dev"
// расцветка коричневая (теплая, ламповая) https://hieromon.github.io/AutoConnect/colorized.html
#define AUTOCONNECT_MENUCOLOR_TEXT        "#e6e6fa"
#define AUTOCONNECT_MENUCOLOR_BACKGROUND  "#3e2723"
#define AUTOCONNECT_MENUCOLOR_ACTIVE      "#4e342e"

// локализация https://hieromon.github.io/AutoConnect/adexterior.html#make-different-menu-labels
#define AUTOCONNECT_MENULABEL_CONFIGNEW   "Новая AP"
#define AUTOCONNECT_MENULABEL_OPENSSIDS   "SSIDs"
#define AUTOCONNECT_MENULABEL_DISCONNECT  "Отключиться"
#define AUTOCONNECT_MENULABEL_RESET       "Перезагрузка..."
#define AUTOCONNECT_MENULABEL_UPDATE      "OTA"
#define AUTOCONNECT_MENULABEL_HOME        "Главная"
#define AUTOCONNECT_MENULABEL_DEVINFO     "Инфо"
#define AUTOCONNECT_BUTTONLABEL_RESET     "Перезагрузить"
#define AUTOCONNECT_BUTTONLABEL_UPDATE    "Обновить"

//////////////////////////////////////////////////////////////////////////////////////////////////
// Какие GPIO к чему будут привязаны и начальные значения по дефолту
//////////////////////////////////////////////////////////////////////////////////////////////////

// пин для пробуждения
uint  GPIO_WAKE_PIN = 16; // = D0 (GPIO 16)
// пин для клапана
uint  GPIO_KLAPAN_PIN = 5; // = D1 (GPIO 5)
// светодиод на борту (повесим на него флаг, отправлять данные на сервер или нет)
uint  GPIO_LED_ONBOARD = 2; // = D4

// пин питания плитки или ТЭНа
uint  GPIO_IPLATE_PIN = 12; // = D6 (GPIO 12)

// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_DC    D2 // GPIO 4 (D2)
#define OLED_RESET D3 // GPIO 0 (D3)
#define OLED_SCK   D5 // GPIO14 (D5) - еще может быть как OLED_CLK
#define OLED_SDA   D7 // GPIO13 (D7) - еще может быть как OLED_MOSI
#define OLED_CS    D8 // GPIO15 (D8)

// термодатчик даллас
#define DS18B20PIN 3  // необходимо отключить прием данных ком порта, чтобы работал порт RXD для наших нужд

#define AnalogPin A0  // для чтения аналогового датчика есть у ESP8266 только один вход. 

//////////////////////////////////////////////////////////////////////////////////////////////////
// Включаем так же библиотеки
//////////////////////////////////////////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////////////////////////////////////////
// автозаменяется библиотека в зависимости от платформы for ESP32 WiFiWebServer и ESP8266WebServer for ESP8266
//////////////////////////////////////////////////////////////////////////////////////////////////
WiFiWebServer     Server;          
AutoConnect       Portal(Server);
AutoConnectConfig Config;

// температура с датчика Dallas - глобальная переменная. по дефолту ставим нереальные -300
float _temperDallas = -300;
// температура с аналогового датчика - глобальная переменная. по дефолту ставим нереальные -300
float _temperAnalog = -300;
//////////////////////////////////////////////////////////////////////////////////////////////////
/// свои файлы добавляем когда уже все глобальные переменные объявлены
//////////////////////////////////////////////////////////////////////////////////////////////////
#include "read_temperature.h"
#include "fetch_led.h"
#include "home_page.h"
#include "custom_pages.h"
#include "thing_speak_sender.h"