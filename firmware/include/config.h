#ifndef _CONFIG_H_
#define _CONFIG_H_

/* Luximetro */
#define LDR_PIN                 34
#define ADC_VOLTAGE_REF         3.3
#define REF_RESISTOR            2200
#define LUX_SCALAR_COEF         1
#define LUX_EXPONENTIAL_COEF    1

/* adc config */
#define ADC_MAX_VALUE           1023
#define CYCLES_PER_SAMPLE       8
#define ADC_SAMPLES             8
#define ADC_ATTENUATION         ADC_11db


#endif
