int temp_cont = 0;

void setup() { 

  Serial.begin(9600);
  //presence_setup();
  temperature_setup();
  panic_setup();

} 

void loop() { 

  //presence_loop();
  if (temp_cont == 5){    //monitorización cada 5seg
    temperature_loop();
    temp_cont = 0;
  }
  temp_cont ++;
  
  //panic_loop();

}
