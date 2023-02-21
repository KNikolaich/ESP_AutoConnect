#include "secret.h"
#include "ThingSpeak.h" 

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;
int sendDelay = 30000;
unsigned long delayForSendTs = millis(); // таймер для работы со считываниями
WiFiClient  client;

void SetupThingSpeak() {
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void SendToTS()
{
  // пауза размером с delay, значение меньше 0 по кельвину не шлем, если посылатель выключен, - тоже не шлем. Так же, включаем отправку вместе со светодиодом
  if (millis() - delayForSendTs > sendDelay && (_temperDallas != -0.06 || _temperAnalog > -300) && digitalRead(GPIO_IPLATE_PIN))
  {      
    if(_temperDallas > 0) // TODO эскуственно обрежем все, что ниже нуля, потому что считываемые данные без датчика -0.06 
      ThingSpeak.setField(1, _temperDallas);
    if(_temperAnalog > -300)
      ThingSpeak.setField(2, _temperAnalog);
    // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
    // pieces of information in a channel.  Here, we write to field 1.
    int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    if(x == 200){
      Serial.println("Channel update successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
    delayForSendTs = millis();
  }

}