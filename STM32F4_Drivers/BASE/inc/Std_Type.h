/**
 * Filename		: Stdype.h
 * Author		: Nghia Taarabt
 * Create Date 	: 18/12/22
 * Brief		: Standard Types for All Drivers
 */
 
#ifndef __STDYPE_H__
#define __STDYPE_H__

#include <stddef.h>

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
typedef signed char         int8;
typedef unsigned char       uint8;
typedef short               int16;
typedef unsigned short      uint16;
typedef int                 int32;
typedef unsigned            uint32;
typedef long long           int64;
typedef unsigned long long  uint64;

/**
 * Some generic macros
*/
#define ENABLE 				1u
#define DISABLE 			0u
#define BIT_SET 			ENABLE
#define BIT_RESET 			DISABLE
#define FLAG_RESET         	BIT_RESET
#define FLAG_SET 			BIT_SET

typedef enum {
	FALSE 	= 0u,
	TRUE 	= 1u
} Bool_Type;

#define DEFAULT_FUNCTION(X) 			(void)X      /* To avoid gcc/g++ warnings */

#endif	/* !(__STDYPE_H__) */
