#include "msp.h"

#include "driverlib.h"
#include "HAL_I2C.h"
#include "HAL_OPT3001.h"
#include <iostream>



void BlinkLEDs(int l_intBlinkTime)
{
    for(int i = 0; i < l_intBlinkTime; i++);
    P2->OUT ^= BIT0 | BIT1 | BIT2;

    for(int i = 0; i < l_intBlinkTime; i++); //1
    P2->OUT ^= BIT0 | BIT1 | BIT2;

    for(int i = 0; i < l_intBlinkTime; i++);
    P2->OUT ^= BIT0 | BIT1 | BIT2;

    for(int i = 0; i < l_intBlinkTime; i++);//2
    P2->OUT ^= BIT0 | BIT1 | BIT2;

    for(int i = 0; i < l_intBlinkTime; i++);
    P2->OUT ^= BIT0 | BIT1 | BIT2;

    for(int i = 0; i < l_intBlinkTime; i++);//3
    P2->OUT ^= BIT0 | BIT1 | BIT2;

}

void ADC_SetUp()
{
    // Configure GPIO
    P4->SEL1 |= BIT3;
    P4->SEL0 |= BIT3;

    // Configure ADC14
    // Turn on ADC14, set sampling time
    ADC14->CTL0 = ADC14_CTL0_ON | ADC14_CTL0_SHP| ADC14_CTL0_SHT0_2;
    // Use sampling timer, 14-bit conversion results
    ADC14->CTL1 = ADC14_CTL1_RES_3;
    //
    ADC14->MCTL[0] |= ADC14_MCTLN_INCH_1;
    // Enable conversions
    ADC14->CTL0 |= ADC14_CTL0_ENC;
}

void ligthSensor_SetUp()
{
    /* Initializes Clock System */
    MAP_CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48);
    MAP_CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1 );
    MAP_CS_initClockSignal(CS_HSMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1 );
    MAP_CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1 );
    MAP_CS_initClockSignal(CS_ACLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);


    /* Initialize I2C communication */
    Init_I2C_GPIO();
    I2C_init();

    /* Initialize OPT3001 digital ambient light sensor */
    OPT3001_init();

    __delay_cycles(100000);
}

void Timer_microphone_setUp()
{
    // Timer32 set up in periodic mode, 32-bit, no pre-scale
        TIMER32_1->CONTROL = TIMER32_CONTROL_SIZE |
                TIMER32_CONTROL_MODE;

        // Load Timer32 counter with period = 0x20000
        TIMER32_1->LOAD= 0xFFFFFF;

        // Enalbe the Timer32 interrupt in NVIC
        __enable_irq();
        NVIC->ISER[0] = 1 << ((T32_INT1_IRQn) & 31);

        // Enable sleep on exit from ISR
        SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;

        // Ensures SLEEPONEXIT takes effect immediately
        __DSB();

        // Start Timer32 with interrupt enabled
        TIMER32_1->CONTROL |= TIMER32_CONTROL_ENABLE |
                TIMER32_CONTROL_IE;
}

void Set_Status()
{

   float l_floatLightSensorValue;
   volatile uint16_t l_uint16MicrophoneValue;
   //int joyButton = 0;

   P4->DIR &= ~BIT0;   //joystick button as an input

   while(1)
    {

       l_floatLightSensorValue = OPT3001_getLux();

       //P2->OUT &= 11111000;

       /*if (l_floatLightSensorValue < 20)
       {
           P2->OUT |= BIT1;
       }
       else
       {
           P2->OUT |= BIT0;
       }*/

       ADC14->CTL0 |= ADC14_CTL0_SC;                        // Start conversion-software trigger
       while (!(ADC14->IFGR0 & BIT0));
       l_uint16MicrophoneValue = ADC14->MEM[0];             // Read conversion result

    }
}

void initialConfiguration()
{
    int l_intBlinkTime = 55000;

    P2->DIR = BIT0 | BIT1 | BIT2;
    P2->OUT = BIT0 | BIT1 | BIT2;


    BlinkLEDs(l_intBlinkTime);

    ligthSensor_SetUp();
    ADC_SetUp();            //Microphone
    Timer_microphone_setUp();
    //Ctrol_button_SetUp(); //To set button
    Set_Status();
}

extern "C"
{
    void T32_INT1_IRQHandler(void)
    {
        TIMER32_1->INTCLR |= BIT0;              // Clear Timer32 interrupt flag
        P2->OUT ^= BIT0 | BIT1 | BIT2;          // Toggle LED
    }
}

