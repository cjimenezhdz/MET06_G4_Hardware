#include "DHT.h"

#define DHTPIN 10     // Pin donde está conectado el sensor
#define DHTTYPE DHT22   // Sensor DHT22

float t_min = 20;
float t_max = 35;//24
float h_min = 30;//50
float h_max = 85;

unsigned long tiempoAnterior = 0;
const unsigned long intervalo = 5000;

const int ledGREEN = 4; //si ponemos el 9 deja de funcionar el DHT sensor
const int led_RED = 16;

DHT dht(DHTPIN, DHTTYPE);

void temp_hum_setup() {
  
  dht.begin();
  pinMode(ledGREEN, OUTPUT);
  pinMode(led_RED, OUTPUT);
  
}
void temp_hum_loop() {

  unsigned long tiempoActual = millis();
  
  if (tiempoActual - tiempoAnterior >= intervalo) {
    tiempoAnterior = tiempoActual;
    float h = dht.readHumidity(); //Leemos la Humedad
    float t = dht.readTemperature(); //Leemos la temperatura en grados Celsius
  
    if(t< t_min || t > t_max){
        digitalWrite(ledGREEN, HIGH);           // turn the LED on (HIGH is the voltage level)

        if (Firebase.ready()){ 
          sendMessageTemp();
        }

      }else{
        digitalWrite(ledGREEN, LOW);            // turn the LED on (HIGH is the voltage level)
      }
  
    if(h< h_min || h > h_max){
        digitalWrite(led_RED, HIGH);           // turn the LED on (HIGH is the voltage level)
        if (Firebase.ready()){ 
          sendMessageHum();
        }
      }else{
        digitalWrite(led_RED, LOW);            // turn the LED on (HIGH is the voltage level)
      }
    
    //--------Enviamos las lecturas por el puerto serial-------------
    
    Serial.print("Humedad ");
    Serial.print(h);
    Serial.print(" % ");
    Serial.print("Temperatura: ");
    Serial.print(t);
    Serial.println(" ºC ");

//--------Enviamos las lecturas al firebase-------------

    if (Firebase.ready()){
      Serial.printf("Set temperature... %s\n", Firebase.RTDB.setFloat(&fbdo, F("/temperature"), t) ? "ok" : fbdo.errorReason().c_str());
      Serial.printf("Set humidity... %s\n", Firebase.RTDB.setFloat(&fbdo, F("/humidity"), h) ? "ok" : fbdo.errorReason().c_str());
    }
  }
}



void sendMessageTemp()
{

    Serial.print("Send Firebase Cloud Messaging... ");

    // Read more details about HTTP v1 API here https://firebase.google.com/docs/reference/fcm/rest/v1/projects.messages
    FCM_HTTPv1_JSON_Message msg;

    msg.token = APN_TOKEN_1;

    msg.notification.title = "MAXIMUM TEMPERATURE REACHED > 24!";

    // For the usage of FirebaseJson, see examples/FirebaseJson/BasicUsage/Create.ino
    FirebaseJson payload;

    msg.data = payload.raw();

    if (Firebase.FCM.send(&fbdo, &msg)) // send message to recipient
        Serial.printf("ok......\n%s\n\n", Firebase.FCM.payload(&fbdo).c_str());
    else
        Serial.println(fbdo.errorReason());      
}



void sendMessageHum()
{

    Serial.print("Send Firebase Cloud Messaging... ");

    // Read more details about HTTP v1 API here https://firebase.google.com/docs/reference/fcm/rest/v1/projects.messages
    FCM_HTTPv1_JSON_Message msg;

    msg.token = APN_TOKEN_1;

    msg.notification.title = "MAXIMUM/MINIMUM HUMIDITY REACHED";

    // For the usage of FirebaseJson, see examples/FirebaseJson/BasicUsage/Create.ino
    FirebaseJson payload;

    msg.data = payload.raw();

    if (Firebase.FCM.send(&fbdo, &msg)) // send message to recipient
        Serial.printf("ok......\n%s\n\n", Firebase.FCM.payload(&fbdo).c_str());
    else
        Serial.println(fbdo.errorReason());      
}
