#include "stm32f10x.h"
#include <stdio.h>
#include "filter.h"
#include <stdlib.h>
#include <math.h>

#define ADC1_DR_ADDRESS    ((uint32_t)0x4001244C)
#define NUMBER_OF_ADC_CHANNEL 8U

void ADC_Config(void);
void DMA_ConfigChannel_11(uint32_t *pStartAddress, uint32_t *pDestination, uint32_t u32NumberDataTranfer);
void Filter(void);

volatile float signal_kalman;
uint16_t u16ValueAdc1Channel[NUMBER_OF_ADC_CHANNEL] = {0U};

int main(void)
{

	DMA_ConfigChannel_11((uint32_t *)ADC1_DR_ADDRESS, (uint32_t *)u16ValueAdc1Channel, NUMBER_OF_ADC_CHANNEL);
	ADC_Config();
	
	while(1)
	{
		Filter();
	}
}

void ADC_Config(void)
{
    /* -- Enable clock for ADC1 and GPIOA -- */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    /* ==Configure ADC pins (PA0 -> Channel 0 to PA7 -> Channel 7) as analog inputs== */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_3| GPIO_Pin_4| GPIO_Pin_5| GPIO_Pin_6| GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
 
    ADC_InitTypeDef ADC_InitStructure;
    /* ADC1 configuration */
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    /*We will convert multiple channels */
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;
    /*select continuous conversion mode */
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//!
    /*select no external triggering */
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    /*right 12-bit data alignment in ADC data register */
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    /*8 channels conversion */
    ADC_InitStructure.ADC_NbrOfChannel = 8;
    /* load structure values to control and status registers */
    ADC_Init(ADC1, &ADC_InitStructure);
    /*configure each channel */
    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_41Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_41Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_41Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_41Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 5, ADC_SampleTime_41Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 6, ADC_SampleTime_41Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 7, ADC_SampleTime_41Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 8, ADC_SampleTime_41Cycles5);
    /*  Enable ADC1 */
    ADC_Cmd(ADC1, ENABLE);
    /* enable DMA for ADC */
    ADC_DMACmd(ADC1, ENABLE);
    /* Enable ADC1 reset calibration register */
    ADC_ResetCalibration(ADC1);
    /* Check the end of ADC1 reset calibration register */
    while(ADC_GetResetCalibrationStatus(ADC1));
    /* Start ADC1 calibration */
    ADC_StartCalibration(ADC1);
    /* Check the end of ADC1 calibration */
    while(ADC_GetCalibrationStatus(ADC1));
		/* Start ADC1 Software Conversion */
		ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}
void DMA_ConfigChannel_11(uint32_t *pStartAddress, uint32_t *pDestination, uint32_t u32NumberDataTranfer)
{
	/* Enable clock for DMA1 */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
  /*
	* Set the peripheral register address in the DMA_CPARx register. 
	* The data will be moved from/ to this address to/ from the memory after the peripheral event
	*/
	DMA1_Channel1->CPAR = (uint32_t)pStartAddress;
	/*
	* Set the memory address in the DMA_CMARx register. The data will be written to or
  * read from this memory after the peripheral event
	*/
	DMA1_Channel1->CMAR = (uint32_t)pDestination;
	/* 
   *Configure the total number of data to be transferred in the DMA_CNDTRx register.
  * After each peripheral event, this value will be decremented
	*/
	DMA1_Channel1->CNDTR = u32NumberDataTranfer;
	/*
	 * Configure the channel priority using the PL[1:0] bits in the DMA_CCRx register
	*/
	/*
	Configure data transfer direction, circular mode, peripheral & memory incremented
  mode, peripheral & memory data size, and interrupt after half and/or full transfer in the
  DMA_CCRx register.
	*/
	DMA1_Channel1->CCR |= 0x25A0;
	/* Activate the channel by setting the ENABLE bit in the DMA_CCRx register. */
	DMA1_Channel1->CCR |= 0x01;
	
}
/*  Low pass filter - High pass filter - Kalman filter*/
void Filter(void)
{
  signal_kalman = kalman_single(u16ValueAdc1Channel[0], 500, 10);
}

