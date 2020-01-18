/**********************************************************************
* Filename    : AllColorLED.c
* Description : A auto flash ColorfulLED
* Author      : Roger Woodruff
* modification: 2019/08/16
**********************************************************************/
#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include <stdlib.h>

#define ledPinRed    0
#define ledPinGreen  1
#define ledPinBlue   2
#define MIN_RANGE    0
#define MAX_RANGE    255
#define DELAY_TIME   1

void ledInit(void)
{
    softPwmCreate(ledPinRed,   0, 255); // Creat SoftPWM pin
    softPwmCreate(ledPinGreen, 0, 255);
    softPwmCreate(ledPinBlue,  0, 255);
}

void ledColorSet(int r_val, int g_val, int b_val)
{
    softPwmWrite(ledPinRed,   r_val); // Set the duty cycle 
    softPwmWrite(ledPinGreen, g_val);
    softPwmWrite(ledPinBlue,  b_val);
}

int main(void)
{
    int r = MIN_RANGE;
    int g = MIN_RANGE;
    int b = MIN_RANGE;

    if (wiringPiSetup() == -1)
    { // when initialize wiring failed,print messageto screen
      printf("setup wiringPi failed !");
      return 1; 
    }
    printf("Program is starting ...\n");
    ledInit();

    while (1)
    {
      ledColorSet(r, g, b); // set random as a duty cycle value 
      for (r = MIN_RANGE; r <= MAX_RANGE; r++)
      {
        for (g = MIN_RANGE; g <= MAX_RANGE; g++)
        {
          for (b = MIN_RANGE; b <= MAX_RANGE; b++)
          {
            ledColorSet(r, g, b);
            delay(DELAY_TIME);
          }
        }
        r++;
        for (g = MAX_RANGE; g != MIN_RANGE; g--)
        {
          for (b = MAX_RANGE; b != MIN_RANGE; b--)
          {
            ledColorSet(r, g, b);
            delay(DELAY_TIME);
          }
        }
      }
      printf("Done.\n");
    }
    return 0;
}
