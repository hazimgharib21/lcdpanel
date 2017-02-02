
long timer = start;

/*
 * Dont touch this part of the code.
 * Use to initiate marquee effect with the message as an argument
 * The message must be in char pointer or char array
 */
void panelInit(char *lol){
  dmd.clearScreen(true);
  dmd.selectFont(Arial_Black_16);
  char *MSG = lol;
  dmd.drawMarquee(MSG,strlen(MSG),(32*WIDTH)-1,0);  
}

void panelDisplay(){
  if((timer + 8) < millis()){
    dmd.stepMarquee(-1,0);
    timer = millis();
  }
}
/*
 * Change the sum to char array for display in led scroller
 */
void toChar(long num){
        char sumChar[25];
        String myString = "YOU SPEND RM ";
        myString+=String(num);
        myString.toCharArray(sumChar, sizeof(sumChar));
        Serial.println(sumChar);
        panelInit(sumChar);
}


