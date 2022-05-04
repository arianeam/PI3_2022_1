#include <Arduino.h>
#include "config.h"

/**
 * @brief Inicializa o ADC
 */
void adc_init()
{
#if CONFIG_IDF_TARGET_ESP32
#pragma message "ESP32"
  analogSetAttenuation(ADC_ATTENUATION);
#else
#pragma message "ESP8266"

#endif
}

/**
 * @brief Returna a luminosidade do ambiente
 * @return float 
 */
float measure(void)
{
  float rawData = (float) analogRead(LDR_PIN) / (ADC_MAX_VALUE * ADC_VOLTAGE_REF);
  float ldrVoltage = ADC_VOLTAGE_REF - rawData;
  float ldrResistance = ldrVoltage / rawData * REF_RESISTOR;

  float lux = LUX_SCALAR_COEF * pow(ldrResistance, LUX_EXPONENTIAL_COEF);
  return lux;
}

void setup(void)
{
  Serial.begin(9600);
  Serial.print("ADC... ");
  adc_init();
  Serial.print("OK!\n");
}

void loop(void)
{
  float data = measure();

  Serial.print("LUX: ");
  Serial.print(data);

  delay(2000);
}