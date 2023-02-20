#include <OneWire.h>
#include <DS18B20.h>
// GND --- термистор --- A0 --- 10к --- 5V
#include <GyverNTC.h>
GyverNTC therm(0, 10000, 3950);	// пин, сопротивление при 25 градусах (R термистора = R резистора!), бета-коэффициент
// GyverNTC therm(0, 10000, 3435, 25, 10000);	// пин, R термистора, B термистора, базовая температура, R резистора
// серый 4300
// проводной 3435

/* Create an instance of OneWire */
OneWire oneWire(DS18B20PIN);
DS18B20 sensor(&oneWire);
unsigned long delayForReadDs = millis(); // таймер для работы со считываниями
unsigned long delayForReadA0 = millis(); // таймер для работы со считываниями
int mSecDelay = 1000;  // пауза перед чтением

void Sensors_setup() {
  /* Start the DS18B20 Sensor */
  sensor.setResolution(12); // 12 бит чтения дает максимальную точность
  sensor.begin();
}

////////////////////////////////////// простой кальман, - фильтр позволяет сглаживать резкие пробросы значений
// _err_measure = 0.8;  // примерный шум измерений
// float _q = 0.005;   // скорость изменения значений 0.001-1, варьировать самому
float simpleKalmanDS(float newVal, float _err_measure = 0.8, float _q = 0.005) {
  static float _err_estimate = _err_measure;
  static float _last_estimate;
  float _kalman_gain = (float)_err_estimate / (_err_estimate + _err_measure);
  float _current_estimate = _last_estimate + (float)_kalman_gain * (newVal - _last_estimate);
  _err_estimate =  (1.0 - _kalman_gain) * _err_estimate + fabs(_last_estimate - _current_estimate) * _q;
  _last_estimate = _current_estimate;
  return _current_estimate;
}

////////////////////////////////////// простой кальман, - фильтр позволяет сглаживать резкие пробросы значений
// _err_measure = 0.8;  // примерный шум измерений
// float _q = 0.005;   // скорость изменения значений 0.001-1, варьировать самому
float simpleKalmanA0(float newVal, float _err_measure = 0.8, float _q = 0.005) {
  static float _err_estimateA0 = _err_measure;
  static float _last_estimateA0;
  float _kalman_gain = (float)_err_estimateA0 / (_err_estimateA0 + _err_measure);
  float _current_estimate = _last_estimateA0 + (float)_kalman_gain * (newVal - _last_estimateA0);
  _err_estimateA0 =  (1.0 - _kalman_gain) * _err_estimateA0 + fabs(_last_estimateA0 - _current_estimate) * _q;
  _last_estimateA0 = _current_estimate;
  return _current_estimate;
}

void Ds18b20_read()
{
  if (millis() - delayForReadDs > mSecDelay) // пауза размером с delay
  {  
    while (!sensor.isConversionComplete());  // ожидаем до тех пор, пока сенсор не считает значение (для разных битрейтов время отличается)
    {
      Serial.print("Temp: ");      
      _temperDallas = simpleKalmanDS(sensor.getTempC());
      Serial.print(_temperDallas);
      Serial.println("ºC");
    }
    delayForReadDs = millis();
    sensor.requestTemperatures(); // закажем заранее чтение , чтобы не тормозить потом с этим процессом. 
  }
}

void Analog_read()
{
  if (millis() - delayForReadA0 > mSecDelay) // пауза размером с delay
  {  
    Serial.print("Temp: ");      
    _temperAnalog = simpleKalmanA0(therm.getTempAverage());
    Serial.print(_temperAnalog);
    Serial.println("ºC");
    delayForReadA0 = millis();
  }
}

// выдаем данные по запросу скрипта
void sensor18b20_data() 
{
 Server.send(200, "text/plane", String(_temperDallas));
}

// выдаем данные по запросу скрипта
void sensorAdc_data() 
{
 Server.send(200, "text/plane", String(_temperAnalog));
}