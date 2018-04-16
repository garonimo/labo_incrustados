File Name                                      Description
----------------------------------------------------------------------------------------
msp432p401x_1                                  Software Toggle P1.0
msp432p401x_adc14_01                           ADC14, Sample A1, AVcc Ref, Set P1.0 if A1 > 0.5*Avcc
msp432p401x_adc14_03                           ADC14, Sample A2-A3 Differential,Set P1.0 if i/p> 1V
msp432p401x_adc14_05                           ADC14, Using an External Reference
msp432p401x_adc14_06                           ADC14, Repeated Sequence of Conversions
msp432p401x_adc14_10                           ADC14, Sample A22 Temp and Convert to oC and oF
msp432p401x_adc14_21                           ADC14, Window Comparator, 2.5V ref
msp432p401x_aes_01                             AES256 Encryption & Decryption
msp432p401x_comp_01                            COMP output Toggle in Sleep Mode; input channel C01; Vcompare is compared against internal 2.0V reference
msp432p401x_comp_05                            COMPE Hysteresis, COUT Toggle in SL; High speed mode
msp432p401x_crc32_01                           CRC32 in CRC16 mode, Compare CRC output with software-based algorithm
msp432p401x_cs_01                              Output MCLK & ACLK @ DCO default frequency
msp432p401x_cs_02                              Configure MCLK for 12MHz operation
msp432p401x_cs_03                              Device configuration for operation @ MCLK = DCO = 48MHz
msp432p401x_cs_06                              LFXT sources ACLK with fault detection. Outputs ACLK on P4.2
msp432p401x_cs_09                              HFXT@48MHz sources MCLK & HSMCLK, output to P4.3 & P4.4
msp432p401x_euscia0_uart_01                    eUSCI_A0 UART echo at 9600 baud using BRCLK = 12MHz
msp432p401x_euscia0_uart_03                    USCI_A0 External Loopback test @ 115200 baud
msp432p401x_euscia0_uart_09                    USCI_A0 wake up from LPM3 by RxD pin as GPIO interrupt
msp432p401x_euscib0_i2c_10                     eUSCI_B0 I2C Master RX multiple bytes from MSP432 Slave
msp432p401x_euscib0_i2c_11                     eUSCI_B0 I2C Slave TX multiple bytes to MSP432 Master
msp432p401x_euscib0_i2c_master_multislave      eUSCI_B0 I2C Master TX bytes to Multiple Slaves
msp432p401x_euscib0_i2c_multislave             eUSCI_B0 I2C 4 Hardware I2C slaves RX single byte
msp432p401x_euscib0_spi_09                     eUSCI_B0, SPI 3-Wire Master Incremented Data with clock polarity high
msp432p401x_euscib0_spi_10                     eUSCI_B0, SPI 3-Wire Slave Data Echo with clock polarity high
msp432p401x_euscib0_spi_11                     eUSCI_B0, SPI 4-Wire Master Incremented Data
msp432p401x_euscib0_spi_12                     eUSCI_B0, SPI 4-Wire Slave Data Echo
msp432p401x_mpu_01                             Configure and use the Memory Protection Unit (MPU)
msp432p401x_p1_01                              Software Poll P6.7, Set P1.0 if P6.7 = 1
msp432p401x_p1_03                              Software Port Interrupt Service on P1.1 from LPM4
msp432p401x_pa_01                              Write a word to Port A (Port 1 + 2)
msp432p401x_pcm_01                             Enter LPM0 (ARM Sleep Mode) with ACLK = REFO, SMCLK = 3MHz
msp432p401x_pcm_02                             Enter LPM3 (ARM Deep Sleep Mode) with ACLK = REFO
msp432p401x_pcm_03                             Enter LPM3 (ARM Deep Sleep Mode) with ACLK = VLO
msp432p401x_pcm_04                             Change VCORE from LEVEL 0 to LEVEL 1
msp432p401x_pcm_05                             Enter Low-Frequency Active mode 
msp432p401x_pcm_06                             Use TimerA in Low-Frequency mode with LPM0
msp432p401x_pcm_07                             Using Low-Frequency LPM0 mode to generate PWM
msp432p401x_pcm_08                             Use DC-DC Regulator
msp432p401x_pcm_09                             Device operation at 48MHz with DC-DC Regulator
msp432p401x_pcm_10                             Enter LPM3.5 mode with GPIO wake-up
msp432p401x_pcm_11                             Enter LPM4.5 mode with GPIO wake-up
msp432p401x_pcm_12                             Power mode transition between LPM3 and AM_LF
msp432p401x_portmap_01                         Use Port Map to output Timer A PWM channels
msp432p401x_portmap_02                         Port Map a single function to multiple pins
msp432p401x_portmap_03                         Port Map single function to multiple pins; Multiple runtime configurations
msp432p401x_ref_01                             Output reference module voltage to a port pin
msp432p401x_reset_01                           Soft Reset
msp432p401x_reset_02                           Hard reset
msp432p401x_rtc_01                             RTC in real time clock mode
msp432p401x_rtc_02                             RTC with 1-second wake-up interval from LPM3 with SVSMH enabled and all SRAM retained
msp432p401x_rtc_04                             RTC PS0 channel waking up device from LPM3, at 16kHz interval
msp432p401x_rtc_lpm3_01                        RTC with 1-second wake-up interval from LPM3 with SVSMH disabled and only Bank 0 is retained
msp432p401x_rtc_lpm35_01                       RTC, LPM3.5, & alarm
msp432p401x_sysctl_01                          Exercise SYSCTL features to retrieve device's memory size
msp432p401x_sysctl_02                          Enable/disable SRAM bank accesses
msp432p401x_sysctl_03                          Enable/disable SRAM bank access & retention
msp432p401x_systick_01                         SysTick used in interval mode
msp432p401x_systick_02                         Use SysTick to measure cycle count of a function
msp432p401x_ta0_01                             Timer0_A3, Toggle P1.0, CCR0 Cont Mode ISR, DCO SMCLK
msp432p401x_ta0_02                             Timer0_A3, Toggle P1.0, CCR0 Up Mode ISR, DCO SMCLK
msp432p401x_ta0_03                             Timer_A3, Toggle P1.0, Overflow ISR, DCO SMCLK
msp432p401x_ta0_04                             Timer0_A3, Toggle P1.0, Overflow ISR, 32kHz ACLK
msp432p401x_ta0_08                             Timer_A3, Toggle P1.0;P7.3,P2.4-5, Cont. Mode ISR, 32kHz ACLK
msp432p401x_ta0_capture                        Timer0_A3 Capture of ACLK
msp432p401x_ta1_05                             Timer1_A3, Toggle P1.0, CCR0 Cont. Mode ISR, 32kHz ACLK
msp432p401x_ta1_11                             Timer_A3, Toggle P8.0/TA1.0, Up Mode, 32kHz ACLK
msp432p401x_ta1_13                             Timer1_A3, Toggle P8.0/TA1.0, Up/Down Mode, DCO SMCLK
msp432p401x_ta1_14                             Timer1_A3, Toggle P8.0/TA1.0, Up/Down Mode, 32kHz ACLK
msp432p401x_ta1_16                             Timer1_A3, PWM TA1.1-2, Up Mode, DCO SMCLK
msp432p401x_ta1_17                             Timer1_A3, PWM TA1.1-2, Up Mode, 32KHz ACLK
msp432p401x_timer32_01                         Timer32 Example, One-shot mode in free run
msp432p401x_timer32_02                         Timer32 Example, One-shot and periodic mode
msp432p401x_wdt_01                             WDT, Toggle P1.0, Interval Overflow ISR, DCO SMCLK
msp432p401x_wdt_02                             WDT, Toggle P1.0, Interval Overflow ISR, 32kHz ACLK
msp432p401x_wdt_03                             WDT Failsafe Clock, WDT mode, DCO SMCLK

