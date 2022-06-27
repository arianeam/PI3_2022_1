#include "dht11.h"
#include "../components/dht/dht.c"

void dht11::dht11_init()
{
    gpio_set_pull_mode(GPIO_NUM_18, GPIO_PULLUP_ONLY);
}

void dht11::read_dht11()
{

    if (dht_read_float_data(DHT_TYPE_DHT11, GPIO_NUM_18, &umidade, &temperatura) == ESP_OK)
    {
        printf("Umidade: %.1f%% Temp: %.1fC\n", umidade, temperatura);
    }
    else
    {
        printf("Erro ao ler dados do sensor dht11\n");
    }
}

float dht11::get_temp()
{
    return temperatura;
}

float dht11::get_umid()
{
    return umidade;
}
