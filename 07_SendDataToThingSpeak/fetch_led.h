
// Define a path to the custom web page for the LED blink control.
#define LED_ENDPOINT  "/properties"
// здесь локализованные надписи на кнопках
#define ON "Включить"
#define OFF "Выключить"
const char LED_ONOFF[] PROGMEM = R"(
{
  "uri": ")" LED_ENDPOINT R"(",
  "title": "Настройки",
  "menu": true,
  "element": [
    {
      "name": "caption4",
      "type": "ACText",
      "value": "Отправляем данные на TS",
      "style": "font-size:25px;text-align:center;",
      "posterior": "div"
    },
    {
      "name": "onoff4",
      "type": "ACButton",
      "value": ")" ON R"("
    },
    {
      "name": "caption2",
      "type": "ACText",
      "value": "На борту.",
      "style": "font-size:25px;text-align:center;",
      "posterior": "div"
    },
    {
      "name": "onoff2",
      "type": "ACButton",
      "value": ")" ON R"("
    }
  ]
}
)";

// Event handler that attaches to an AutoConnectButton named `led`.
// This event handler receives a reference to AutoConnectButton as `led`
// and a reference to the AutoConnectAux of the page rendered in the client
// browser.
void ledOnOff(AutoConnectButton& me, AutoConnectAux& ledOnOff) {
  String currCaption = "";
  int currentPin = 0;
  // для реверсивных светодиодов этот флаг ставим в true. Это такие светодиоды, которые горят при нулевом значении на пине
  bool isReverse = false; 
  if(me.name == "onoff2") {
    currCaption = "caption2";
    currentPin  = GPIO_KLAPAN_PIN;
    isReverse = true;
  }
  else if(me.name == "onoff4"){    
    currCaption = "caption4";
    currentPin  = GPIO_IPLATE_PIN;
  }
  // работа основная. если кнопка была названа ON, включаем и наоборот
  if (me.value == ON) {

    // Since "ON" has been passed from the AutoConnectButton as `led`. Let the
    // LED turns on.
    bool LED_ACTIVELEVEL = true;
    if(isReverse) LED_ACTIVELEVEL = false;
    digitalWrite(currentPin, LED_ACTIVELEVEL);

    // Direct assignment to AutoConnectElement values is not reflected on the
    // web page; use the `response` function to update the value of the element
    // on the web page.
    me.response(OFF);

    // The `on` event handler attached to AutoConnectElements can override the
    // value and attributes of other elements placed on that AutoConnectAux page.
    // For example, a following statement changes the font color of the `caption`
    // element along with a LED blinking.
    ledOnOff[currCaption].response("style", "{\"color\":\"red\", \"font-weight\":\"bold\"}");
  }
  if (me.value == OFF) {
    bool LED_ACTIVELEVEL = false;
    if(isReverse) LED_ACTIVELEVEL = true;
    digitalWrite(currentPin, LED_ACTIVELEVEL);
    me.response(ON);
    ledOnOff[currCaption].response("style", "{\"color\":\"black\", \"font-weight\":\"normal\"}");
  }
}

// привязываем настройки
void buildInSetup(AutoConnect &portal)
{
    // Built-in LED port setting up
  Serial.printf("LEDs port assignment GPIOs ## %d, %d\n", GPIO_KLAPAN_PIN, GPIO_IPLATE_PIN);
  pinMode(GPIO_IPLATE_PIN, OUTPUT);
  pinMode(GPIO_KLAPAN_PIN, OUTPUT);
  digitalWrite(GPIO_KLAPAN_PIN, true);// это реверсивный светодиод, ему true - выключает
  digitalWrite(GPIO_IPLATE_PIN, false); 

  // связываем конфиг

  // Load the AutoConnectAux page with the LED ON/OFF button into AutoConnect.
  // The sketch can get its instance using the AutoConnect::locate function
  // after AutoConnectAux is loaded.
  portal.load(FPSTR(LED_ONOFF));
  AutoConnectAux& led = portal.locate(LED_ENDPOINT);

  // The AutoConnectElement::on function allows the sketch to register an event
  // handler that interacts with the element individually.
  AutoConnectButton& onOff4 = led["onoff4"].as<AutoConnectButton>();
  onOff4.on(ledOnOff);
  // для реакции на кнопку 2
    AutoConnectButton& onOff2 = led["onoff2"].as<AutoConnectButton>();
  onOff2.on(ledOnOff);
  Serial.println("Access to blink the LED http://" + WiFi.localIP().toString() + LED_ENDPOINT);
}