/**
 * Filename		: stm32f4xx.h
 * Author		: Nghia Taarabt
 * Create Date 	: 18/12/22
 * Brief		: Header File for STM32F4
 */

#ifndef INC_STM32F4XX_H_
#define INC_STM32F4XX_H_

#include "Std_Type.h"
#include "RCC_Base.h"
#include "NVIC_Base.h"
#include "SCB_Base.h"
#include "SYSCFG_Base.h"

/**********************************START:Processor Specific Details **********************************/

/*
 * base addresses of Flash and SRAM memories
 */

#define FLASH_BASEADDR						0x08000000U   		/*!<explain this macro briefly here  */
#define SRAM1_BASEADDR						0x20000000U  		/*!<explain this macro briefly here  */
#define SRAM2_BASEADDR						0x2001C000U 		/*!<explain this macro briefly here  */
#define ROM_BASEADDR						0x1FFF0000U
#define SRAM 								SRAM1_BASEADDR


/*
 * AHBx and APBx Bus Peripheral base addresses
 */

#define PERIPH_BASEADDR 					0x40000000U
#define APB1PERIPH_BASEADDR					PERIPH_BASEADDR
#define APB2PERIPH_BASEADDR					0x40010000U
#define AHB1PERIPH_BASEADDR					0x40020000U
#define AHB2PERIPH_BASEADDR					0x50000000U


/************************************* Register Access ***********************************/
#define REG_WRITE32(address,data)			*(uint32*)address=data
#define REG_READ32(address)					*(uint32*)address

/* -------------------------  Interrupt Number Definition  ------------------------ */

typedef enum IRQn
{
/* -------------------  Cortex-M4 Processor Exceptions Numbers  ------------------- */
  NonMaskableInt_IRQn           = -14,      /*  2 Non Maskable Interrupt */
  HardFault_IRQn                = -13,      /*  3 HardFault Interrupt */
  MemoryManagement_IRQn         = -12,      /*  4 Memory Management Interrupt */
  BusFault_IRQn                 = -11,      /*  5 Bus Fault Interrupt */
  UsageFault_IRQn               = -10,      /*  6 Usage Fault Interrupt */
  SVCall_IRQn                   =  -5,      /* 11 SV Call Interrupt */
  DebugMonitor_IRQn             =  -4,      /* 12 Debug Monitor Interrupt */
  PendSV_IRQn                   =  -2,      /* 14 Pend SV Interrupt */
  SysTick_IRQn                  =  -1,      /* 15 System Tick Interrupt */

/* ----------------------  ARMCM4 Specific Interrupt Numbers  --------------------- */
  WDT_IRQn                      =   0,      /* Watchdog Timer Interrupt */
  RTC_IRQn                      =   1,      /* Real Time Clock Interrupt */
  TIM0_IRQn                     =   2,      /* Timer0 / Timer1 Interrupt */
  TIM2_IRQn                     =   3,      /* Timer2 / Timer3 Interrupt */
  MCIA_IRQn                     =   4,      /* MCIa Interrupt */
  MCIB_IRQn                     =   5,      /* MCIb Interrupt */
  UART0_IRQn                    =   6,      /* UART0 Interrupt */
  UART1_IRQn                    =   7,      /* UART1 Interrupt */
  UART2_IRQn                    =   8,      /* UART2 Interrupt */
  UART4_IRQn                    =   9,      /* UART4 Interrupt */
  AACI_IRQn                     =  10,      /* AACI / AC97 Interrupt */
  CLCD_IRQn                     =  11,      /* CLCD Combined Interrupt */
  ENET_IRQn                     =  12,      /* Ethernet Interrupt */
  USBDC_IRQn                    =  13,      /* USB Device Interrupt */
  USBHC_IRQn                    =  14,      /* USB Host Controller Interrupt */
  CHLCD_IRQn                    =  15,      /* Character LCD Interrupt */
  FLEXRAY_IRQn                  =  16,      /* Flexray Interrupt */
  CAN_IRQn                      =  17,      /* CAN Interrupt */
  LIN_IRQn                      =  18,      /* LIN Interrupt */
  I2C_IRQn                      =  19,      /* I2C ADC/DAC Interrupt */
  CPU_CLCD_IRQn                 =  28,      /* CPU CLCD Combined Interrupt */
  UART3_IRQn                    =  30,      /* UART3 Interrupt */
  SPI_IRQn                      =  31       /* SPI Touchscreen Interrupt */
} IRQn_Type;

#endif /* INC_STM32F4XX_H_ */
