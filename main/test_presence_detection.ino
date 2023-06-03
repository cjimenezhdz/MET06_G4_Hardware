int pirPinUp=5; 
int pirStateUp=0;

int pirPinDown=0; 
int pirStateDown=0;

float sensorDistance=0.5;
float fallingTime=sqrt((2*sensorDistance)/9.8);  //1s

unsigned long tiempoPresenciaAnterior = 0;
unsigned long tiempoPresenciaActual = 0;
const unsigned long intervaloPresencia = 5000;

void presence_setup() { 
  pinMode(pirPinDown, INPUT);
  pinMode(pirPinUp, INPUT);
} 

void presence_loop() { 

pirStateUp = digitalRead(pirPinUp); //read state of the PIR 

if (pirStateUp == HIGH) { 
   
        Serial.println("UP Motion!");
    }

/*
    if(!possible_fall){
    pirStateUp = digitalRead(pirPinUp); //read state of the PIR 
    pirStateDown = digitalRead(pirPinDown); //read state of the PIR
    }
    
    if (pirStateUp == HIGH && pirStateDown != HIGH) { 
        possible_fall=false;
        tiempoPresenciaActual = millis();
    }
      
      
     //delay(fallingTime);
    // Serial.println("UP Motion!"); //if the value read is low, there  was no motion 

    if(tiempoPresenciaActual - tiempoPresenciaAnterior >= fallingTime){
      
    
     pirStateDown = digitalRead(pirPinDown); //read state of the PIR
          if(pirStateDown==HIGH){
          //Serial.println("----------CAIDA DETECTADA------------");
          //delay(5000);
          }
    }else { 
      
      //Serial.println("UP No motion"); //if the value read was high, there was motion 
    }


    }


/*
    pirStateUp = digitalRead(pirPinUp); //read state of the PIR 
    pirStateDown = digitalRead(pirPinDown); //read state of the PIR
    
    if (pirStateUp == HIGH && pirStateDown != HIGH) { 
      
     delay(fallingTime);
    // Serial.println("UP Motion!"); //if the value read is low, there  was no motion 
          
     pirStateDown = digitalRead(pirPinDown); //read state of the PIR
          if(pirStateDown==HIGH){
          //Serial.println("----------CAIDA DETECTADA------------");
          //delay(5000);
          }
    }else { 
      
      //Serial.println("UP No motion"); //if the value read was high, there was motion 
    }
*/

}
