int input ;

/*---------------------------WIFI INI-------------------------------*/ 
// Include WiFi library
#include <ESP8266WiFi.h>

/* 1. Define the WiFi credentials */
#define WIFI_SSID "realme X2"
#define WIFI_PASSWORD "met06grupo04"

/*---------------------------FIREBASE INI-------------------------------*/ 

// Include Firebase library (this library)
#include <Firebase_ESP_Client.h>

// Define the Firebase Data object
FirebaseData fbdo;

// Define the FirebaseAuth data for authentication data
FirebaseAuth auth;

// Define the FirebaseConfig data for config data
FirebaseConfig config;

 
 /*---------------------------FIREBASE CLOUD MESSAGING CONECTION-------------------------------*/ 
 // Provide the token generation process info.
#include <addons/TokenHelper.h>
  
 #define FIREBASE_FCM_SERVER_KEY "AAAAluTMveM:APA91bHaOwcEHp2C-b6RHHxv9hhuaLL99eAj7oPfHyQV-pOezo6n_q6_FfsuHoeRubd3Q9TBCB4_eGSp2lzBHS32YUVHjGhyupQY_1e-FnrUTrcW7PSXI6SU6047MFcb9G4PkPKHDzet"
  
 /* 3. Define the iOS APNs tokens to register */
 #define APN_TOKEN_1 "eiDdYwOyTVG3YZfgfdt50D:APA91bFcjoWYn2Y7CArNQsNtJ_gegkrh3AuDtXwY7x_31AjrHfTW8NLkZG1wpmmzMcdLGuMTySFI-LsKu8n2YyMinLh0kRMI77GxrXdswzGvsWyEQMIi2fVgYNgN-VPfUKOd2HjvzQZR"
 #define APN_TOKEN_2 "eUFEzchUTHmNdZDBgIRz6w:APA91bGMDS5foFrPvGZrHvU5EhqFBvm2i1Sl8S3cUinG62jmxX2ELVzw-qKfH83pZ9Yv43AjxsKGpHZ3J7K7vM6Rhu_QLoX7pBwT29KvKueP-2TajojRdlJ30ZKCts9mz27vybekOuK3"

void setup() { 
  
  //Serial.begin(9600);
  Serial.begin(115200);

/*---------------------------WIFI CONECTION-------------------------------*/ 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
  Serial.print("Connecting to Wi-Fi");
  unsigned long ms = millis();
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300); 
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();


/*---------------------------FIREBASE CONECTION-------------------------------*/ 
  
  // Assign the project host and api key 
  config.host = "https://met06-g4-default-rtdb.europe-west1.firebasedatabase.app/";
  config.api_key = "AIzaSyDVOsghNp3-ym4aSWa31PCd383cNqLTfuk";
  
  // Assign the user sign in credentials
  auth.user.email = "cecilia@jimenez.com";
  auth.user.password = "cecilia";

  /* Assign the sevice account credentials and private key (required) */
  config.service_account.data.client_email = "firebase-adminsdk-5es1t@met06-g4.iam.gserviceaccount.com";
  config.service_account.data.project_id = "met06-g4";
  config.service_account.data.private_key = "-----BEGIN PRIVATE KEY-----\nMIIEvQIBADANBgkqhkiG9w0BAQEFAASCBKcwggSjAgEAAoIBAQDIMwLJOI+caJgQ\nCeu7O8VVzM2A2VFqPtYAu8W6Pn22VaTZXD0MVwY9plSICCgZH/yZEaQt1uqzknw5\nGANpkz/vp74aOvQs45RDKWQvx/RlaAJ5JXWQsgS7cPVF1IwQAAJxmdOX3herHFMZ\nDsBt/7LkKo4/3J+cIyGQXell5krRkt/BRTD0AaqQwm3xD8crrhp686UEBH8Ln2uP\nyhvlp62mw2Qn3B01VNj5cN816mBUyqHAZG5BJ0Ru/x7nJU/oMPaS73/6uu44/tBR\nqYAi79HcRC8+8obo6yNOKfRU/3qqttOg9GndFVuYwpizG5EIsy5l7zVPCxHVKoJv\nXLiGsMUTAgMBAAECggEAORo7sDNe2wkGXoTF5TjON4PcFeVmkHxtw/XLFy1d5BUX\nmRvzGcL0t77qm4ZgEZKLFQnwH1cOyLt+jTZpOsLSWMQquAaawPcEwgdbWTmaXxZE\nplNl7iioquI0Q3+1l5a5G7f5n3asn5TLqvkHMBjf6K6utk5yhDGNEEWJHhSKwK23\n0olXgOUGYVpNA2tDq5rvjdiHjNTaba+TU2a8jb7SwylaZkKIdBmmIzWp92ZNcGvB\nd/JSm8VhjeZFCBWWL46DdN3ScH/iSC3DA76p3x9ebvGsX0ywEiJkHM78i4kG7Ugd\nWMHq5JdnniEF4sJ23pz4dKppx3r1WoP9AjFOT49IsQKBgQDnD4CNQokL04thRmsz\nPsrJh/OgzGX85KVGCTArLEa8Yp02uj1G6C4tXYmoJNzOFqlB1cCRkd9Om/1kCPkp\nybHQl2YzHF7q0MwDfNxvGUzw7+aOJ13ey85EKhCU6MBDjPBndHzdXLBuU7yDPp4V\neC/Wv6mUw3mlvjzwPGhNSLgOCwKBgQDdzsWVdgAZwX4DA/UoZO4CgefobNwT0Xc4\n+ROiaONhSo6KAvAGWSyASzOTaTCsdWoOLOYxX4IQQ/AXfupeR7yAaz4K0DjHdprd\nksEvQG0vzVFar8kk+SE5J8EalbUb4vDhzS//Vy6YlhpWpWPdTe4phCHZi4tUiprO\nI7G7MfPyGQKBgCpbbyd2IQVn/E8Sx6gXRLl5ELJThga8K4gROyFO9pCmS0ezEHSl\nL4Hlecy3JTsqcFC/TJPi99rDQcpK0tJURSKF/pg0BTpqmFuzUf2T18T7VXqNwOmM\n1v0r8Oo7WLOJbLCqbBFwYm93LkGpAvXQmIR3kjDRPMWjgCxSBpTUVdlNAoGAOKfs\nSDUP6YRHD7YfFOZS9UkBV5kWzekfLupQXZe1HNDSf+YoMTbt6wdKcUjZKfQD1wMY\n+VuP+V+hIB9G9jYUrCi4fEKbfjeJbzdhKRSnzyH+uc9U7aDFH7hL1uKOlETvin3C\n2NIIEOmmaKNuUsTpJKmfi9XdDQcqa6UqbMphqWECgYEAqRqz/PeGMR4/6Lla7SIM\nje/PXbAOct4qJzel+Ha7JiujVeKmRO9T4gBtaP9EhPLxy2Zff4eIlNZ3PHZ1lG3u\nT4ZqZrm5noEv7RvgfN4RJareOWJldr4tcwIUeqdWJ+DqpcEeF2JHDlx3YV9eTfF7\nB11Cp4SCHO4nSxikcQ5ilAY=\n-----END PRIVATE KEY-----\n"; 

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h
  
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
  
 
  // Optional, set the size of BearSSL WiFi to receive and transmit buffers
  // Firebase may not support the data transfer fragmentation, you may need to reserve the buffer to match
  // the data to transport.
  fbdo.setBSSLBufferSize(1024, 1024); // minimum size is 512 bytes, maximum size is 16384 bytes
 
  // Optional, set the size of HTTP response buffer
  // Prevent out of memory for large payload but data may be truncated and can't determine its type.
  fbdo.setResponseSize(1024); // minimum size is 1024 bytes


 /*---------------------------FIREBASE CLOUD MESSAGING CONECTION-------------------------------*/ 
 
  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  Firebase.FCM.setServerKey(FIREBASE_FCM_SERVER_KEY);

 Serial.print("Subscribe the topic... ");

    int numToken = 1;
    const char *APNs[1];
    APNs[0] = APN_TOKEN_1;
  

    if (Firebase.FCM.regisAPNsTokens(&fbdo, "com.example.met06_g4_finalproject" /* Bundle id of the app */, false /* sandbox */, APNs /* array of APNs tokens */, numToken)){
        Serial.printf("ok......\n%s\n\n", Firebase.FCM.payload(&fbdo).c_str());
    }else{
        Serial.println(fbdo.errorReason());
    }

 

  
  
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
