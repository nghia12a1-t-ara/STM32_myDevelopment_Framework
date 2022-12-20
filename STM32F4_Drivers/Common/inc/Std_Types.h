/**
 * Filename		: Std_Types.h
 * Author		: Nghia Taarabt
 * Create Date 	: 18/12/22
 * Brief		: Standard Types for All Drivers
 */
 
#ifndef _STD_TYPES_H_
#define _STD_TYPES_H_

#include <stddef.h>
#include <stdint.h>

/**
 * Define Volatile Types
 */
#define __vo				volatile
#define __io				volatile
#define __i					volatile
#define __o					volatile
#define __I					volatile
#define	__IO				volatile
#define	__O					volatile

/**
 * Compiler Attributes 
 */
#define __weak 				__attribute__((weak))
#define __STATIC_INLINE		static inline

#ifndef NULL
	#define NULL 			0
#endif
#define NULL_PTR			(void*)NULL

/**
 * Define Standard Types
 */
#define uint64				uint64_t
#define uint32				uint32_t
#define uint16				uint16_t
#define uint8				uint8_t

#define int64				int64_t
#define int32				int32_t
#define int16				int16_t
#define int8				int8_t

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

typedef enum {
	FALSE = 0,
	TRUE = 1
} boolean;

#define DEFAULT_FUNCTION(X) 			(void)X      /* To avoid gcc/g++ warnings */

#endif	/* !(_STD_TYPES_H_) */
