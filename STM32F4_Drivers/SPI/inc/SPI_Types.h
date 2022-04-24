#ifndef __SPI_TYPES_
#define __SPI_TYPES_

/*
 *  Configuration structure for SPIx peripheral
 */
typedef struct
{
	uint8 SPI_DeviceMode;
	uint8 SPI_BusConfig;
	uint8 SPI_SclkSpeed;
	uint8 SPI_DFF;
	uint8 SPI_CPOL;
	uint8 SPI_CPHA;
	uint8 SPI_SSM;
} SPI_Config_t;


/*
 *Handle structure for SPIx peripheral
 */
typedef struct
{
	SPI_Types 	*pSPIx;   /*!< This holds the base address of SPIx(x:0,1,2) peripheral >*/
	SPI_Config_t 	SPIConfig;
	uint8 		*pTxBuffer; /* !< To store the app. Tx buffer address > */
	uint8 		*pRxBuffer;	/* !< To store the app. Rx buffer address > */
	uint32 		TxLen;		/* !< To store Tx len > */
	uint32 		RxLen;		/* !< To store Tx len > */
	uint8 		TxState;	/* !< To store Tx state > */
	uint8 		RxState;	/* !< To store Rx state > */
} SPI_Handle_t;


/*
 * SPI application states
 */
#define SPI_READY 						0
#define SPI_BUSY_IN_RX 					1
#define SPI_BUSY_IN_TX 					2

/*
 * Possible SPI Application events
 */
#define SPI_EVENT_TX_CMPLT   			1
#define SPI_EVENT_RX_CMPLT   			2
#define SPI_EVENT_OVR_ERR    			3
#define SPI_EVENT_CRC_ERR    			4

/*
 * @SPI_DeviceMode
 */
#define SPI_DEVICE_MODE_MASTER    		1
#define SPI_DEVICE_MODE_SLAVE     		0

/*
 * @SPI_BusConfig
 */
#define SPI_BUS_CONFIG_FD               1
#define SPI_BUS_CONFIG_HD               2
#define SPI_BUS_CONFIG_SIMPLEX_RXONLY   3

/*
 * @SPI_SclkSpeed
 */
#define SPI_SCLK_SPEED_DIV2             0
#define SPI_SCLK_SPEED_DIV4             1
#define SPI_SCLK_SPEED_DIV8             2
#define SPI_SCLK_SPEED_DIV16            3
#define SPI_SCLK_SPEED_DIV32            4
#define SPI_SCLK_SPEED_DIV64            5
#define SPI_SCLK_SPEED_DIV128           6
#define SPI_SCLK_SPEED_DIV256           7

/*
 * @SPI_DFF
 */
#define SPI_DFF_8BITS 					0
#define SPI_DFF_16BITS  				1

/*
 * @CPOL
 */
#define SPI_CPOL_HIGH 					1
#define SPI_CPOL_LOW  					0

/*
 * @CPHA
 */
#define SPI_CPHA_HIGH 					1
#define SPI_CPHA_LOW  					0

/*
 * @SPI_SSM
 */
#define SPI_SSM_EN     					1
#define SPI_SSM_DI     					0

/*
 * SPI related status flags definitions
 */
#define SPI_TXE_FLAG    				( 1 << SPI_SR_TXE)
#define SPI_RXNE_FLAG   				( 1 << SPI_SR_RXNE)
#define SPI_BUSY_FLAG   				( 1 << SPI_SR_BSY)


#endif 	/* !(__SPI_TYPES_) */
