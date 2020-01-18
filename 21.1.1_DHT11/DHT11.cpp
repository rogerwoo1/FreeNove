/**********************************************************************
* Filename    : DHT11.cpp
* Description : read the temperature and humidity data of DHT11
* Author      : freenove
* modification: 2018/03/07
**********************************************************************/
#include <wiringPi.h>
#include <stdio.h>
#include <stdint.h>
#include "DHT.hpp"

#define DHT11_Pin  0    // define the pin of sensor

int main()
{
    DHT dht;    // create a DHT class object
    int chk;    // read the return value of sensor
    int sumCnt = 0; // times of reading sensor
    int GoodReadingsCount = 0;

    if (wiringPiSetup() == -1)
    { // when initialize wiring failed, print message to screen
      printf("setup wiringPi failed!\n");
      return(1);
    }
    while (1)
    {
      chk = dht.readDHT11(DHT11_Pin); // read DHT11 and get a return value.
      sumCnt++;  // counting number of reading times
      switch (chk)
      { // Determine whether data read is normal according to the return value.
        case DHTLIB_OK:                 // if the return value is DHTLIB_OK, the data is normal.
          GoodReadingsCount++;
          #if defined(DEBUG_ON)
          printf("DHT11, OK!\n");
          #endif
          printf("Humidity is %.2f %%, Temperature is %.2f *C, sumCnt is %d, okRate is %.2f %%\n",
                 dht.humidity,
                 dht.temperature,
                 sumCnt,
                 ((100.0 * GoodReadingsCount) / sumCnt));
          break;
        case DHTLIB_ERROR_CHECKSUM:     // data check has errors
          #if defined(DEBUG_ON)
          printf("DHTLIB_ERROR_CHECKSUM!\n");
          #endif
          break;
        case DHTLIB_ERROR_TIMEOUT:      // reading DHT times out
          #if defined(DEBUG_ON)
          printf("DHTLIB_ERROR_TIMEOUT!\n");
          #endif
          break;
        case DHTLIB_INVALID_VALUE:      // other errors
          #if defined(DEBUG_ON)
          printf("DHTLIB_INVALID_VALUE!\n");
          #endif
          break;
        default:
          break;
      }
      delay(2000);
    }
    return(1);
}
