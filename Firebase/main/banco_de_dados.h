#ifndef BANCO_DE_DADOS_H
#define BANCO_DE_DADOS_H

#include "freertos/FreeRTOS.h"
#include <freertos/task.h>
#include <stdio.h>
#include <iostream>
#include <esp_err.h>
#include <stdlib.h>
#include <esp_err.h>
#include "esp_mac.h"
#include "esp_log.h"
#include <string.h>

#define TAG "BASE_MAC"

class BancoDeDados
{
private:
    std::string mac = " ";

    void read_mac_address(void);

public:
    std::string get_mac_address(void);
};

#endif