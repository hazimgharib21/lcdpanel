/*
 * 7 segment countdown function
 *
 *  The number receive will be seperated. Each number for each 7 segment.
 */
void Countdown(uint8_t data[], uint8_t clk[], uint8_t latch[], uint8_t count){

  int temp;

  int num1 = count / 10;
  int num2 = count - (num1 * 10);

  digitalWrite(latch[1],LOW);
  shiftOut(data[1],clk[1],MSBFIRST,numHex[num1]);
  digitalWrite(latch[1],HIGH);
  
  digitalWrite(latch[0],LOW);
  shiftOut(data[0],clk[0],MSBFIRST,numHex[num2]);
  digitalWrite(latch[0],HIGH);
 
}
