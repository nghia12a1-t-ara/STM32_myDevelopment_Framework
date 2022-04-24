#ifndef _STD_TYPES_H_
#define _STD_TYPES_H_

#include <stddef.h>
#include <stdint.h>

/**
 * Define Volatile Types
 */
#define __vo		volatile
#define __io		volatile
#define __i			volatile
#define __o			volatile
#define __weak 		__attribute__((weak))

/**
 * Define Standard Types
 */
#define uint32		uint32
#define uint16		uint16
#define uint8		uint8

/**
 * Some generic macros
*/
#define ENABLE 				1
#define DISABLE 			0
#define SET 				ENABLE
#define RESET 				DISABLE
#define GPIO_PIN_SET        SET
#define GPIO_PIN_RESET      RESET
#define FLAG_RESET         	RESET
#define FLAG_SET 			SET


#endif	/* !(_STD_TYPES_H_) */
