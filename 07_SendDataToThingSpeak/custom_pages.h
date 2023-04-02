void handleRoot() {  Server.send(200, "text/html", String(webRootPage));}

void handleLedState() {
  String state = "uncknow";
  if(digitalRead(GPIO_IPLATE_PIN)) state = "ON"; else state = "OFF";
  Server.send(200, "text/plane", state);
}

// привязываем свои страницы
void joinPages(AutoConnect& portal) {
  buildInSetup(portal);
  WiFiWebServer& webServer = portal.host();
  webServer.on("/", handleRoot);
  
  // обработка ajax запроса на данные с сервера (приходит каждые x секунд)
  webServer.on("/ds18b20read", sensor18b20_data);
  // обработка ajax запроса на данные с сервера (приходит каждые x секунд)
  //webServer.on("/adcread", sensorAdc_data);

  // стрипт запрашивает состояние светодиода
  webServer.on("/led_state_read", handleLedState);
}
