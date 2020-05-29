#include <Arduino.h>
#include "kline.h"

k_line_prop kline (&Serial3, 10400, 14, 1000);


void setup()
{
  
  
  
  
  Serial.begin(10400);
  Serial.println("ablak");


  pinMode(LED_BUILTIN, OUTPUT);
  
  
  Serial.println(kline.kds_kline_ini());
}

void loop()
{
  
  kline.kds_read_tps();
  delay(30);
  kline.kds_read_rpm();
  delay(30);
 
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);    


}
