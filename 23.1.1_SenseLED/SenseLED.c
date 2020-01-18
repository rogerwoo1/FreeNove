/**********************************************************************
* Filename    : SenseLED.c
* Description : Controlling an led by infrared Motion sensor.
* Author      : freenove
* modification: 2016/06/12
**********************************************************************/
#include <wiringPi.h>
#include <stdio.h>

#define ledPin    1    // define the ledPin
#define sensorPin 0    // define the sensorPin

int main(void)
{
  unsigned int LastReading = HIGH;

  if (wiringPiSetup() == -1)
  { // when initialize wiring fails, print message to screen
    printf("setup wiringPi failed!");
    return 1;
  }

  pinMode(ledPin, OUTPUT);
  pinMode(sensorPin, INPUT);

  while (1)
  {
    if (digitalRead(sensorPin) == HIGH)
    { // if read sensor for high level
      if (LastReading != HIGH)
      {
        LastReading = HIGH;
        digitalWrite(ledPin, HIGH);   // led on
        printf("led on...\n");
      }
    }
    else
    {
      if (LastReading != LOW)
      {
        LastReading = LOW;
        digitalWrite(ledPin, LOW);    // led off
        printf("...led off\n");
      }
    }
  }

  return 0;
}

