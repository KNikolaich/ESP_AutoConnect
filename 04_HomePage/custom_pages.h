#if defined(ARDUINO_ARCH_ESP8266)
using WiFiWebServer = ESP8266WebServer;
#elif defined(ARDUINO_ARCH_ESP32)
using WiFiWebServer = WebServer;
#endif

#include <AutoConnectFS.h>
AutoConnectFS::FS& FlashFS = AUTOCONNECT_APPLIED_FILESYSTEM;

const char* HELLO_URI = "/hello";
ACText(Caption, "Hello, world", "", "", AC_Tag_DIV);
ACRadio(Styles, {}, "");
ACSubmit(Apply, "Apply", HELLO_URI);

// JSON document loading buffer
String ElementJson;

// Load the element from specified file in the flash on board.
void loadParam(String fileName) {
  Serial.printf("Style %s ", fileName.c_str());
  if (!fileName.startsWith("/"))
    fileName = String("/") + fileName;
  File param = FlashFS.open(fileName.c_str(), "r");
  if (param) {
    ElementJson = param.readString();
    param.close();
    Serial.printf("loaded:\n%s", ElementJson.c_str());
  }
  else
    Serial.println("open failed");
}
// AutoConnectAux for the custom Web page.
AutoConnectAux helloPage(HELLO_URI, "Hello", true, { Caption, Styles, Apply });

// Redirects from root to the hello page.
void onRoot() {
  WiFiWebServer&  webServer = Portal.host();
  webServer.sendHeader("Location", String("http://") + webServer.client().localIP().toString() + String(HELLO_URI));
  webServer.send(302, "text/plain", "");
  webServer.client().flush();
  webServer.client().stop();
}

// Load the attribute of the element to modify at runtime from external.
String onHello(AutoConnectAux& aux, PageArgument& args) {
  // Select the style parameter file and load it into the text element.
  AutoConnectRadio& styles = helloPage["Styles"].as<AutoConnectRadio>();
  loadParam(styles.value());

  // List parameter files stored on the flash.
  // Those files need to be uploaded to the filesystem in advance.
  styles.empty();
#if defined(ARDUINO_ARCH_ESP32)
  File  dir = FlashFS.open("/", "r");
  if (dir) {
    File  parmFile = dir.openNextFile();
    while (parmFile) {
      if (!parmFile.isDirectory())
        styles.add(String(parmFile.name()));
      parmFile = dir.openNextFile();
    }
  }
#elif defined(ARDUINO_ARCH_ESP8266)
  Dir dir = FlashFS.openDir("/");
  while (dir.next()) {
    if (!dir.isDirectory())
      styles.add(dir.fileName());
  }
#endif

  // Apply picked style
  helloPage.loadElement(ElementJson);
  return String();
}

// & тут обязательный символ, обозначает пердачу объекта в качестве ссылки
void joinPages(AutoConnect       &portal)
{  
  helloPage.on(onHello);      // Register the attribute overwrite handler.
  portal.join(helloPage);     // Join the hello page.
  
  WiFiWebServer&  webServer = portal.host();
  webServer.on("/", onRoot); 
}
