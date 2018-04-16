/* --COPYRIGHT--,BSD_EX
 * Copyright (c) 2013, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *******************************************************************************
 *
 *                       MSP432 CODE EXAMPLE DISCLAIMER
 *
 * MSP432 code examples are self-contained low-level programs that typically
 * demonstrate a single peripheral function or device feature in a highly
 * concise manner. For this the code may rely on the device's power-on default
 * register values and settings such as the clock configuration and care must
 * be taken when combining code from several examples to avoid potential side
 * effects. Also see http://www.ti.com/tool/mspdriverlib for an API functional
 * library & https://dev.ti.com/pinmux/ for a GUI approach to peripheral configuration.
 *
 * --/COPYRIGHT--*/
//******************************************************************************
//   MSP432P401 Demo - Soft Reset
//
//   Description: This code examples exercises the soft reset feature by
//   triggering the soft reset with/out an assigned source number [0-15], and
//   after reset the code checks for the source of the reset. The example cycles
//   through soft reset w/o source and all soft reset sources, 0 to 15, and
//   completes when all soft reset sources have been triggered and confirmed
//   after subsequent resets.
//
//   Breakpoints can be set in each case statement to check when the associated
//   soft reset was triggered/confirmed.
//
//   When you reach the very end of the code example, the device should have
//   gone through 17 soft resets.
//
//
//  See msp432p401_reset_02 example for hard reset.
//
//                MSP432P401x
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//            |             P1.0|-->LED
//
//   Dung Dang
//   Texas Instruments Inc.
//   October 2015 (updated) | November 2013 (created)
//   Built with Code Composer Studio V6.0
//******************************************************************************
#include "msp.h"
#include "stdint.h"

uint8_t* stateMachine = (uint8_t*)0x20005000;

int main(void) {
    volatile uint32_t i;

    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;               // Stop WDT
    P1->DIR |= BIT0;                          // P1.0 set as output
    P1->OUT &= ~BIT0;                         // Turn off P1.0 LED

    /* Code test through soft resets with
        - No source
        - Source 0 -> 15in that order.
       After reset, check for source of reset to move on to next test
       After RSTCTL_SOFTRESET_STAT_SRC15, all tests should pass
    */


    if (*stateMachine == 0x00)
    {
        /* stateMachine is the RAM variable that does not get re-initialized
         * after soft reset. */
        *stateMachine = 1;

        /* Issue soft reset without specified source */
        RSTCTL->RESET_REQ |= (0x6900 | RSTCTL_RESET_REQ_SOFT_REQ);
    }

    /* Set breakpoints in the different case statements to check the source of
     * previous soft interrupt. Each breakpoint should only be hit once even
     * after resets.
     *
     * Remove all breakpoints to let the device run through all soft reset
     * iterations to the end of the code.
     */

    if (*stateMachine == 1)
    {
        switch (RSTCTL->SOFTRESET_STAT)        // Get the source of the soft reset
        {
            case 0:                         // Soft reset with no source indicated
                /* Issue soft reset with source = 0 */
                RSTCTL->SOFTRESET_SET |= RSTCTL_SOFTRESET_SET_SRC0;
                while(1);
            case RSTCTL_SOFTRESET_STAT_SRC0:  // Soft reset with source #0
                /* Clear soft reset source by writing to reset clear register */
                RSTCTL->SOFTRESET_CLR |= RSTCTL_SOFTRESET_STAT_SRC0;
                /* Issue soft reset with the next source */
                RSTCTL->SOFTRESET_SET |= RSTCTL_SOFTRESET_SET_SRC1;
                while(1);
            case RSTCTL_SOFTRESET_STAT_SRC1:
                RSTCTL->SOFTRESET_CLR |= RSTCTL_SOFTRESET_STAT_SRC1;
                RSTCTL->SOFTRESET_SET |= RSTCTL_SOFTRESET_SET_SRC2;
                while(1);
            case RSTCTL_SOFTRESET_STAT_SRC2:
                RSTCTL->SOFTRESET_CLR |= RSTCTL_SOFTRESET_STAT_SRC2;
                RSTCTL->SOFTRESET_SET |= RSTCTL_SOFTRESET_SET_SRC3;
                while(1);
            case RSTCTL_SOFTRESET_STAT_SRC3:
                RSTCTL->SOFTRESET_CLR |= RSTCTL_SOFTRESET_STAT_SRC3;
                RSTCTL->SOFTRESET_SET |= RSTCTL_SOFTRESET_SET_SRC4;
                while(1);
            case RSTCTL_SOFTRESET_STAT_SRC4:
                RSTCTL->SOFTRESET_CLR |= RSTCTL_SOFTRESET_STAT_SRC4;
                RSTCTL->SOFTRESET_SET |= RSTCTL_SOFTRESET_SET_SRC5;
                while(1);
            case RSTCTL_SOFTRESET_STAT_SRC5:
                RSTCTL->SOFTRESET_CLR |= RSTCTL_SOFTRESET_STAT_SRC5;
                RSTCTL->SOFTRESET_SET |= RSTCTL_SOFTRESET_SET_SRC6;
                while(1);
            case RSTCTL_SOFTRESET_STAT_SRC6:
                RSTCTL->SOFTRESET_CLR |= RSTCTL_SOFTRESET_STAT_SRC6;
                RSTCTL->SOFTRESET_SET |= RSTCTL_SOFTRESET_SET_SRC7;
                while(1);
            case RSTCTL_SOFTRESET_STAT_SRC7:
                RSTCTL->SOFTRESET_CLR |= RSTCTL_SOFTRESET_STAT_SRC7;
                RSTCTL->SOFTRESET_SET |= RSTCTL_SOFTRESET_SET_SRC8;
                while(1);
            case RSTCTL_SOFTRESET_STAT_SRC8:
                RSTCTL->SOFTRESET_CLR |= RSTCTL_SOFTRESET_STAT_SRC8;
                RSTCTL->SOFTRESET_SET |= RSTCTL_SOFTRESET_SET_SRC9;
                while(1);
            case RSTCTL_SOFTRESET_STAT_SRC9:
                RSTCTL->SOFTRESET_CLR |= RSTCTL_SOFTRESET_STAT_SRC9;
                RSTCTL->SOFTRESET_SET |= RSTCTL_SOFTRESET_SET_SRC10;
                while(1);
            case RSTCTL_SOFTRESET_STAT_SRC10:
                RSTCTL->SOFTRESET_CLR |= RSTCTL_SOFTRESET_STAT_SRC10;
                RSTCTL->SOFTRESET_SET |= RSTCTL_SOFTRESET_SET_SRC11;
                while(1);
            case RSTCTL_SOFTRESET_STAT_SRC11:
                RSTCTL->SOFTRESET_CLR |= RSTCTL_SOFTRESET_STAT_SRC11;
                RSTCTL->SOFTRESET_SET |= RSTCTL_SOFTRESET_SET_SRC12;
                while(1);
            case RSTCTL_SOFTRESET_STAT_SRC12:
                RSTCTL->SOFTRESET_CLR |= RSTCTL_SOFTRESET_STAT_SRC12;
                RSTCTL->SOFTRESET_SET |= RSTCTL_SOFTRESET_SET_SRC13;
                while(1);
            case RSTCTL_SOFTRESET_STAT_SRC13:
                RSTCTL->SOFTRESET_CLR |= RSTCTL_SOFTRESET_STAT_SRC13;
                RSTCTL->SOFTRESET_SET |= RSTCTL_SOFTRESET_SET_SRC14;
                while(1);
            case RSTCTL_SOFTRESET_STAT_SRC14:
                RSTCTL->SOFTRESET_CLR |= RSTCTL_SOFTRESET_STAT_SRC14;
                RSTCTL->SOFTRESET_SET |= RSTCTL_SOFTRESET_SET_SRC15;
                while(1);
            case RSTCTL_SOFTRESET_STAT_SRC15:
                RSTCTL->SOFTRESET_CLR |= RSTCTL_SOFTRESET_STAT_SRC15;
                /* All soft reset sources have been exercised. Update stateMachine
                 * and conclude the example
                 */
                *stateMachine = 2;
                break;

            default:
                while(1);
        }

    }
    /* *stateMachine == 2 means we've gone through all soft reset sources */

    if (*stateMachine == 2)
    {
        P1->OUT |= BIT0;                      // Turn on LED indicating success

        /* Reset the RAM variable *stateMachine to 0, in case you'd like to go
         * through the whole experience again by reseting the device */
        *stateMachine = 0;
    }
    else
    {
        while (1)
        {
            P1->OUT ^= BIT0;                  // Blink LED to indicate erroneous reset/execution in the code
            for (i=0;i<20000;i++);
        }
    }
}

