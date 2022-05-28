/*
 * NVIC_REG.h
 *
 *  Created on: May 15, 2022
 *      Author: Admin
 */

#ifndef NVIC_REG_H_
#define NVIC_REG_H_

#include <stdint.h>

/*
 * ARM Cortex Mx Processor NVIC ISERx register Addresses
 */

/*
 * ARM Cortex Mx Processor NVIC ISERx register Addresses
 */

#define NVIC_ISER0          ( (volatile uint32_t *)0xE000E100 )
#define NVIC_ISER1          ( (volatile uint32_t *)0xE000E104 )
#define NVIC_ISER2          ( (volatile uint32_t *)0xE000E108 )
#define NVIC_ISER3          ( (volatile uint32_t *)0xE000E10c )


/*
 * ARM Cortex Mx Processor NVIC ICERx register Addresses
 */
#define NVIC_ICER0 			( (volatile uint32_t *)0XE000E180 )
#define NVIC_ICER1			( (volatile uint32_t *)0XE000E184 )
#define NVIC_ICER2  		( (volatile uint32_t *)0XE000E188 )
#define NVIC_ICER3			( (volatile uint32_t *)0XE000E18C )


#define NVIC_ICPR0			( (volatile uint32_t *)(0xE000E280UL) )
#define NVIC_ICPR1			( (volatile uint32_t *)(0xE000E284UL) )
#define NVIC_ICPR2			( (volatile uint32_t *)(0xE000E288UL) )

/*
 * ARM Cortex Mx Processor Priority Register Address Calculation
 */
#define NVIC_PR_BASE_ADDR 	( (volatile uint32_t *)0xE000E400 )

/*
 * ARM Cortex Mx Processor number of priority bits implemented in Priority Register
 */
#define NO_PR_BITS_IMPLEMENTED		4

#endif /* NVIC_REG_H_ */
