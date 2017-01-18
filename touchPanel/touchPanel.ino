#include <Adafruit_MPR121.h>
#include <Wire.h>
#include <SoftwareSerial.h>

#define arraySize(x) ((sizeof(x)) / (sizeof(x[0])))

#define outputLogic true

// output pin for 7 segment
#define data_0 12
#define data_1 13
#define clock_0 14
#define clock_1 15
#define latch_0 16
#define latch_1 17

// Initialize timer
unsigned long panelMillis = 0;
unsigned long pinMillis = 0;
unsigned long timerMillis = 0;
int timerUpdate = 1000;
int panelUpdate = 2000;
int pinUpdate = 50;
int touchInput = 17;

// initialize variable
boolean start = false;
int count = 30;

/*
 * treshold value
 * Decrease the treshold value to increase the sensitivity
 */
int treshold[17] = {
  3, //0
  3, //1
  3, //2
  3, //3
  3, //4
  3, //5
  3, //6
  3, //7
  3, //8
  3, //9
  3, //10
  3, //11
  3, //12
  3, //13
  3, //14
  3, //15
  3  //16
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
/*
 * Hex number to use with 7segment code
 */
int numHex[] = {192, 249, 164, 176, 153, 146, 130, 248, 128, 152, 0};

int average[200] = {};


int endGame = 20;

SoftwareSerial mySerial(8, 9); // RX, TX

Adafruit_MPR121 mprA = Adafruit_MPR121();
Adafruit_MPR121 mprB = Adafruit_MPR121();

// initialize output for 7 segment
uint8_t dataPin[] = {
  data_0,
  data_1,
};

uint8_t clockPin[] = {
  clock_0,
  clock_1,
};

uint8_t latchPin[] = {
  latch_0,
  latch_1,
};

struct outputStruct{
  uint8_t pin;
  boolean state;
} latch[arraySize(latchPin)], data[arraySize(dataPin)], clk[arraySize(clockPin)];



void setup() {
  initialization();
  Countdown(dataPin, clockPin, latchPin, numHex[10]);
}

void loop() {
  /*
   * Always update the smooth input from touch panel(release)
   */
  if((millis() - pinMillis) >= pinUpdate){
      pinMillis = millis();
      pinData();
      
      if(getPinTouched() == 16){
        start = true;
      }
  }
  // start touch panel is push
  while(start){
    // Always update for 7 segment
    Countdown(dataPin, clockPin, latchPin, count);
    /*
     * Get touch panel input every 2 seconds
     */
     touchInput = getPinTouched();
     //Serial.println(data2);
    if((millis() - panelMillis) >= panelUpdate){
      panelMillis = millis();
      if(touchInput == 17){
        // do nothing  
      }else{
        mySerial.write(touchInput);
        Serial.println(touchInput);
        touchInput = 17;
      }
      
    }
    /*
     * Always update the smooth input from touch panel(release)
     */
    if((millis() - pinMillis) >= pinUpdate){
      pinMillis = millis();
      pinData();
    }
    /*
     * Update the countdown timer every 1 second
     */
    if((millis() - timerMillis) >= timerUpdate){
      timerMillis = millis();
      Serial.print("Countdown : ");
      Serial.println(count);
      count--;
    }
    // endGame when counter reach zero
    if(count == 0){
      start = false;
      count = 30;

      Countdown(dataPin, clockPin, latchPin, numHex[10]);     
      mySerial.write(endGame);
    }
  }
  
}
