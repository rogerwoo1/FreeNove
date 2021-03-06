/**********************************************************************
* Filename    : DHT.hpp
* Description : DHT Temperature & Humidity Sensor library for Raspberry
* Author      : freenove
* modification: 2018/03/07
**********************************************************************/
#ifndef _DHT_H_
#define _DHT_H_

#include <wiringPi.h>
#include <stdio.h>
#include <stdint.h>

// read return flag of sensor
#define DHTLIB_OK               0
#define DHTLIB_ERROR_CHECKSUM   -1
#define DHTLIB_ERROR_TIMEOUT    -2
#define DHTLIB_INVALID_VALUE    -999

#define DHTLIB_DHT11_WAKEUP     18

#define DHTLIB_TIMEOUT          100

//#define DEBUG_ON

class DHT
{
  public:
    double humidity;         // use to store humidity data read
    double temperature;      // use to store temperature data read
    int readDHT11(int pin);  // read DHT11
  private:
    uint8_t bits[5];         // Buffer to receiver data
    int readSensor(int pin, int wakeupDelay);
    void PrintBits(void);
    void PrintErrorBits(unsigned char TONumber, unsigned char *bits, unsigned char idx, unsigned char mask);
};

#endif
