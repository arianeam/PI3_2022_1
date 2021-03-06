/**
 * @file display.c
 * @brief Gerencia o display
 * @version 0.1
 * @date 2022-05-28
 */
#include "display.h"

//#include "image.xbm" // Testes com bitmap


/**
 * @brief Inicializa o display e configura o I2C
 */
void display::init()
{
    int i2c_master_port = I2C_MASTER_NUM;
    display_status_t display_status;

    display_status = NAO_INICIADO;

     i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
    };

     conf.master.clk_speed = I2C_MASTER_FREQ_HZ;

    esp_err_t err;
    err = i2c_param_config(I2C_MASTER_PORT, &conf);
    ESP_ERROR_CHECK(err);
    err = i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
    ESP_ERROR_CHECK(err);

    if (err != ESP_OK)
        return;

    printf("I2C OK!\n");

    Display.i2c_port = I2C_MASTER_PORT;
    Display.i2c_addr = DISPLAY_I2C_ADDRESS;
    Display.screen = SSD1306_SCREEN;
    Display.width = DISPLAY_WIDTH;
    Display.height = DISPLAY_HEIGHT;

    if (ssd1306_init(&Display) != 0)
    {
        printf("Falha na inicialização do display\n");
        display_status = ERRO;
        return;
    }

    ssd1306_set_whole_display_lighting(&Display, false);
    printf("OLED OK!\nTamanho do buffer %d\n", sizeof(buffer));

    font = font_builtin_fonts[FONT_FACE_GLCD5x7];

    //display_status = DISPLAY_OK;

    // ssd1306_clear_screen(&display);
}

/**
 * @brief Envia uma string para o display
 *
 * @param str String
 * @param x posição X
 * @param y posição Y
 */
void display::write(const char *str, uint8_t x, uint8_t y)
{
    ssd1306_draw_string(&Display, buffer, font, x, y, str, OLED_COLOR_WHITE, OLED_COLOR_BLACK);
    ssd1306_load_frame_buffer(&Display, buffer);
}

/**
 * @brief Escreve um número float no display
 *
 * @param num float
 * @param x posição X
 * @param y posição Y
 */
void display::write(float num, uint8_t x, uint8_t y)
{
    // TODO:
    // TESTAR

    char str[13];
    sprintf(str, "%g", num);

    ssd1306_draw_string(&Display, buffer, font, x, y, str, OLED_COLOR_WHITE, OLED_COLOR_BLACK);
    ssd1306_load_frame_buffer(&Display, buffer);
}

void display::clear_buffer(void)
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
// void display_test(void)
// {
//     display_write_string("PI3_2022_1", 0, 8);

//     vTaskDelay(2000 / portTICK_PERIOD_MS);

//     printf("Iniciando animacao\n");
//     uint8_t i, j;

//     for (i = 0; i < 50; i++)
//     {
//         for (j = 9; j > 0; j--)
//         {
//             display_load_bitmap(monkeyAnimation[j]);
//             vTaskDelay(50 / portTICK_PERIOD_MS);
//         }
//     }

//     printf("OK\n");
// }

/**
 * @brief Exibe um bitmap no display
 *
 * @param bitmap
 */
void display::load_bitmap(unsigned char *bitmap)
{
    clear_buffer();

    if (ssd1306_load_xbm(&Display, bitmap, buffer))
    {
        printf("Erro ao carregar o buffer\n");
    }
}
