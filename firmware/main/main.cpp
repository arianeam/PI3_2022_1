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
std::string emote_status = DORMINDO;
int8_t count = 0;
std::string leitura_sensores;

//-----tasks---------------------
// void task_status_planta(void *pvParameters);

void task_parametros_lidos(void *pvParameters);

void task_db(void *pvParameters); // Atualiza o banco de dados
void task_display(void *pvParameters);
void task_sensores(void *pvParameters);
void task_status_planta(void *pvParameters);

//---------------------------

BancoDeDados bd;
display display1;

// void atualiza_valores_lidos(void)
// {
//     printf("\n---- %s -----\n", bd.get_data_bd("temperatura_ideal_min").c_str());
// }

struct
{
    float temperatura_minima;
    float temperatura_maxima;
    std::string umidade_ideal_ar;
    std::string umidade_ideal_solo;
    std::string umidade_regar;
    std::string luminosidade_ideal;
    std::string nome_vaso;
    int umidade_solo_index;
} parametros_lidos;

// void monitora_planta(void)
// {
//     float temperatura = std::stof(bd.get_sensor_data(TEMPERATURA));

//     if (temperatura < parametros_lidos.temperatura_minima)
//     {
//         emote_status = FRIO;
//     }
//     else if (temperatura > parametros_lidos.temperatura_maxima)
//     {
//         emote_status = CALOR;
//     }
// }

extern "C" void app_main(void)
{
    gpio_set_direction(LED_STATUS, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_COMUNICACAO, GPIO_MODE_OUTPUT);

    gpio_set_level(LED_STATUS, 1);
    gpio_set_level(LED_COMUNICACAO, 1);

    display1.init();

    wifiInit(SSID, PASSWORD);
    gpio_set_level(LED_COMUNICACAO, 0);

    bd.banco_de_dados_init();

    // atualiza_valores_lidos();

    vTaskDelay(2000 / portTICK_PERIOD_MS);

    gpio_set_level(LED_STATUS, 0);

    xTaskCreate(task_display, "task_display", configMINIMAL_STACK_SIZE * 5, NULL, 5, NULL);
    xTaskCreate(task_sensores, "task_sensores", configMINIMAL_STACK_SIZE * 10, NULL, 5, NULL);

    xTaskCreate(task_parametros_lidos, "task_parametros_lidos", configMINIMAL_STACK_SIZE * 10, NULL, 5, NULL);

    xTaskCreate(task_db, "task_db", configMINIMAL_STACK_SIZE * 10, NULL, 5, NULL);

    // xTaskCreate(task_status_planta, "task_status_planta", configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);

    //------testes-------------------
    bd.set_sensor_data(UMIDADE_SOLO, "seco");
    bd.set_sensor_data(LUMINOSIDADE, "sombra");
    bd.set_sensor_data(TEMPERATURA, 25);

    //----------------------------------

    while (1)
    {
        led_state = !led_state;
        gpio_set_level(LED_STATUS, led_state);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

void task_display(void *pvParameters)
{

    while (1)
    {
        uint8_t i, j;

        if(count==0){
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

        // static unsigned int counte = 0;

        // counte++;
        // if (counte == 0)
        // {
        //     emote_status = FELIZ;
        // }
        // else if (counte == 5)
        // {
        //     emote_status = TRISTE;
        // }
        // else if (counte == 10)
        // {
        //     emote_status = DEFINHANDO;
        // }
        // else if (counte == 15)
        // {
        //     emote_status = FRIO;
        // }
        // else if (counte == 20)
        // {
        //     emote_status = CALOR;
        // }
        // else if (counte == 25)
        // {
        //     emote_status = SEDE;
        // }
        // else if (counte == 30)
        // {
        //     emote_status = ENCHARCADO;
        // }
        // else if (counte == 35)
        // {
        //     emote_status = PALIDO;
        // }
        // else if (counte == 40)
        // {
        //     emote_status = DORMINDO;
        // }
        // else if (counte >= 45)
        // {
        //     emote_status = OFUSCADO;
        //     counte = 0;
        // }
        printf("status planta %s\n", emote_status.c_str());
        bd.set_sensor_data(PLANTA, emote_status);

        for (i = 0; i < 4; i++)
        {
            for (j = 9; j > 0; j--)
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
                else if (emote_status == "dormindo")
                {
                    display1.load_bitmap(dormindo[j]);
                }
                else if (emote_status == "encharcado")
                {
                    display1.load_bitmap(encharcado[j]);
                }
                else if (emote_status == "palido")
                {
                    display1.load_bitmap(palido[j]);
                }
                else if (emote_status == "ofuscado")
                {
                    display1.load_bitmap(ofuscado[j]);
                }

                vTaskDelay(50 / portTICK_PERIOD_MS);
            }
            vTaskDelay(500 / portTICK_PERIOD_MS);
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void task_parametros_lidos(void *pvParameters)
{

    while (1)
    {
        vTaskDelay(10000 / portTICK_RATE_MS);
        // parametros_lidos.luminosidade_ideal = std::stof()
        parametros_lidos.temperatura_minima = std::stof(bd.get_data_bd("temperatura_ideal_min"));
        parametros_lidos.temperatura_maxima = std::stof(bd.get_data_bd("temperatura_ideal_max"));
        parametros_lidos.umidade_ideal_solo = bd.get_data_bd("umidade_ideal_solo");
        parametros_lidos.luminosidade_ideal = bd.get_data_bd("luminosidade_ideal");
        parametros_lidos.umidade_regar = bd.get_data_bd("umidade_regar");

        vTaskDelay(10000 / portTICK_RATE_MS);
    }
}

void task_db(void *pvParameters)
{
    while (1)
    {
        // index: 0-temperatura lida, 1-umidade solo, 2-luminosidade,3-umidade ar, 4-bateria
        vTaskDelay(1000 / portTICK_RATE_MS);

        if (bd.publish_data(FB_TEMPERATURA_LIDA, bd.get_sensor_data(TEMPERATURA)) == ESP_OK)
        {
            printf("Temp OK\n");
        }

        if (bd.publish_data(FB_UMIDADE_AR_LIDA, bd.get_sensor_data(UMIDADE_AR)) == ESP_OK)
        {
            printf("Umidade OK\n");
        }

        if (bd.publish_data(FB_STATUS_BATERIA, bd.get_sensor_data(BATERIA)) == ESP_OK)
        {
            printf("Bateria OK\n");
        }

        if (bd.publish_data(FB_UMIDADE_SOLO_LIDA, bd.get_sensor_data(UMIDADE_SOLO)) == ESP_OK)
        {
            printf("Umidade solo OK\n");
        }

        if (bd.publish_data(FB_LUMINOSIDADE_LIDA, bd.get_sensor_data(LUMINOSIDADE)) == ESP_OK)
        {
            printf("Umidade solo OK\n");
        }

        if (bd.publish_data(FB_STATUS_PLANTA, bd.get_sensor_data(PLANTA)) == ESP_OK)
        {
            printf("Status planta OK\n");
        }

        vTaskDelay(pdMS_TO_TICKS(10000));
    }
}

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

    /* DHT11 */
    float temperatura = -100;
    float umidade = -100;
    gpio_set_pull_mode(DHT_PIN, GPIO_PULLUP_ONLY);

    uint8_t contador_lux, contador_bat, contador_solo, contador_temperatura;
    contador_lux = 0;
    contador_bat = 0;
    contador_solo = 0;
    contador_temperatura = 0;

    while (1)
    {
        if (contador_lux++ == 5)
        {
            contador_lux = 0;
            printf("Luminosidade = %f lux\n", luximeter_read());
            // bd.set_sensor_data(LUMINOSIDADE, obter_faixa_luminosidade());
            bd.set_sensor_data(LUMINOSIDADE, "sombra");
        }

        if (contador_bat++ == 10)
        {
            contador_bat = 0;
            measure_battery();
            bd.set_sensor_data(BATERIA, get_battery_percentage());
        }

        if (contador_solo++ == 30)
        {
            contador_solo = 0;
            // bd.set_sensor_data(UMIDADE_SOLO, ler_umidade_solo());
            bd.set_sensor_data(UMIDADE_SOLO, "seco");
        }

        if (contador_temperatura++ == 10)
        {
            contador_temperatura = 0;
            if (dht_read_float_data(DHT_TYPE_DHT11, DHT_PIN, &umidade, &temperatura) == ESP_OK)
            {
                printf("Umidade: %.1f%% Temp: %.1fC\n", umidade, temperatura);
                // bd.set_sensor_data(TEMPERATURA, temperatura);
                // bd.set_sensor_data(UMIDADE_AR, umidade);

                bd.set_sensor_data(TEMPERATURA, 20);
            }
            else
            {
                printf("Erro ao ler dados do sensor dht11\n");
            }
        }

        leitura_sensores = bd.get_sensor_data(TEMPERATURA); // temperatura lida
        printf("LEITURAS SENSORES %f \n", std::stof(leitura_sensores));
        if (std::stof(leitura_sensores) < parametros_lidos.temperatura_minima)
        {
            if (count >= 0 && count < 3)
            {
                count++;
            }

            emote_status = FRIO;
        }
        else if (std::stof(leitura_sensores) > parametros_lidos.temperatura_maxima)
        {
            if (count < 3)
            {
                count++;
            }
            emote_status = CALOR;
        }

        leitura_sensores = bd.get_sensor_data(UMIDADE_SOLO); // umidade solo
        printf("LEITURAS SENSORES %s\n ", leitura_sensores.c_str());
        if (leitura_sensores != parametros_lidos.umidade_ideal_solo)
        {
            if (count < 3)
            {
                count++;
            }

            if (leitura_sensores == parametros_lidos.umidade_regar)
            {
                emote_status = SEDE;
            }
            else
            {

                emote_status = ENCHARCADO;
            }
        }

        leitura_sensores = bd.get_sensor_data(LUMINOSIDADE); // luminosidade
        printf("LEITURAS SENSORES %s\n", leitura_sensores.c_str());
        if (leitura_sensores != parametros_lidos.luminosidade_ideal)
        {
            if (leitura_sensores != "escuro")
            {

                if (count < 3)
                {
                    count++;
                }

                if (parametros_lidos.luminosidade_ideal == "sombra")
                {
                    emote_status = OFUSCADO;
                    
                }
                else if (parametros_lidos.luminosidade_ideal == "meia-sombra" && leitura_sensores == "sombra")
                {
                    emote_status = PALIDO;
                    
                }
                else if (parametros_lidos.luminosidade_ideal == "meia-sombra" && leitura_sensores == "sol-pleno")
                {
                    emote_status = OFUSCADO;
                    
                }
                else
                {
                    emote_status = PALIDO;
                    
                }
            }
        }

        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}

void task_status_planta(void *pvParameters)
{

    while (1)
    {

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}