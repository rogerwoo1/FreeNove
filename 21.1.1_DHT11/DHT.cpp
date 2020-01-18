/**********************************************************************
* Filename    : DHT.cpp
* Description : DHT Temperature & Humidity Sensor library for Raspberry
* Author      : freenove
* modification: 2018/03/07
**********************************************************************/

#include "DHT.hpp"

void DHT::PrintBits(void)
{
    printf("bits:\t%d,\t%d,\t%d,\t%d,\t%d\n",
           bits[0], bits[1], bits[2], bits[3], bits[4]);
}

void DHT::PrintErrorBits(unsigned char TONumber, unsigned char *bits, unsigned char idx, unsigned char mask)
{
    printf("TO %d, Byte = %d, Mask = 0x%x\n", TONumber, idx, mask);
    printf("bits:\t%d,\t%d,\t%d,\t%d,\t%d\n",
           bits[0], bits[1], bits[2], bits[3], bits[4]);
}

// Function: Read DHT sensor, store the original data in bits[]
// return values:DHTLIB_OK   DHTLIB_ERROR_CHECKSUM  DHTLIB_ERROR_TIMEOUT

int DHT::readSensor(int pin, int wakeupDelay)
{
    int mask = 0x80;
    int idx = 0;
    int i;
    int32_t t;

    for (i = 0; i < 5; i++)
    {
      bits[i] = 0;
    }
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    delay(wakeupDelay);
    digitalWrite(pin, HIGH);
    delayMicroseconds(40);
    pinMode(pin, INPUT);
    pullUpDnControl(pin, PUD_OFF);

    t = micros();
    while (digitalRead(pin) == LOW)
    {
      if ((micros() - t) > DHTLIB_TIMEOUT)
      {
        #if defined(DEBUG_ON)
        printf("TO 1\n");
        #endif
        return(DHTLIB_ERROR_TIMEOUT);
      }
    }
    t = micros();
    while (digitalRead(pin) == HIGH)
    {
      if ((micros() - t) > DHTLIB_TIMEOUT)
      {
        #if defined(DEBUG_ON)
        printf("TO 2\n");
        #endif
        return(DHTLIB_ERROR_TIMEOUT);
      }
    }
    for (i = 0; i < 40; i++)
    {
      t = micros();
      while (digitalRead(pin) == LOW)
      {
        if ((micros() - t) > DHTLIB_TIMEOUT)
        {
          #if defined(DEBUG_ON)
          PrintErrorBits(3, bits, idx, mask);
          #endif
          return(DHTLIB_ERROR_TIMEOUT);
        }
      }
      t = micros();
      while (digitalRead(pin) == HIGH)
      {
        if ((micros() - t) > DHTLIB_TIMEOUT)
        {
          #if defined(DEBUG_ON)
          PrintErrorBits(4, bits, idx, mask);
          #endif
          return(DHTLIB_ERROR_TIMEOUT);
        }
      }
      if ((micros() - t ) > 60)
      {
        bits[idx] |= mask;
      }
      mask >>= 1;
      if (mask == 0)
      {
        mask = 0x80;
        idx++;
      }
    }
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);
    #if defined(DEBUG_ON)
    PrintBits();
    #endif
    return(DHTLIB_OK);
}

// Function：Read DHT sensor, analyze the data of temperature and humidity
// return：DHTLIB_OK   DHTLIB_ERROR_CHECKSUM 

int DHT::readDHT11(int pin)
{
    int rv;
    uint8_t sum;

    rv = readSensor(pin, DHTLIB_DHT11_WAKEUP);
    if (rv != DHTLIB_OK)
    {
      humidity = DHTLIB_INVALID_VALUE;
      temperature = DHTLIB_INVALID_VALUE;
      return(rv);
    }
    humidity = bits[0];
    temperature = bits[2] + bits[3] * 0.1;
    sum = bits[0] + bits[1] + bits[2] + bits[3];
    if (bits[4] != sum)
    {
      humidity = DHTLIB_INVALID_VALUE;
      temperature = DHTLIB_INVALID_VALUE;
      return(DHTLIB_ERROR_CHECKSUM);
    }
    return(DHTLIB_OK);
}
