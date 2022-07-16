#ifndef BANCO_DE_DADOS_H
#define BANCO_DE_DADOS_H

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>
#include <iostream>
#include <esp_err.h>
#include <stdlib.h>
#include <esp_err.h>
#include "esp_mac.h"
#include "esp_log.h"
#include <string.h>

#include "jsoncpp/value.h"
#include "jsoncpp/json.h"
#include "esp_firebase/esp_firebase.h"
#include "firebase_config.h"
#include "esp_log.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"

#define TAG "BASE_MAC"

class BancoDeDados
{
private:
    std::string mac = "";
    void read_mac_address(void);
    // void json_str_bd(void);

    std::string umidade;
    std::string temperatura;

public:
    std::string get_mac_address(void);

    void banco_de_dados_init(void);
    int publish_battery_info(uint16_t mV, uint8_t percentage);
    int publish_temperature_info(float temp, float humi);
    //int publish_temperature_info(float temp, float humi);

    // int publish_temperature_info(void);
};

#endif