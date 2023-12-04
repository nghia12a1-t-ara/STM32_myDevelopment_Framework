#ifndef __FLASH_TYPE_H__
#define __FLASH_TYPE_H__

/* Exported types ------------------------------------------------------------*/
/** 
  * @brief FLASH Status  
  */ 
typedef enum
{ 
	FLASH_BUSY = 1,
	FLASH_ERROR_PGS,
	FLASH_ERROR_PGP,
	FLASH_ERROR_PGA,
	FLASH_ERROR_WRP,
	FLASH_ERROR_PROGRAM,
	FLASH_ERROR_OPERATION,
	FLASH_COMPLETE
} FLASH_Status;

/************* Define FLASH_CR Bits ***************/
#define FLASH_CR_LOCK_SHIFT			(31U)
#define FLASH_CR_ERRIE_SHIFT        (25U)
#define FLASH_CR_EOPIE_SHIFT        (24U)
	
#define FLASH_CR_LOCK_MASK			(1U << 31)
#define FLASH_CR_ERRIE_MASK			(1U << 25)
#define FLASH_CR_EOPIE_MASK			(1U << 24)

/** @defgroup FLASH_Program_Parallelism   
  * @{
  */
#define FLASH_PSIZE_BYTE			((uint32)0x00000000UL)
#define FLASH_PSIZE_HALF_WORD		((uint32)0x00000100UL)
#define FLASH_PSIZE_WORD			((uint32)0x00000200UL)
#define FLASH_PSIZE_DOUBLE_WORD		((uint32)0x00000300UL)
#define FLASH_CR_PSIZE_MASK			((uint32)0x300UL)
#define SECTOR_MASK		            ((uint32)0xFFFFFF07UL)

#define FLASH_CR_STRT_SHIFT			(16U)
#define FLASH_CR_MER_SHIFT			(2U)
#define FLASH_CR_SER_SHIFT			(1U)
#define FLASH_CR_PG_SHIFT           (0U)
#define FLASH_CR_SNB_SHIFT          (3U)

#define FLASH_CR_SNB_MASK           (0x78UL)
#define FLASH_CR_STRT_MASK			(1U << 16)
#define FLASH_CR_MER_MASK			(1U << 2)
#define FLASH_CR_SER_MASK			(1U << 1)
#define FLASH_CR_PG_MASK			(1U << 0)

#define FLASH_CR_SNB(x)             ((uint32)((uint32)x<<FLASH_CR_SNB_SHIFT)&FLASH_CR_SNB_MASK)

/************* Define FLASH_SR Bits ***************/
#define FLASH_SR_BSY_SHIFT			(16U)
#define FLASH_SR_RDERR_SHIFT        (8U)
#define FLASH_SR_PGSERR_SHIFT		(7U)
#define FLASH_SR_PGPERR_SHIFT		(6U)
#define FLASH_SR_PGAERR_SHIFT		(5U)
#define FLASH_SR_WRPERR_SHIFT		(4U)
#define FLASH_SR_OPERR_SHIFT		(1U)
#define FLASH_SR_EOP_SHIFT			(0U)

#define FLASH_SR_BSY_MASK   		(1U << 16)
#define FLASH_SR_RDERR_MASK			(1U << 8)
#define FLASH_SR_PGSERR_MASK		(1U << 7)
#define FLASH_SR_PGPERR_MASK		(1U << 6)
#define FLASH_SR_PGAERR_MASK		(1U << 5)
#define FLASH_SR_WRPERR_MASK		(1U << 4)
#define FLASH_SR_OPERR_MASK			(1U << 1)
#define FLASH_SR_EOP_MASK			(1U << 0)


#endif	/* !(__FLASH_TYPE_H__) */
