#include "kline.h"


k_line_prop::k_line_prop( HardwareSerial* serial,long baudRate, uint8_t txpin, uint16_t timeout)
{   
    _txpin=txpin;
    _baud=baudRate;
    kline_rxtx = serial;
    kline_rxtx->begin(baudRate);
    kline_rxtx->setTimeout(timeout);
}

uint8_t k_line_prop::kds_kline_ini()
{
    uint8_t ini_response[] = {0x80, 0xF1, 0x11, 0xC1, 0xEA, 0x8F, 0xBF};
     // SEND : 0x81, 0x11, 0xF1, 0x81, 0x4

    kline_rxtx->end();

    pinMode(_txpin,OUTPUT);

    digitalWrite(_txpin,HIGH);
    delay(1000);
    digitalWrite(_txpin,LOW);
    delay(25);
    digitalWrite(_txpin,HIGH);
    delay(25);

    kline_rxtx->begin(_baud);

    //KDS INI
    kline_rxtx->write(0x81);
    kline_rxtx->write(0x11);
    kline_rxtx->write(0xF1);
    kline_rxtx->write(0x81);
    kline_rxtx->write(0x4);
    
    uint8_t readbyte=13;

    #ifdef DEBUG
      time_0=millis();
    #endif
  
    kline_rxtx->readBytes(buffer,readbyte);
    
    

    #ifdef DEBUG
        time_1=millis();
        Serial.print("K-line INI: ");
        printHex(buffer,readbyte);
        Serial.println();
        Serial.print("Time: ");
        Serial.print(time_1-time_0);
        Serial.println(" ms");
        

    #endif
   
    
    for (uint8_t i = 0; i < 1; i++)
    {
      if ( buffer[i+5] != ini_response[i] ) return 0;
    }
    return 1;
    
}



uint16_t k_line_prop::kds_read_tps()
{   //KDS Read_TPS
    kline_rxtx->write(0x80);
    kline_rxtx->write(0x11);
    kline_rxtx->write(0xF1);
    kline_rxtx->write(0x2);
    kline_rxtx->write(0x21);
    kline_rxtx->write(0x4);
    kline_rxtx->write(0xA9);

    uint8_t readbyte=16;
    
    #ifdef DEBUG
      time_0=millis();
    #endif


    kline_rxtx->readBytes(buffer,readbyte);
    
    uint16_t tps = 0;
    
    tps=tps+(buffer[13]<<8);
    tps=tps+buffer[14];



    #ifdef DEBUG
      time_1=millis();
      Serial.print("K-line TPS: ");
      printHex(buffer,readbyte);
      Serial.println();
      Serial.print("Time: ");
      Serial.print(time_1-time_0);
      Serial.println(" ms");
      Serial.println(tps);
    #endif

  return tps;
}



uint8_t k_line_prop::kds_read_rpm()
{   //KDS Read_RPM
    kline_rxtx->write(0x80);
    kline_rxtx->write(0x11);
    kline_rxtx->write(0xF1);
    kline_rxtx->write(0x2);
    kline_rxtx->write(0x21);
    kline_rxtx->write(0x9);
    kline_rxtx->write(0xAE);

    uint8_t readbyte=17;
    
    #ifdef DEBUG
      time_0=millis();
    #endif


    kline_rxtx->readBytes(buffer,readbyte);
    
    
    #ifdef DEBUG
      time_1=millis();
      Serial.print("K-line RPM: ");
      printHex(buffer,readbyte);
      Serial.println();
      Serial.print("Time: ");
      Serial.print(time_1-time_0);
      Serial.println(" ms");
    #endif

  return 0;
}







void k_line_prop::printHex(uint8_t *data, uint8_t length)
{  
 
  for (int i=0; i<length; i++)
  {
      Serial.print("x");
      Serial.print(data[i],HEX);
      Serial.print(" ");
  }

}