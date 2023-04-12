
const int ledBLUE = 2;
const int buttonPin = 13;
int buttonState = 0;

void panic_setup() { 
 
  pinMode(ledBLUE, OUTPUT);
  pinMode(buttonPin, OUTPUT);

} 

void panic_loop() { 

 while(true){
    buttonState = digitalRead(buttonPin);
  
    if( buttonState == HIGH){
      digitalWrite(ledBLUE, HIGH);  // turn the LED on (HIGH is the voltage level)
      Serial.println("-------------BOTON PANICO!-------------");
    }else{
      digitalWrite(ledBLUE, LOW);  // turn the LED on (HIGH is the voltage level)
    }
  }
}
