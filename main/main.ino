//int temp_cont=0;
int input ;
//boolean bucle=false;

void setup() { 
  
  Serial.begin(9600);
  /*presence_setup();
  //panic_setup();
  temp_hum_setup();
  servo_setup();
  SmartLight_setup();*/

  // Preguntar al usuario qué loop quiere generar
  Serial.println("¿Qué loop quieres generar? Escribe: 
    \n'1'-> Emergencia temperatura/humedad, 
    \n'2'-> Emergencia caida, 
    \n'3'-> Emergencia botón panico
    \n'4'-> Smart Light
    \n'5'-> Grifo");
}

void loop() { 

  // Leer la respuesta del usuario
  input = Serial.readString().toInt();
  Serial.flush();

  switch (input){
    case 1:
      main_temp_hum();
      break;
    
    case 2:
      main_presence();
      break;

    case 3:
      main_panic();
      break;

    case 4:
      main_smart_light();
      break;
    
    case 5:
      main_grifo();
      break;

    
    default:
      Serial.println("Opción inválida, por favor intenta de nuevo");
      break;
  }


 /* Serial.println("---"); 
  Serial.println(Serial.readString());
 // Leer la respuesta del usuario
    Serial.flush();
    

    while (Serial.available() == 0) {
      }   
    input = Serial.parseInt();
    
    Serial.println(input);
     bucle=true;
    // Ejecutar el loop correspondiente según la respuesta del usuario
    switch (Serial.readString().toInt()) {
      case 1:
      while(bucle){
        presence_loop();
      }
        break;

      case 2:
      
      while(bucle){
        panic_loop();
        Serial.println('2');
      }
        break;

      case '3:
        // Monitorizar la temperatura cada 5 segundos
        if (temp_cont == 400000){    //monitorización cada 5seg, fcloclk es de 80 MHz(T=12,5ns) y queremos un T=5s)
          temp_hum_loop();
          temp_cont = 0;
        }
        temp_cont ++;
        break;

      case 'S':
        servo_loop();
        break;

      case 'L':
        SmartLight_loop();
        break;

      default:
        Serial.println("Opción inválida, por favor intenta de nuevo");
        break;
    }

  //}*/
}
