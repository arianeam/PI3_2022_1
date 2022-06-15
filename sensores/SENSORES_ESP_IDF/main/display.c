/**
 * @file display.c
 * @brief Gerencia o display
 * @version 0.1
 * @date 2022-05-28
 */
#include "display.h"
#include "freertos/FreeRTOS.h"
#include <freertos/task.h>
#include <driver/gpio.h>
//#include <ssd1306/ssd1306.h>
#include <../components/ESP32-RTOS-SSD1306/ssd1306/ssd1306.h>
#include <driver/i2c.h>
#include <esp_err.h>
#include "config.h"
//#include <fonts/fonts.h>
#include <../components/ESP32-RTOS-FONTS/fonts/fonts.h>
#include <stdlib.h>

#include "image.xbm" // Testes com bitmap

typedef enum
{
    NAO_INICIADO = -1,
    DISPLAY_OK = 0,
    ERRO,
} display_status_t;

display_status_t display_status;
ssd1306_t display;
const font_info_t *font = NULL;
static uint8_t buffer[DISPLAY_WIDTH * DISPLAY_HEIGHT / 8];

#define I2C_MASTER_SCL_IO 22        /*!< GPIO number used for I2C master clock */
#define I2C_MASTER_SDA_IO 21        /*!< GPIO number used for I2C master data  */
#define I2C_MASTER_NUM 0            /*!< I2C master i2c port number, the number of i2c peripheral interfaces available will depend on the chip */
#define I2C_MASTER_FREQ_HZ 400000   /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE 0 /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE 0 /*!< I2C master doesn't need buffer */
#define I2C_MASTER_TIMEOUT_MS 1000

/**
 * @brief Inicializa o display e configura o I2C
 */
void display_init()
{
    int i2c_master_port = I2C_MASTER_NUM;

    display_status = NAO_INICIADO;

    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };

    esp_err_t err;
    err = i2c_param_config(I2C_MASTER_PORT, &conf);
    ESP_ERROR_CHECK(err);
    err = i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
    ESP_ERROR_CHECK(err);

    if (err != ESP_OK)
        return;

    printf("I2C OK!\n");

    display.i2c_port = I2C_MASTER_PORT;
    display.i2c_addr = DISPLAY_I2C_ADDRESS;
    display.screen = SSD1306_SCREEN;
    display.width = DISPLAY_WIDTH;
    display.height = DISPLAY_HEIGHT;

    if (ssd1306_init(&display) != 0)
    {
        printf("Falha na inicialização do display\n");
        display_status = ERRO;
        return;
    }

    ssd1306_set_whole_display_lighting(&display, false);
    printf("OLED OK!\nTamanho do buffer %d\n", sizeof(buffer));

    font = font_builtin_fonts[FONT_FACE_GLCD5x7];

    display_status = DISPLAY_OK;

    // ssd1306_clear_screen(&display);
}

/**
 * @brief Envia uma string para o display
 *
 * @param str String
 * @param x posição X
 * @param y posição Y
 */
void display_write_string(const char *str, uint8_t x, uint8_t y)
{
    ssd1306_draw_string(&display, buffer, font, x, y, str, OLED_COLOR_WHITE, OLED_COLOR_BLACK);
    ssd1306_load_frame_buffer(&display, buffer);
}

/**
 * @brief Escreve um número float no display
 *
 * @param num float
 * @param x posição X
 * @param y posição Y
 */
void display_write_float(float num, uint8_t x, uint8_t y)
{
    // TODO:
    // TESTAR

    char str[13];
    sprintf(str, "%g", num);
    display_write_string(str, x, y); // sends the string
}

void clear_buffer(void)
{
    unsigned int i;

    for (i = 0; i < sizeof(buffer); i++)
    {
        buffer[i] = 0x00;
    }
}

/**
 * @brief Realiza um teste no display
 */
void display_test(void)
{
    display_write_string("PI3_2022_1", 0, 8);

    vTaskDelay(2000 / portTICK_PERIOD_MS);

    printf("Iniciando animacao\n");
    uint8_t i, j;

    for (i = 0; i < 50; i++)
    {
        for (j = 9; j > 0; j--)
        {
            display_load_bitmap(monkeyAnimation[j]);
            vTaskDelay(50 / portTICK_PERIOD_MS);
        }
    }

    printf("OK\n");
}

/**
 * @brief Exibe um bitmap no display
 *
 * @param bitmap
 */
void display_load_bitmap(unsigned char *bitmap)
{
    clear_buffer();

    if (ssd1306_load_xbm(&display, bitmap, buffer))
    {
        printf("Erro ao carregar o buffer\n");
    }
}

