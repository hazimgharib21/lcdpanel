
#define arraySize(x) ((sizeof(x)) / (sizeof(x[0])))

#define debugMode false
#define serialMode true
#define baudrate 9600
#define outputLogic true

//#define panelUpdate 50
//#define timerUpdate 1000

int input = 0;
boolean start = false;
int panelUpdate = 50;
int timerUpdate = 1000;
unsigned long panelMillis = 0;
unsigned long timerMillis = 0;
int count = 0;

// OUTPUT
const uint8_t latch_0 = 2;
const uint8_t data_0 = 3;
const uint8_t clock_0 = 4;
const uint8_t latch_1 = 5;
const uint8_t data_1 = 6;
const uint8_t clock_1 = 7;

uint8_t outputPin[] = {
  data_0,
  clock_0,
  data_1,
  clock_1,
};

uint8_t latchPin[] = {
  latch_0,
  latch_1,
};

struct outputStruct{
  uint8_t pin;
  boolean state;
} output[arraySize(outputPin)], latch[arraySize(latchPin)];

void setup(){
  initSerial();
  initOutput();
}

void loop(){
  if(Serial.available() > 0){
    input = Serial.parseInt();
    if(input == 1) start = true;
  }
 
  while(start){
    if((millis() - panelMillis) >= panelUpdate){
      panelMillis = millis();
      Serial.println("update");
    }
    if((millis() - timerMillis) >= timerUpdate){
      timerMillis = millis();
      Serial.print("Countdown : ");
      Serial.println(count);
      count++;
    }
    if(count >= 26){
      Serial.println("times up");
      start = false;
      count = 0;
    }
  }

  
}

void initSerial(){
  if (debugMode || serialMode){
    Serial.begin(baudrate);
    while(!Serial){}
    if (serialMode) Serial.print(F("< Arduino ready >\n"));
    if (debugMode) Serial.print(F("< DebugMode begin >\n"));
  }
}

void initOutput(){
  for(uint8_t i = 0; i < arraySize(outputPin); i++){
    output[i].pin = outputPin[i];
    output[i].state = !outputLogic;
    pinMode(output[i].pin, OUTPUT);
    digitalWrite(output[i].pin, output[i].state);
  }
  for(uint8_t i = 0; i < arraySize(latchPin); i++){
    latch[i].pin = outputPin[i];
    latch[i].state = !outputLogic;
    pinMode(latch[i].pin, OUTPUT);
    digitalWrite(latch[i].pin, latch[i].state);
  }
}



