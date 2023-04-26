
int input ;

void setup() { 
  
  Serial.begin(9600);
  //panic_setup();


  // Preguntar al usuario qué loop quiere generar
  ///*
  Serial.println("¿Qué loop quieres generar? Escribe: \n"
    "'1' -> Emergencia temperatura/humedad, caída y botón pánico\n"
    "'2' -> Smart Light, \n"
    "'3' -> Grifo");

  // Leer la respuesta del usuario
  
  while (Serial.available() == 0) {
      }   
  input = Serial.readString().toInt();
    switch (input){
    case 1:
      temp_hum_setup();
      //presence_setup();
      //panic_setup();
      break;
    
    case 2:
      SmartLight_setup();
      break;

    case 3:
      servo_setup();
      break;
    }
    //*/
}

void loop() { 

///*
  switch (input){
    case 1:
      while(true){
        temp_hum_loop();
        presence_loop();
        panic_loop();
      }
      break;
    
    case 2:
      SmartLight_loop();
      break;

    case 3:
      servo_loop();
      break;

    default:
      Serial.println("Opción inválida, por favor intenta de nuevo");
      break;
  }
//*/
  
  //panic_loop();
}
