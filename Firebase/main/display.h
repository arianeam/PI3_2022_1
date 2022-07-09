#ifndef DISPLAY_H
#define DISPLAY_H

#include "freertos/FreeRTOS.h"
#include <freertos/task.h>
#include <stdio.h>
#include <iostream>
#include <driver/gpio.h>
#include <driver/i2c.h>
#include <esp_err.h>
#include <ssd1306/ssd1306.h>
#include <fonts/fonts.h>
#include <stdlib.h>
#include <../components/ESP32-RTOS-SSD1306/ssd1306/ssd1306.h>

#include "config.h"
#include <../components/ESP32-RTOS-FONTS/fonts/fonts.h>
#include "display.h"

#define I2C_MASTER_SCL_IO 22        /*!< GPIO number used for I2C master clock */
#define I2C_MASTER_SDA_IO 21        /*!< GPIO number used for I2C master data  */
#define I2C_MASTER_NUM 0            /*!< I2C master i2c port number, the number of i2c peripheral interfaces available will depend on the chip */
#define I2C_MASTER_FREQ_HZ 400000   /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE 0 /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE 0 /*!< I2C master doesn't need buffer */
#define I2C_MASTER_TIMEOUT_MS 1000

class display
{
private:
    typedef enum
    {
        NAO_INICIADO = -1,
        DISPLAY_OK = 0,
        ERRO,
    } display_status_t;

    ssd1306_t Display;

    const font_info_t *font = NULL;
    uint8_t buffer[DISPLAY_WIDTH * DISPLAY_HEIGHT / 8];

public:
    void init();
    
    void write(const char *str, uint8_t x, uint8_t y);
    void write(float num, uint8_t x, uint8_t y);
    void load_bitmap(unsigned char *bitmap);
    void clear_buffer(void);
};

#endif