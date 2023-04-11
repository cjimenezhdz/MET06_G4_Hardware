const int button = 10;
const int ledButton = 12;
int buttonStateLight = 0;
int buttonModeLight = 0;

const int LightSensor = 0;
const int ledLightSensor = 4;
int LightState = 0;
int LightMode = 0;

void SmartLight_setup() { 
 
  pinMode(button, INPUT);
  pinMode(ledButton, OUTPUT);
  pinMode(LightSensor, INPUT);
  pinMode(ledLightSensor, OUTPUT);
  
} 

void SmartLight_loop() { 

  while(true){
    buttonStateLight = digitalRead(button);
  
    if (buttonStateLight == HIGH) {
      buttonModeLight++;
      if (buttonModeLight > 3) {
        buttonModeLight = 0;
      }
      delay(1000);
    }
  
  
    switch (buttonModeLight) {
      case 0:                           
        analogWrite(ledButton, 0);
        Serial.println("Modo1");
        break;
      case 1:                           
        analogWrite(ledButton, 50);
        Serial.println("Modo2");
        break;
      case 2:                           
        analogWrite(ledButton, 150);
        Serial.println("Modo3");
        break;
      case 3:                          
        analogWrite(ledButton, 250);
        Serial.println("Modo4");
        break;      
    }
  }
}
