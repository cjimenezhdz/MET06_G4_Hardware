
const int ledBLUE = 12;
const int buttonPin = 14;
int buttonState = 0;
bool boolState = false;
bool boolStateFirebase = false;
bool lastFirebaseState = false;
bool  buttonPress=false;
bool FirebaseRead=false;

unsigned long tiempoPanicoAnterior = 0;
unsigned long tiempoPanicoActual = 0;
const unsigned long intervaloPanico = 5000;

void panic_setup() { 
 
  pinMode(ledBLUE, OUTPUT);
  pinMode(buttonPin, OUTPUT);

} 

void panic_loop() { 

  buttonState = digitalRead(buttonPin); 
  tiempoPanicoActual = millis();

  if (Firebase.ready()&& buttonPress==false && FirebaseRead==false){
    Serial.printf("Get bool ref... %s\n", Firebase.RTDB.getBool(&fbdo, F("/emergency"), &boolStateFirebase) ? boolStateFirebase ? "true" : "false" : fbdo.errorReason().c_str());
  }

  if(buttonState == HIGH){
    digitalWrite(ledBLUE, HIGH);  // turn the LED on (HIGH is the voltage level)
    boolStateFirebase = true;
    tiempoPanicoAnterior = tiempoPanicoActual;
    if (Firebase.ready()){
      buttonPress=true;
      Serial.printf("Set emergency... %s\n", Firebase.RTDB.setBool(&fbdo, F("/emergency"), boolStateFirebase) ? "ok" : fbdo.errorReason().c_str());

      sendMessage();
    }
  }else if(boolStateFirebase){
    digitalWrite(ledBLUE, HIGH);  // turn the LED on (HIGH is the voltage level)
    tiempoPanicoAnterior = tiempoPanicoActual;
    boolStateFirebase=false;
    FirebaseRead=true;
    sendMessage();
  }else if(tiempoPanicoActual - tiempoPanicoAnterior >= intervaloPanico) {
    digitalWrite(ledBLUE, LOW);  // turn the LED on (HIGH is the voltage level)
    boolStateFirebase = false;
    FirebaseRead=false;
    if (Firebase.ready()&& buttonPress){
      Serial.printf("Set emergency... %s\n", Firebase.RTDB.setBool(&fbdo, F("/emergency"), boolStateFirebase) ? "ok" : fbdo.errorReason().c_str());
      buttonPress=false;
    }
  } 

}

void sendMessage()
{

    Serial.print("Send Firebase Cloud Messaging... ");

    // Read more details about HTTP v1 API here https://firebase.google.com/docs/reference/fcm/rest/v1/projects.messages
    FCM_HTTPv1_JSON_Message msg;

    msg.token = APN_TOKEN_1;

    msg.notification.title = "EMERGENCIA!";

    // For the usage of FirebaseJson, see examples/FirebaseJson/BasicUsage/Create.ino
    FirebaseJson payload;

    msg.data = payload.raw();

    if (Firebase.FCM.send(&fbdo, &msg)) // send message to recipient
        Serial.printf("ok......\n%s\n\n", Firebase.FCM.payload(&fbdo).c_str());
    else
        Serial.println(fbdo.errorReason());
        
}
