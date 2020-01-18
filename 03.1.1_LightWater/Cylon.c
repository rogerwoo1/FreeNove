/**********************************************************************
* Filename    : Cylong.c
* Description : Display 10 LEDBar Graph 
* Author      : Roger woodruff
* modification: 2019/08/14
**********************************************************************/
#include <wiringPi.h>
#include <stdio.h>

#define leds 10
int pins[leds] = { 0, 1, 2, 3, 4, 5, 6, 8, 9, 10 };

#define TBL_SIZE 10

unsigned char OffTable1[TBL_SIZE] = {  0, 1, 2, 3, 4, 3, 2,  1 };
unsigned char OffTable2[TBL_SIZE] = { 10, 9, 8, 6, 5, 6, 8,  9 };
unsigned char OnTable1[TBL_SIZE]  = {  1, 2, 3, 4, 3, 2, 1,  0 };
unsigned char OnTable2[TBL_SIZE]  = {  9, 8, 6, 5, 6, 8, 9, 10 };
unsigned char Cycle = 0;

#define TIME_DELAY_MAX       100
#define TIME_DELAY_MIN       10
#define TIME_DELAY_INCREMENT 10

unsigned int TimeDelay = TIME_DELAY_MAX;

// make led_n on

void led_on(int n)
{
    digitalWrite(n, LOW);
}

// make led_n off
void led_off(int n)
{
    digitalWrite(n, HIGH);
}

int main(void)
{
    int i;

    printf("Program is starting ... \n");

    if (wiringPiSetup() == -1)
    { // when initialize wiring failed,print messageto screen
      printf("setup wiringPi failed !");
      return 1; 
    }

    for (i = 0; i < leds; i++)
    { // make leds pins' mode is output
      pinMode(pins[i], OUTPUT);
    }

    while (1)
    {
      for (i = 0; i < TBL_SIZE; i++)
      {
        led_off(OffTable1[i]);
        led_off(OffTable2[i]);
        led_on(OnTable1[i]);
        led_on(OnTable2[i]);
        delay(TimeDelay);
      }
      if (Cycle)
      {
        TimeDelay += TIME_DELAY_INCREMENT;
      }
      else
      {
	TimeDelay -= TIME_DELAY_INCREMENT;
      }
      if (TimeDelay < TIME_DELAY_MIN)
      {
        Cycle = !Cycle;
	TimeDelay = TIME_DELAY_MIN;
      }
      if (TimeDelay > TIME_DELAY_MAX)
      {
        Cycle = !Cycle;
	TimeDelay = TIME_DELAY_MAX;
      }
    }
    return 0;
}
