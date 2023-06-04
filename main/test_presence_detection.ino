int pirPinUp=5; 
int pirStateUp=0;

int pirPinDown=0; 
int pirStateDown=0;

float sensorDistance=0.31;
float fallingTime=sqrt((2*sensorDistance)/9.8);  //1s

unsigned long tiempoPresenciaAnterior = 0;
unsigned long tiempoPresenciaActual = 0;
const unsigned long intervaloPresencia = 5000;
unsigned long tiempoDown=0;
bool possible_fall=false;
bool walking=false;

void presence_setup() { 
  pinMode(pirPinDown, INPUT);
  pinMode(pirPinUp, INPUT);
} 

void presence_loop() { 
/*
pirStateUp = digitalRead(pirPinUp); //read state of the PIR 
pirStateDown = digitalRead(pirPinDown); //read state of the PIR

if (pirStateUp == HIGH) { 
      tiempoPresenciaActual = millis();      
      Serial.println("*******************************UP Motion!****************************************");
      Serial.println(tiempoPresenciaActual);
    }
    
if (pirStateDown == HIGH) { 
     tiempoPresenciaAnterior = millis();     
     Serial.println("//////////////DOWN Motion!//////////");
     Serial.println(tiempoPresenciaAnterior-tiempoPresenciaActual);
    }
    
/*
if (pirStateUp == HIGH && !possible_fall) { 
      tiempoPresenciaActual = millis();      
      Serial.println("*******************************UP Motion!****************************************");
      Serial.println(tiempoPresenciaActual);
      possible_fall=true;
    }
    
if (pirStateDown == HIGH && possible_fall) { 
     tiempoPresenciaAnterior = millis();     
     Serial.println("//////////////DOWN Motion!//////////");
     possible_fall=false;
     Serial.println(tiempoPresenciaAnterior-tiempoPresenciaActual);
    }else if (pirStateDown == HIGH){

    Serial.println("-----------------NO CAIDA----------------");

}

*/   


    if(possible_fall){
      
      tiempoPresenciaActual = millis();
      pirStateDown = digitalRead(pirPinDown); //read state of the PIR
      tiempoDown = tiempoPresenciaActual - tiempoPresenciaAnterior;
      
      if(pirStateDown==HIGH && tiempoDown <= 850){
        possible_fall=false;
        Serial.println(tiempoDown);
        Serial.println("*******************************ANDANDOOOOOOOO!****************************************");
      }else if(pirStateDown==HIGH && tiempoDown > 850 && tiempoDown < 3000){
        Serial.println(tiempoDown);
        Serial.println("-----------------Caida DETECTADA!------------------------");   
        possible_fall=false;
      }else if(tiempoDown >= 3000){
        Serial.println(tiempoDown);
        Serial.println("///////////////////NADAAAAAAA!/////////////////////");
        possible_fall=false;
      }
      
    }else{
    
    pirStateUp = digitalRead(pirPinUp); //read state of the PIR 
    pirStateDown = digitalRead(pirPinDown); //read state of the PIR

    if (pirStateUp == HIGH && pirStateDown != HIGH) { 
        possible_fall=true;
        tiempoPresenciaAnterior = millis();
        Serial.println(tiempoPresenciaAnterior);
        Serial.println("???????????????????????????????????????????????????????????????????????????????");
    }else{
        Serial.println("..........................................................?");
    }
    
    }
    

}
