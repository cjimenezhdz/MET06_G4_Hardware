#include <Servo.h>

Servo Grifo;  //create servo object to control a servo

const int ServoPin = 5; //lo tenia en la 15

const int buttonServoPin = 14;  //pin del pulsador que regula el servo
int buttonServoState = 0;     //estado del pulsador que regula el servo

const int buttonServoEmergencyPin = 16;    //pin pulsador emergencia
int buttonServoEmergencyState = 0;    //estado pulsador emergencia

int servoPos = 0;
int servoMode = 0;

const int ledYELLOW = 4; 

void servo_setup() {
  Grifo.attach(ServoPin);                           // attaches the servo to SERVOPIN
  pinMode(buttonServoPin, INPUT);
  pinMode(buttonServoEmergencyPin, INPUT);
  pinMode(ledYELLOW, OUTPUT);
}

void servo_loop() {

  switch (servoMode) {
    case 0:                           //GRIFO CERRADO
      servoPos = 0;
      analogWrite(ledYELLOW, 0);
      break;
    case 1:                           //GRIFO CAUDAL MEDIO
      servoPos = 90;
      analogWrite(ledYELLOW, 50);
      /*delay(200);
      analogWrite(ledYELLOW, 0);
      delay(200);*/
      break;
    case 2:                           //GRIFO CAUDAL ALTO
      servoPos = 180;
      analogWrite(ledYELLOW, 255);
      /*delay(100);
      analogWrite(ledYELLOW, 0);
      delay(100);*/
      break;
    case 3:                           //GRIFO CERRADO EMERGENCIA
      servoPos = 0;
      analogWrite(ledYELLOW, 100);
    }

  Grifo.write(servoPos);
  delay(15);

  buttonServoState = digitalRead(buttonServoPin);
  buttonServoEmergencyState = digitalRead(buttonServoEmergencyPin);
  
  if(buttonServoState==HIGH || buttonServoEmergencyState == HIGH){

    if (buttonServoEmergencyState == HIGH) {
      servoMode = 3;
      Serial.println("EMERGENCY");
    }
  
    if (buttonServoState == HIGH) {
      servoMode++;
      if (servoMode > 2) {
        servoMode = 0;
      }
      //delay(600);
    }
    
    if (Firebase.ready()) {
      Serial.printf("Set tap State... %s\n", Firebase.RTDB.setFloat(&fbdo, F("/tap"), servoMode) ? "ok" : fbdo.errorReason().c_str());
    }
  
  } else if (Firebase.ready()) {
    
    Serial.printf("Get int ref... %s\n", Firebase.RTDB.getInt(&fbdo, F("/tap"), &servoMode) ? String(servoMode).c_str() : fbdo.errorReason().c_str());
  }
  
  
      
}