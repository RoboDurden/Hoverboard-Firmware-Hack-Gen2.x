////////////////////////////////////////////////////////////////////////////////
/// @file     reg_syscfg.h
/// @author   AE TEAM
/// @brief    THIS FILE CONTAINS ALL THE FUNCTIONS PROTOTYPES FOR THE SERIES OF
///           MM32 FIRMWARE LIBRARY.
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

#ifndef __REG_SYSCFG_H
#define __REG_SYSCFG_H

// Files includes

#include <stdint.h>
#include <stdbool.h>
#include "types.h"




#if defined ( __CC_ARM )
#pragma anon_unions
#endif









#define SYSCFG_BASE                     (0x40010000UL + 0x0000)              ///< Base Address: 0x40010000






////////////////////////////////////////////////////////////////////////////////
/// @brief SysTem Configuration Register Structure Definition
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    __IO u32 CFGR;                                                         ///< SYSCFG configuration register                  offset: 0x00
    __IO u32 RESERVED0;
    __IO u32 EXTICR[4];
} SYSCFG_TypeDef;


#define SYSCFG                             ((SYSCFG_TypeDef *) SYSCFG_BASE)



////////////////////////////////////////////////////////////////////////////////
///@brief System Configuration (SYSCFG)
////////////////////////////////////////////////////////////////////////////////

/// @brief SYSCFG_CFGR Register Bit definition
#define SYSCFG_CFGR_MEM_MODE               ((u32)0x00000003)               ///< SYSCFG_Memory Remap Config
#define SYSCFG_CFGR_MEM_MODE_0             ((u32)0x00000001)               ///< SYSCFG_Memory Remap Config Bit 0
#define SYSCFG_CFGR_MEM_MODE_1             ((u32)0x00000002)               ///< SYSCFG_Memory Remap Config Bit 1
///
#define SYSCFG_CFGR_ADC_DMA_RMP            ((u32)0x00000100)               ///< ADC DMA remap
#define SYSCFG_CFGR_UART1TX_DMA_RMP        ((u32)0x00000200)               ///< UART1 TX DMA remap
#define SYSCFG_CFGR_UART1RX_DMA_RMP        ((u32)0x00000400)               ///< UART1 RX DMA remap
#define SYSCFG_CFGR_TIM16_DMA_RMP          ((u32)0x00000800)               ///< Timer 16 DMA remap
#define SYSCFG_CFGR_TIM17_DMA_RMP          ((u32)0x00001000)               ///< Timer 17 DMA remap
/// @brief SYSCFG_EXTICR1 Register Bit definition
#define SYSCFG_EXTICR1_EXTI0               ((u16)0x000F)                   ///< EXTI 0 configuration
#define SYSCFG_EXTICR1_EXTI1               ((u16)0x00F0)                   ///< EXTI 1 configuration
#define SYSCFG_EXTICR1_EXTI2               ((u16)0x0F00)                   ///< EXTI 2 configuration
#define SYSCFG_EXTICR1_EXTI3               ((u16)0xF000)                   ///< EXTI 3 configuration

///  @brief  EXTI0 configuration
#define SYSCFG_EXTICR1_EXTI0_PA            ((u16)0x0000)                   ///< PA[0] pin
#define SYSCFG_EXTICR1_EXTI0_PB            ((u16)0x0001)                   ///< PB[0] pin
#define SYSCFG_EXTICR1_EXTI0_PC            ((u16)0x0002)                   ///< PC[0] pin
#define SYSCFG_EXTICR1_EXTI0_PD            ((u16)0x0003)                   ///< PD[0] pin

///  @brief  EXTI1 configuration
#define SYSCFG_EXTICR1_EXTI1_PA            ((u16)0x0000)                   ///< PA[1] pin
#define SYSCFG_EXTICR1_EXTI1_PB            ((u16)0x0010)                   ///< PB[1] pin
#define SYSCFG_EXTICR1_EXTI1_PC            ((u16)0x0020)                   ///< PC[1] pin
#define SYSCFG_EXTICR1_EXTI1_PD            ((u16)0x0030)                   ///< PD[1] pin

///  @brief  EXTI2 configuration
#define SYSCFG_EXTICR1_EXTI2_PA            ((u16)0x0000)                   ///< PA[2] pin
#define SYSCFG_EXTICR1_EXTI2_PB            ((u16)0x0100)                   ///< PB[2] pin
#define SYSCFG_EXTICR1_EXTI2_PC            ((u16)0x0200)                   ///< PC[2] pin
#define SYSCFG_EXTICR1_EXTI2_PD            ((u16)0x0300)                   ///< PD[2] pin


///  @brief  EXTI3 configuration
#define SYSCFG_EXTICR1_EXTI3_PA            ((u16)0x0000)                   ///< PA[3] pin
#define SYSCFG_EXTICR1_EXTI3_PB            ((u16)0x1000)                   ///< PB[3] pin
#define SYSCFG_EXTICR1_EXTI3_PC            ((u16)0x2000)                   ///< PC[3] pin
#define SYSCFG_EXTICR1_EXTI3_PD            ((u16)0x3000)                   ///< PD[3] pin


/// @brief SYSCFG_EXTICR2 Register Bit definition
#define SYSCFG_EXTICR2_EXTI4               ((u16)0x000F)                   ///< EXTI 4 configuration
#define SYSCFG_EXTICR2_EXTI5               ((u16)0x00F0)                   ///< EXTI 5 configuration
#define SYSCFG_EXTICR2_EXTI6               ((u16)0x0F00)                   ///< EXTI 6 configuration
#define SYSCFG_EXTICR2_EXTI7               ((u16)0xF000)                   ///< EXTI 7 configuration

/// @brief  EXTI4 configuration
#define SYSCFG_EXTICR2_EXTI4_PA            ((u16)0x0000)                   ///< PA[4] pin
#define SYSCFG_EXTICR2_EXTI4_PB            ((u16)0x0001)                   ///< PB[4] pin
#define SYSCFG_EXTICR2_EXTI4_PC            ((u16)0x0002)                   ///< PC[4] pin
#define SYSCFG_EXTICR2_EXTI4_PD            ((u16)0x0003)                   ///< PD[4] pin


/// @brief  EXTI5 configuration
#define SYSCFG_EXTICR2_EXTI5_PA            ((u16)0x0000)                   ///< PA[5] pin
#define SYSCFG_EXTICR2_EXTI5_PB            ((u16)0x0010)                   ///< PB[5] pin
#define SYSCFG_EXTICR2_EXTI5_PC            ((u16)0x0020)                   ///< PC[5] pin
#define SYSCFG_EXTICR2_EXTI5_PD            ((u16)0x0030)                   ///< PD[5] pin

/// @brief  EXTI6 configuration

#define SYSCFG_EXTICR2_EXTI6_PA            ((u16)0x0000)                   ///< PA[6] pin
#define SYSCFG_EXTICR2_EXTI6_PB            ((u16)0x0100)                   ///< PB[6] pin
#define SYSCFG_EXTICR2_EXTI6_PC            ((u16)0x0200)                   ///< PC[6] pin
#define SYSCFG_EXTICR2_EXTI6_PD            ((u16)0x0300)                   ///< PD[6] pin


/// @brief  EXTI7 configuration
#define SYSCFG_EXTICR2_EXTI7_PA            ((u16)0x0000)                   ///< PA[7] pin
#define SYSCFG_EXTICR2_EXTI7_PB            ((u16)0x1000)                   ///< PB[7] pin
#define SYSCFG_EXTICR2_EXTI7_PC            ((u16)0x2000)                   ///< PC[7] pin
#define SYSCFG_EXTICR2_EXTI7_PD            ((u16)0x3000)                   ///< PD[7] pin

/// @brief SYSCFG_EXTICR3 Register Bit definition
#define SYSCFG_EXTICR3_EXTI8               ((u16)0x000F)                   ///< EXTI 8 configuration
#define SYSCFG_EXTICR3_EXTI9               ((u16)0x00F0)                   ///< EXTI 9 configuration
#define SYSCFG_EXTICR3_EXTI10              ((u16)0x0F00)                   ///< EXTI 10 configuration
#define SYSCFG_EXTICR3_EXTI11              ((u16)0xF000)                   ///< EXTI 11 configuration

///  @brief  EXTI8 configuration
#define SYSCFG_EXTICR3_EXTI8_PA            ((u16)0x0000)                   ///< PA[8] pin
#define SYSCFG_EXTICR3_EXTI8_PB            ((u16)0x0001)                   ///< PB[8] pin
#define SYSCFG_EXTICR3_EXTI8_PC            ((u16)0x0002)                   ///< PC[8] pin
#define SYSCFG_EXTICR3_EXTI8_PD            ((u16)0x0003)                   ///< PD[8] pin


///  @brief  EXTI9 configuration

#define SYSCFG_EXTICR3_EXTI9_PA            ((u16)0x0000)                   ///< PA[9] pin
#define SYSCFG_EXTICR3_EXTI9_PB            ((u16)0x0010)                   ///< PB[9] pin
#define SYSCFG_EXTICR3_EXTI9_PC            ((u16)0x0020)                   ///< PC[9] pin
#define SYSCFG_EXTICR3_EXTI9_PD            ((u16)0x0030)                   ///< PD[9] pin

///  @brief  EXTI10 configuration
#define SYSCFG_EXTICR3_EXTI10_PA           ((u16)0x0000)                   ///< PA[10] pin
#define SYSCFG_EXTICR3_EXTI10_PB           ((u16)0x0100)                   ///< PB[10] pin
#define SYSCFG_EXTICR3_EXTI10_PC           ((u16)0x0200)                   ///< PC[10] pin
#define SYSCFG_EXTICR3_EXTI10_PD           ((u16)0x0300)                   ///< PE[10] pin

///  @brief  EXTI11 configuration
#define SYSCFG_EXTICR3_EXTI11_PA           ((u16)0x0000)                   ///< PA[11] pin
#define SYSCFG_EXTICR3_EXTI11_PB           ((u16)0x1000)                   ///< PB[11] pin
#define SYSCFG_EXTICR3_EXTI11_PC           ((u16)0x2000)                   ///< PC[11] pin
#define SYSCFG_EXTICR3_EXTI11_PD           ((u16)0x3000)                   ///< PD[11] pin


/// @brief SYSCFG_EXTICR4 Register Bit definition
#define SYSCFG_EXTICR4_EXTI12               ((u16)0x000F)                  ///< EXTI 12 configuration
#define SYSCFG_EXTICR4_EXTI13               ((u16)0x00F0)                  ///< EXTI 13 configuration
#define SYSCFG_EXTICR4_EXTI14               ((u16)0x0F00)                  ///< EXTI 14 configuration
#define SYSCFG_EXTICR4_EXTI15               ((u16)0xF000)                  ///< EXTI 15 configuration

#define SYSCFG_EXTICR4_EXTI12_PA            ((u16)0x0000)                  ///< PA[12] pin for EXTI12
#define SYSCFG_EXTICR4_EXTI12_PB            ((u16)0x0001)                  ///< PB[12] pin for EXTI12
#define SYSCFG_EXTICR4_EXTI12_PC            ((u16)0x0002)                  ///< PC[12] pin for EXTI12
#define SYSCFG_EXTICR4_EXTI12_PD            ((u16)0x0003)                  ///< PD[12] pin for EXTI12

#define SYSCFG_EXTICR4_EXTI13_PA            ((u16)0x0000)                  ///< PA[13] pin for EXTI13
#define SYSCFG_EXTICR4_EXTI13_PB            ((u16)0x0010)                  ///< PB[13] pin for EXTI13
#define SYSCFG_EXTICR4_EXTI13_PC            ((u16)0x0020)                  ///< PC[13] pin for EXTI13
#define SYSCFG_EXTICR4_EXTI13_PD            ((u16)0x0030)                  ///< PD[13] pin for EXTI13

#define SYSCFG_EXTICR4_EXTI14_PA            ((u16)0x0000)                  ///< PA[14] pin for EXTI14
#define SYSCFG_EXTICR4_EXTI14_PB            ((u16)0x0100)                  ///< PB[14] pin for EXTI14
#define SYSCFG_EXTICR4_EXTI14_PC            ((u16)0x0200)                  ///< PC[14] pin for EXTI14
#define SYSCFG_EXTICR4_EXTI14_PD            ((u16)0x0300)                  ///< PD[14] pin for EXTI14

#define SYSCFG_EXTICR4_EXTI15_PA            ((u16)0x0000)                  ///< PA[15] pin for EXTI15
#define SYSCFG_EXTICR4_EXTI15_PB            ((u16)0x1000)                  ///< PB[15] pin for EXTI15
#define SYSCFG_EXTICR4_EXTI15_PC            ((u16)0x2000)                  ///< PC[15] pin for EXTI15
#define SYSCFG_EXTICR4_EXTI15_PD            ((u16)0x3000)                  ///< PD[15] pin for EXTI15



/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
