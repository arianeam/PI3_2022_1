#include "tarefas.h"

void task_display(void *pvParameters)
{
    ESP_LOGI("Display", "Iniciando... ");

    display display1;
    display1.display_init();
    ESP_LOGI("Display", "OK!");

    while (1)
    {
        uint8_t i, j;

        for (i = 0; i < 20; i++)
        {
            for (j = 3; j > 0; j--)
            {
                display1.display_load_bitmap(sorriso[j]);
                vTaskDelay(50 / portTICK_PERIOD_MS);
            }
        }
        // vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void task_dht(void *pvParameters)
{
    // dht11 dht11_1;
    // dht11_1.dht11_init();
    float temperatura = -100;
    float umidade = -100;
    gpio_set_pull_mode(GPIO_NUM_18, GPIO_PULLUP_ONLY);

    while (1)
    {
        // dht11_1.read_dht11();
        // temperatura = dht11_1.get_temp();
        // umidade = dht11_1.get_umid();
        // printf("Umidade recebida: %.1f%% Temperatura recebida: %.1fC\n", umidade, temperatura);
        // vTaskDelay(pdMS_TO_TICKS(2000));
        if (dht_read_float_data(DHT_TYPE_DHT11, GPIO_NUM_18, &umidade, &temperatura) == ESP_OK)
        {
            printf("Umidade: %.1f%% Temp: %.1fC\n", umidade, temperatura);
        }
        else
        {
            printf("Erro ao ler dados do sensor dht11\n");
        }
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}