#include "DHT.h"

#define DHTPIN 10     // Pin donde está conectado el sensor
#define DHTTYPE DHT22   // Sensor DHT22

DHT dht(DHTPIN, DHTTYPE);

void temp_hum_setup() {

  Serial.println("Iniciando...");
  dht.begin();
}
void temp_hum_loop() {

  float h = dht.readHumidity(); //Leemos la Humedad
  float t = dht.readTemperature(); //Leemos la temperatura en grados Celsius

  //--------Enviamos las lecturas por el puerto serial-------------
  
  delay(1000);
  Serial.print("Humedad ");
  Serial.print(h);
  Serial.print(" % ");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.println(" ºC ");
}
