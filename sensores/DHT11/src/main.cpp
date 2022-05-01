#include <Arduino.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>

#define DHTPIN 27  //D27
#define DHTTYPE DHT11
#define LED_PIN 26

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:

  //teste led blink
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(9600);
  Serial.println("DHTxx test!");
  dht.begin();
 
}

void loop() {

// teste led blink------------------------
digitalWrite(LED_PIN, HIGH);
delay(1000);
digitalWrite(LED_PIN, LOW);
delay(1000);
//------------------------------------------
  delay(2000);
  // put your main code here, to run repeatedly:

  // A leitura da temperatura e umidade pode levar 250ms!
  // O atraso do sensor pode chegar a 2 segundos.
  float umidade = dht.readHumidity();
  float temperatura = dht.readTemperature();
  // testa se retorno é valido, caso contrário algo está errado.
  if (isnan(temperatura) || isnan(umidade)) 
  {
    Serial.println("Failed to read from DHT");
  } 
  else
  {
    Serial.print("Umidade: ");
    Serial.print(umidade);
    Serial.print(" %t");
    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.println(" *C");
  }
}