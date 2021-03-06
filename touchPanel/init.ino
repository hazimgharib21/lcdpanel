/*
  Initialization for serial, output pin and MPR121
 */
void initialization(){
  initSerial();
  initOutput();
  initMPR();
}

/*
  Serial Initialization
 */
void initSerial(){
  Serial.begin(9600);
  mySerial.begin(2400);
  while(!Serial){
    delay(10); 
  }

  mySerial.write(resetTouch);
}

/*
 * MPR initialization
 */
void initMPR(){
  
  Serial.println("MPR121 Capacitive Touch Sensor Initialization");

  // Initializing the MPR121 
  while(!mprA.begin(0x5A)) {
    Serial.println("MPR121 0x5A not found, check wiring?");
  }

  // address 0x5B achieve by cutting the jumper on add pin and shorting add pin to 3.3v pin
  while(!mprB.begin(0x5B)) {
    Serial.println("MPR121 0x5B not found, check wiring?");
  }

  Serial.println("MPR121 found!");

  // This loop is use to get the initial value of touch sensor
  for(int i = 0; i < 17; i++){
    relValue[i] = relVal(i);
  }

}

/*
 * Output initialization
 */
void initOutput(){

  // buzzer and start LED pin initialization
  pinMode(startLED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(startLED, LOW);
  digitalWrite(buzzer, LOW);
  
  // touch panel led and 7 segment pin initialization 
  for(uint8_t i = 0; i < arraySize(latchPin); i++){
    latch[i].pin = latchPin[i];
    latch[i].state = !outputLogic;
    pinMode(latch[i].pin, OUTPUT);
    digitalWrite(latch[i].pin, latch[i].state);
  }

  for(uint8_t i = 0; i < arraySize(dataPin); i++){
    data[i].pin = dataPin[i];
    data[i].state = !outputLogic;
    pinMode(data[i].pin, OUTPUT);
    digitalWrite(data[i].pin, data[i].state);
  }

  for(uint8_t i = 0; i < arraySize(clockPin); i++){
    clk[i].pin = clockPin[i];
    clk[i].state = !outputLogic;
    pinMode(clk[i].pin, OUTPUT);
    digitalWrite(clk[i].pin, clk[i].state);
  }
}

void bebunyi(int bunyik){
  if(bunyik == 1){
    digitalWrite(buzzer, HIGH);
  }
  if(bunyik == 0){
    digitalWrite(buzzer, LOW);
  }
}

void software_Reset() // Restarts program from beginning but does not reset the peripherals and registers
{
  asm volatile ("  jmp 0");  
}  

int freeRam () 
{
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}
