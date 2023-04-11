
const int ledBLUE = 3;
const int buttonPin = 13;
int buttonState = 0;

boolean bucle=false;

void panic_setup() { 
 
  pinMode(ledBLUE, OUTPUT);
  pinMode(buttonPin, OUTPUT);

} 

void panic_loop() { 

 while(!bucle){
    buttonState = digitalRead(buttonPin);
  
    if( buttonState == HIGH){
      digitalWrite(ledBLUE, HIGH);  // turn the LED on (HIGH is the voltage level)
    }else{
      digitalWrite(ledBLUE, LOW);  // turn the LED on (HIGH is the voltage level)
    }
  }
}
