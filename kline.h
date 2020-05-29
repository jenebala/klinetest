#ifndef kline_prop_h
#define kline_prop_h

#include "Arduino.h"


#define DEBUG


class k_line_prop
{
  public:    
  

  k_line_prop(HardwareSerial* serial,long baudRate, uint8_t txpin, uint16_t timeout);
    
  uint8_t kds_kline_ini();
  uint16_t kds_read_tps();
  uint8_t kds_read_rpm();


      
  
  private:
  HardwareSerial* kline_rxtx;
  long _baud=0;
  uint8_t _txpin=0;
  long time_0=0;
  long time_1=0;
  uint8_t buffer[100];

  void printHex(uint8_t *data, uint8_t length);


};

#endif