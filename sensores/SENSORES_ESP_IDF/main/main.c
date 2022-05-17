#include <stdio.h>

#include "dht.h"
//#include "sdkconfig.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

void task_dht (void *pvParameters);

void app_main(void)
{
    xTaskCreate(task_dht, "task_dht", configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);
}


void task_dht (void *pvParameters) {
    
    float temperatura, umidade;

    gpio_set_pull_mode(18, GPIO_PULLUP_ONLY);


    while (1)
    {
        if (dht_read_float_data(DHT_TYPE_DHT11, 18, &umidade, &temperatura) == ESP_OK)
            printf("Umidade: %.1f%% Temp: %.1fC\n", umidade, temperatura);
        else
            printf("Erro ao ler dados do sensor dht11\n");
        
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}