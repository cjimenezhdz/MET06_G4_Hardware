#include "DHT.h"

#define DHTPIN 9     // Pin donde está conectado el sensor

//#define DHTTYPE DHT11   // Descomentar si se usa el DHT 11
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
  
  Serial.print("Humedad ");
  Serial.print(h);
  Serial.print(" % ");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.println(" ºC ");


  
}