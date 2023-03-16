#include <OneWire.h>                
#include <DallasTemperature.h>

OneWire ourWire(5);                  //Se establece el pin 2  como bus OneWire
DallasTemperature sensors(&ourWire);  //Se declara una variable u objeto para nuestro sensor

float temp;
float temp_min = 20;
float temp_max = 26;

const int ledGREEN = 10;

void temperature_setup() { 
 
  sensors.begin();   //Se inicia el sensor
  pinMode(ledGREEN, OUTPUT);

} 

void temperature_loop(){

  sensors.requestTemperatures();            //Se envía el comando para leer la temperatura
  temp= sensors.getTempCByIndex(0);         //Se obtiene la temperatura en ºC

  if(temp < temp_min || temp > temp_max){
    digitalWrite(ledGREEN, HIGH);           // turn the LED on (HIGH is the voltage level)
  }else{
    digitalWrite(ledGREEN, LOW);            // turn the LED on (HIGH is the voltage level)
  }

  Serial.print("Temperatura= ");
  Serial.print(temp);
  Serial.println(" ºC");
  delay(5000);                               //monitorización cada 5 seg  = 5000ms                 
}
