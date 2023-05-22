
const int ledBLUE = 12;
const int buttonPin = 14;
int buttonState = 0;
bool boolState = false;
bool boolStateFirebase = false;

unsigned long tiempoPanicoAnterior = 0;
unsigned long tiempoPanicoActual=0;
const unsigned long intervaloPanico = 5000;

void panic_setup() { 
 
  pinMode(ledBLUE, OUTPUT);
  pinMode(buttonPin, OUTPUT);

} 

void panic_loop() { 

  buttonState = digitalRead(buttonPin); 

  tiempoPanicoActual = millis();

  if(boolStateFirebase && !boolState){
    digitalWrite(ledBLUE, HIGH);  // turn the LED on (HIGH is the voltage level)
    boolStateFirebase = false;
    tiempoPanicoAnterior = tiempoPanicoActual;

  }else if( buttonState == HIGH){
    digitalWrite(ledBLUE, HIGH);  // turn the LED on (HIGH is the voltage level)
    boolState = true;
    tiempoPanicoAnterior = tiempoPanicoActual;

    if (Firebase.ready()){
      Serial.printf("Set emergency... %s\n", Firebase.RTDB.setBool(&fbdo, F("/emergency"), boolState) ? "ok" : fbdo.errorReason().c_str());
    }

  }else if(tiempoPanicoActual - tiempoPanicoAnterior >= intervaloPanico) {
    digitalWrite(ledBLUE, LOW);  // turn the LED on (HIGH is the voltage level)
    boolState = false;
    
    if (Firebase.ready()){
      Serial.printf("Set emergency... %s\n", Firebase.RTDB.setBool(&fbdo, F("/emergency"), boolState) ? "ok" : fbdo.errorReason().c_str());
      Serial.printf("Get bool ref... %s\n", Firebase.RTDB.getBool(&fbdo, F("/emergency"), &boolStateFirebase) ? boolStateFirebase ? "true" : "false" : fbdo.errorReason().c_str());
    }
  }    
  
}
