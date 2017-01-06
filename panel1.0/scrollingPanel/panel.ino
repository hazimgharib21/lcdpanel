long start = millis();
long timer = start;

void panelInit(char *lol){
  
  dmd.clearScreen(true);
  dmd.selectFont(Arial_Black_16);
  char *MSG = lol;
  dmd.drawMarquee(MSG,strlen(MSG),(32*WIDTH)-1,0);
  
    
  
}

void panelDisplay(){
  if((timer + 20) < millis()){
    dmd.stepMarquee(-1,0);
    timer = millis();
  }
}

