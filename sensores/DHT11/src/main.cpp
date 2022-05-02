#include <Arduino.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>

#define DHT_PIN 18    // pino de dados do DHT11
#define DHTTYPE DHT11 // selecionar tipo do DHT
#define LED_PIN 2    // pino para led de teste

DHT dht(DHT_PIN, DHTTYPE);

void setup()
{

  // teste led blink
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(9600);
  Serial.println("DHTxx teste!");
  dht.begin();

  delay(2000);
}

void loop()
{

  // teste led blink------------------------

  digitalWrite(LED_PIN, HIGH);
  delay(1000);
  digitalWrite(LED_PIN, LOW);
  delay(1000);

  //------------------------------------------

  float umidade = dht.readHumidity();
  float temperatura = dht.readTemperature();

  // testa se retorno é valido, caso contrário algo está errado.
  if (isnan(temperatura) || isnan(umidade))
  {
    Serial.println("Falha na leitura do DHTxx");
  }
  else
  {
    Serial.print("Umidade: ");
    Serial.print(umidade);
    Serial.print(" %  ");
    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.println(" *C");
  }

  delay(2000);
}