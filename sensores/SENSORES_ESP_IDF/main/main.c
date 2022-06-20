#include <stdio.h>
#include <stdlib.h>
#include "dht.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include "driver/gpio.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"

#include "display.h"
#include "sorriso.h"
#include "comunicacao.h"

//----------------------------------
/* Firebase */

#include <../components/jsoncpp/value.h>
#include <../components/jsoncpp/json.h>

#include "../components/esp_firebase/esp_firebase.h"
#include "wifi_utils.h"

#include "firebase_config.h"

//----------------------------------

#define DEFAULT_VREF 1100 // Use adc2_vref_to_gpio() to obtain a better estimate
#define NO_OF_SAMPLES 64  // Multisampling
static const adc_atten_t atten = ADC_ATTEN_DB_11;
static const adc_unit_t unit = ADC_UNIT_1;

static esp_adc_cal_characteristics_t *adc_chars;

//------Config. ESP 32----------------------------------------------------------
static const adc_channel_t channel = ADC_CHANNEL_6; // GPIO34 if ADC1, GPIO14 if ADC2
static const adc_bits_width_t width = ADC_WIDTH_BIT_12;
//-----------------------------------------------------------------------------

//--------------Protótipos das funções---------------------
static void print_char_val_type(esp_adc_cal_value_t val_type);
static void check_efuse(void);
//---------------------------------------------------------

// -------------Protótipos das tarefas (tasks)------------
void task_dht(void *pvParameters);
void task_teste_queue(void *pvParameters);
void task_adc_hl_69(void *pvParameters);
void task_display(void *pvParameters);
//--------------------------------------------------------

//------------struct e fila para passagem dos dados do DHT11 para o display-------------
struct DHT11_param
{
    float umid;
    float temp;

} dht11_parametros;

QueueHandle_t xQueue_dht11;
//---------------------------------------------------------------------------------------

//-----------Main------------------------------------------
void app_main(void)
{
    //----------------------------------------
    /*
    Trecho disponível no exemplo "adc1_example_main.c" do fabricante Espressif
    que pode ser encontrada no link:
    https://github.com/espressif/esp-idf/tree/master/examples/peripherals/adc/single_read/adc
    */
    // Check if Two Point or Vref are burned into eFuse
    check_efuse();

    display_init();

    wifi_init();

    // Configure ADC
    adc1_config_width(width);
    adc1_config_channel_atten(channel, atten);

    // Characterize ADC
    adc_chars = calloc(1, sizeof(esp_adc_cal_characteristics_t));
    esp_adc_cal_value_t val_type = esp_adc_cal_characterize(unit, atten, width, DEFAULT_VREF, adc_chars);
    print_char_val_type(val_type);
    //------------------------------------------

    xTaskCreate(task_dht, "task_dht", configMINIMAL_STACK_SIZE * 5, NULL, 5, NULL);
    xTaskCreate(task_teste_queue, "task_teste_queue", configMINIMAL_STACK_SIZE * 5, NULL, 5, NULL);
    xTaskCreate(task_adc_hl_69, "task_adc_hl_69", configMINIMAL_STACK_SIZE * 5, NULL, 5, NULL);
    xTaskCreate(task_display, "task_display", configMINIMAL_STACK_SIZE * 5, NULL, 5, NULL);
}
//---------------------------------------------------------

//---------Implementação das tarefas (tasks)----------------
void task_dht(void *pvParameters)
{

    struct DHT11_param dht11_parametros_lidos;

    gpio_set_pull_mode(18, GPIO_PULLUP_ONLY);

    xQueue_dht11 = xQueueCreate(10, sizeof(struct DHT11_param));

    if (xQueue_dht11 == 0)
    {
        printf("Erro ao criar fila!");
    }

    while (1)
    {
        if (dht_read_float_data(DHT_TYPE_DHT11, 18, &(dht11_parametros_lidos.umid), &(dht11_parametros_lidos.temp)) == ESP_OK)
        {

            printf("Umidade: %.1f%% Temp: %.1fC\n", dht11_parametros_lidos.umid, dht11_parametros_lidos.temp);

            xQueueSend(xQueue_dht11, (void *)&dht11_parametros_lidos, (TickType_t)10);
        }

        else
            printf("Erro ao ler dados do sensor dht11\n");

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void task_teste_queue(void *pvParameters)
{
    struct DHT11_param dht11_receber_parametros;

    // display_init();

    while (1)
    {

        if (xQueue_dht11 != 0)
        {

            if (xQueueReceive(xQueue_dht11, &(dht11_receber_parametros), (TickType_t)10))
            {
                printf("Umidade recebida: %.1f%% Temp recebida: %.1fC\n", dht11_receber_parametros.umid, dht11_receber_parametros.temp);
                // display_write_float(dht11_receber_parametros.temp,64,28);
            }
            else
            {

                printf("Erro ao receber fila!");
            }
        }
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void task_adc_hl_69(void *pvParameters)
{
    while (1)
    {
        uint32_t adc_reading = 0;
        // Multisampling
        for (int i = 0; i < NO_OF_SAMPLES; i++)
        {
            if (unit == ADC_UNIT_1)
            {
                adc_reading += adc1_get_raw((adc1_channel_t)channel);
            }
            else
            {
                int raw;
                adc2_get_raw((adc2_channel_t)channel, width, &raw);
                adc_reading += raw;
            }
        }
        adc_reading /= NO_OF_SAMPLES;
        // Convert adc_reading to voltage in mV
        uint32_t voltage = esp_adc_cal_raw_to_voltage(adc_reading, adc_chars);
        printf("Raw: %d\tVoltage: %dmV\n", adc_reading, voltage);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void task_display(void *pvParameters)
{
    while (1)
    {

        uint8_t i, j;

        for (i = 0; i < 20; i++)
        {
            for (j = 3; j > 0; j--)
            {
                display_load_bitmap(sorriso[j]);
                vTaskDelay(50 / portTICK_PERIOD_MS);
            }
        }

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
//--------------------------------------------------------------------

//------------Implementação das funções-------------------------------

/*
Função disponível no exemplo "adc1_example_main.c" do fabricante Espressif
que pode ser encontrada no link:
https://github.com/espressif/esp-idf/tree/master/examples/peripherals/adc/single_read/adc
*/
static void check_efuse(void)
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

/*
Função disponível no exemplo "adc1_example_main.c" do fabricante Espressif
que pode ser encontrada no link:
https://github.com/espressif/esp-idf/tree/master/examples/peripherals/adc/single_read/adc
*/
static void print_char_val_type(esp_adc_cal_value_t val_type)
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

//--------------------------------------------------------------------