int pirPinUp=5; 
int pirStateUp=0;

int pirPinDown=13; 
int pirStateDown=0;

float sensorDistance=0.25;
float fallingTime=sqrt((2*sensorDistance)/9.8);

void presence_setup() { 
  pinMode(pirPinDown, INPUT);
  pinMode(pirPinUp, INPUT);
} 

void presence_loop() { 
    
  while(true){

    pirStateUp = digitalRead(pirPinUp); //read state of the PIR 
    pirStateDown = digitalRead(pirPinDown); //read state of the PIR
    
    if (pirStateUp == HIGH && pirStateDown != HIGH) { 
      
     delay(fallingTime);
     Serial.println("UP Motion!"); //if the value read is low, there  was no motion 
          
     pirStateDown = digitalRead(pirPinDown); //read state of the PIR
          if(pirStateDown==HIGH){
          Serial.println("----------CAIDA DETECTADA------------");
          delay(5000);
          }
    }else { 
      
      Serial.println("UP No motion"); //if the value read was high, there was motion 
    }

  }

}
