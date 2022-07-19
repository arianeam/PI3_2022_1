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
#include "config.h"

#include "emocoes_ze.h"

#define DISPLAY_ON
#define DHT_ON

static uint8_t state;
std::string emote_status = FELIZ;
int8_t count = 0;
//-----tasks---------------------
void task_display(void *pvParameters);
void task_dht(void *pvParameters);
void task_adc(void *pvParameters);
void task_db(void *pvParameters); // Atualiza o banco de dados
void task_parametros_ideais(void *pvParameters);
void task_status_planta(void *pvParameters);
//---------------------------

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

    gpio_set_level(LED_STATUS, 0);

    xTaskCreate(task_adc, "task_adc", configMINIMAL_STACK_SIZE * 10, NULL, 5, NULL);

    // vTaskDelay(500 / portTICK_PERIOD_MS);

    xTaskCreate(task_parametros_ideais, "task_parametros_ideais", configMINIMAL_STACK_SIZE * 8, NULL, 5, NULL);

    // vTaskDelay(3000 / portTICK_PERIOD_MS);

#ifdef DHT_ON
    xTaskCreate(task_dht, "task_dht", configMINIMAL_STACK_SIZE * 10, NULL, 5, NULL);
#endif

    xTaskCreate(task_db, "task_db", configMINIMAL_STACK_SIZE * 10, NULL, 5, NULL);

    xTaskCreate(task_status_planta, "task_status_planta", configMINIMAL_STACK_SIZE * 5, NULL, 5, NULL);

    //------testes-------------------
    bd.set_sensor_data(UMIDADE_SOLO, "seco");
    bd.set_sensor_data(LUMINOSIDADE, "sombra");
    //----------------------------------

    while (1)
    {
        state = !state;
        gpio_set_level(LED_STATUS, state);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

void task_status_planta(void *pvParameters)
{
    std::string leitura_sensores;

    while (1)
    {
        leitura_sensores = bd.get_sensor_data(TEMPERATURA); // temperatura lida
         printf("LEITURAS SENSORES %f \n", std::stof(leitura_sensores));
        if (std::stof(leitura_sensores) < parametros_ideais.temperatura_minima)
        {
           
            if (count >= 0 && count < 3)
            {
                count++;
            }

            // emote_status = FRIO;
        }
        else if (std::stof(leitura_sensores) > parametros_ideais.temperatura_maxima)
        {
            if (count < 3)
            {
                count++;
            }
            // emote_status = CALOR;
        }
        // else
        // {
        //     if (count > 0)
        //     {
        //         count--;
        //     }
        // }


        leitura_sensores = bd.get_sensor_data(UMIDADE_SOLO); // umidade solo
         printf("LEITURAS SENSORES %s\n ", leitura_sensores.c_str());
        if (leitura_sensores != parametros_ideais.umidade_ideal_solo)
        {
            if (count < 3)
            {
                count++;
            } // emote_status =
        }
        // else
        // {
        //     if (count > 0)
        //     {
        //         count--;
        //     }
        // }

        leitura_sensores = bd.get_sensor_data(LUMINOSIDADE); // luminosidade
         printf("LEITURAS SENSORES %s\n", leitura_sensores.c_str());
        if (leitura_sensores != parametros_ideais.luminosidade_ideal)
        {
            if (count < 3)
            {
                count++;
            } // emote_status =
        }
        // else
        // {
        //     if (count > 0)
        //     {
        //         count--;
        //     }
        // }


        if (count == 0)
        {
            emote_status = FELIZ;
        }
        else if (count == 2)
        {
            emote_status = TRISTE;
            count = 0;
        }
        else if (count == 3)
        {
            emote_status = DEFINHANDO;
            count = 0;
        }
      
       
        // printf("leitura sensores: %s", leitura_sensores.c_str());
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}

void task_display(void *pvParameters)
{

    while (1)
    {
        uint8_t i, j;

        printf("stratus planta %s", emote_status.c_str());
        // emote_status = SEDE;
        for (i = 0; i < 16; i++)
        {
            for (j = 7; j > 0; j--)
            {
                if (emote_status == "triste")
                {
                    display1.load_bitmap(triste[j]);
                }
                else if (emote_status == "sede")
                {
                    display1.load_bitmap(sede[j]);
                }

                else if (emote_status == "feliz")
                {
                    display1.load_bitmap(feliz[j]);
                }
                else if (emote_status == "definhando")
                {
                    display1.load_bitmap(definhando[j]);
                }
                else if (emote_status == "frio")
                {
                    display1.load_bitmap(frio[j]);
                }
                else if (emote_status == "calor")
                {
                    display1.load_bitmap(calor[j]);
                }
              
                vTaskDelay(50 / portTICK_PERIOD_MS);
            }
            vTaskDelay(500 / portTICK_PERIOD_MS);
        }
        vTaskDelay(10000 / portTICK_PERIOD_MS);
    }
}

void task_adc(void *pvParameters)
{
    battery_measure_init();

    luximeter_init();
    float lux;

    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(10000));

        measure_battery();

        lux = luximeter_read();

        bd.set_sensor_data(BATERIA, get_battery_percentage());
        bd.set_sensor_data(LUMINOSIDADE, lux);

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
        parametros_ideais.umidade_ideal_solo = bd.get_data_bd("umidade_ideal_solo");
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
            bd.set_sensor_data(TEMPERATURA, temperatura);
            bd.set_sensor_data(UMIDADE_AR, umidade);
        }
        else
        {
            printf("Erro ao ler dados do sensor dht11\n");
        }
        vTaskDelay(pdMS_TO_TICKS(10000));
    }
}

void task_db(void *pvParameters)
{
    while (1)
    {
        // index: 0-temperatura lida, 1-umidade solo, 2-luminosidade,3-umidade ar, 4-bateria
        vTaskDelay(1000 / portTICK_RATE_MS);

        if (bd.publish_data("temperatura_lida", bd.get_sensor_data(0)) == ESP_OK)
        {
            printf("Temp OK\n");
        }

        if (bd.publish_data("umidade_lida_ar", bd.get_sensor_data(1)) == ESP_OK)
        {
            printf("Umidade OK\n");
        }

        if (bd.publish_data("status_bateria", bd.get_sensor_data(4)) == ESP_OK)
        {
            printf("Bateria OK\n");
        }

        vTaskDelay(pdMS_TO_TICKS(10000));
    }
}