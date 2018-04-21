#include "msp.h"

#include "driverlib.h"
#include "HAL_I2C.h"
#include "HAL_OPT3001.h"



void BlinkLEDs(int l_intBlinkTime)
{
    for(int i = 0; i < l_intBlinkTime; i++);
    P1->OUT ^= BIT0;
    P2->OUT ^= BIT0 | BIT1 | BIT2;

    for(int i = 0; i < l_intBlinkTime; i++); //1
    P1->OUT ^= BIT0;
    P2->OUT ^= BIT0 | BIT1 | BIT2;

    for(int i = 0; i < l_intBlinkTime; i++);
    P1->OUT ^= BIT0;
    P2->OUT ^= BIT0 | BIT1 | BIT2;

    for(int i = 0; i < l_intBlinkTime; i++);//2
    P1->OUT ^= BIT0;
    P2->OUT ^= BIT0 | BIT1 | BIT2;

    for(int i = 0; i < l_intBlinkTime; i++);
    P1->OUT ^= BIT0;
    P2->OUT ^= BIT0 | BIT1 | BIT2;

    for(int i = 0; i < l_intBlinkTime; i++);//3
    P1->OUT ^= BIT0;
    P2->OUT ^= BIT0 | BIT1 | BIT2;
}

void initialConfiguration()
{
    int l_intBlinkTime = 55000;

    P2->DIR = BIT0 | BIT1 | BIT2;
    P2->OUT = BIT0 | BIT1 | BIT2;

    P1->DIR = BIT0;
    P1->OUT = BIT0;

    BlinkLEDs(l_intBlinkTime);
}

