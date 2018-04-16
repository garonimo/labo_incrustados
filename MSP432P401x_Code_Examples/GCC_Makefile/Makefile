#===============================================================
#Makefile for building MSP Code Examples in command line
#environement using the GCC Open Source Compiler for MSP432
#===============================================================

# Require DEVICE to be specified
ifndef DEVICE
$(info Please specify a device, e.g. DEVICE=MSP432P401R)
$(error unspecified device)
endif
# Require EXAMPLE to be specified
ifndef EXAMPLE
$(info Please specify an example, e.g. EXAMPLE=msp432p401_adc14_01)
$(error unspecified example)
endif

###################### Windows OS ######################
ifeq ($(OS),Windows_NT)
	OS          := $(shell uname -o)
	################## GCC Root Variable ###################
	GCC_DIR     ?= '$(shell where arm-none-eabi-gcc)/../../'
	GCC_MSP_INC_DIR ?= $(GCC_DIR)/../arm/include
	GCC_CMSIS_INC_DIR ?= $(GCC_MSP_INC_DIR)/CMSIS
	LDDIR       := $(GCC_MSP_INC_DIR)/$(DEVICE)
	RM          := rd /s /q
	ifeq ($(OS),Cygwin)
		MKDIR       = mkdir -p -- $@
	else
		MKDIR       = @mkdir $(subst /,\\,$@)
	endif
################### Linux or Mac OS ####################
else
	OS          := $(shell uname)
	################## GCC Root Variable ###################
	GCC_DIR     ?= ${shell dirname '${shell sh -c "which arm-none-eabi-gcc"}'}/..
	GCC_MSP_INC_DIR ?= $(GCC_DIR)/../arm/include
	GCC_CMSIS_INC_DIR ?= $(GCC_MSP_INC_DIR)/CMSIS
	LDDIR       := $(GCC_MSP_INC_DIR)/$(shell echo $(DEVICE) | tr A-Z a-z)
	RM          := rm -rf
	MKDIR       = mkdir -p -- $@
endif

######################################
GCC_BIN_DIR     ?= $(GCC_DIR)/bin
GCC_INC_DIR     ?= $(GCC_DIR)/arm-none-eabi/include
######################################
CC              := $(GCC_BIN_DIR)/arm-none-eabi-gcc
GDB             := $(GCC_BIN_DIR)/arm-none-eabi-gdb
######################################
CFLAGS          := -c -mcpu=cortex-m4 -march=armv7e-m -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mthumb -D__$(DEVICE)__ -DTARGET_IS_MSP432P4XX -Dgcc -g -gstrict-dwarf -Wall
LDFLAGS         := -mcpu=cortex-m4 -march=armv7e-m -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mthumb -D__$(DEVICE)__ -DTARGET_IS_MSP432P4XX -Dgcc -g -gstrict-dwarf -Wall -T$(LDDIR).lds -l'c' -l'gcc' -l'nosys'
INCLUDES        := -I $(GCC_CMSIS_INC_DIR) -I $(GCC_MSP_INC_DIR) -I $(GCC_INC_DIR)
######################################
SRC_DIR         := $(EXAMPLE)/C
STARTUP         := startup_msp432p401x_gcc
SYSTEM          := system_msp432p401x
OBJECTS         := $(EXAMPLE)/C/$(EXAMPLE).o $(EXAMPLE)/C/$(STARTUP).o $(EXAMPLE)/C/$(SYSTEM).o 
######################################

all: $(SRC_DIR)/$(EXAMPLE).out

$(EXAMPLE)/C:
	@$(MKDIR)

$(EXAMPLE)/C/%.o: ../C/$(EXAMPLE)/%.c
	@echo ============================================
	@echo Compiling $<
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

$(EXAMPLE)/C/$(EXAMPLE).out: $(EXAMPLE)/C $(OBJECTS)
	@echo ============================================
	@echo Linking objects and generating output binary
	$(CC) $(LDFLAGS) $(word 2,$^) $(EXAMPLE)/C/startup_msp432p401x_gcc.o $(EXAMPLE)/C/system_msp432p401x.o -o $@

debug: all
	$(GDB) $(EXAMPLE)/C/$(EXAMPLE).out

clean:
	@$(RM) $(EXAMPLE)