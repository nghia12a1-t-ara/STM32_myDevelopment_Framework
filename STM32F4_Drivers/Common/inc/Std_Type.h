/**
 * Filename		: Std_Type.h
 * Author		: Nghia Taarabt
 * Create Date 	: 18/12/22
 * Brief		: Standard Types for All Drivers
 */
 
#ifndef __STD_TYPE_H__
#define __STD_TYPE_H__

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
#define BIT_SET 			ENABLE
#define BIT_RESET 			DISABLE
#define FLAG_RESET         	BIT_RESET
#define FLAG_SET 			BIT_SET

typedef enum {
	FALSE 	= 0u,
	TRUE 	= 1u
} boolean;

#define DEFAULT_FUNCTION(X) 			(void)X      /* To avoid gcc/g++ warnings */

#endif	/* !(__STD_TYPE_H__) */
