/**
 * Filename		: Bootloader.c
 * Author		: Nghia-Taarabt
 * Create Date 	: 18/12/22
 * Brief		: Bootloader Main Function
 */

#include "Bootloader.h"

void BootMainFunction()
{
    //uint32 NewAddressApp;
    
    /* Get Binary Data (HEX, SREC) from PC - UART, SPI, QSPI, EEP, ... */
    //Boot_From_UART();
        
#ifdef LOAD_TO_FLASH
    /* Write Application to Flash */
    
    //NewAddressApp = 0U;     /* @TODO */
#endif  /* LOAD_TO_FLASH */

#ifdef LOAD_TO_RAM
    /* Write Application to RAM */
    
    
    //NewAddressApp = BOOT_RAM_APPLICATION;
#endif  /* LOAD_TO_RAM */

    /* Jump to new application in SRAM */
    //Jump_To_Application(NewAddressApp);
}

/**
 * @brief   Function to Jump to Application
 * @param   AppStartAddress - Start address of Application
 * @retval  None
 */
void Jump_To_Application(uint32 AppStartAddress)
{
    uint32 topOfMainStack;
    
    /* First address of Vector Table will contain Start of Stack Address */
    topOfMainStack = REG_READ32(AppStartAddress);
    
    /* Function pointer to Reset_Handler of new Application */
    void (*App_Reset_Handler)(void) = 
            (void(*)(void))(*(volatile uint32*)(AppStartAddress+4));
    
    /* Disable all Interrupt and suspend systick timer */
    DisableAllInterrupt();
    SYSTICK->CSR = 0;
    SYSTICK->RVR = 0;
    SYSTICK->CVR = 0;
    
    /* Clear Pending Interrupt Request */
    SCB->SHCSR &= ~(SCB_SHCSR_USGFAULTACT_MASK |
                    SCB_SHCSR_BUSFAULTACT_MASK |
                    SCB_SHCSR_MEMFAULTACT_MASK);
    
    /* Set MSP and Vector Table Offset */
    __asm volatile ("MSR msp, %0" : : "r" (topOfMainStack) : );
    SCB->VTOR = AppStartAddress;
    
    /* Jump to Application by Function Pointer */
    App_Reset_Handler();
}
