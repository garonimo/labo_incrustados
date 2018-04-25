#include "msp.h"

#include "driverlib.h"
#include "HAL_I2C.h"
#include "HAL_OPT3001.h"
#include <iostream>

int g_intNumberOfLights = 2; //1,2 o 3
int g_intLightsCtrl;

int g_intBlinkTime = 550000;
int g_intCounterInterrupMic = 0;
int g_intCounterMic_Prom = 0;
float g_floatMicPromValue = 0;
uint16_t g_uint16_tDayNight_Threshold = 17; //Umbral dia/noche
bool g_boolIsLightOn = false;
bool g_boolAreLEDsBlincked = false;
bool g_boolUseRealTime = false;
int g_intRealTimeCounter = 0;
volatile uint16_t g_uint16MicrophoneValue;
int g_intMicValue1;
int g_intMicValue2;
int g_intMicValue3;
int g_intMicValue4;
int g_intMicValue5;
int g_intMicValue6;
int g_intMicValue7;
int g_intMicValue8;
float g_floatMicRead_Prom1 = 0;
float g_floatMicRead_Prom2 = 0;
float g_floatMicRead_Prom3 = 0;
float g_floatMicRead_Prom4 = 0;
float g_floatMicRead_Prom5 = 0;
float g_floatMicRead_Prom6 = 0;
float g_floatMicRead_Prom_5sec = 0;  //promedio de os ultimos 5 segundos

void BlinkLEDs()
{

    P2->DIR |= g_intLightsCtrl;
    P2->OUT |= g_intLightsCtrl;

    for(int i = 0; i < g_intBlinkTime; i++);
    P2->OUT ^= g_intLightsCtrl;

    for(int i = 0; i < g_intBlinkTime; i++); //1
    P2->OUT ^= g_intLightsCtrl;

    for(int i = 0; i < g_intBlinkTime; i++);
    P2->OUT ^= g_intLightsCtrl;

    for(int i = 0; i < g_intBlinkTime; i++);//2
    P2->OUT ^= g_intLightsCtrl;

    for(int i = 0; i < g_intBlinkTime; i++); //3
    P2->OUT ^= g_intLightsCtrl;

}

void ADC_SetUp()
{
    // Se configuran los pines para usarse en ADC
    P4->SEL1 |= BIT3;
    P4->SEL0 |= BIT3;

    // Se establece el tiempo de muestreo
    ADC14->CTL0 = ADC14_CTL0_ON | ADC14_CTL0_SHP| ADC14_CTL0_SHT0_2;
    // Conversiones de 14 bits
    ADC14->CTL1 = ADC14_CTL1_RES_2;
    //
    ADC14->MCTL[0] |= ADC14_MCTLN_INCH_1;
    // Se habilitan las conversiones
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


    /* Se inicializa el I2C */
    Init_I2C_GPIO();
    I2C_init();

    /* Se inicializa el sensor de luz */
    OPT3001_init();

    //Se recomienda un delay
    __delay_cycles(100000);
}

void Timer_microphone_setUp()
{
    // Se usa el timer con 32 bits y sin pre-escala
    TIMER32_1->CONTROL = TIMER32_CONTROL_SIZE |
                TIMER32_CONTROL_MODE;

    // Se cuenta 6 millones de veces que es 5B8D80 en Hex, para lograr 0.125 s
    TIMER32_1->LOAD= 0x5B8D80;


    // Para  habilitar el contador e interrupcion para este contador
    TIMER32_1->CONTROL |= TIMER32_CONTROL_ENABLE |
              TIMER32_CONTROL_IE;
}

void Timer_Light_On_setUp()
{
    // Se usa el timer con 32 bits y sin pre-escala
    TIMER32_2->CONTROL = TIMER32_CONTROL_SIZE |
                TIMER32_CONTROL_MODE;

    // Se cuenta 144 millones de veces que es 8954400 en Hex, para lograr 3 s
    TIMER32_2->LOAD= 0x8954400;


}

void Set_Status()
{

   float l_floatLightSensorValue;
   bool l_boolWasButtonPushed = false;

   P4->DIR &= ~BIT0;   //joystick button as an input


   if (g_intNumberOfLights == 3)
   {
       g_intLightsCtrl = BIT0 | BIT1 | BIT2;
   }
   else if (g_intNumberOfLights == 2)
   {
       g_intLightsCtrl = BIT0;
   }
   else if (g_intNumberOfLights == 1)
   {
       g_intLightsCtrl = BIT1;
   }
   else
   {
       g_intLightsCtrl = BIT0 | BIT1 | BIT2;
   }

   BlinkLEDs();

   /*Este es el loop principal, aqui se determina si se enciende la luz o no, se
    * hacen los calculos y revisiones necesarias para saber si se esta en el estado de encendido o no*/
   while(1)
    {

       uint16_t l_uint8_ButtonFlag = P4 -> IN;

       /*Para la supresion de rebotes
       if (l_uint8_ButtonFlag < 255)
       {
           while(P4 -> IN != 255);
           l_boolWasButtonPushed = true;
       }*/

       l_floatLightSensorValue = OPT3001_getLux();
       // Se habilitan las interrupciones en NVIC para ambos timer
       __enable_irq();
       NVIC->ISER[0] = 1 << ((T32_INT1_IRQn) & 31);
       NVIC->ISER[0] = 1 << ((T32_INT2_IRQn) & 31);

       ADC14->CTL0 |= ADC14_CTL0_SC;                        // Se habilita el ADC
       while (!(ADC14->IFGR0 & BIT0));
       g_uint16MicrophoneValue = ADC14->MEM[0];             // Resultado del ADC

       g_floatMicRead_Prom_5sec = (g_floatMicRead_Prom5 + g_floatMicRead_Prom4 + g_floatMicRead_Prom3 + g_floatMicRead_Prom2 + g_floatMicRead_Prom1)/5;
       g_floatMicPromValue = (g_uint16MicrophoneValue + g_intMicValue2 + g_intMicValue3 + g_intMicValue4 + g_intMicValue5 + g_intMicValue6 + g_intMicValue7 + g_intMicValue8)/8;
       g_floatMicRead_Prom6 = g_floatMicPromValue;
       float l_floatCompareSound = 1.10*g_floatMicRead_Prom_5sec;

       if (((l_floatLightSensorValue < g_uint16_tDayNight_Threshold) && (g_floatMicRead_Prom6 > (l_floatCompareSound)) && ~g_boolIsLightOn) || (l_boolWasButtonPushed))
       {
           P2->OUT |= g_intLightsCtrl;
           g_boolIsLightOn = true;
           l_boolWasButtonPushed = false;
           TIMER32_2->CONTROL |= TIMER32_CONTROL_ENABLE |
                     TIMER32_CONTROL_IE;               // Para  habilitar el timer que cuenta cuando se enciende la luz
       }

    }
}

void initialConfiguration()
{

    ligthSensor_SetUp();
    ADC_SetUp();            //para el microfono
    Timer_microphone_setUp();
    Timer_Light_On_setUp();
    Set_Status();
}

    /*Interrupcion para la lectura del microfono
     * Esta interrupcion lee el microfono cada 0.125s, cada segundo saca el promedio
     * del nivel de sonido de ese segundo con 8 muestras.
     * La primera vez guarda el promedio de los primeros 6 segundos en variables distintas,
     * despues va rotando cada valor. Haciendo que en la variable g_floatMicRead_Prom6 se guarde
     * el promedio del ultimo segundo y en otra variable se pueda guardar el valos de los 5 segundos
     * anteriores al ultimo. */
extern "C"
{
    void T32_INT1_IRQHandler(void)
    {
        float l_floatMicPromValue;
        g_intCounterInterrupMic += 1;
        switch (g_intCounterInterrupMic)
        {
            case 1:
                g_intMicValue1 = g_uint16MicrophoneValue;
                break;
            case 2:
                g_intMicValue2 = g_uint16MicrophoneValue;
                break;
            case 3:
                g_intMicValue3 = g_uint16MicrophoneValue;
                break;
            case 4:
                g_intMicValue4 = g_uint16MicrophoneValue;
                break;
            case 5:
                g_intMicValue5 = g_uint16MicrophoneValue;
                break;
            case 6:
                g_intMicValue6 = g_uint16MicrophoneValue;
                break;
            case 7:
                g_intMicValue7 = g_uint16MicrophoneValue;
                break;
            case 8:
                g_intMicValue8 = g_uint16MicrophoneValue;
                break;
            default:
                g_intCounterInterrupMic = 0;
                break;
        }
        if (g_intCounterInterrupMic >= 8)
        {
            g_intCounterInterrupMic = 0;
            if (g_intCounterMic_Prom < 7)
            {
                g_intCounterMic_Prom += 1;
            }
            l_floatMicPromValue = (g_intMicValue1 + g_intMicValue2 + g_intMicValue3 + g_intMicValue4 + g_intMicValue5 + g_intMicValue6 + g_intMicValue7 + g_intMicValue8)/8;
            switch (g_intCounterMic_Prom)
            {
                case 1:
                    g_floatMicRead_Prom1 = l_floatMicPromValue;
                    break;
                case 2:
                    g_floatMicRead_Prom2 = l_floatMicPromValue;
                    break;
                case 3:
                    g_floatMicRead_Prom3 = l_floatMicPromValue;
                    break;
                case 4:
                    g_floatMicRead_Prom4 = l_floatMicPromValue;
                    break;
                case 5:
                    g_floatMicRead_Prom5 = l_floatMicPromValue;
                    break;
                case 6:
                    g_floatMicRead_Prom6 = g_floatMicPromValue;
                    break;
                default:
                    /*Los valores promedio se rotan cada nuevo segundo*/
                    g_floatMicRead_Prom1 = g_floatMicRead_Prom2;
                    g_floatMicRead_Prom2 = g_floatMicRead_Prom3;
                    g_floatMicRead_Prom3 = g_floatMicRead_Prom4;
                    g_floatMicRead_Prom4 = g_floatMicRead_Prom5;
                    g_floatMicRead_Prom5 = g_floatMicRead_Prom6;
                    break;
            }
        }

        TIMER32_1->INTCLR |= BIT0;              // se borra la bandera de interrupcion
    }
}

extern "C"
{
    void T32_INT2_IRQHandler(void) //Interrupcion para la luz encendida
    {
        if (~g_boolUseRealTime)
        {
            P2->OUT &= ~g_intLightsCtrl;
            g_boolIsLightOn = false;
            TIMER32_2->CONTROL &= ~TIMER32_CONTROL_ENABLE &
                      ~TIMER32_CONTROL_IE;      // Para  deshabilitar el timer que cuenta cuando se enciende la luz
        }
        else
        {
            g_intRealTimeCounter += 1;
            if (g_intRealTimeCounter >= 600)
            {
                P2->OUT &= ~g_intLightsCtrl;
                            g_boolIsLightOn = false;
                TIMER32_2->CONTROL &= ~TIMER32_CONTROL_ENABLE &
                                      ~TIMER32_CONTROL_IE;
                g_intRealTimeCounter = 0;
            }
        }

        TIMER32_2->INTCLR |= BIT0;          // se borra la bandera de interrupcion
    }
}
