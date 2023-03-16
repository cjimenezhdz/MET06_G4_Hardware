
const int ledBLUE = 13;

const int buttonPin = 9;
int buttonState = 0;

void panic_setup() { 
 
  pinMode(ledBLUE, OUTPUT);
  pinMode(buttonPin, OUTPUT);

} 

void panic_loop() { 

  buttonState = digitalRead(buttonPin);

  if( buttonState == HIGH){
    digitalWrite(ledBLUE, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(5000);                  // keeps on HIGH the LED for 5 secs
  }else{
    digitalWrite(ledBLUE, LOW);  // turn the LED on (HIGH is the voltage level)
  }

}
