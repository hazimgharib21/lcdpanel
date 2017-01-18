#include <SPI.h>
#include <DMD.h>
#include <SoftwareSerial.h>
#include <TimerOne.h>
#include "SystemFont5x7.h"
#include "Arial_Black_16.h"

SoftwareSerial mySerial(2, 3); // Rxbiru, Txcokelat
// Fire up the DMD library as dmd
#define WIDTH 5
#define HEIGHT 1
DMD dmd(WIDTH, HEIGHT);

boolean gameStart = false;
char *ayat_mula = "BANK NEGARA MALAYSIA RM1,000,000                    CLICK START TO PLAY";
char *ayat_0 = "RM 30";
char *ayat_1 = "RM 200,000";
char *ayat_2 = "RM 800";
char *ayat_3 = "RM 2,000";
char *ayat_4 = "RM 1,500";
char *ayat_5 = "RM 12";
char *ayat_6 = "RM 600";
char *ayat_7 = "RM 600,000";
char *ayat_8 = "RM 60,000";
char *ayat_9 = "RM 800";
char *ayat_10 = "RM 250";
char *ayat_11 = "RM 200,000";
char *ayat_12 = "RM 300";
char *ayat_13 = "RM 7,000";
char *ayat_14 = "RM 120";
char *ayat_15 = "RM 100,000";
char *ayat_Sum = "You Spend";
char *nasihat1 = "You had RM1,000,000 but have spend nothing";
char *nasihat2 = "You know what you should spend on, however you still want to enjoy"; 
int num = 0;
int start = 0;
int sum = 0;

String myString;

void ScanDMD(){
  dmd.scanDisplayBySPI();
}

void setup(void){
  Timer1.initialize(3000);
  Timer1.attachInterrupt(ScanDMD);
  dmd.clearScreen(true);
  Serial.begin(9600);
  mySerial.begin(2400);

  pinMode(9, OUTPUT);
  panelInit(ayat_mula);
}

void loop(){
/*  
  if(mySerial.available()>0){
    Serial.println(mySerial.read());
  }
*/
  
  while(mySerial.available() == 0){panelDisplay();};
  
  if(mySerial.available() > 0){
    start = mySerial.read();
    delay(1);
    if(start = 16){
      gameStart = true;
      sum = 0;
    }
  }
  while(gameStart){
    dmd.clearScreen(true);
    panelDisplay();
    if(mySerial.available() > 0){
      num = mySerial.read();
      delay(1);
      Serial.println(num);
      switch(num){
      case 17:
        panelInit("RM 0");
        Serial.println("RM 0");
        //sum += 30;
        break;
      case 0:
        panelInit(ayat_0);
        //sum += 30;
        break;
      case 1:
        panelInit(ayat_1);
        //sum += 200000;
        break;
      case 2:
        panelInit(ayat_2);
        //sum += 800;
        break;
      case 3:
        panelInit(ayat_3);
        //sum += 2000;
        break;
      case 4:
        panelInit(ayat_4);
        //sum += 1500;
        break;
      case 5:
        panelInit(ayat_5);
        //sum += 12;
        break;
      case 6:
        panelInit(ayat_6);
        //sum += 600;
        break;
        case 7:
        panelInit(ayat_7);
        //sum += 600000;
        break;
      case 8:
        panelInit(ayat_8);
        //sum += 60000;
        break;
      case 9:
        panelInit(ayat_9);
        //sum += 800;
        break;
      case 10:
        panelInit(ayat_10);
        //sum += 250;
        break;
      case 11:
        panelInit(ayat_11);
        //sum += 200000;
        break;
      case 12:
        panelInit(ayat_12);
        //sum += 300;
        break;
      case 13:
        panelInit(ayat_13);
        //sum += 7000;
        break;
      case 14:
        panelInit(ayat_14);
        //sum += 120;
        break;
      case 15:
        panelInit(ayat_15);
        //sum += 100000;
        break;
    
    }
    }
    /*  case 17:
        gameStart = false;
        char sumChar[sizeof(sum)];
        myString=String(sum);
        myString.toCharArray(sumChar, sizeof(sumChar));
        panelInit(ayat_Sum);
        delay(2000);
        panelInit(sumChar);
        delay(2000);
        if(sum == 0){
          panelInit(nasihat1);
        }else if(sum > 0){
          panelInit(nasihat2);
        }
        delay(5000);
        panelInit(ayat_mula);
        break;*/
  
  }
  //Serial.println(number);
  
  
}


