#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>

#define I2C_MASTER_SCL_IO 22        /*!< GPIO number used for I2C master clock */
#define I2C_MASTER_SDA_IO 21        /*!< GPIO number used for I2C master data  */
#define I2C_MASTER_NUM 0            /*!< I2C master i2c port number, the number of i2c peripheral interfaces available will depend on the chip */
#define I2C_MASTER_FREQ_HZ 400000   /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE 0 /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE 0 /*!< I2C master doesn't need buffer */
#define I2C_MASTER_TIMEOUT_MS 1000



namespace display
{
    void display_init();
    void display_test(void);

    void display_write_string(const char *str, uint8_t x, uint8_t y);
    void display_write_float(float num, uint8_t x, uint8_t y);
    void display_load_bitmap(unsigned char *bitmap);
    void clear_buffer(void);
}

#endif