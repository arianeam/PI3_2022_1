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
uint8_t emote_status = DORMINDO;
int8_t count = 0;
std::string leitura_sensores;

long long uptime;

//-----tasks---------------------
void task_db(void *pvParameters); // Atualiza o banco de dados
void task_display(void *pvParameters);
void task_sensores(void *pvParameters);
void task_status_planta(void *pvParameters);

void atualiza_parametros(void);
void verificar_status(void);
//---------------------------

BancoDeDados bd;
display display1;

struct
{
    float temperatura_minima = -100.0;
    float temperatura_maxima = 100.0;
    std::string umidade_ideal_ar;
    std::string umidade_ideal_solo = "úmido";
    std::string umidade_regar = "seco";
    std::string luminosidade_ideal = "meia-sombra";
    std::string nome_vaso;
    int umidade_solo_index;
} parametros_lidos;

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

    if (bd.get_connection_state() == 1)
    {
        atualiza_parametros();
    }

    gpio_set_level(LED_STATUS, 0);

    xTaskCreate(task_display, "task_display", configMINIMAL_STACK_SIZE * 5, NULL, 3, NULL);
    xTaskCreate(task_sensores, "task_sensores", configMINIMAL_STACK_SIZE * 10, NULL, 4, NULL);
    xTaskCreate(task_db, "task_db", configMINIMAL_STACK_SIZE * 10, NULL, 5, NULL);
    xTaskCreate(task_status_planta, "task_status_planta", configMINIMAL_STACK_SIZE * 5, NULL, 3, NULL);

    //------testes-------------------
    bd.set_sensor_data(UMIDADE_SOLO, "úmido");
    bd.set_sensor_data(LUMINOSIDADE, "meia-sombra");
    float temp_teste = 20.0;
    bd.set_temperatura_sensor(temp_teste);
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

        bd.set_sensor_data(PLANTA, emote_status);
        // emote_status = OFUSCADO;

        for (i = 0; i < 4; i++)
        {
            for (j = 0; j < 8; j++)
            {
                switch (emote_status)
                {
                case TRISTE:
                    display1.load_bitmap(triste[j]);
                    count = 0;
                    break;
                case SEDE:
                    display1.load_bitmap(sede[j]);
                    count = 0;
                    break;
                case FELIZ:
                    display1.load_bitmap(feliz[j]);
                    count = 0;
                    break;
                case DEFINHANDO:
                    display1.load_bitmap(definhando[j]);
                    count = 0;
                    break;
                case FRIO:
                    display1.load_bitmap(frio[j]);
                    count = 0;
                    break;
                case CALOR:
                    display1.load_bitmap(calor[j]);
                    count = 0;
                    break;
                case DORMINDO:
                    display1.load_bitmap(dormindo[j]);
                    count = 0;
                    break;
                case ENCHARCADO:
                    display1.load_bitmap(encharcado[j]);
                    count = 0;
                    break;
                case PALIDO:
                    display1.load_bitmap(palido[j]);
                    count = 0;
                    break;
                case OFUSCADO:
                    display1.load_bitmap(ofuscado[j]);
                    count = 0;
                    break;
                default:
                    break;
                }

                vTaskDelay(50 / portTICK_PERIOD_MS);
            }
            vTaskDelay(500 / portTICK_PERIOD_MS);
        }
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

/**
 * @brief Atualiza os valores definidos no aplicativo
 */
void atualiza_parametros(void)
{
    printf("Atualizando valores lidos");
    parametros_lidos.temperatura_minima = std::stof(bd.get_data_bd("temperatura_ideal_min"));
    parametros_lidos.temperatura_maxima = std::stof(bd.get_data_bd("temperatura_ideal_max"));
    parametros_lidos.umidade_ideal_solo = bd.get_data_bd("umidade_ideal_solo");
    parametros_lidos.luminosidade_ideal = bd.get_data_bd("luminosidade_ideal");
    parametros_lidos.umidade_regar = bd.get_data_bd("umidade_regar");
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

        if (bd.publish_data(FB_UPTIME, std::to_string(uptime)) == ESP_OK)
        {
            printf("Uptime OK\n");
        }

        static unsigned int counter;

        if (counter++ >= 3)
        {
            counter = 0;
            atualiza_parametros();
        }

        vTaskDelay(pdMS_TO_TICKS(5000));
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
            // bd.set_sensor_data(LUMINOSIDADE, "sombra");
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
            //bd.set_sensor_data(UMIDADE_SOLO, "seco");
        }

        if (contador_temperatura++ == 10)
        {
            contador_temperatura = 0;
            if (dht_read_float_data(DHT_TYPE_DHT11, DHT_PIN, &umidade, &temperatura) == ESP_OK)
            {
                printf("Umidade: %.1f%% Temp: %.1fC\n", umidade, temperatura);
                // bd.set_sensor_data(TEMPERATURA, temperatura);
                // bd.set_sensor_data(UMIDADE_AR, umidade);

                // bd.set_sensor_data(TEMPERATURA, 20);
            }
            else
            {
                printf("Erro ao ler dados do sensor dht11\n");
            }
        }

        uptime += 5;
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void task_status_planta(void *pvParameters)
{

    while (1)
    {
        verificar_status();

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void verificar_status(void)
{
    uint8_t status_temporario = FELIZ;

    float temp = bd.get_temperatura_sensor();
    printf("TEMPERATURA SENSOR %f\n", temp);

    if (temp < parametros_lidos.temperatura_minima)
    {
        if (count < 3)
        {
            count++;
        }

        status_temporario = FRIO;
    }
    else if (temp > parametros_lidos.temperatura_maxima)
    {
        if (count < 3)
        {
            count++;
        }
        status_temporario = CALOR;
    }

    leitura_sensores = bd.get_sensor_data(UMIDADE_SOLO); // umidade solo
    leitura_sensores = "\"" + leitura_sensores + "\""; // devido o kodular inserir aspas nas strings comparadas aqui
    // printf("UMIDADE SOLO SENSOR %s\n", leitura_sensores.c_str());

    // printf("UMIDADE IDEAL SOLO  %s\n", parametros_lidos.umidade_ideal_solo.c_str());

    // printf("UMIDADE REGAR  %s\n", parametros_lidos.umidade_regar.c_str());

    if (leitura_sensores != parametros_lidos.umidade_ideal_solo)
    {
        //printf("\n\nDIFERENTE\n\n");
        if (count < 3)
        {
            count++;
        }

        if (leitura_sensores == parametros_lidos.umidade_regar)
        {
            status_temporario = SEDE;
        }
        else if (leitura_sensores != parametros_lidos.umidade_regar)
        {

            status_temporario = ENCHARCADO;
        }
    }

    leitura_sensores = bd.get_sensor_data(LUMINOSIDADE); // luminosidade
    leitura_sensores = "\"" + leitura_sensores + "\"";   // devido o kodular inserir aspas nas strings comparadas aqui
    printf("LUMINOSIDADE SENSOR %s\n", leitura_sensores.c_str());
    printf("LUMINOSIDADE IDEAL %s\n", leitura_sensores.c_str());

    if (leitura_sensores != parametros_lidos.luminosidade_ideal)
    {
        if (leitura_sensores != "\"escuro\"")
        {

            if (count < 3)
            {
                count++;
            }

            if (parametros_lidos.luminosidade_ideal == "\"sombra\"")
            {
                status_temporario = OFUSCADO;
            }
            else if (parametros_lidos.luminosidade_ideal == "\"meia-sombra\"" && leitura_sensores == "\"sombra\"")
            {
                status_temporario = PALIDO;
            }
            else if (parametros_lidos.luminosidade_ideal == "\"meia-sombra\"" && leitura_sensores == "\"sol-pleno\"")
            {
                status_temporario = OFUSCADO;
            }
            else
            {
                status_temporario = PALIDO;
            }
        }
    }
    emote_status = status_temporario;

    switch (count)
    {
    case 0:
        emote_status = FELIZ;
        break;
    case 2:
        emote_status = TRISTE;
        break;
    case 3:
        emote_status = DEFINHANDO;
        break;
    default:
        break;
    }

    printf("STATUS %d\n", emote_status);
}