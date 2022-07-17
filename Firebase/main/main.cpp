#include <iostream>
#include <stdio.h>

#include <esp_err.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "jsoncpp/value.h"
#include "jsoncpp/json.h"
#include "esp_firebase/esp_firebase.h"
#include "wifi_utils.h"
#include "firebase_config.h"
#include "esp_log.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"

#include "../components/dht/dht.h"
#include "display.h"
#include "sorriso.h"
#include "adc_1.h"
#include "banco_de_dados.h"
#include "sensores.h"

static uint8_t state;

#define DHT_ON
#define DISPLAY_ON

//-----tasks---------------------
void task_display(void *pvParameters);
void task_dht(void *pvParameters);
void task_adc(void *pvParameters);
void task_db(void *pvParameters); // Atualiza o banco de dados
void task_parametros_ideais(void *pvParameters);
void task_status_planta(void *pvParameters);

//---------------------------

#define LED_STATUS GPIO_NUM_25
#define LED_1 GPIO_NUM_26
#define DHT_PIN GPIO_NUM_27

BancoDeDados bd;
display display1;

struct
{
    float temperatura_minima;
    float temperatura_maxima;
    std::string umidade_ideal_ar;
    std::string umidade_ideal_solo;
    std::string luminosidade_ideal;
    std::string nome_vaso;
} parametros_ideais;

extern "C" void app_main(void)
{
    gpio_set_direction(LED_STATUS, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_1, GPIO_MODE_OUTPUT);

    gpio_set_level(LED_STATUS, 1);
    gpio_set_level(LED_1, 1);

    wifiInit(SSID, PASSWORD); // blocking until it connects

    gpio_set_level(LED_1, 0);

    display1.init();
    // BancoDeDados bd;
    bd.banco_de_dados_init();

#ifdef DISPLAY_ON
    xTaskCreate(task_display, "task_display", configMINIMAL_STACK_SIZE * 5, NULL, 5, NULL);
#endif

    vTaskDelay(500 / portTICK_PERIOD_MS);

    // parametros_ideais.temperatura_minima = std::stof(bd.get_data_bd("temperatura_ideal_min"));
    // parametros_ideais.temperatura_maxima = std::stof(bd.get_data_bd("temperatura_ideal_max"));
    // parametros_ideais.umidade_ideal_solo = bd.get_data_bd("umidade_ideal_ar");
    // parametros_ideais.luminosidade_ideal = bd.get_data_bd("luminosidade_ideal");

    gpio_set_level(LED_STATUS, 0);

    // printf("TEMP IDEAL MIN: %f -------\n", parametros_ideais.temperatura_minima);
    // printf("TEMP IDEAL MAX: %f -------\n", parametros_ideais.temperatura_maxima);
    // printf("UMIDADE IDEAL AR: %s -------\n", parametros_ideais.umidade_ideal_solo.c_str());
    // printf("LUMINOSIDADE IDEAL: %s -------\n", parametros_ideais.luminosidade_ideal.c_str());

    xTaskCreate(task_adc, "task_adc", configMINIMAL_STACK_SIZE * 10, NULL, 5, NULL);

    vTaskDelay(500 / portTICK_PERIOD_MS);

    xTaskCreate(task_parametros_ideais, "task_parametros_ideais", configMINIMAL_STACK_SIZE * 8, NULL, 5, NULL);

    // vTaskDelay(3000 / portTICK_PERIOD_MS);

#ifdef DHT_ON
    xTaskCreate(task_dht, "task_dht", configMINIMAL_STACK_SIZE * 10, NULL, 5, NULL);
#endif

    while (1)
    {
        state = !state;
        gpio_set_level(LED_STATUS, state);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }

    // xTaskCreate(task_status_planta, "task_status_planta", configMINIMAL_STACK_SIZE * 5, NULL, 5, NULL);
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
                display1.load_bitmap(sorriso[j]);
                vTaskDelay(50 / portTICK_PERIOD_MS);
            }
        }
    }
}

void task_adc(void *pvParameters)
{
    battery_measure_init();

    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(10000));

        measure_battery();

        bd.set_sensor_data(4, get_battery_percentage());

        vTaskDelay(10000 / portTICK_RATE_MS);
    }
}

void task_parametros_ideais(void *pvParameters)
{

    while (1)
    {
        vTaskDelay(10000 / portTICK_RATE_MS);

        // parametros_ideais.luminosidade_ideal = std::stof()
        parametros_ideais.temperatura_minima = std::stof(bd.get_data_bd("temperatura_ideal_min"));
        parametros_ideais.temperatura_maxima = std::stof(bd.get_data_bd("temperatura_ideal_max"));
        parametros_ideais.umidade_ideal_solo = bd.get_data_bd("umidade_ideal_ar");
        parametros_ideais.luminosidade_ideal = bd.get_data_bd("luminosidade_ideal");

        vTaskDelay(10000 / portTICK_RATE_MS);
    }
}

void task_dht(void *pvParameters)
{

    float temperatura = -100;
    float umidade = -100;
    gpio_set_pull_mode(DHT_PIN, GPIO_PULLUP_ONLY);

    while (1)
    {

        if (dht_read_float_data(DHT_TYPE_DHT11, DHT_PIN, &umidade, &temperatura) == ESP_OK)
        {
            printf("Umidade: %.1f%% Temp: %.1fC\n", umidade, temperatura);
            bd.set_sensor_data(0, temperatura);
            bd.set_sensor_data(1, umidade);
        }
        else
        {
            printf("Erro ao ler dados do sensor dht11\n");
        }
        vTaskDelay(pdMS_TO_TICKS(10000));
    }
}

void task_status_planta(void *pvParameters)
{
    std::string leitura_sensores;
    while (1)
    {
        leitura_sensores = bd.get_sensor_data(0);
        printf("leitura sensores: %s", leitura_sensores.c_str());
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}

void task_db(void *pvParameters)
{
    while (1)
    {
        vTaskDelay(1000 / portTICK_RATE_MS);

        if (bd.publish_data("temperatura_lida", bd.get_sensor_data(0)) == ESP_OK)
        {
            printf("Temp OK\n");
        }

        if (bd.publish_data("umidade_lida_ar",  bd.get_sensor_data(1)) == ESP_OK)
        {
            printf("Umidade OK\n");
        }

        if (bd.publish_data("status_bateria",  bd.get_sensor_data(4)) == ESP_OK)
        {
            printf("Bateria OK\n");
        }

        vTaskDelay(pdMS_TO_TICKS(10000));
    }
}