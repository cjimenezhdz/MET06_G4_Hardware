int input ;

// Include WiFi library
#include <ESP8266WiFi.h>

// Include Firebase library (this library)
#include <Firebase_ESP_Client.h>

// Define the Firebase Data object
FirebaseData fbdo;

// Define the FirebaseAuth data for authentication data
FirebaseAuth auth;

// Define the FirebaseConfig data for config data
FirebaseConfig config;

void setup() { 
  
  Serial.begin(9600);
  // Assign the project host and api key 
  config.host = "https://met06-g4-default-rtdb.europe-west1.firebasedatabase.app/";
  config.api_key = "AIzaSyDVOsghNp3-ym4aSWa31PCd383cNqLTfuk";
  // Assign the user sign in credentials
  auth.user.email = "calpecarlos12@gmail.com";
  auth.user.password = "carlos";
  // Initialize the library with the Firebase authen and config.
  Firebase.begin(&config, &auth);
  // Optional, set AP reconnection in setup()
  Firebase.reconnectWiFi(true);
  // Optional, set number of error retry
  Firebase.RTDB.setMaxRetry(&fbdo, 3);
  // Optional, set number of error resumable queues
  Firebase.RTDB.setMaxErrorQueue(&fbdo, 30);
  // Optional, use classic HTTP GET and POST requests.
  // This option allows get and delete functions (PUT and DELETE HTTP requests) works for
  // device connected behind the Firewall that allows only GET and POST requests.
  Firebase.RTDB.enableClassicRequest(&fbdo, true);
  #if defined(ESP8266)
  // Optional, set the size of BearSSL WiFi to receive and transmit buffers
  // Firebase may not support the data transfer fragmentation, you may need to reserve the buffer to match
  // the data to transport.
  fbdo.setBSSLBufferSize(1024, 1024); // minimum size is 512 bytes, maximum size is 16384 bytes
  #endif
  // Optional, set the size of HTTP response buffer
  // Prevent out of memory for large payload but data may be truncated and can't determine its type.
  fbdo.setResponseSize(1024); // minimum size is 1024 bytes
    // Preguntar al usuario qué loop quiere generar
    ///*

    
  Serial.println("¿Qué loop quieres generar? Escribe: \n"
    "'1' -> Emergencia temperatura/humedad, caída y botón pánico\n"
    "'2' -> Smart Light, \n"
    "'3' -> Grifo");

  // Leer la respuesta del usuario
  
  while (Serial.available() == 0) {
      }   
  input = Serial.readString().toInt();
    switch (input){
    case 1:
      temp_hum_setup();
      presence_setup();
      panic_setup();
      break;
    case 2:
      SmartLight_setup();
      break;

    case 3:
      servo_setup();
      break;
    }
}

void loop() { 
  switch (input){
    case 1:
        temp_hum_loop();
        presence_loop();
        panic_loop();
      break;
    
    case 2:
      SmartLight_loop();
      break;

    case 3:
      servo_loop();
      break;

    default:
      Serial.println("Opción inválida, por favor intenta de nuevo");
      break;
  }
}
