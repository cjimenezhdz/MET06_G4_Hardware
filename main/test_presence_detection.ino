int pirPinUp=5; 
int pirStateUp=0;

int pirPinDown=0; 
int pirStateDown=0;

float sensorDistance=0.31;
float fallingTime=sqrt((2*sensorDistance)/9.8);  //1s

unsigned long tiempoPresenciaActual = 0;
unsigned long tiempoPresenciaAnterior = 0;
unsigned long tiempoDown=0;

//-------FIREBASE DATA---------
bool possible_fall=false;
bool walking=false;
bool boolStateFall=false;

unsigned long timeFall = 0;
unsigned long timeAfterFall = 0;
const unsigned long tresholdDisableFall = 5000;

void presence_setup() { 
  pinMode(pirPinDown, INPUT);
  pinMode(pirPinUp, INPUT);
} 

void presence_loop() { 
/*
pirStateUp = digitalRead(pirPinUp); //read state of the PIR 
pirStateDown = digitalRead(pirPinDown); //read state of the PIR

if (pirStateUp == HIGH) { 
      tiempoPresenciaActual = millis();      
      Serial.println("*******************************UP Motion!****************************************");
      Serial.println(tiempoPresenciaActual);
    }
    
if (pirStateDown == HIGH) { 
     tiempoPresenciaAnterior = millis();     
     Serial.println("//////////////DOWN Motion!//////////");
     Serial.println(tiempoPresenciaAnterior-tiempoPresenciaActual);
    }
    
/*
if (pirStateUp == HIGH && !possible_fall) { 
      tiempoPresenciaActual = millis();      
      Serial.println("*******************************UP Motion!****************************************");
      Serial.println(tiempoPresenciaActual);
      possible_fall=true;
    }
    
if (pirStateDown == HIGH && possible_fall) { 
     tiempoPresenciaAnterior = millis();     
     Serial.println("//////////////DOWN Motion!//////////");
     possible_fall=false;
     Serial.println(tiempoPresenciaAnterior-tiempoPresenciaActual);
    }else if (pirStateDown == HIGH){

    Serial.println("-----------------NO CAIDA----------------");

}

*/


    if(possible_fall){
      
      tiempoPresenciaActual = millis();
      pirStateDown = digitalRead(pirPinDown); //read state of the PIR
      tiempoDown = tiempoPresenciaActual - tiempoPresenciaAnterior;
      
      if(pirStateDown==HIGH && tiempoDown <= 850){
        possible_fall=false;
        Serial.println(tiempoDown);
        Serial.println("*******************************ANDANDOOOOOOOO!****************************************");
      }else if(pirStateDown==HIGH && tiempoDown > 850 && tiempoDown < 3000){
        Serial.println(tiempoDown);
        Serial.println("-----------------Caida DETECTADA!------------------------"); 
        possible_fall=false;


        if (Firebase.ready()){      
              sendMessagePresence();
              boolStateFall=true;
              Serial.printf("Set fall true ... %s\n", Firebase.RTDB.setBool(&fbdo, F("/fall"), boolStateFall) ? "ok" : fbdo.errorReason().c_str());
              timeFall=millis();
        }

      }else if(tiempoDown >= 3000){
        Serial.println(tiempoDown);
        Serial.println("///////////////////NADAAAAAAA!/////////////////////");
        possible_fall=false;
      }
      
    }else{
    
    pirStateUp = digitalRead(pirPinUp); //read state of the PIR 
    pirStateDown = digitalRead(pirPinDown); //read state of the PIR

    if (pirStateUp == HIGH && pirStateDown != HIGH) { 
        possible_fall=true;
        tiempoPresenciaAnterior = millis();
        Serial.println(tiempoPresenciaAnterior);
        Serial.println("???????????????????????????????????????????????????????????????????????????????");
    }else{
        Serial.println("....................READYYY......................");
    }
    
    }

    if(Firebase.ready() && boolStateFall==true && timeAfterFall - timeFall > tresholdDisableFall){
       boolStateFall=false;
       Serial.printf("Set fall false ... %s\n", Firebase.RTDB.setBool(&fbdo, F("/fall"), boolStateFall) ? "ok" : fbdo.errorReason().c_str());
    }

}



void sendMessagePresence()
{

    Serial.print("Send Firebase Cloud Messaging... ");

    // Read more details about HTTP v1 API here https://firebase.google.com/docs/reference/fcm/rest/v1/projects.messages
    FCM_HTTPv1_JSON_Message msg;

    msg.token = APN_TOKEN_1;

    msg.notification.title = "CAIDA DETECTADA!";

    // For the usage of FirebaseJson, see examples/FirebaseJson/BasicUsage/Create.ino
    FirebaseJson payload;

    msg.data = payload.raw();

    if (Firebase.FCM.send(&fbdo, &msg)) // send message to recipient
        Serial.printf("ok......\n%s\n\n", Firebase.FCM.payload(&fbdo).c_str());
    else
        Serial.println(fbdo.errorReason());
        
}
