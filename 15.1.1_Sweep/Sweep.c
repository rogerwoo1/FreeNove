/**********************************************************************
* Filename    : Sweep.c
* Description : Servo sweep
* Author      : freenove
* modification: 2016/07/05
**********************************************************************/
#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>

#if 0
#define OFFSET_MS    (3)               // define the unit of servo pulse offset: 0.1ms
#else
#define OFFSET_MS    (0)               // define the unit of servo pulse offset: 0.1ms
#endif
#define SERVO_MIN_MS (5 + OFFSET_MS)   // define the pulse duration for minimum angle of servo
#define SERVO_MAX_MS (25 + OFFSET_MS)  // define the pulse duration for maximum angle of servo
#define servoPin     (1)               // define the GPIO number connected to servo

long map(long value, long fromLow, long fromHigh, long toLow, long toHigh)
{
    return (((toHigh - toLow) * (value - fromLow)) / (fromHigh  -fromLow)) + toLow;
}

// initialization function for servo PMW pin
void servoInit(int pin)
{
    softPwmCreate(pin, 0, 200);
}

// Specify a certain rotation angle (0-180) for the servo
void servoWrite(int pin, int angle)
{
    if (angle > 180)
    {
      angle = 180;
    }

    if (angle < 0)
    {
      angle = 0;
    }

    softPwmWrite(pin, map(angle, 0, 180, SERVO_MIN_MS, SERVO_MAX_MS));   
}

// specify the unit for pulse(5-25ms) with specific duration output by servo pin: 0.1ms
void servoWriteMS(int pin, int ms)
{
    if(ms > SERVO_MAX_MS)
    {
      ms = SERVO_MAX_MS;
    }

    if(ms < SERVO_MIN_MS)
    {
      ms = SERVO_MIN_MS;
    }

    softPwmWrite(pin, ms);
}

int main(void)
{
    int i;

    if (wiringPiSetup() == -1)
    { // when initialize wiring failed, print message to screen
      printf("setup wiringPi failed!");
      return 1; 
    }

    printf("Program is starting ...\n");
    servoInit(servoPin);        // initialize PMW pin of servo

#if 0
    while (1)
    {
      for (i = SERVO_MIN_MS; i < SERVO_MAX_MS; i++)
      { // make servo rotate from minimum angle to maximum angle
        servoWriteMS(servoPin, i);
        delay(10);
      }
      delay(500);
      for (i = SERVO_MAX_MS; i > SERVO_MIN_MS; i--)
      { // make servo rotate from maximum angle to minimum angle
        servoWriteMS(servoPin, i);
        delay(10);
      }
      delay(500);
    }
#else
    while (1)
    {
      for (i = 0; i <= 180; i++)
      { // make servo rotate from minimum angle to maximum angle
        servoWrite(servoPin, i);
        delay(10);
      }
      delay(500);
      for (i = 180; i > 0; i--)
      { // make servo rotate from maximum angle to minimum angle
        servoWrite(servoPin, i);
        delay(10);
      }
      delay(500);
    }
#endif
    return 0;
}
