#include <OneWire.h>
#include <DS18B20.h>

/* Create an instance of OneWire */
OneWire oneWire(DS18B20PIN);
DS18B20 sensor(&oneWire);
unsigned long delayForReadDs = millis(); // таймер для работы со считываниями
int mSecDelay = 1000;  // пауза перед чтением

// настройки простого Кальман фильтра
float _err_measure = 0.8;  // примерный шум измерений
float _q = 0.005;   // скорость изменения значений 0.001-1, варьировать самому

void Ds18b20_setup() {
  /* Start the DS18B20 Sensor */
  sensor.setResolution(12); // 12 бит чтения дает максимальную точность
  sensor.begin();
}

////////////////////////////////////// простой кальман, - фильтр позволяет сглаживать резкие пробросы значений
float simpleKalman(float newVal) {
  float _kalman_gain, _current_estimate;
  static float _err_estimate = _err_measure;
  static float _last_estimate;
  _kalman_gain = (float)_err_estimate / (_err_estimate + _err_measure);
  _current_estimate = _last_estimate + (float)_kalman_gain * (newVal - _last_estimate);
  _err_estimate =  (1.0 - _kalman_gain) * _err_estimate + fabs(_last_estimate - _current_estimate) * _q;
  _last_estimate = _current_estimate;
  return _current_estimate;
}

void Ds18b20_read()
{
  if (millis() - delayForReadDs > mSecDelay) // пауза размером с delay
  {  
    while (!sensor.isConversionComplete());  // ожидаем до тех пор, пока сенсор не считает значение (для разных битрейтов время отличается)
    {
      Serial.print("Temp: ");      
      _temperDallas = simpleKalman(sensor.getTempC());
      Serial.print(_temperDallas);
      Serial.println("ºC");
    }
    delayForReadDs = millis();
    sensor.requestTemperatures(); // закажем заранее чтение , чтобы не тормозить потом с этим процессом. 
  }
}

// выдаем данные по запросу скрипта
void sensor_data() 
{
//  int a = analogRead(A0);
//  int temp= a/4.35;
 Server.send(200, "text/plane", String(_temperDallas));
}
