#include <iostream>
#include <stdio.h>
#include <esp_err.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "jsoncpp/value.h"
#include "jsoncpp/json.h"
#include "esp_firebase/esp_firebase.h"
#include "wifi_utils.h"
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

static uint8_t led_state;
std::string emote_status = FELIZ;
int8_t count = 0;

//-----tasks---------------------
// void task_dht(void *pvParameters);
// void task_adc(void *pvParameters);
// void task_db(void *pvParameters); // Atualiza o banco de dados
// void task_parametros_ideais(void *pvParameters);
// void task_status_planta(void *pvParameters);

void task_display(void *pvParameters);
void task_sensores(void *pvParameters);

//---------------------------

extern "C"
{
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

    /**
     * @brief Task dos sensores
     * 
     * @param pvParameters 
     */
    void task_sensores(void *pvParameters)
    {
        luximeter_init();
        battery_measure_init();
        umidade_solo_init();

        uint8_t contador_lux, contador_bat, contador_solo;

        while (1)
        {
            if(contador_lux++ == 5)
            {
                contador_lux = 0;
                printf ("minosidade = %f lux\n",luximeter_read());
                printf ("Faixa %s\n", obter_faixa_luminosidade().c_str());
            }

            if(contador_bat++ == 10)
            {
                contador_bat = 0;
                measure_battery();
            }

            if(contador_solo++ == 30)
            {
                contador_solo = 0;
                ler_umidade_solo();
            }

            vTaskDelay(1000/portTICK_PERIOD_MS);

        }
        
    }


    void app_main(void)
    {
        gpio_set_direction(LED_STATUS, GPIO_MODE_OUTPUT);
        gpio_set_direction(LED_1, GPIO_MODE_OUTPUT);

        gpio_set_level(LED_STATUS, 1);
        gpio_set_level(LED_1, 1);

        display1.init();
        display1.load_bitmap(triste[0]);

        wifiInit(SSID, PASSWORD); // blocking until it connects

        gpio_set_level(LED_1, 0);

        // BancoDeDados bd;
        bd.banco_de_dados_init();

        xTaskCreatePinnedToCore(task_display, "task_display", configMINIMAL_STACK_SIZE * 5, NULL, 5, NULL, PRO_CPU_NUM);

        vTaskDelay(500 / portTICK_PERIOD_MS);

        gpio_set_level(LED_STATUS, 0);

        xTaskCreate(task_sensores, "task_sensores", configMINIMAL_STACK_SIZE * 5, NULL, 5, NULL);

        // xTaskCreate(task_adc, "task_adc", configMINIMAL_STACK_SIZE * 10, NULL, 5, NULL);
        // xTaskCreate(task_parametros_ideais, "task_parametros_ideais", configMINIMAL_STACK_SIZE * 8, NULL, 5, NULL);
        // xTaskCreate(task_dht, "task_dht", configMINIMAL_STACK_SIZE * 10, NULL, 5, NULL);
        // xTaskCreate(task_db, "task_db", configMINIMAL_STACK_SIZE * 10, NULL, 5, NULL);
        // xTaskCreate(task_status_planta, "task_status_planta", configMINIMAL_STACK_SIZE * 5, NULL, 5, NULL);

        //------testes-------------------
        bd.set_sensor_data(UMIDADE_SOLO, "seco");
        bd.set_sensor_data(LUMINOSIDADE, "sombra");
        //----------------------------------

        while (1)
        {
            led_state = !led_state;
            gpio_set_level(LED_STATUS, led_state);
            vTaskDelay(500 / portTICK_PERIOD_MS);
        }
    }

    void task_status_planta(void *pvParameters)
    {
        std::string leitura_sensores;

        while (1)
        {
            // leitura_sensores = bd.get_sensor_data(TEMPERATURA); // temperatura lida
            //  printf("LEITURAS SENSORES %f \n", std::stof(leitura_sensores));
            // if (std::stof(leitura_sensores) < parametros_ideais.temperatura_minima)
            // {

            //     if (count >= 0 && count < 3)
            //     {
            //         count++;
            //     }

            //     // emote_status = FRIO;
            // }
            // else if (std::stof(leitura_sensores) > parametros_ideais.temperatura_maxima)
            // {
            //     if (count < 3)
            //     {
            //         count++;
            //     }
            //     // emote_status = CALOR;
            // }
            // // else
            // // {
            // //     if (count > 0)
            // //     {
            // //         count--;
            // //     }
            // // }

            // leitura_sensores = bd.get_sensor_data(UMIDADE_SOLO); // umidade solo
            //  printf("LEITURAS SENSORES %s\n ", leitura_sensores.c_str());
            // if (leitura_sensores != parametros_ideais.umidade_ideal_solo)
            // {
            //     if (count < 3)
            //     {
            //         count++;
            //     } // emote_status =
            // }
            // // else
            // // {
            // //     if (count > 0)
            // //     {
            // //         count--;
            // //     }
            // // }

            // leitura_sensores = bd.get_sensor_data(LUMINOSIDADE); // luminosidade
            //  printf("LEITURAS SENSORES %s\n", leitura_sensores.c_str());
            // if (leitura_sensores != parametros_ideais.luminosidade_ideal)
            // {
            //     if (count < 3)
            //     {
            //         count++;
            //     } // emote_status =
            // }
            // // else
            // // {
            // //     if (count > 0)
            // //     {
            // //         count--;
            // //     }
            // // }
            vTaskDelay(1000 / portTICK_RATE_MS);
        }
    }

    void task_display(void *pvParameters)
    {
        while (1)
        {
            uint8_t i, j;

            static unsigned int counte;

            counte++;
            if (counte == 0)
            {
                emote_status = FELIZ;
            }
            else if (counte == 5)
            {
                emote_status = TRISTE;
            }
            else if (counte == 10)
            {
                emote_status = DEFINHANDO;
            }
            else if (counte == 15)
            {
                emote_status = FRIO;
            }
            else if (counte == 20)
            {
                emote_status = CALOR;
            }
            else if (counte >= 25)
            {
                emote_status = SEDE;
                counte = 0;
            }
            printf("status planta %s\n", emote_status.c_str());
            // emote_status = SEDE;
            for (i = 0; i < 4; i++)
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
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
    }

    // void task_adc(void *pvParameters)
    // {
    //     battery_measure_init();

    //     luximeter_init();
    //     float lux;

    //     while (1)
    //     {
    //         vTaskDelay(pdMS_TO_TICKS(10000));

    //         measure_battery();

    //         lux = luximeter_read();

    //         bd.set_sensor_data(BATERIA, get_battery_percentage());
    //         bd.set_sensor_data(LUMINOSIDADE, obter_faixa_luminosidade());

    //         vTaskDelay(10000 / portTICK_RATE_MS);
    //     }
    // }

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

}