===============================================================
 
Makefile for building MSP Code Examples in command line
environement using the Open Source GCC Toolchain

GCC - Open Source Compiler for MSP Microcontrollers

    http://www.ti.com/tool/msp430-gcc-opensource

GCC ARM Embedded Homepage:

    https://launchpad.net/gcc-arm-embedded

===============================================================

Makefile usage:

    make DEVICE=<deviceName> EXAMPLE=<exampleName>
    e.g. DEVICE=MSP432P401R EXAMPLE=msp432p401_adc14_01


Debug with GDB:

    make debug DEVICE=<deviceName> EXAMPLE=<exampleName>

===============================================================

This Makefile assumes the GCC ARM Embedded Toolchain is installed
into the default path of the MSP432-GCC-OPENSOURCE installer, and
the compiler bin directory is added to your Environmental PATH Variable.

To explicitly specify the GCC install path, use:

    make DEVICE=<deviceName> EXAMPLE=<exampleName> \
         GCC_DIR=<path_To_GCC_ARM_Root_containing_bin>

This Makefile also sets the MSP432 device specific include path relative
to MSP432-GCC-OPENSOURCE's default installation directory. To specify
a different include path:

    make DEVICE=<deviceName> EXAMPLE=<exampleName> \
         GCC_MSP_INC_DIR=<path_To_MSP432_device_include_path>

If using GCC installed inside Code Composer Studio, specify both
the GCC root and the MSP432 include path,

    make DEVICE=<deviceName> EXAMPLE=<exampleName> \
         GCC_DIR=<path_To_CCS/ccsv6/tools/compiler/gcc-arm-none-eabi-version> \
         GCC_MSP_INC_DIR=<path_To_CCS/ccsv6/ccs_base/arm/include>

===============================================================