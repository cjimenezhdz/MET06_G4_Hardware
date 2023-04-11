int pirPinDown =5; 
int pirStateDown=0;
int pirPinUp =14; 
int pirStateUp=0;
float sensorDistance=0.5;
float fallingTime=sqrt((2*sensorDistance)/9.8);

void presence_setup() { 
  pinMode(pirPinDown, INPUT);
  pinMode(pirPinUp, INPUT);
} 

void presence_loop() { 

  while(true){
    
    pirStateUp = digitalRead(pirPinUp); //read state of the PIR 
  
    if (pirStateUp == HIGH) { 
         delay(fallingTime);
    }
       /* Serial.println("UP Motion!"); //if the value read is low, there  was no motion 
        
    } else { 
      
      Serial.println("UP No motion"); //if the value read was high, there was motion 
    } */
    
   
    pirStateDown = digitalRead(pirPinDown); //read state of the PIR
  
    /*
    if (pirStateDown == HIGH) { 
        
        Serial.println("DOWNMotion!"); //if the value read is low, there  was no motion 
        
    } else { 
      
     Serial.println("Down No motion"); //if the value read was high, there was motion 
    }*/
  
    if(pirStateUp==HIGH && pirStateDown==HIGH){
      Serial.println("Caida Detectada");
    }
    
  }
  
}
