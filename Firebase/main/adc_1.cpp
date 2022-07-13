#include "adc_1.h"
/*
+----------+-------------+-----------------+
|          | attenuation | suggested range |
|    SoC   |     (dB)    |      (mV)       |
+==========+=============+=================+
|          |       0     |    100 ~  950   |
|          +-------------+-----------------+
|          |       2.5   |    100 ~ 1250   |
|   ESP32  +-------------+-----------------+
|          |       6     |    150 ~ 1750   |
|          +-------------+-----------------+
|          |      11     |    150 ~ 2450   |
+----------+-------------+-----------------+
|          |       0     |      0 ~  750   |
|          +-------------+-----------------+
|          |       2.5   |      0 ~ 1050   |
| ESP32-S2 +-------------+-----------------+
|          |       6     |      0 ~ 1300   |
|          +-------------+-----------------+
|          |      11     |      0 ~ 2500   |
+----------+-------------+-----------------+
*/
static const adc_atten_t atten = ADC_ATTEN_DB_11;
static const adc_bits_width_t width = ADC_WIDTH_BIT_12;
static const adc_unit_t unit = ADC_UNIT_1;
static esp_adc_cal_characteristics_t *adc_chars;

#define DEFAULT_VREF 1100 // Use adc2_vref_to_gpio() to obtain a better estimate
#define NO_OF_SAMPLES 64  // Multisampling


void adc::check_efuse(void)
{
    // Check if TP is burned into eFuse
    if (esp_adc_cal_check_efuse(ESP_ADC_CAL_VAL_EFUSE_TP) == ESP_OK)
    {
        printf("eFuse Two Point: Supported\n");
    }
    else
    {
        printf("eFuse Two Point: NOT supported\n");
    }
    // Check Vref is burned into eFuse
    if (esp_adc_cal_check_efuse(ESP_ADC_CAL_VAL_EFUSE_VREF) == ESP_OK)
    {
        printf("eFuse Vref: Supported\n");
    }
    else
    {
        printf("eFuse Vref: NOT supported\n");
    }
}

void adc::print_char_val_type(esp_adc_cal_value_t val_type)
{
    if (val_type == ESP_ADC_CAL_VAL_EFUSE_TP)
    {
        printf("Characterized using Two Point Value\n");
    }
    else if (val_type == ESP_ADC_CAL_VAL_EFUSE_VREF)
    {
        printf("Characterized using eFuse Vref\n");
    }
    else
    {
        printf("Characterized using Default Vref\n");
    }
}

void adc::adc_init(adc1_channel_t canal)
{
    //------Config. ESP 32----------------------------------------------------------
    channel = canal; // GPIO34 if ADC1, GPIO14 if ADC2
    //-----------------------------------------------------------------------------

    check_efuse();

    // Configure ADC
    adc1_config_width(width);
    adc1_config_channel_atten(channel, atten);

    // Characterize ADC
    adc_chars = (esp_adc_cal_characteristics_t *)calloc(1, sizeof(esp_adc_cal_characteristics_t));
    esp_adc_cal_value_t val_type = esp_adc_cal_characterize(unit, atten, width, DEFAULT_VREF, adc_chars);
    print_char_val_type(val_type);
    //------------------------------------------
}

void adc::read_adc()
{
    // taskENTER_CRITICAL();

    uint32_t adc_reading = 0;
    // Multisampling
    for (int i = 0; i < NO_OF_SAMPLES; i++)
    {

        adc_reading += adc1_get_raw((adc1_channel_t)channel);
    }
    adc_reading /= NO_OF_SAMPLES;
    // Convert adc_reading to voltage in mV
    uint32_t voltage = esp_adc_cal_raw_to_voltage(adc_reading, adc_chars);
    printf("Raw: %d\tVoltage: %dmV\n", adc_reading, voltage);

    // taskEXIT_CRITICAL();
}

uint32_t adc::read()
{
    // taskENTER_CRITICAL();

    uint32_t adc_reading = 0;
    // Multisampling
    for (int i = 0; i < NO_OF_SAMPLES; i++)
    {

        adc_reading += adc1_get_raw((adc1_channel_t)channel);
    }
    adc_reading /= NO_OF_SAMPLES;

    // taskEXIT_CRITICAL();

    return adc_reading;
}