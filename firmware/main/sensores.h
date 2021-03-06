/**
 * @file sensores.h
 * @brief
 * @version 0.1
 * @date 2022-07-09
 */
#include "adc_1.h"
#include "config.h"
#include "math.h"

enum
{
    DISCHARGING,
    CHARGING,
    CHARGE_COMPLETE,
} charge_state;

struct
{
    uint16_t voltage;  // Tensão da bateria (mV)
    int8_t percentage; // Porcentagem da carga (0 ~ 100)
    uint8_t status;    // Status da bateria
    uint8_t state;     // charge_state
} battery;

adc adc_battery;
adc adc_lux;
adc adc_solo;

/**
 * @brief Inicializa a medição da bateria
 */
void battery_measure_init(void)
{
    // GPIO33 - Medição de bateria
    battery.status = DISCHARGING;
    battery.percentage = 0;
    battery.voltage = BATTERY_MIN_VOLTAGE;

    adc_battery.adc_init(ADC_BAT);

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

    if (battery.percentage > 100)
        battery.percentage = 100;
    if (battery.percentage <= 0)
        battery.percentage = 0;

#ifdef MONITOR_CHARGE_STATE
    if (gpio_get_level(CHARGING_INPUT) == 1)
        battery.status = CHARGING;
    else if (gpio_get_level(CHARGING_COMPLETE_INPUT) == 1)
        battery.status = CHARGE_COMPLETE;
    else
        battery.status = DISCHARGING;
#endif

    printf("Battery raw %d\nVoltage %d mV, Status %d, Percentage %d\n", raw, battery.voltage, battery.status, battery.percentage);
}

/**
 * @brief Obtem o estado da bateria
 *
 * @return uint8_t : 0 - Descarregando
 *                   1 - Carregando
 *                   2 - Carga completa
 */
uint8_t get_battery_state(void)
{
    return battery.status;
}

/**
 * @brief Obtem a tensão da bateria
 *
 * @return uint16_t : tensão em mV
 */
uint16_t get_battery_voltage(void)
{
    return battery.voltage;
}

/**
 * @brief Obtem a porcentagem de carga da bateria
 *
 * @return uint8_t : carga restante (0 ~ 100%)
 */
uint8_t get_battery_percentage(void)
{
    return battery.percentage;
}

/**
 * @brief Inicializa o ADC utilizado pelo luximetro
 *
 */
void luximeter_init(void)
{
    adc_lux.adc_init(ADC_LUX);
}

/**
 * @brief Mede a luminosidade do ambiente
 *
 * @return float : valor em lux
 */
float luximeter_read(void)
{
    float lux, ldrR, ldrV, resV;
    uint16_t adc_raw;

    adc_raw = adc_lux.read();
    resV = (adc_raw / ADC_MAX_VALUE) * DEFAULT_VREF;
    ldrV = DEFAULT_VREF - resV;
    ldrR = (ldrV / resV) * REF_RESISTANCE;

    lux = LUX_SCALAR_COEF * pow(ldrR, LUX_EXPONENTIAL_COEF);
    printf("Luximetro RAW %d - %f lux\n", adc_raw, lux);
    printf("ldrV %f, ldrR %f, resV %f", ldrV, ldrR, resV);

    return lux;
}

/**
 * @brief Retorna a faixa de luminosidade lida como string
 */
std::string obter_faixa_luminosidade(void)
{
    float lux;
    lux = luximeter_read();
    std::string info;

    if (lux > SOMBRA_MIN && lux < SOMBRA_MAX)
    {
        info = "sombra";
    }
    else if (lux > MEIA_SOMBRA_MIN && lux < MEIA_SOMBRA_MAX)
    {
        info = "meia-sombra";
    }
    else if (lux > SOL_DIRETO)
    {
        info = "sol-pleno";
    }
    else
    {
        info = "escuro";
    }

    printf("Faixa lida: %s\n", info.c_str());
    return info;
}


/**
 * @brief Inicializa o ADC do medidor de umidade do solo
 */
void umidade_solo_init(void)
{
    adc_lux.adc_init(ADC_SOLO);
}


/**
 * @brief Retorna a umidade do solo lida como string
 */
std::string ler_umidade_solo(void)
{
    uint16_t raw = adc_solo.read();

    std::string retorno_umidade_solo;

    if (raw < SOLO_SECO)
    {
        retorno_umidade_solo = "seco";
    }
    else if (raw > SOLO_SECO && raw < SOLO_UMIDO)
    {
        retorno_umidade_solo = "úmido";
    }
    else if (raw > SOLO_UMIDO && raw < SOLO_MOLHADO)
    {
        retorno_umidade_solo = "molhado";
    }

    return retorno_umidade_solo;
}