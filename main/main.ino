
void setup() { 

  Serial.begin(9600);
  //presence_setup();
  temperature_setup();
  panic_setup();

} 

void loop() { 

  //presence_loop();
  temperature_loop();
  panic_loop();

}
