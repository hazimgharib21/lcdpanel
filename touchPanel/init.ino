void initialization(){
  initSerial();
  initMPR();
  initOutput();
}

void initSerial(){
  Serial.begin(9600);
  mySerial.begin(2400);
  while(!Serial){
    delay(10); 
  }
}

/*
 * MPR initialization
 */
void initMPR(){
  
  Serial.println("MPR121 Capacitive Touch Sensor Initialization");

  if (!mprA.begin(0x5A)) {
    Serial.println("MPR121 0x5A not found, check wiring?");
    while (1);
  }else{
    Serial.println("MPR121 0x5A found!");
  }
  // add 0x5B achieve by cutting the jumper on add pin and shorting add pin to 3.3v pin
  if (!mprB.begin(0x5B)) {
    Serial.println("MPR121 0x5B not found, check wiring?");
    while (1);
  }else{
    Serial.println("MPR121 05xB found!");
  }

  for(int i = 0; i < 17; i++){
    relValue[i] = relVal(i);
  }
}


/*
 * Output initialization
 */
void initOutput(){
  
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
