const int button = 10;
const int ledButton = 12;
int buttonStateLight = 0;
int buttonModeLight = 0;

const int LightSensor = 0;
const int ledLightSensor = 4;

int lightIntensity = 0;

void SmartLight_setup() { 
 
  pinMode(button, INPUT);
  pinMode(ledButton, OUTPUT);
  pinMode(LightSensor, INPUT);
  pinMode(ledLightSensor, OUTPUT);
  
} 

void SmartLight_loop() { 

  buttonStateLight = digitalRead(button);

  if (buttonStateLight == HIGH) {
    buttonModeLight++;
    if (buttonModeLight > 3) {
      buttonModeLight = 0;
    }
    delay(750);
  
    switch (buttonModeLight) {
      case 0:                           
        lightIntensity = 0;
        break;
      case 1:                           
        lightIntensity = 50;
        break;
      case 2:                           
        lightIntensity = 150;
        break;
      case 3:                          
        lightIntensity = 250;
        break;      
    }

    if (Firebase.ready()) {
      Serial.printf("Set smart light intensity... %s\n", Firebase.RTDB.setFloat(&fbdo, F("/smartLight"), lightIntensity) ? "ok" : fbdo.errorReason().c_str());
    }

  } else if (Firebase.ready()) {
      Serial.printf("Get int ref... %s\n", Firebase.RTDB.getInt(&fbdo, F("/smartLight"), &lightIntensity) ? String(lightIntensity).c_str() : fbdo.errorReason().c_str());
  }
  
  analogWrite(ledButton, lightIntensity); // Actualizamos la intensidad del LED
}
