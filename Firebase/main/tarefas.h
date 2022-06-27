#ifndef TAREFAS_H
#define TAREFAS_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"

#include "../components/dht/dht.h"
#include "display.h"
#include "sorriso.h"

void task_display(void *pvParameters);
void task_dht(void *pvParameters);

#endif