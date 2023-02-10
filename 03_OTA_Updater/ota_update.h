/***
* тут у нас собраны файлы для обновления и метод для подключения этого обнавления
*/
void exitOTAStart() {
  Serial.println("OTA started");
}

void exitOTAProgress(unsigned int amount, unsigned int sz) {
  Serial.printf("OTA in progress: received %d bytes, total %d bytes\n", sz, amount);
}

void exitOTAEnd() {
  Serial.println("OTA ended");
}

void exitOTAError(uint8_t err) {
  Serial.printf("OTA error occurred %d\n", err);
}

/// это метод , который должен быть вызван во время настроек для подключения OTA обновления, но, в принципе об этих событиях можно забыть
void setupPortalOta(AutoConnect &portal)
{
  portal.onOTAStart(exitOTAStart);
  portal.onOTAEnd(exitOTAEnd);
  portal.onOTAProgress(exitOTAProgress);
  portal.onOTAError(exitOTAError);
}