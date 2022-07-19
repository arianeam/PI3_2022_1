/**
 * @file config.h
 * @brief Configurações do vaso inteligente
 * @version 0.1
 * @date 2022-07-19 
 */
#ifndef CONFIG_H_
#define CONFIG_H_


/* Display OLED */
#define DISPLAY_I2C_ADDRESS         0x3C
#define DISPLAY_WIDTH               128
#define DISPLAY_HEIGHT              64
#define I2C_MASTER_PORT             I2C_NUM_0

/* Wifi */
#define SSID                        "VIVO-10"
#define PASSWORD                    "nina2017j09"
//#define SSID "Andreia_NeoRede"
//#define PASSWORD "70960600"

/* Firebase */
#define API_KEY                     "AIzaSyDLVTKNaeNSG_lSELBeVdZoQPbkmXfg-Ow"
// Copy your firebase real time database link here 
#define DATABASE_URL                "https://pi-3-esp32-default-rtdb.firebaseio.com/"  
#define USER_EMAIL                  "testemail@gmail.com"   // This gmail does not exist outside your database. it only exists in the firebase project as a user
#define USER_PASSWORD               "testpass"      // Dont add your gmail credentials. Setup users authentication in your Firebase project first


/* Configurações de luminosidade */
// http://www.paisagismobauru.com.br/curiosidades/curiosidades/
#define SOMBRA_MIN                  2500
#define SOMBRA_MAX                  4999
#define MEIA_SOMBRA_MIN             5000
#define MEIA_SOMBRA_MAX             19999
#define SOL_DIRETO                  20000

/* Umidade do solo (valores do ADC) */
#define SOLO_SECO                   1
#define SOLO_UMIDO                  2
#define SOLO_MOLHADO                3

/* Firebase */
#define TEMPERATURA_LIDA           "temperatura_lida"
#define UMIDADE_AR_LIDA             "umidade_lida_ar"
#define UMIDADE_SOLO_LIDA           "umidade_lida_solo"
#define STATUS_BATERIA              "status_bateria"
#define LUMINOSIDADE_LIDA           "luminosidade_lida"

/* Bateria */
#define BATTERY_MAX_VOLTAGE         4200
#define BATTERY_NOMINAL_VOLTAGE     3700
#define BATTERY_MIN_VOLTAGE         3200
#define CONVERSION_VALUE            1.62884
#define MONITOR_CHARGE_STATE

/* Luximetro */
#define LUX_SCALAR_COEF             82.018158288
#define LUX_EXPONENTIAL_COEF        -0.5834
#define REF_RESISTANCE              2200
#define ADC_MAX_VALUE               4096

/* GPIO */
#define ADC_BAT                     ADC1_CHANNEL_6
#define ADC_LUX                     ADC1_CHANNEL_5
#define ADC_SOLO                    ADC1_CHANNEL_4
#define CHARGING_COMPLETE_INPUT     GPIO_NUM_13
#define CHARGING_INPUT              GPIO_NUM_14
#define LED_STATUS                  GPIO_NUM_25
#define LED_1                       GPIO_NUM_26
#define DHT_PIN                     GPIO_NUM_27

/* STATUS PLANTA */
#define FELIZ                       "feliz"
#define TRISTE                      "triste"
#define DEFINHANDO                  "definhando"
#define FRIO                        "frio"
#define CALOR                       "calor"
#define SEDE                        "sede"

/* Index */
#define TEMPERATURA                 0
#define UMIDADE_SOLO                1
#define LUMINOSIDADE                2
#define UMIDADE_AR                  3
#define BATERIA                     4


#endif