
const int ledBLUE = 12;
const int buttonPin = 14;
int buttonState = 0;

void panic_setup() { 
 
  pinMode(ledBLUE, OUTPUT);
  pinMode(buttonPin, OUTPUT);

} 

void panic_loop() { 

    buttonState = digitalRead(buttonPin);
  
    if( buttonState == HIGH){
      digitalWrite(ledBLUE, HIGH);  // turn the LED on (HIGH is the voltage level)
    }else{
      digitalWrite(ledBLUE, LOW);  // turn the LED on (HIGH is the voltage level)
    }
    
}
