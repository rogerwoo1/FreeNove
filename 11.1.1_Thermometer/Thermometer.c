/**********************************************************************
* Filename    : Thermometer.c
* Description : A DIY Thermometer
* Author      : freenove
* modification: 2016/06/20
**********************************************************************/
#include <wiringPi.h>
#include <pcf8591.h>
#include <stdio.h>
#include <math.h>

#define address 0x48  // pcf8591 default address
#define pinbase 64    // any number >= 64
#define A0 pinbase + 0
#define A1 pinbase + 1
#define A2 pinbase + 2
#define A3 pinbase + 3
#define TEMP_CORRECTION 4

int main(void)
{
    int adcValue;
    float tempK;
    float tempC;
    float tempF;
    float voltage;
    float Rt;

    if (wiringPiSetup() == -1)
    { // when initialize wiring failed, print message to screen
      printf("setup wiringPi failed !");
      return 1; 
    }

    pcf8591Setup(pinbase, address);

    while (1)
    {
      adcValue = analogRead(A0);                                // read A0 pin
      voltage = (float)adcValue / 255.0 * 3.3;                  // calculate voltage
      Rt = (10 * voltage) / (3.3 - voltage);                    // calculate resistance value of thermistor
      tempK = 1 / (1 / (273.15 + 25) + log(Rt / 10) / 3950.0);  // calculate temperature (Kelvin)
      tempC = tempK - 273.15;                                   // calculate temperature (Celsius)
      tempC -= TEMP_CORRECTION;                                 // guess at calibration
      tempF = ((9 * tempC) / 5) + 32;                           // calculate farenhieht
      printf("ADC value: %d,\tVoltage: %.2fV,\tTemperature: %.2fC,\t%.2fF\n",
             adcValue, voltage, tempC, tempF);
      delay(100);
    }
    return 0;
}
