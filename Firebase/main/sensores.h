/**
 * @file sensores.h
 * @brief
 * @version 0.1
 * @date 2022-07-09
 */
#include "adc_1.h"

#define BATTERY_MAX_VOLTAGE     4200
#define BATTERY_NOMINAL_VOLTAGE 3700
#define BATTERY_MIN_VOLTAGE     3200

#define CONVERSION_VALUE        1.26984

// #define MONITOR_CHARGE_STATE

#define CHARGING_COMPLETE_INPUT GPIO_NUM_13
#define CHARGING_INPUT          GPIO_NUM_12

enum
{
    DISCHARGING,
    CHARGING,
    CHARGE_COMPLETE,
}charge_state;

struct
{
    uint16_t voltage;   // Tensão da bateria (mV)
    int8_t percentage; // Porcentagem da carga (0 ~ 100)
    uint8_t status;     // Status da bateria
    uint8_t state;      // charge_state
}battery;

adc adc_battery;
 
/**
 * @brief Inicializa a medição da bateria
 */
void battery_measure_init(void)
{
    // GPIO33 - Medição de bateria
    battery.status = DISCHARGING;
    battery.percentage = 0;
    battery.voltage = BATTERY_MIN_VOLTAGE;

    adc_battery.adc_init(ADC1_CHANNEL_5);

#ifdef MONITOR_CHARGE_STATE
    ESP_LOGI("BAT", "Monitor charge state");
    gpio_set_direction(CHARGING_INPUT, GPIO_MODE_INPUT);
    gpio_set_direction(CHARGING_COMPLETE_INPUT, GPIO_MODE_INPUT);
#endif

}


/**
 * @brief Mede a tensão da bateria e status de carga
 */
void measure_battery()
{
    uint32_t raw;

    raw = adc_battery.read();

    battery.voltage = raw * CONVERSION_VALUE;
    battery.percentage = (battery.voltage - BATTERY_MIN_VOLTAGE) / 10;

    if(battery.percentage > 100)    battery.percentage = 100;
    if(battery.percentage <= 0)     battery.percentage = 0;

#ifdef MONITOR_CHARGE_STATE
    if(gpio_get_level(CHARGING_INPUT) == 1)
        battery.status = CHARGING;
    else if(gpio_get_level(CHARGING_COMPLETE_INPUT) == 1)
        battery.status = CHARGE_COMPLETE;
    else
        battery.status = DISCHARGING;
#endif

    printf("Battery raw %d\nVoltage %d, Status %d, Percentage %d\n", raw, battery.voltage, battery.status, battery.percentage);
}


/**
 * @brief Get the battery state object
 * 
 * @return uint8_t 
 */
uint8_t get_battery_state(void)
{
    return battery.status;
}

/**
 * @brief Get the battery voltage object
 * 
 * @return uint16_t 
 */
uint16_t get_battery_voltage(void)
{
    return battery.voltage;
}

/**
 * @brief Get the battery percentage object
 * 
 * @return uint8_t 
 */
uint8_t get_battery_percentage(void)
{
    return battery.percentage;
}

/**
 * @brief 
 * 
 */
void luximeter_init(void)
{

}

/**
 * @brief 
 * 
 */
void luximeter_read(void)
{

}
