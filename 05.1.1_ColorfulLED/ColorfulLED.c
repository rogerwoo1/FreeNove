/**********************************************************************
* Filename    : ColorfulLED.c
* Description : A auto flash ColorfulLED
* Author      : freenove
* modification: 2019/07/05
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
    int r;
    int g;
    int b;

    if (wiringPiSetup() == -1)
    { // when initialize wiring failed,print messageto screen
      printf("setup wiringPi failed !");
      return 1; 
    }
    printf("Program is starting ...\n");
    ledInit();

    while (1)
    {
      r = random() % MAX_RANGE; // get a random in (MIN_RANGE, MAX_RANGE)
      r = ((r >= MIN_RANGE) ? r : MIN_RANGE);
      g = random() % MAX_RANGE;
      g = ((g >= MIN_RANGE) ? g : MIN_RANGE);
      b = random() % MAX_RANGE;
      b = ((b >= MIN_RANGE) ? b : MIN_RANGE);
      ledColorSet(r, g, b); // set random as a duty cycle value 
      printf("r=%d,  g=%d,  b=%d\n", r, g, b);
      delay(3000);
    }
    return 0;
}
