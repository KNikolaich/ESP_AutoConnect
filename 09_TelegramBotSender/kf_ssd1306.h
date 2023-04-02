/*********************************************************************
Это работает на монохромном дисплее SPI OLEDs базирующемся на SSD1306
для удачной работы дисплея необходимо проверить, что в файле 
c:\Users\[userName]\Documents\Arduino\libraries\Adafruit_SSD1306\Adafruit_SSD1306.h
(или там, где у вас устанавливаются либы)
строки верно закомментированы, - в зависимости от размера вашего дисплея

//   #define SSD1306_64_48
#define SSD1306_128_64
//   #define SSD1306_128_32
//   #define SSD1306_96_16

*********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "Bitmaps.h"
#if defined(ARDUINO_ARCH_ESP8266)
// Declaration for SSD1306 display connected using software SPI (default case):
// If using software SPI (the default case):
#define OLED_DC    4  // GPIO 4 (D2)
#define OLED_RESET 0  // GPIO 0 (D3)
#define OLED_CLK   14 // GPIO14 (D5) - еще может быть как OLED_SCK
#define OLED_MOSI  13 // GPIO13 (D7) - еще может быть как OLED_SDA
#define OLED_CS    15 // GPIO15 (D8)
#elif defined(ARDUINO_ARCH_ESP32)
#define OLED_MOSI  22
#define OLED_CLK   18
#define OLED_DC    16
#define OLED_CS    5
#define OLED_RESET 17
#endif
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

/* Uncomment this block to use hardware SPI
#define OLED_DC     16
#define OLED_CS     5
#define OLED_RESET  17
Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);
*/

#define LOGO_HEIGHT   64
#define LOGO_WIDTH    128

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void testdrawbitmap(void) {
  display.clearDisplay();

  display.drawBitmap(
    (display.width()  - LOGO_WIDTH ) / 2,
    (display.height() - LOGO_HEIGHT) / 2,
    epd_bitmap_autogon2, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
  delay(1000);
}

void SetupSsd1306()   {                
  //Serial.begin(115200);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC);
  // init done
  
  delay(500);
  display.clearDisplay();
  testdrawbitmap();
  delay(1000);
  display.clearDisplay();

  // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Hello, world!");
  display.setTextColor(BLACK, WHITE); // 'inverted' text
  display.println(3.141592);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print("0x"); display.println(0xDEADBEEF, HEX);
  display.display();
  delay(2000);
}

void drawTemperature()
{  
  display.clearDisplay();

  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("Hello, world!"));

  // display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
  display.printf("Dallas: %.2f `C", _temperDallas);
  display.setCursor(3,18);
  display.setTextSize(1);             // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);

  display.print(_temperAnalog, 3);

  display.println(F(" 'C"));

  display.display();
}

unsigned long delayForOled = millis(); // таймер для работы со считываниями
void Ssd1306Handle()
{   
  if (millis() - delayForOled > 250) // пауза размером с 0.25сек
  {
    drawTemperature();
    delayForOled = millis();
  }
}