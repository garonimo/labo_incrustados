/*
 * Virtual_Hor.cpp
 *
 * Andrés Sánchez - B26214
 *
 *  Aqui se tiene la defición de los métodos de la clase Virtual_Hor
 */

#include "Virtual_Hor.hpp"


Graphics_Context g_sContext;
Graphics_Rectangle g_rRectangule_Brown;
Graphics_Rectangle g_rRectangule_Blue;
uint32_t g_uint32LcdXMin = 0;
uint32_t g_uint32LcdXMax = 127;
uint32_t g_uint32LcdYMin_Brown = 0;
uint32_t g_uint32LcdYMax_Brown = 127;
uint32_t g_uint32LcdYMin_Blue = 0;
uint32_t g_uint32LcdYMax_Blue = 127;
double g_floatHorRatio = 1;

uint16_t g_uint16AcelerometerX = 0;
double g_DoubleAcelerometerY = 0;
uint16_t g_uint16AcelerometerZ = 0;

/*Constructor*/
Virtual_Hor::Virtual_Hor(uint16_t i_uint16Test)
{
    i_uint16Test = i_uint16Test;
}

/*
 * En este método(Get_Hor) se determina el ángulo de pitch, de manera relativa, mediante un cálculo adimensional.
 * 11400 es el valor máximo del acelerómetro en el eje Y(relacionado con el ángulo de pitch), esto es cuando está totalmente hacia arriba.
 * 5000 es  el valor mínimo del eje Y en el acelerómetro(estando totalmente hacia abajo), por lo que en g_floatHorRatio se tiene un
 * valor entre cero y uno, cuando g_floatHorRatio = 0 se está totalmente hacia arriba, cuando g_floatHorRatio = 1
 * se está totalmente hacia abajo, y cuando g_floatHorRatio = 0.5, se está en equilibrio.
 * */
uint8_t Virtual_Hor::Get_Hor()
{
    double l_doubleYaxisMaxValue = 11400;
    double l_doubleYaxisMinValue = 5000;

    g_floatHorRatio = (l_doubleYaxisMaxValue-g_DoubleAcelerometerY)/(l_doubleYaxisMaxValue-l_doubleYaxisMinValue);

    if (g_floatHorRatio < 0)
    {
        g_floatHorRatio = 0;
    }
    else if (g_floatHorRatio > 1)
    {
        g_floatHorRatio = 1;
    }

    return(NO_ERR);
}


/*
 * La función run se encarga de dibujar los cuadros café y azul mediante la libreria presente en driverlib.
 * Se utiliza un booleano l_boolAllBrown, que cuando es true se debe imprimir café en toda la pantalla, este es un caso especial
 * ya que como el azul solo varia el Ymin, siempre tenia(como mínimo) una linea en azul, y con el if presente en la función
 * se suprime esta línea si es necesario*/
uint8_t Virtual_Hor::run()
{
    bool l_boolAllBrown = false;

    Get_Hor();
    if (g_floatHorRatio > 0.987)
    {
        g_rRectangule_Blue.yMin = 0;
        g_rRectangule_Blue.yMax = 0;
        l_boolAllBrown = true;
    }
    else
    {
        g_rRectangule_Blue.yMin = g_uint32LcdYMax_Blue*g_floatHorRatio;
        g_rRectangule_Blue.yMax = g_uint32LcdYMax_Blue;
    }

    g_rRectangule_Brown.yMin = g_uint32LcdYMin_Brown;
    g_rRectangule_Brown.yMax = g_uint32LcdYMax_Brown*g_floatHorRatio;

    if (!l_boolAllBrown)
    {
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BROWN);
        Graphics_fillRectangle(&g_sContext, &g_rRectangule_Brown);
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
        Graphics_fillRectangle(&g_sContext, &g_rRectangule_Blue);
    }
    else
    {
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BROWN);
        Graphics_fillRectangle(&g_sContext, &g_rRectangule_Brown);
    }

    MAP_PCM_gotoLPM0(); //se mantiene activo el acelerómetro

    return(NO_ERR);
}

uint8_t Virtual_Hor::setup()
{

    /* En esta parte del código se desabilita el watch dog, se configuran los niveles de tensión
     * y tiempos de espera para el microcontrolador */
    MAP_WDT_A_holdTimer();
    MAP_Interrupt_disableMaster();
    MAP_PCM_setCoreVoltageLevel(PCM_VCORE1);
    MAP_FlashCtl_setWaitState(FLASH_BANK0, 2);
    MAP_FlashCtl_setWaitState(FLASH_BANK1, 2);

    /* Aquí se configuran las distintas frecuencias de reloj */
    MAP_CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48);
    MAP_CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1 );
    MAP_CS_initClockSignal(CS_HSMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1 );
    MAP_CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1 );
    MAP_CS_initClockSignal(CS_ACLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);

    /* Aquí se configura lo relacionado a la pantalla LCD
     * se llama a una librería que inicializa la pantalla, configura la orientación y los colores a utilizar
     * según el contexto actual*/
    Crystalfontz128x128_Init();

    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);

    Graphics_initContext(&g_sContext, &g_sCrystalfontz128x128);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_RED);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLUE);
    GrContextFontSet(&g_sContext, &g_sFontFixed6x8);


    /* Aquí se configura todo lo relacionado al ADC y al acelerómetro con la librería driverlib
     * Se utilizan las pines 4.0, 4.2 y 6.1 como entradas al ADC
     *   */
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4, GPIO_PIN0 | GPIO_PIN2, GPIO_TERTIARY_MODULE_FUNCTION);
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6, GPIO_PIN1, GPIO_TERTIARY_MODULE_FUNCTION);

    MAP_ADC14_enableModule();
    MAP_ADC14_initModule(ADC_CLOCKSOURCE_ADCOSC, ADC_PREDIVIDER_64, ADC_DIVIDER_8,
            0);


    MAP_ADC14_configureMultiSequenceMode(ADC_MEM0, ADC_MEM2, true);
    MAP_ADC14_configureConversionMemory(ADC_MEM0,
            ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A14, ADC_NONDIFFERENTIAL_INPUTS);

    MAP_ADC14_configureConversionMemory(ADC_MEM1,
            ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A13, ADC_NONDIFFERENTIAL_INPUTS);

    MAP_ADC14_configureConversionMemory(ADC_MEM2,
            ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A11, ADC_NONDIFFERENTIAL_INPUTS);


    /* En esta parte se configuran y se habilitan las interrupciones para los
     * resultados de la conversión ADC
     * cuando se tiene una conversión lista se llama a la interrupción ADC14_IRQHandler*/
    MAP_ADC14_enableInterrupt(ADC_INT2);

    MAP_Interrupt_enableInterrupt(INT_ADC14);
    MAP_Interrupt_enableMaster();


    MAP_ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);

    MAP_ADC14_enableConversion();
    MAP_ADC14_toggleConversionTrigger();


    /*En esta última parte lo que se hace es poner inicialmente la mitad de la pantalla en azul y la otra mitad
     * en café, para tener configurados estos colores.
     * Aunque esta parte no es visible para el ojo humano, ya que casi de inmediato se llama a la función run que
     * se encarga de  mover el tamaño de loa cuadros de colores en base al ángulo.*/
    Graphics_clearDisplay(&g_sContext);

    g_rRectangule_Blue.xMin = g_uint32LcdXMin;
    g_rRectangule_Blue.xMax = g_uint32LcdXMax;
    g_rRectangule_Blue.yMin = g_uint32LcdYMin_Blue;
    g_rRectangule_Blue.yMax = g_uint32LcdYMax_Blue;

    g_rRectangule_Brown.xMin = g_uint32LcdXMin;
    g_rRectangule_Brown.xMax = g_uint32LcdXMax;
    g_rRectangule_Brown.yMin = g_uint32LcdYMin_Brown;
    g_rRectangule_Brown.yMax = g_uint32LcdYMax_Brown/2;

    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BROWN);

    Graphics_fillRectangle(&g_sContext, &g_rRectangule_Brown);


    return(NO_ERR);
}

extern "C"
{
/* Interrupcion para la lectura del acelerómetro
 * Mediante una conversión ADC
 * */
    void ADC14_IRQHandler(void)
    {
        uint64_t status;

        status = MAP_ADC14_getEnabledInterruptStatus();
        MAP_ADC14_clearInterruptFlag(status);

        if(status & ADC_INT2)
        {
            g_uint16AcelerometerX = ADC14_getResult(ADC_MEM0);
            g_DoubleAcelerometerY = ADC14_getResult(ADC_MEM1);
            g_uint16AcelerometerZ = ADC14_getResult(ADC_MEM2);

        }

    }
}
