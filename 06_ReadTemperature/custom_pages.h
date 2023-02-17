char* getTemperDallas()
{
  char result[8]; // Buffer big enough for 7-character float
  dtostrf(_temperDallas, 6, 2, result); // Leave room for too large numbers!
  return result;
}

void handleRoot() 
{
 String s = webRootPage;
 Server.send(200, "text/html", s);
}

// привязываем свои страницы
void joinPages(AutoConnect &portal)
{  
  buildInSetup(portal);
  WiFiWebServer&  webServer = portal.host();
  webServer.on("/", handleRoot); 
  // обработка ajax запроса на данные с сервера (приходит каждые x секунд)
  webServer.on("/ds18b20read", sensor_data);
}
