/* Тут определяем константы и глобальные переменные
*/
#define FIRMWARE_VERSION  "0.4.1-dev"
// расцветка коричневая (теплая, ламповая) https://hieromon.github.io/AutoConnect/colorized.html
#define AUTOCONNECT_MENUCOLOR_TEXT        "#e6e6fa"
#define AUTOCONNECT_MENUCOLOR_BACKGROUND  "#3e2723"
#define AUTOCONNECT_MENUCOLOR_ACTIVE      "#4e342e"

// локализация https://hieromon.github.io/AutoConnect/adexterior.html#make-different-menu-labels
#define AUTOCONNECT_MENULABEL_CONFIGNEW   "Настройка новой AP"
#define AUTOCONNECT_MENULABEL_OPENSSIDS   "Открыть SSIDs"
#define AUTOCONNECT_MENULABEL_DISCONNECT  "Отключиться"
#define AUTOCONNECT_MENULABEL_RESET       "Перезагрузка..."
#define AUTOCONNECT_MENULABEL_UPDATE      "OTA обновление"
#define AUTOCONNECT_MENULABEL_HOME        "Главная"
#define AUTOCONNECT_MENULABEL_DEVINFO     "Инфо"
#define AUTOCONNECT_BUTTONLABEL_RESET     "Перезагрузить"
#define AUTOCONNECT_BUTTONLABEL_UPDATE    "Обновить"



// включаем клапан (он на GPIO_KLAPAN_PIN)
bool     Check_klpn = false;
// пин для клапана
uint GPIO_KLAPAN_PIN = 12;

 // включаем реле плитки (GPIO_IPLATE_PIN)
bool     Check_plate = false;
// пин питания плитки или ТЭНа
uint GPIO_IPLATE_PIN = 25; //14
