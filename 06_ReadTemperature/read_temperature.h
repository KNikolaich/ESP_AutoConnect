#include <OneWire.h>
#include <DS18B20.h>

/* Create an instance of OneWire */
OneWire oneWire(DS18B20PIN);
DS18B20 sensor(&oneWire);
unsigned long delayForReadDs = millis(); // таймер для работы со считываниями
int mSecDelay = 1000;  // пауза перед чтением

void Ds18b20_setup() {
  /* Start the DS18B20 Sensor */
  sensor.setResolution(12); // 12 бит чтения дает максимальную точность
  sensor.begin();
}

void Ds18b20_read()
{
  if (millis() - delayForReadDs > mSecDelay) // пауза размером с delay
  {  
    
    while (!sensor.isConversionComplete());  // ожидаем до тех пор, пока сенсор не считает значение (для разных битрейтов время отличается)
    {
      Serial.print("Temp: ");      
      _temperDallas = sensor.getTempC();
      Serial.print(_temperDallas);
      Serial.println("ºC");
    }
    delayForReadDs = millis();
    sensor.requestTemperatures(); // закажем заранее чтение , чтобы не тормозить потом с этим процессом. 
    // sensor.requestTemperatures();
    // _temperDallas = sensor.getTempC(insideThermometer);
    // Serial.print("Temperature = ");
    // Serial.print(_temperDallas);
  }
}

void sensor_data() 
{
//  int a = analogRead(A0);
//  int temp= a/4.35;
 String sensor_value = String(_temperDallas);
 Server.send(200, "text/plane", sensor_value);
}
