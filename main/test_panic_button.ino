
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
    }
  }else if(boolStateFirebase){
    digitalWrite(ledBLUE, HIGH);  // turn the LED on (HIGH is the voltage level)
    tiempoPanicoAnterior = tiempoPanicoActual;
    boolStateFirebase=false;
    FirebaseRead=true;
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
