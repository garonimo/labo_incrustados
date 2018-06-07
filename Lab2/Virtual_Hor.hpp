/*
 * Virtual_Hor.hpp
 *
 * Andrés Sánchez - B26214
 *
 *  Este es el header para la clase de Virtual_Hor
 */

#ifndef Virtual_Hor_HPP_
#define Virtual_Hor_HPP_
#define __NOP __nop
#include "msp.h"
#include "Task.hpp"

extern "C"
{
    #include "msp.h"
    #include <driverlib/driverlib.h>
    #include <GrLib/grlib/grlib.h>
    #include "LcdDriver/Crystalfontz128x128_ST7735.h"
    #include <stdio.h>
}


class Virtual_Hor : public Task
{
    public:
        Virtual_Hor(uint16_t);
        uint16_t i_uint16Test;
        virtual uint8_t run(void);
        virtual uint8_t setup(void);
        virtual uint8_t Get_Hor(void);
    protected:
    private:
};

#endif /* Virtual_Hor_HPP_ */
