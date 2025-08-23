/**
 * @file DMA_Irq.c
 * @brief DMA Interrupt Service Routines for STM32F4xx
 * @author Embedded Software Team
 * @version 1.0
 * @date 2024
 */

#include "DMA.h"
#include "DMA_HwAccess.h"

/* External callback functions - defined by application */
extern void DMA_TransferCompleteCallback(DMA_InstanceType Instance, DMA_StreamType Stream);
extern void DMA_HalfTransferCallback(DMA_InstanceType Instance, DMA_StreamType Stream);
extern void DMA_TransferErrorCallback(DMA_InstanceType Instance, DMA_StreamType Stream, DMA_ErrorType Error);

/* Private constants */
#define DMA_STREAM_MASK_SHIFT_0    0U
#define DMA_STREAM_MASK_SHIFT_6    6U
#define DMA_STREAM_MASK_SHIFT_16   16U
#define DMA_STREAM_MASK_SHIFT_22   22U

#define DMA_FLAG_MASK_LOW          0x3FU
#define DMA_FLAG_MASK_HIGH         0x0F400000U

/**
 * @brief Get interrupt flags for specific stream
 * @param Instance DMA instance (DMA1 or DMA2)
 * @param Stream DMA stream number (0-7)
 * @return Current interrupt flags
 */
static uint32_t DMA_GetStreamFlags(DMA_InstanceType Instance, DMA_StreamType Stream)
{
    uint32_t flags = 0U;
    DMA_TypeDef* dmaBase = DMA_GetInstance(Instance);
    
    if (dmaBase == NULL)
    {
        return 0U;
    }
    
    if (Stream <= DMA_STREAM_1)
    {
        /* Streams 0-1: Use LISR register */
        flags = dmaBase->LISR >> (Stream * DMA_STREAM_MASK_SHIFT_6);
    }
    else if (Stream <= DMA_STREAM_3)
    {
        /* Streams 2-3: Use LISR register with offset */
        flags = dmaBase->LISR >> ((Stream - 2U) * DMA_STREAM_MASK_SHIFT_6 + DMA_STREAM_MASK_SHIFT_16);
    }
    else if (Stream <= DMA_STREAM_5)
    {
        /* Streams 4-5: Use HISR register */
        flags = dmaBase->HISR >> ((Stream - 4U) * DMA_STREAM_MASK_SHIFT_6);
    }
    else
    {
        /* Streams 6-7: Use HISR register with offset */
        flags = dmaBase->HISR >> ((Stream - 6U) * DMA_STREAM_MASK_SHIFT_6 + DMA_STREAM_MASK_SHIFT_16);
    }
    
    return flags & DMA_FLAG_MASK_LOW;
}

/**
 * @brief Clear interrupt flags for specific stream
 * @param Instance DMA instance (DMA1 or DMA2)
 * @param Stream DMA stream number (0-7)
 * @param Flags Flags to clear
 */
static void DMA_ClearStreamFlags(DMA_InstanceType Instance, DMA_StreamType Stream, uint32_t Flags)
{
    DMA_TypeDef* dmaBase = DMA_GetInstance(Instance);
    
    if (dmaBase == NULL)
    {
        return;
    }
    
    if (Stream <= DMA_STREAM_1)
    {
        /* Streams 0-1: Use LIFCR register */
        dmaBase->LIFCR = Flags << (Stream * DMA_STREAM_MASK_SHIFT_6);
    }
    else if (Stream <= DMA_STREAM_3)
    {
        /* Streams 2-3: Use LIFCR register with offset */
        dmaBase->LIFCR = Flags << ((Stream - 2U) * DMA_STREAM_MASK_SHIFT_6 + DMA_STREAM_MASK_SHIFT_16);
    }
    else if (Stream <= DMA_STREAM_5)
    {
        /* Streams 4-5: Use HIFCR register */
        dmaBase->HIFCR = Flags << ((Stream - 4U) * DMA_STREAM_MASK_SHIFT_6);
    }
    else
    {
        /* Streams 6-7: Use HIFCR register with offset */
        dmaBase->HIFCR = Flags << ((Stream - 6U) * DMA_STREAM_MASK_SHIFT_6 + DMA_STREAM_MASK_SHIFT_16);
    }
}

/**
 * @brief Common DMA interrupt handler
 * @param Instance DMA instance (DMA1 or DMA2)
 * @param Stream DMA stream number (0-7)
 */
static void DMA_CommonIRQHandler(DMA_InstanceType Instance, DMA_StreamType Stream)
{
    uint32_t flags = DMA_GetStreamFlags(Instance, Stream);
    
    /* Check Transfer Complete interrupt */
    if (flags & DMA_FLAG_TCIF)
    {
        /* Clear Transfer Complete flag */
        DMA_ClearStreamFlags(Instance, Stream, DMA_FLAG_TCIF);
        
        /* Call user callback */
        DMA_TransferCompleteCallback(Instance, Stream);
    }
    
    /* Check Half Transfer interrupt */
    if (flags & DMA_FLAG_HTIF)
    {
        /* Clear Half Transfer flag */
        DMA_ClearStreamFlags(Instance, Stream, DMA_FLAG_HTIF);
        
        /* Call user callback */
        DMA_HalfTransferCallback(Instance, Stream);
    }
    
    /* Check Transfer Error interrupt */
    if (flags & DMA_FLAG_TEIF)
    {
        /* Clear Transfer Error flag */
        DMA_ClearStreamFlags(Instance, Stream, DMA_FLAG_TEIF);
        
        /* Call user callback */
        DMA_TransferErrorCallback(Instance, Stream, DMA_ERROR_TRANSFER);
    }
    
    /* Check Direct Mode Error interrupt */
    if (flags & DMA_FLAG_DMEIF)
    {
        /* Clear Direct Mode Error flag */
        DMA_ClearStreamFlags(Instance, Stream, DMA_FLAG_DMEIF);
        
        /* Call user callback */
        DMA_TransferErrorCallback(Instance, Stream, DMA_ERROR_DIRECT_MODE);
    }
    
    /* Check FIFO Error interrupt */
    if (flags & DMA_FLAG_FEIF)
    {
        /* Clear FIFO Error flag */
        DMA_ClearStreamFlags(Instance, Stream, DMA_FLAG_FEIF);
        
        /* Call user callback */
        DMA_TransferErrorCallback(Instance, Stream, DMA_ERROR_FIFO);
    }
}

/* DMA1 Stream Interrupt Handlers */
void DMA1_Stream0_IRQHandler(void)
{
    DMA_CommonIRQHandler(DMA_INSTANCE_1, DMA_STREAM_0);
}

void DMA1_Stream1_IRQHandler(void)
{
    DMA_CommonIRQHandler(DMA_INSTANCE_1, DMA_STREAM_1);
}

void DMA1_Stream2_IRQHandler(void)
{
    DMA_CommonIRQHandler(DMA_INSTANCE_1, DMA_STREAM_2);
}

void DMA1_Stream3_IRQHandler(void)
{
    DMA_CommonIRQHandler(DMA_INSTANCE_1, DMA_STREAM_3);
}

void DMA1_Stream4_IRQHandler(void)
{
    DMA_CommonIRQHandler(DMA_INSTANCE_1, DMA_STREAM_4);
}

void DMA1_Stream5_IRQHandler(void)
{
    DMA_CommonIRQHandler(DMA_INSTANCE_1, DMA_STREAM_5);
}

void DMA1_Stream6_IRQHandler(void)
{
    DMA_CommonIRQHandler(DMA_INSTANCE_1, DMA_STREAM_6);
}

void DMA1_Stream7_IRQHandler(void)
{
    DMA_CommonIRQHandler(DMA_INSTANCE_1, DMA_STREAM_7);
}

/* DMA2 Stream Interrupt Handlers */
void DMA2_Stream0_IRQHandler(void)
{
    DMA_CommonIRQHandler(DMA_INSTANCE_2, DMA_STREAM_0);
}

void DMA2_Stream1_IRQHandler(void)
{
    DMA_CommonIRQHandler(DMA_INSTANCE_2, DMA_STREAM_1);
}

void DMA2_Stream2_IRQHandler(void)
{
    DMA_CommonIRQHandler(DMA_INSTANCE_2, DMA_STREAM_2);
}

void DMA2_Stream3_IRQHandler(void)
{
    DMA_CommonIRQHandler(DMA_INSTANCE_2, DMA_STREAM_3);
}

void DMA2_Stream4_IRQHandler(void)
{
    DMA_CommonIRQHandler(DMA_INSTANCE_2, DMA_STREAM_4);
}

void DMA2_Stream5_IRQHandler(void)
{
    DMA_CommonIRQHandler(DMA_INSTANCE_2, DMA_STREAM_5);
}

void DMA2_Stream6_IRQHandler(void)
{
    DMA_CommonIRQHandler(DMA_INSTANCE_2, DMA_STREAM_6);
}

void DMA2_Stream7_IRQHandler(void)
{
    DMA_CommonIRQHandler(DMA_INSTANCE_2, DMA_STREAM_7);
}

/**
 * @brief Enable DMA stream interrupt
 * @param Instance DMA instance (DMA1 or DMA2)
 * @param Stream DMA stream number (0-7)
 * @param InterruptType Type of interrupt to enable
 * @return DMA_StatusType Operation status
 */
DMA_StatusType DMA_EnableInterrupt(DMA_InstanceType Instance, DMA_StreamType Stream, DMA_InterruptType InterruptType)
{
    DMA_Stream_TypeDef* streamBase;
    
    /* Input validation */
    if ((Instance >= DMA_INSTANCE_MAX) || (Stream >= DMA_STREAM_MAX))
    {
        return DMA_STATUS_ERROR;
    }
    
    streamBase = DMA_GetStreamInstance(Instance, Stream);
    if (streamBase == NULL)
    {
        return DMA_STATUS_ERROR;
    }
    
    /* Enable specified interrupt */
    switch (InterruptType)
    {
        case DMA_INTERRUPT_TC:
            streamBase->CR |= DMA_SxCR_TCIE;
            break;
            
        case DMA_INTERRUPT_HT:
            streamBase->CR |= DMA_SxCR_HTIE;
            break;
            
        case DMA_INTERRUPT_TE:
            streamBase->CR |= DMA_SxCR_TEIE;
            break;
            
        case DMA_INTERRUPT_DME:
            streamBase->CR |= DMA_SxCR_DMEIE;
            break;
            
        case DMA_INTERRUPT_FE:
            streamBase->FCR |= DMA_SxFCR_FEIE;
            break;
            
        case DMA_INTERRUPT_ALL:
            streamBase->CR |= (DMA_SxCR_TCIE | DMA_SxCR_HTIE | DMA_SxCR_TEIE | DMA_SxCR_DMEIE);
            streamBase->FCR |= DMA_SxFCR_FEIE;
            break;
            
        default:
            return DMA_STATUS_ERROR;
    }
    
    return DMA_STATUS_OK;
}

/**
 * @brief Disable DMA stream interrupt
 * @param Instance DMA instance (DMA1 or DMA2)
 * @param Stream DMA stream number (0-7)
 * @param InterruptType Type of interrupt to disable
 * @return DMA_StatusType Operation status
 */
DMA_StatusType DMA_DisableInterrupt(DMA_InstanceType Instance, DMA_StreamType Stream, DMA_InterruptType InterruptType)
{
    DMA_Stream_TypeDef* streamBase;
    
    /* Input validation */
    if ((Instance >= DMA_INSTANCE_MAX) || (Stream >= DMA_STREAM_MAX))
    {
        return DMA_STATUS_ERROR;
    }
    
    streamBase = DMA_GetStreamInstance(Instance, Stream);
    if (streamBase == NULL)
    {
        return DMA_STATUS_ERROR;
    }
    
    /* Disable specified interrupt */
    switch (InterruptType)
    {
        case DMA_INTERRUPT_TC:
            streamBase->CR &= ~DMA_SxCR_TCIE;
            break;
            
        case DMA_INTERRUPT_HT:
            streamBase->CR &= ~DMA_SxCR_HTIE;
            break;
            
        case DMA_INTERRUPT_TE:
            streamBase->CR &= ~DMA_SxCR_TEIE;
            break;
            
        case DMA_INTERRUPT_DME:
            streamBase->CR &= ~DMA_SxCR_DMEIE;
            break;
            
        case DMA_INTERRUPT_FE:
            streamBase->FCR &= ~DMA_SxFCR_FEIE;
            break;
            
        case DMA_INTERRUPT_ALL:
            streamBase->CR &= ~(DMA_SxCR_TCIE | DMA_SxCR_HTIE | DMA_SxCR_TEIE | DMA_SxCR_DMEIE);
            streamBase->FCR &= ~DMA_SxFCR_FEIE;
            break;
            
        default:
            return DMA_STATUS_ERROR;
    }
    
    return DMA_STATUS_OK;
}
