#ifndef ADC_1_H
#define ADC_1_H

#include "freertos/FreeRTOS.h"
#include <freertos/task.h>
#include <stdio.h>
#include <iostream>
#include <driver/gpio.h>
#include <driver/i2c.h>
#include <esp_err.h>
#include "driver/adc.h"
#include "esp_adc_cal.h"

#include <stdlib.h>

#define DEFAULT_VREF 1100 // Use adc2_vref_to_gpio() to obtain a better estimate


class adc
{
private:
    adc1_channel_t channel;
    
public:
    // https://github.com/espressif/esp-idf/blob/v4.4.1/components/driver/include/driver/adc.h
    void adc_init(adc1_channel_t canal);
    void check_efuse(void);
    void print_char_val_type(esp_adc_cal_value_t val_type);
    void read_adc();

    uint32_t read();

};

#endif