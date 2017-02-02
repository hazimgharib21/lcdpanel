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
unsigned long timeEnd = 0;
unsigned long timeNasihat = 0;
boolean gameStart = false;
boolean endGame = false;

// Initialize timer
int endUpdate = 20000;


// Initialize words
char *ayat_mula = "BANK NEGARA MALAYSIA RM1,000,000                    CLICK START TO PLAY";

// Display when user press start
char *ayat_Start = "GAME START!! SPEND YOUR MONEY!!";

/*
 * The Price of Things based on inputs
 */
char *ayat_0 = "RM 600,000"; // Bungalow House
char *ayat_1 = "RM 100,000"; // Piano
char *ayat_2 = "RM 600"; // Books
char *ayat_3 = "RM 120"; // Terrace House
char *ayat_4 = "RM 12"; // Hamburger
char *ayat_5 = "RM 7,000"; // Home theatre
char *ayat_6 = "RM 1,500"; // Designer Bags
char *ayat_7 = "RM 300"; // Sports Jersey
char *ayat_8 = "RM 2,000"; // Ensiklopedia
char *ayat_9 = "RM 200,000"; // Mini Van
char *ayat_10 = "RM 800"; // Kucing
char *ayat_11 = "RM 250"; // Foreign Language Class
char *ayat_12 = "RM 200,000"; // Lambo
char *ayat_13 = "RM 800"; // Bicycle
char *ayat_14 = "RM 30"; // 2KG of fruits
char *ayat_15 = "RM 60,000"; // Cincin
char *ayat_noTouch = "RM 0";

/*
 * Advice depends on the sum spend by user
 */
char *nasihat1 = "YOU HAD RM 1,000,000 AND HAD SPEND NOTHING";
char *nasihat2 = "YOU WORKED HARD FOR YOUR MONEY OR MAYBE MONEY COMES EASILY FOR YOU, SO YOU SPEND IT ON ITEMS YOU WANT"; 
char *nasihat3 = "EACH PERSON'S WANTS AND NEEDS MAY DIFFER, BASED ON THEIR BACKGROUND, UPBRINGING AND EARNING POWER";
char *nasihat4 = "YOU KNOW WHAT YOU SHOULD SPEND ON, HOWEVER, YOU STILL WANT TO ENJOY THE GOOD THINGS IN LIFE";
char *nasihat5 = "GOOD JOB! YOU HAVE A GOOD BALANCE BETWEEN NEEDS AND WANTS. YOU KNOW WHAT YOU PRIORITIES ARE";
char *nasihat6 = "CONGRATULATIONS YOU ARE A WISE SPENDER. YOU HAVE CHOSEN ITEMS THAT WOULD ENRICH YOUR LIFE";
char *nasihat7 = "YOU SPEND TO MUCH";

int num = 0;
int start = 0;
long sum = 0;
boolean noRepeat = false;
int nasihatEnd = 25;

// fucntion use for led scroller
void ScanDMD(){
  dmd.scanDisplayBySPI();
}

void setup(void){
  // Initialize led scroller
  Timer1.initialize(3000);
  Timer1.attachInterrupt(ScanDMD);
  dmd.clearScreen(true);

  // Initialize Serial
  Serial.begin(9600);
  mySerial.begin(2400);

  // Initialize the display
  panelInit(ayat_mula);
}

void loop(){
/*  
  if(mySerial.available()>0){
    Serial.println(mySerial.read());
  }
*/

  // needed to update the marquee effect
  while(mySerial.available() == 0){panelDisplay();};

  // Wait for user to press start
  if(mySerial.available() > 0){
    start = mySerial.read();
    delay(1);
    if(start == 16){
      gameStart = true;
      sum = 0;
    
      panelInit(ayat_Start);
    }
    if(start == 21){
      panelInit(ayat_mula);
    }
  }

  // game start
  while(gameStart){
    
    // needed for marquee effect
    panelDisplay();
    
    
    
    // wait for user input
    if(mySerial.available() > 0){
      num = mySerial.read();
      delay(1);
      Serial.println(num);

      // what to do with each user input
      switch(num){
        case 0:
          panelInit(ayat_0);
          sum += 30;
          break;
        case 1:
          panelInit(ayat_1);
          sum += 200000;
          break;
        case 2:
          panelInit(ayat_2);
          sum += 800;
          break;
        case 3:
          panelInit(ayat_3);
          sum += 2000;
          break;
        case 4:
          panelInit(ayat_4);
          sum += 1500;
          break;
        case 5:
          panelInit(ayat_5);
          sum += 12;
          break;
        case 6:
          panelInit(ayat_6);
          sum += 600;
          break;
        case 7:
          panelInit(ayat_7);
          sum += 600000;
          break;
        case 8:
          panelInit(ayat_8);
          sum += 60000;
          break;
        case 9:
          panelInit(ayat_9);
          sum += 800;
          break;
        case 10:
          panelInit(ayat_10);
          sum += 250;
          break;
        case 11:
          panelInit(ayat_11);
          sum += 200000;
          break;
        case 12:
          panelInit(ayat_12);
          sum += 300;
          break;
        case 13:
          panelInit(ayat_13);
          sum += 7000;
          break;
        case 14:
          panelInit(ayat_14);
          sum += 120;
          break;
        case 15:
          panelInit(ayat_15);
          sum += 100000;
          break;
        case 20:
          // end of game
          timeNasihat = millis();
          timeEnd = millis();
          toChar(sum);
          gameStart = false;
          endGame = true;
          break;
        case 21:
          // panel arduino restart
          panelInit(ayat_mula);
          gameStart = false;
          break;
        case 22:
          // no touch
          panelInit(ayat_noTouch);
          break;
      }
    }

    
    
  
  }
  /*
   * Game end
   * use this loop to display sum and advice without user input interruption
   */
  while(endGame){
      // needed for marquee effect
      panelDisplay();

      // noRepeat use so that the advice only show once
      if((millis() - timeNasihat) >= 4000){
        timeNasihat = millis();
        if(!noRepeat){
          Serial.println("Nasihat");
          if(sum == 0){
            panelInit(nasihat1);
            endUpdate = 12000;
          }else if(sum > 0 && sum < 200000){
            panelInit(nasihat2);
            endUpdate = 20000;
          }else if(sum > 200000 && sum < 300000){
            panelInit(nasihat3);
            endUpdate = 20000;
          }else if(sum > 300000 && sum < 500000){
            panelInit(nasihat4);
            endUpdate = 20000;
          }else if(sum > 500000 && sum < 800000){
            panelInit(nasihat5);
            endUpdate = 20000;
          }else if(sum > 800000 && sum < 1000000){
            panelInit(nasihat6);
            endUpdate = 20000;
          }else if(sum > 1000000){
            panelInit(nasihat7);
            endUpdate = 20000;
          }
          noRepeat = true;
        }
      }

      // initialize all conditions
      if((millis() - timeEnd) >= endUpdate){
        Serial.println(timeEnd);
        timeEnd = millis();
        Serial.println("End");
        panelInit(ayat_mula);
        endGame = false;
        noRepeat = false;
        sum = 0;
        mySerial.write(nasihatEnd);
      }
    }
  
  
  
}


