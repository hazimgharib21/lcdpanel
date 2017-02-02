//  include all library needed
#include <Adafruit_MPR121.h> // library for MPR121 touch sensor
#include <Wire.h> // library for i2c (needed with Adafruit_MPR121.h)
#include <SoftwareSerial.h> // Use softwareSerial to use serial com with other pin

//  Define needed variable for code
#define arraySize(x) ((sizeof(x)) / (sizeof(x[0]))) // to get array length
#define outputLogic true // Output pin logic

// output pin for 7 segment
#define data_0  22
#define latch_0 24
#define clock_0   26
#define data_1  28
#define latch_1 30
#define clock_1   32

// output pi for led
#define data_2  34
#define latch_2 36
#define clock_2   38
#define data_3  43
#define latch_3 45
#define clock_3   47

// output pin for buzzer and start LED
#define buzzer 49
#define startLED 8

// Initialize timer
unsigned long pinMillis = 0;
unsigned long timerMillis = 0;
unsigned long endMillis = 0;
unsigned long testMillis = 0;
//unsigned long resetMillis = 0;
unsigned long runningMillis = 0;
unsigned long updateCount = 0;
int stillRunning = 1000;
int resetUpdate = 1000;
int bunyiUpdate = 500;
int endUpdate = 20000;
int timerUpdate = 1000;
//int panelUpdate = 1000;
int pinUpdate = 10;
//int touchInput = 17;

boolean buzzerBol = false;
uint16_t lasttouched = 0;
uint16_t currtouched = 0;
boolean mpr = false;

// initialize variable
boolean start = false;
int count = 30;

/*
 * treshold value
 * Decrease the treshold value to increase the sensitivity
 */
int treshold[17] = {
  8, //0
  8, //1
  8, //2
  10, //3
  10, //4
  10, //5
  10, //6
  10, //7
  10, //8
  10, //9
  10, //10
  10, //11
  10, //12
  10, //13
  10, //14
  10, //15
  10  //16
};

/*
 * The smooth input from touch panel will be stored here
 * update every 50ms in pinData() function
 */
float output[17] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

/*
 * The average data from touch panel input(release)
 * 50 sample are taken to get the value
 */
int relValue[17] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

//  Hex number to use with 7segment code
int numHex[] = {192, 249, 164, 176, 153, 146, 130, 248, 128, 152, 0};

// This is use for the 7 segment pattern while waiting
int pusingPusing[] = {254, 253, 243, 239, 223 , 127};
int pusingLagi = 0;

//  Bin number to use with led
int numBin[] = {
  1, 
  2, 
  4, 
  8, 
  16, 
  32, 
  64, 
  128, 
  256, 
  512, 
  1024, 
  2048, 
  4096, 
  8192, 
  16384,
  32768,
  65536,
  0
};

// use to store the first 200 value of touch panel
int average[200] = {};

// variable
int endGame = 20;
int noTouch = 22;
int resetTouch = 21;
boolean nasihat = false;

// initialize SoftwareSerial pin
SoftwareSerial mySerial(15, 16); // RX, TX

// initialize mpr121
Adafruit_MPR121 mprA = Adafruit_MPR121();
Adafruit_MPR121 mprB = Adafruit_MPR121();

// the array and struct use for output initialization
uint8_t dataPin[] = {
  data_0,
  data_1,
  data_2,
  data_3,
};

uint8_t clockPin[] = {
  clock_0,
  clock_1,
  clock_2,
  clock_3,
};

uint8_t latchPin[] = {
  latch_0,
  latch_1,
  latch_2,
  latch_3,
};

struct outputStruct{
  uint8_t pin;
  boolean state;
} latch[arraySize(latchPin)], data[arraySize(dataPin)], clk[arraySize(clockPin)];



void setup() {

  initialization();

  // initialize 7 segment and led with initial value
  Countdown(dataPin, clockPin, latchPin, 0);
  led(dataPin, clockPin, latchPin, 8);

}

void loop() {

    // Use for debugging the hang problem
  if((millis() - runningMillis) >= stillRunning){
    Serial.print("Still running for " );
    int minit = (updateCount) / 60;
    Serial.print(minit);
    Serial.println(" minutes");
    runningMillis = millis();
    Serial.print("Free Ram : ");
    Serial.println(freeRam());
    updateCount++;
  }

  delay(10);
   
  // check user input every 50ms 
  if((millis() - pinMillis) >= pinUpdate){

    // Initialize touch led and 7 segment
    Countdown(dataPin, clockPin, latchPin, 0);
    led(dataPin, clockPin, latchPin, 17);
    pinMillis = millis();
    pinData();

      
    if(getPinTouched() == 16){

      digitalWrite(startLED, HIGH);
      for(int j = 0; j < 5; j++){

        digitalWrite(buzzer, HIGH);
        delay(50);
        digitalWrite(buzzer, LOW);
        delay(50);
        digitalWrite(startLED, LOW);
      }

        mySerial.write(16);
        start = true;
      }
  }

  // Start game when touch panel is touched
  while(start){
    
    // Always update for 7 segment
    Countdown(dataPin, clockPin, latchPin, count);
    
    // Always update the smooth input from touch panel(release)
    pinData();

    delay(10);
    
    // Here we implement debounce for the touched input
    currtouched = getPinTouched();

    for(uint8_t i = 0; i < 16; i++){

      if((numBin[currtouched] & _BV(i)) && !(numBin[lasttouched] & _BV(i))){

        mySerial.write(i);
        led(dataPin, clockPin, latchPin, currtouched);
        bebunyi(1);
      }

      if(!(numBin[currtouched] & _BV(i)) && (numBin[lasttouched] & _BV(i))){

        led(dataPin, clockPin, latchPin, 17);
        bebunyi(0);
        }
    }

    lasttouched = currtouched;
    
    /*
     * Update the countdown timer every 1 second
     */
    if((millis() - timerMillis) >= timerUpdate){

      timerMillis = millis();
      count--;
    }

    // endGame when counter reach zero
    if(count == 0){
      
      nasihat = true;
      start = false;
      mySerial.write(endGame);
      count = 30;
      Countdown(dataPin, clockPin, latchPin, numHex[10]); 
      endMillis = millis(); 
      for(int i = 0; i < 6; i++){
        digitalWrite(buzzer, HIGH);
        delay(50);
        digitalWrite(buzzer, LOW);
        delay(50);
      }
    }
  }

  // The waiting part while the led scroller give advice
  while(nasihat){

    delay(10);
    pusingLagi++;

    // The smooth data from touch panel is still updated
    if((millis() - pinMillis) >= pinUpdate){
      pinMillis = millis();
      pinData();
    }
    if((millis() - endMillis) >= endUpdate){
      endMillis = millis();
      nasihat = false;
    }

  // the 7 segment pattern while waiting
  digitalWrite(latchPin[1],LOW);
  shiftOut(dataPin[1],clockPin[1],MSBFIRST,pusingPusing[pusingLagi]);
  digitalWrite(latchPin[1],HIGH);
  
  digitalWrite(latchPin[0],LOW);
  shiftOut(dataPin[0],clockPin[0],MSBFIRST,pusingPusing[pusingLagi]);
  digitalWrite(latchPin[0],HIGH);

  if(pusingLagi == 6){
    pusingLagi = 0;
  }

  delay(50);
  
  }
  
}
