#include <Servo.h>

Servo Grifo;  // create servo object to control a servo

int buttonServoPin; //pendiente asignar puerto
int buttonServoState;

int buttonServoEmergencyPin; // pendiente asignar puerto
int buttonServoEmergencyState; 

int servoCont=0;

int ledYELLOW; // pendiente asignar puerto analógico

void setup() {
  Grifo.attach(4);  // attaches the servo on GIO2 to the servo object
}

void loop() {
  int servoPos;
  
  buttonServoState=digitalRead(buttonServoPin);
  
  if (buttonServoState=HIGH){

    if(servoCont<3){       
      for (pos=0;pos>=servoCont*90;pos +=90){
        Grifo.write(pos);
        delay(15);
        analogWrite(ledYELLOW,pos);
      }
      servoCont++;
    }else if(servoCont=3){
      Grifo.write(0);
      delay(15);
      servoCont==0; 
      analogWrite(ledYELLOW,0);
    }
  }
  
  buttonServoEmergencyState=digitalRead(buttonServoEmergencyPin);
  if (Button_statebuttonServoEmergencyState_emergencia=HIGH){
    Grifo.write(0);
    delay(15);
    analogWrite(ledYELLOW,0);
  }
} 
    
    