/*
  This function is use to collect 200 raw data from touch panel
  From the 200 data, we use the last 50 data to get the average value
  This is because the last 50 data is the stable data. The data is not accurate when starting up
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
  return 17;
  
}



