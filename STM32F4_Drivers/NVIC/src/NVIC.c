
#include "NVIC.h"

/****************************************************************************/
/****************************** GPIO INTERRUPT ******************************/
/****************************************************************************/
/*
 * @func	GPIO_IRQConfig
 * @brief	Configure the IRQ Number
 * @param	IRQ Number
 * 			IRQ Priority
 * 			EnorDi - ENABLE or DISABLE IRQ Number
 * @reval	none
 */
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi)
{
	if (EnorDi == ENABLE)
	{
		if (IRQNumber <= 31)
		{
			/* Program ISER0 Register */
			*NVIC_ISER0 |= (1 << IRQNumber);
		}
		else if (IRQNumber > 31 && IRQNumber < 64)	/* 32 to 63 */
		{
			/* Program ISER1 Register */
			*NVIC_ISER1 |= (1 << (IRQNumber % 32));
		}
		else if (IRQNumber >= 64 && IRQNumber < 96)	/* 64 to 95 */
		{
			/* Program ISER2 Register */
			*NVIC_ISER3 |= (1 << (IRQNumber % 64));
		}
	}
	else
	{
		if (IRQNumber <= 31)
		{
			/* Program ICER0 Register */
			*NVIC_ICER0 |= (1 << IRQNumber);
		}
		else if (IRQNumber > 31 && IRQNumber < 64)	/* 32 to 63 */
		{
			/* Program ICER1 Register */
			*NVIC_ICER1 |= (1 << (IRQNumber % 32));
		}
		else if (IRQNumber >= 64 && IRQNumber < 96)	/* 64 to 95 */
		{
			/* Program ICER2 Register */
			*NVIC_ICER3 |= (1 << (IRQNumber % 64));
		}
	}
}


/*
 * @func	GPIO_IRQPriorityConfig
 * @brief	Configure the IRQ Priority
 * @param	IRQ Number
 * 			IRQ Priority
 * @reval	none
 */
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority)
{
	/* 1. First lets find out the ipr register */
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_section = IRQNumber % 4;

	uint8_t shift_amount = (8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED);
	*(NVIC_PR_BASE_ADDR + (iprx * 4)) |= (IRQPriority << shift_amount);
}


/*
 * @func	GPIO_IRQHandling
 * @brief
 * @param	IRQ Number
 * @reval	none
 */
void GPIO_IRQHandling(uint8_t PinNumber)
{
	/* Clear the EXTI PR (pending register) corresponding to the pin number */
	if (EXTI->PR & (1 << PinNumber))
	{
		EXTI->PR |= (1 << PinNumber);	/* Clear PR bit */
	}
}


/****************************************************************************/
/******************************* SPI INTERRUPT ******************************/
/****************************************************************************/
/**
 * @fn      		  - SPI_IRQInterruptConfig
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -

 */
void SPI_IRQInterruptConfig(uint8 IRQNumber, uint8 EnorDi)
{

	if(EnorDi == ENABLE)
	{
		if(IRQNumber <= 31)
		{
			//program ISER0 register
			*NVIC_ISER0 |= ( 1 << IRQNumber );

		}else if(IRQNumber > 31 && IRQNumber < 64 ) //32 to 63
		{
			//program ISER1 register
			*NVIC_ISER1 |= ( 1 << (IRQNumber % 32) );
		}
		else if(IRQNumber >= 64 && IRQNumber < 96 )
		{
			//program ISER2 register //64 to 95
			*NVIC_ISER3 |= ( 1 << (IRQNumber % 64) );
		}
	}else
	{
		if(IRQNumber <= 31)
		{
			//program ICER0 register
			*NVIC_ICER0 |= ( 1 << IRQNumber );
		}else if(IRQNumber > 31 && IRQNumber < 64 )
		{
			//program ICER1 register
			*NVIC_ICER1 |= ( 1 << (IRQNumber % 32) );
		}
		else if(IRQNumber >= 6 && IRQNumber < 96 )
		{
			//program ICER2 register
			*NVIC_ICER3 |= ( 1 << (IRQNumber % 64) );
		}
	}

}


/*********************************************************************
 * @fn      		  - SPI_IRQPriorityConfig
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -

 */
void SPI_IRQPriorityConfig(uint8 IRQNumber,uint32 IRQPriority)
{
	//1. first lets find out the ipr register
	uint8 iprx = IRQNumber / 4;
	uint8 iprx_section  = IRQNumber %4 ;

	uint8 shift_amount = ( 8 * iprx_section) + ( 8 - NO_PR_BITS_IMPLEMENTED) ;

	*(  NVIC_PR_BASE_ADDR + iprx ) |=  ( IRQPriority << shift_amount );

}


/****************************************************************************/
/******************************* I2C INTERRUPT ******************************/
/****************************************************************************/
/**
 * @fn      		  - I2C_IRQInterruptConfig
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -

 */
void I2C_IRQInterruptConfig(uint8 IRQNumber, uint8 EnorDi)
{

	if(EnorDi == ENABLE)
	{
		if(IRQNumber <= 31)
		{
			//program ISER0 register
			*NVIC_ISER0 |= ( 1 << IRQNumber );

		}else if(IRQNumber > 31 && IRQNumber < 64 ) //32 to 63
		{
			//program ISER1 register
			*NVIC_ISER1 |= ( 1 << (IRQNumber % 32) );
		}
		else if(IRQNumber >= 64 && IRQNumber < 96 )
		{
			//program ISER2 register //64 to 95
			*NVIC_ISER3 |= ( 1 << (IRQNumber % 64) );
		}
	}else
	{
		if(IRQNumber <= 31)
		{
			//program ICER0 register
			*NVIC_ICER0 |= ( 1 << IRQNumber );
		}else if(IRQNumber > 31 && IRQNumber < 64 )
		{
			//program ICER1 register
			*NVIC_ICER1 |= ( 1 << (IRQNumber % 32) );
		}
		else if(IRQNumber >= 6 && IRQNumber < 96 )
		{
			//program ICER2 register
			*NVIC_ICER3 |= ( 1 << (IRQNumber % 64) );
		}
	}

}


/*********************************************************************
 * @fn      		  - I2C_IRQPriorityConfig
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -

 */
void I2C_IRQPriorityConfig(uint8 IRQNumber,uint32 IRQPriority)
{
	//1. first lets find out the ipr register
	uint8 iprx = IRQNumber / 4;
	uint8 iprx_section  = IRQNumber %4 ;

	uint8 shift_amount = ( 8 * iprx_section) + ( 8 - NO_PR_BITS_IMPLEMENTED) ;

	*(  NVIC_PR_BASE_ADDR + iprx ) |=  ( IRQPriority << shift_amount );

}


/****************************************************************************/
/****************************** USART INTERRUPT *****************************/
/****************************************************************************/

/**
 * @fn      		  - USART_IRQInterruptConfig
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -

 */
void USART_IRQInterruptConfig(uint8 IRQNumber, uint8 EnorDi)
{

	if ( EnorDi == ENABLE )
	{
		if ( IRQNumber <= 31 )
		{
			//program ISER0 register
			*NVIC_ISER0 |= ( 1 << IRQNumber );

		}
		else if( IRQNumber > 31 && IRQNumber < 64 ) //32 to 63
		{
			//program ISER1 register
			*NVIC_ISER1 |= ( 1 << (IRQNumber % 32) );
		}
		else if ( IRQNumber >= 64 && IRQNumber < 96 )
		{
			//program ISER2 register //64 to 95
			*NVIC_ISER3 |= ( 1 << (IRQNumber % 64) );
		}
	}
	else
	{
		if ( IRQNumber <= 31 )
		{
			//program ICER0 register
			*NVIC_ICER0 |= ( 1 << IRQNumber );
		}
		else if ( (IRQNumber > 31) && (IRQNumber < 64) )
		{
			//program ICER1 register
			*NVIC_ICER1 |= ( 1 << (IRQNumber % 32) );
		}
		else if ( (IRQNumber >= 6) && (IRQNumber < 96) )
		{
			//program ICER2 register
			*NVIC_ICER3 |= ( 1 << (IRQNumber % 64) );
		}
	}
}


/*********************************************************************
 * @fn      		  - USART_IRQPriorityConfig
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -

 */
void USART_IRQPriorityConfig(uint8 IRQNumber,uint32 IRQPriority)
{
	//1. first lets find out the ipr register
	uint8 iprx = IRQNumber / 4;
	uint8 iprx_section  = IRQNumber %4 ;

	uint8 shift_amount = ( 8 * iprx_section) + ( 8 - NO_PR_BITS_IMPLEMENTED) ;

	*(  NVIC_PR_BASE_ADDR + iprx ) |=  ( IRQPriority << shift_amount );
}

