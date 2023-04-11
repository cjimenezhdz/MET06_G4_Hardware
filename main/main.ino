
int input ;

void setup() { 
  
  Serial.begin(9600);
  //presence_setup();
  panic_setup();
  //temp_hum_setup();
  //servo_setup();
  //SmartLight_setup();

  // Preguntar al usuario qué loop quiere generar
  /*
  Serial.println("¿Qué loop quieres generar? Escribe: \n"
    "'1' -> Emergencia temperatura/humedad, \n"
    "'2' -> Emergencia caída, \n"
    "'3' -> Emergencia botón pánico, \n"
    "'4' -> Smart Light, \n"
    "'5' -> Grifo");

  // Leer la respuesta del usuario
  
  while (Serial.available() == 0) {
      }   
  input = Serial.readString().toInt();
    switch (input){
    case 1:
      temp_hum_setup();
      break;
    
    case 2:
      presence_setup();
      break;

    case 3:
      panic_setup();
      break;

    case 4:
      SmartLight_setup();
      break;
    
    case 5:
      servo_setup();
      break;

    }
    */
}

void loop() { 

  switch (input){
    case 1:
      temp_hum_loop();
      break;
    
    case 2:
      presence_loop();
      break;

    case 3:
      panic_loop();
      break;

    case 4:
      SmartLight_loop();
      break;
    
    case 5:
      servo_loop();
      break;

    
    default:
      Serial.println("Opción inválida, por favor intenta de nuevo");
      break;
  }

  panic_loop();
}
