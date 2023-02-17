/* Тут определяем константы и глобальные переменные
*/
#define FIRMWARE_VERSION  "0.6.3 dev"
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
// включаем клапан (он на GPIO_KLAPAN_PIN)
bool  Check_klpn = false;
// пин для клапана
uint  GPIO_KLAPAN_PIN = 13; // = D7

 // включаем реле плитки (GPIO_IPLATE_PIN)
bool  Check_plate = false;
// пин питания плитки или ТЭНа
uint  GPIO_IPLATE_PIN = 4; // = D2

// термодатчик даллас
#define DS18B20PIN 12      // надо заменить на нейтральный, т.к. это пин голубого светодиода LED_BUILDIN и в то же время TXD1

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

// температура с датчика - глобальная переменная. по дефолту ставим нереальные -300
float _temperDallas = -300;
//////////////////////////////////////////////////////////////////////////////////////////////////
/// свои файлы добавляем когда уже все глобальные переменные объявлены
//////////////////////////////////////////////////////////////////////////////////////////////////
#include "read_temperature.h"
#include "fetch_led.h"
#include "home_page.h"
#include "custom_pages.h"
#include "thing_speak_sender.h"