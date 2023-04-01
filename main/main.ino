int temp_cont=0;
String input ;
boolean bucle=false;

void setup() { 
  panic_setup();
  Serial.begin(9600);
  //presence_setup();
 
 /* temp_hum_setup();
  servo_setup();
  SmartLight_setup();*/

  // Preguntar al usuario qué loop quiere generar
}

void loop() { 


 /* Serial.println("---"); 
  Serial.println(Serial.readString());
 // Leer la respuesta del usuario
    Serial.flush();
    Serial.println("¿Qué loop quieres generar? (Escribe 'presence', 'panic', 'temp_hum', 'servo' o 'SmartLight')");

    while (Serial.available() == 0) {
      }   
    input = Serial.parseInt();
    
    Serial.println(input);*/
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

      case 'T':
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
