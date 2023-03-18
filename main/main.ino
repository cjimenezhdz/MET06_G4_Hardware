int temp_cont = 0;

void setup() { 

  Serial.begin(9600);
  //presence_setup();
 panic_setup();
  temp_hum_setup();

} 

void loop() { 

  //presence_loop();
  if (temp_cont == 400000){    //monitorización cada 5seg, fcloclk es de 80 MHz(T=12,5ns) y queremos un T=5s)
      temp_hum_loop();
      temp_cont = 0;
  }
  temp_cont ++;
  
  panic_loop();
  

}
