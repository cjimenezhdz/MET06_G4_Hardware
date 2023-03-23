int pirPin = 13; 
int pirState = 0;
bool motionState = false;

const int ledRED = 5;

void presence_setup() { 
  //Serial.begin(9600);
  pinMode(pirPin, INPUT);
  pinMode(ledRED, OUTPUT);
} 

void presence_loop() { 
  pirState = digitalRead(pirPin); //read state of the PIR 
 
  if (pirState == HIGH) { 
      digitalWrite(ledRED, HIGH);  // turn the LED on (HIGH is the voltage level)
      delay(5000);
      Serial.println("Motion!"); //if the value read is low, there  was no motion 
      if (motionState = false){
        motionState = true;
      }
  } else { 
    digitalWrite(ledRED, LOW);  // turn the LED on (HIGH is the voltage level)
    Serial.println("No motion"); //if the value read was high, there was motion 
    if (motionState = true){
        motionState = false;
      }
  } 
 
  //delay(500); 
}
