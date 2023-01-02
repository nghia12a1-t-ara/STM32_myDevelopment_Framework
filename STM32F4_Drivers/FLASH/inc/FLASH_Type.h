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
#define FLASH_CR_LOCK_POS			(31)
#define FLASH_CR_ERRIE_POS			(25)
#define FLASH_CR_EOPIE_POS			(24)
	
#define FLASH_CR_LOCK				(1 << 31)
#define FLASH_CR_ERRIE				(1 << 25)
#define FLASH_CR_EOPIE				(1 << 24)

/** @defgroup FLASH_Program_Parallelism   
  * @{
  */
#define FLASH_PSIZE_BYTE			((uint32_t)0x00000000)
#define FLASH_PSIZE_HALF_WORD		((uint32_t)0x00000100)
#define FLASH_PSIZE_WORD			((uint32_t)0x00000200)
#define FLASH_PSIZE_DOUBLE_WORD		((uint32_t)0x00000300)
#define FLASH_CR_PSIZE_MASK			((uint32_t)0xFFFFFCFF)
#define FLASH_CR_SECTOR_MASK		((uint32_t)0xFFFFFF07)

#define FLASH_CR_STRT_POS			(16)
#define FLASH_CR_MER_POS			(2)
#define FLASH_CR_SER_POS			(1)
#define FLASH_CR_PG_POS				(0)

#define FLASH_CR_STRT				(1 << 16)
#define FLASH_CR_MER				(1 << 2)
#define FLASH_CR_SER				(1 << 1)
#define FLASH_CR_PG					(1 << 0)

/************* Define FLASH_SR Bits ***************/
#define FLASH_SR_BSY_POS			(16)
#define FLASH_SR_RDERR_POS			(8)
#define FLASH_SR_PGSERR_POS			(7)
#define FLASH_SR_PGPERR_POS			(6)
#define FLASH_SR_PGAERR_POS			(5)
#define FLASH_SR_WRPERR_POS			(4)
#define FLASH_SR_OPERR_POS			(1)
#define FLASH_SR_EOP_POS			(0)

#define FLASH_SR_BSY				(1 << 16)
#define FLASH_SR_RDERR				(1 << 8)
#define FLASH_SR_PGSERR				(1 << 7)
#define FLASH_SR_PGPERR				(1 << 6)
#define FLASH_SR_PGAERR				(1 << 5)
#define FLASH_SR_WRPERR				(1 << 4)
#define FLASH_SR_OPERR				(1 << 1)
#define FLASH_SR_EOP				(1 << 0)


#endif	/* !(__FLASH_TYPE_H__) */
