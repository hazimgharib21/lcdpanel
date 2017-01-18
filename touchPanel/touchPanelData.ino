/*
 * int pin - value of the pin
 * Get 200 data of realease value
 * Calculate the average of the last 50 data
 * return the average of the realease value from touch panel
 */
int relVal(int pin){
  int sum;
  
  for(int i = 0; i < 200; i++){
    if(pin > 11){
      output[pin] += (mprA.filteredData(pin - 12) - output[pin]) * 0.07;
    }
    output[pin] += (mprB.filteredData(pin) - output[pin]) * 0.07;
    average[i] = output[pin];
  }
  for(int i = 150; i < 200; i++){
    sum += average[i];
  }
  //Serial.println(sum/50);
  return (sum / 50);
}
/*
 * Use to always update the smooth input from touch panel
 */
void pinData(){
  for(int pin = 0; pin < 17; pin++){
    if(pin > 11){
      output[pin] += (mprA.filteredData(pin - 12) - output[pin]) * 0.07;
    }
    output[pin] += (mprB.filteredData(pin) - output[pin]) * 0.07;
    
  }
}
/*
 * Use the realease value and compare it with the current input value
 * output[] - current touch panel input
 * relValue[] - the initial value on touch panel(not touch)
 * treshold[] - the difference of touch and release, decrease this value to increase sensitivity
 */
int getPinTouched(){
  for(int i = 0; i < 17; i++){
    if(output[i] < relValue[i] - treshold[i]){
      return i;
    }
  }
  // return 17;
}
