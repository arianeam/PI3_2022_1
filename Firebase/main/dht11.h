#ifndef DHT11_H
#define DHT11_H

#include <stdio.h>
#include <iostream>
#include <driver/gpio.h>
#include "../components/dht/dht.h"


#define DHT_PIN GPIO_NUM_18

class dht11
{
private:
    float temperatura, umidade;

public:
    void dht11_init();
    void read_dht11();
    float get_temp();
    float get_umid();
};

#endif
