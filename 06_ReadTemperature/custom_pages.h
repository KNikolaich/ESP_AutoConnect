char* getTemperDallas()
{
  char result[8]; // Buffer big enough for 7-character float
  dtostrf(_temperDallas, 6, 2, result); // Leave room for too large numbers!
  return result;
}


// const char* HELLO_URI = "/hello";
//ACText(Caption, "Температура в Далласе", "", "", AC_Tag_DIV);

// ACText(Caption, getTemperDallas(), "", "", AC_Tag_DIV);
// ACRadio(Styles, {}, "");
// ACSubmit(Apply, "Apply", HELLO_URI);


// AutoConnectAux for the custom Web page.
//AutoConnectAux helloPage(HELLO_URI, "Привет", true, { Caption, Styles, Apply });

// Redirects from root to the hello page.
// void onRoot() {
//   WiFiWebServer&  webServer = Portal.host();
//   webServer.sendHeader("Location", String("http://") + webServer.client().localIP().toString() + String(HELLO_URI));
//   webServer.send(302, "text/plain", ""); // ds18b20read
//   webServer.client().flush();
//   webServer.client().stop();
// }

// Load the attribute of the element to modify at runtime from external.
// String onHello(AutoConnectAux& aux, PageArgument& args) {
//   // Select the style parameter file and load it into the text element.
//   AutoConnectRadio& styles = helloPage["Styles"].as<AutoConnectRadio>();
//   Serial.println("Hello page refresh");
//   return String();
// }
void handleRoot() 
{
 String s = webRootPage;
 Server.send(200, "text/html", s);
}

// & тут обязательный символ, обозначает пердачу объекта в качестве ссылки
void joinPages(AutoConnect &portal)
{  
  //helloPage.on(onHello);      // Register the attribute overwrite handler.
  //portal.load(FPSTR(PAGE));
  buildInSetup(portal);
  //portal.join(helloPage);     // Join the hello page.
  //portal.append("/hello", "HELLO"); // т.о. можно добавить какую то кастомную страницу
  // которая затем может быть описана банальным образом типа 
  /* 
   server.on("/hello", [](){
    server.send(200, "text/html", String(F(
"<html>"
"<head><meta name='viewport' content='width=device-width,initial-scale=1.0'></head>"
"<body><h2>Hello, world</h2></body>"
"</html>"
    )));
  });
  */
  WiFiWebServer&  webServer = portal.host();
  webServer.on("/", handleRoot); 
  // обработка ajax запроса на данные с сервера (приходит каждые x секунд)
  webServer.on("/ds18b20read", sensor_data);
}
