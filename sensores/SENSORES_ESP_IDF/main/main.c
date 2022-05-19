#include <stdio.h>

#include "dht.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

// -------------Protótipos das tarefas (tasks)------------
void task_dht(void *pvParameters);
void task_teste_queue(void *pvParameters);
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
    xTaskCreate(task_dht, "task_dht", configMINIMAL_STACK_SIZE * 5, NULL, 5, NULL);
    xTaskCreate(task_teste_queue, "task_teste_queue", configMINIMAL_STACK_SIZE * 5, NULL, 5, NULL);
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

    while (1)
    {

        if (xQueue_dht11 != 0)
        {

            if (xQueueReceive(xQueue_dht11, &(dht11_receber_parametros), (TickType_t)10))
            {
                printf("Umidade recebida: %.1f%% Temp recebida: %.1fC\n", dht11_receber_parametros.umid, dht11_receber_parametros.temp);
            }
            else
            {

                printf("Erro ao receber fila!");
            }
        }
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

//--------------------------------------------------------------------