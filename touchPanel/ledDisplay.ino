/*
  touch panel led
  
  We are using shift register to light up the led.
 */
void led(uint8_t data[], uint8_t clk[], uint8_t latch[], uint8_t num){

  if(num == 17){
    digitalWrite(latch[2],LOW);
    shiftOut(data[2],clk[2],MSBFIRST,numBin[num]);
    digitalWrite(latch[2],HIGH);

    digitalWrite(latch[3],LOW);
    shiftOut(data[3],clk[3],MSBFIRST,numBin[num]);
    digitalWrite(latch[3],HIGH);
  }

  if(num < 8){
    digitalWrite(latch[3],LOW);
    shiftOut(data[3],clk[3],MSBFIRST,numBin[num]);
    digitalWrite(latch[3],HIGH);
  }
  if((num >= 8) && (num < 17)){
    digitalWrite(latch[2],LOW);
    shiftOut(data[2],clk[2],MSBFIRST,numBin[num - 8]);
    digitalWrite(latch[2],HIGH);
  }

  
}
