////////////////////////////////////////////////////////////////////////////////
/// @file     hal_dma.h
/// @author   AE TEAM
/// @brief    THIS FILE CONTAINS ALL THE FUNCTIONS PROTOTYPES FOR THE DMA
///           FIRMWARE LIBRARY.
////////////////////////////////////////////////////////////////////////////////
/// @attention
///
/// THE EXISTING FIRMWARE IS ONLY FOR REFERENCE, WHICH IS DESIGNED TO PROVIDE
/// CUSTOMERS WITH CODING INFORMATION ABOUT THEIR PRODUCTS SO THEY CAN SAVE
/// TIME. THEREFORE, MINDMOTION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
/// CONSEQUENTIAL DAMAGES ABOUT ANY CLAIMS ARISING OUT OF THE CONTENT OF SUCH
/// HARDWARE AND/OR THE USE OF THE CODING INFORMATION CONTAINED HEREIN IN
/// CONNECTION WITH PRODUCTS MADE BY CUSTOMERS.
///
/// <H2><CENTER>&COPY; COPYRIGHT MINDMOTION </CENTER></H2>
////////////////////////////////////////////////////////////////////////////////

// Define to prevent recursive inclusion
#ifndef __HAL_DMA_H
#define __HAL_DMA_H

// Files includes
#include "types.h"
#include "reg_common.h"
#include "reg_dma.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup DMA_HAL
/// @brief DMA HAL modules
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup DMA_Exported_Types
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief DMA data transfer direction Enumerate definition
/// @anchor DMA_data_transfer_direction
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    DMA_DIR_PeripheralSRC = 0U,
    DMA_DIR_PeripheralDST = DMA_CCR_DIR  // 0x00000010U
} DMA_data_transfer_direction_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief DMA peripheral incremented mode Enumerate definition
/// @anchor DMA_peripheral_incremented_mode
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    DMA_PeripheralInc_Disable = 0U,
    DMA_PeripheralInc_Enable  = DMA_CCR_PINC  // 0x00000040U
} DMA_peripheral_incremented_mode_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief DMA memory incremented mode Enumerate definition
/// @anchor DMA_memory_incremented_mode
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    DMA_MemoryInc_Disable = 0U,
    DMA_MemoryInc_Enable  = DMA_CCR_MINC  // 0x00000080U
} DMA_memory_incremented_mode_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief DMA peripheral data size Enumerate definition
/// @anchor DMA_peripheral_data_size
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    DMA_PeripheralDataSize_Byte     = 0U,
    DMA_PeripheralDataSize_HalfWord = DMA_CCR_PSIZE_HALFWORD,
    DMA_PeripheralDataSize_Word     = DMA_CCR_PSIZE_WORD
} DMA_peripheral_data_size_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief DMA memory data size Enumerate definition
/// @anchor DMA_memory_data_size
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    DMA_MemoryDataSize_Byte     = 0U,
    DMA_MemoryDataSize_HalfWord = DMA_CCR_MSIZE_HALFWORD,                       // 0x00000400U
    DMA_MemoryDataSize_Word     = DMA_CCR_MSIZE_WORD                            // 0x00000800U
} DMA_memory_data_size_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief DMA circular normal mode Enumerate definition
/// @anchor DMA_circular_normal_mode
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    DMA_Mode_Normal   = 0U,
    DMA_Mode_Circular = DMA_CCR_CIRC                                            // 0x00000020U
} DMA_circular_normal_mode_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief DMA priority level Enumerate definition
/// @anchor DMA_priority_level
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    DMA_Priority_Low      = 0U,
    DMA_Priority_Medium   = DMA_CCR_PL_Medium,                                  // 0x00001000U
    DMA_Priority_High     = DMA_CCR_PL_High,                                    // 0x00002000U
    DMA_Priority_VeryHigh = DMA_CCR_PL_VeryHigh                                 // 0x00003000U
} DMA_priority_level_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief DMA memory to memory Enumerate definition
/// @anchor DMA_memory_to_memory
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    DMA_M2M_Disable = 0U,
    DMA_M2M_Enable  = DMA_CCR_M2M                                               // 0x00004000U
} DMA_memory_to_memory_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief DMA auto reload Enumerate definition
/// @anchor DMA_auto_reload
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    DMA_Auto_Reload_Disable = 0U,  //
    DMA_Auto_Reload_Enable  = DMA_CCR_ARE
} DMA_auto_reload_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief  DMA Init structure definition
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    u32 DMA_PeripheralBaseAddr;                                 ///< the peripheral base address for DMA Channeln.
    u32 DMA_MemoryBaseAddr;                                     ///< the memory base address for DMA Channeln.
    DMA_data_transfer_direction_TypeDef DMA_DIR;                ///< the peripheral is the source or destination.
    u32 DMA_BufferSize;                                         ///< Specifies the buffer size, in data unit, of the Buffer size
    DMA_peripheral_incremented_mode_TypeDef DMA_PeripheralInc;  ///< Specifies whether the Peripheral address increment or not
    DMA_memory_incremented_mode_TypeDef DMA_MemoryInc;          ///< Specifies whether the memory address register is increment or not
    DMA_peripheral_data_size_TypeDef DMA_PeripheralDataSize;    ///< Specifies the Peripheral data width.
    DMA_memory_data_size_TypeDef DMA_MemoryDataSize;            ///< Specifies the Memory data width.
    DMA_circular_normal_mode_TypeDef DMA_Mode;                  ///< Specifies the operation mode of the DMA Channeln  circular or normal mode.
    DMA_priority_level_TypeDef DMA_Priority;                    ///< Specifies the software priority for the DMA priority level
    DMA_memory_to_memory_TypeDef DMA_M2M;                       ///< Specifies if the DMA Channeln will be used in  memory-to-memory transfer.
    DMA_auto_reload_TypeDef DMA_Auto_reload;                     ///< Specifies if the DMA Channeln will auto reload the CNDTR register
} DMA_InitTypeDef;

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup DMA_Exported_Variables
/// @{
#ifdef _HAL_DMA_C_

#define GLOBAL
#else
#define GLOBAL extern
#endif

#undef GLOBAL
/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup DMA_Exported_Functions
/// @{

void DMA_DeInit(DMA_Channel_TypeDef* channel);
void DMA_Init(DMA_Channel_TypeDef* channel, DMA_InitTypeDef* init_struct);
void DMA_StructInit(DMA_InitTypeDef* init_struct);
void DMA_Cmd(DMA_Channel_TypeDef* channel, FunctionalState state);
void DMA_ITConfig(DMA_Channel_TypeDef* channel, u32 it, FunctionalState state);
void DMA_ClearFlag(u32 flag);
void DMA_ClearITPendingBit(u32 it);

u16        DMA_GetCurrDataCounter(DMA_Channel_TypeDef* channel);
FlagStatus DMA_GetFlagStatus(u32 flag);
ITStatus   DMA_GetITStatus(u32 it);

void exDMA_SetPeripheralAddress(DMA_Channel_TypeDef* channel, u32 addr);
void exDMA_SetTransmitLen(DMA_Channel_TypeDef* channel, u16 len);
void exDMA_SetMemoryAddress(DMA_Channel_TypeDef* channel, u32 addr);

/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif //__HAL_DMA_H
////////////////////////////////////////////////////////////////////////////////
