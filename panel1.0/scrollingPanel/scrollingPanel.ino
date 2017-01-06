#include <SPI.h>
#include <DMD.h>
#include <TimerOne.h>
#include "SystemFont5x7.h"
#include "Arial_Black_16.h"

// Fire up the DMD library as dmd
#define WIDTH 3
#define HEIGHT 1
DMD dmd(WIDTH, HEIGHT);

char *ayat_0 = "Sile Tekan Setat!!!";
char *ayat_1 = "Tertekan Satu";
char *ayat_2 = "Dua la sial";
char *ayat_3 = "pukimak tiga";
char *ayat_4 = "empat babi";
char *ayat_5 = "lima abah kau";
char *ayat_6 = "enam pukimak";
char *ayat_7 = "tujuh lahabau";
char *ayat_8 = "lapan cipan";
char *ayat_9 = "semilan lancau";
char *ayat_10 = "sapuloooooooooooooooooooo";
char *ayat_11 = "satusatu";
char *ayat_12 = "satudua";
char *ayat_13 = "satutiga";
char *ayat_14 = "satuempat";
char *ayat_15 = "satulima";
char *ayat_16 = "Satuenam";
int number = 0;

void ScanDMD(){
  dmd.scanDisplayBySPI();
}

void setup(void){
  Timer1.initialize(3000);
  Timer1.attachInterrupt(ScanDMD);

  dmd.clearScreen(true);
  Serial.begin(9600);

  panelInit(ayat_0);
}

void loop(){
  number = 0;

  while(Serial.available() == 0){panelDisplay();};
  
  while(Serial.available() > 0){
    byte num = Serial.read();
    number = (number * 10) + (num - '0');
    delay(5);
    
    
    
    
    
  }
  switch(number){
      case 0:
        panelInit(ayat_0);
        break;
      case 1:
        panelInit(ayat_1);
        break;
      case 2:
        panelInit(ayat_2);
        break;
      case 3:
        panelInit(ayat_3);
        break;
        case 4:
        panelInit(ayat_4);
        break;
      case 5:
        panelInit(ayat_5);
        break;
      case 6:
        panelInit(ayat_6);
        break;
        case 7:
        panelInit(ayat_7);
        break;
      case 8:
        panelInit(ayat_8);
        break;
      case 9:
        panelInit(ayat_9);
        break;
      case 10:
        panelInit(ayat_10);
        break;
      case 11:
        panelInit(ayat_11);
        break;
      case 12:
        panelInit(ayat_12);
        break;
        case 13:
        panelInit(ayat_13);
        break;
      case 14:
        panelInit(ayat_14);
        break;
      case 15:
        panelInit(ayat_15);
        break;
      case 16:
        panelInit(ayat_16);
        break;
  }
  Serial.println(number);
  
  
}



