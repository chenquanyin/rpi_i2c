#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

int main()
{
    int i = 0;
    wiringPiSetup();
    pinMode(0,OUTPUT);
    while(1)
    {
        digitalWrite(0,HIGH);
        usleep(500*1000);
        digitalWrite(0,LOW);
        usleep(500*1000);
    }
    return 0;
}

