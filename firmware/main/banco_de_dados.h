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
#include "config.h"
#include "esp_log.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"

#define TAG "BANCO_DE_DADOS"

class BancoDeDados
{
private:
    bool connection_state;

    std::string mac = "";
    void read_mac_address(void);
    // void json_str_bd(void);

    std::string sensor_data[5]; // 0-temperatura lida, 1-umidade solo, 2-luminosidade,3-umidade ar, 4-bateria

    std::string temperatura, umidade;

    std::string data_received;

public:
    std::string get_mac_address(void);

    void banco_de_dados_init(void);

    esp_err_t publish_data(std::string key, uint8_t value);
    esp_err_t publish_data(std::string key, uint16_t value);
    esp_err_t publish_data(std::string key, float value);
    esp_err_t publish_data(std::string key, std::string value);

    // get data db
    std::string get_data_bd(std::string key);

    
    std::string get_sensor_data(int index);

    void set_sensor_data(int index, uint8_t value);
    void set_sensor_data(int index, uint16_t value);
    void set_sensor_data(int index, float value);
    void set_sensor_data(int index, std::string value);
};

#endif