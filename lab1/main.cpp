#include "msp.h"
#include "Control_luces.h"


/**
 * main.c
 */
void main(void)
{


	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// se detiene el watchdog

	initialConfiguration();

}
