int pirPinDown =5; 
int pirStateDown=0;
int pirPinUp =2; 
int pirStateUp=0;


void presence_setup() { 
  pinMode(pirPinDown, INPUT);
  pinMode(pirPinUp, INPUT);
} 

void presence_loop() { 
  //pirStateDown = digitalRead(pirPinDown); //read state of the PIR 
  pirStateUp = digitalRead(pirPinUp); //read state of the PIR 
  
 /* if (pirStateDown == HIGH) { 
      
      Serial.println("DOWNMotion!"); //if the value read is low, there  was no motion 
      
  } else { 
    
   // Serial.println("No motion"); //if the value read was high, there was motion 
  }*/

  if (pirStateUp == HIGH) { 
      
      Serial.println("UP Motion!"); //if the value read is low, there  was no motion 
      
  } else { 
    
    Serial.println("No motion"); //if the value read was high, there was motion 
  } 
 
  delay(500); 
}
