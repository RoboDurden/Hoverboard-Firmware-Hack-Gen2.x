////////////////////////////////////////////////////////////////////////////////
/// @file     reg_exti.h
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

#ifndef __REG_EXTI_H
#define __REG_EXTI_H

// Files includes

#include <stdint.h>
#include <stdbool.h>
#include "types.h"




#if defined ( __CC_ARM )
#pragma anon_unions
#endif









////////////////////////////////////////////////////////////////////////////////
/// @brief EXTI Base Address Definition
////////////////////////////////////////////////////////////////////////////////
#define EXTI_BASE                       (0x40010000UL + 0x0000)              ///< Base Address: 0x40010000



////////////////////////////////////////////////////////////////////////////////
/// @brief EXTI Registers Structure Definition
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    __IO u32 CFGR;                                                              ///< configuration register,                        offset: 0x00
    u32 Reserved;                                                               ///< Reserved                                       offset: 0x04
    __IO u32 CR[4];                                                             ///< External interrupt configuration register,     offset: 0x08 - 0x17
    u32 Reserved1[0x100 - 0x06];                                                ///< Reserved space
    __IO u32 IMR;                                                               ///< Interrupt Mask Register                        offset: 0x00 + 0x400
    __IO u32 EMR;                                                               ///< Event Mask Register                            offset: 0x04 + 0x400
    __IO u32 RTSR;                                                              ///< Rising Trigger Status Register                 offset: 0x08 + 0x400
    __IO u32 FTSR;                                                              ///< Falling Trigger Status Register                offset: 0x0C + 0x400
    __IO u32 SWIER;                                                             ///< Software Interrupt Enable Register             offset: 0x10 + 0x400
    __IO u32 PR;                                                                ///< Pending Register                               offset: 0x14 + 0x400
} EXTI_TypeDef;



////////////////////////////////////////////////////////////////////////////////
/// @brief EXTI type pointer Definition
////////////////////////////////////////////////////////////////////////////////
#define EXTI                        ((EXTI_TypeDef*) EXTI_BASE)



////////////////////////////////////////////////////////////////////////////////
/// @brief EXTI_CFGR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define EXTI_CFGR_MEMMODE_Pos       (0)
#define EXTI_CFGR_MEMMODE           (0x03U << EXTI_CFGR_MEMMODE_Pos)        ///< EXTI_Memory Remap Config
#define EXTI_CFGR_MEMMODE_0         (0x01U << EXTI_CFGR_MEMMODE_Pos)        ///< EXTI_Memory Remap Config Bit 0
#define EXTI_CFGR_MEMMODE_1         (0x02U << EXTI_CFGR_MEMMODE_Pos)        ///< EXTI_Memory Remap Config Bit 1
#define EXTI_CFGR_FLASH_MEMORY      (0x00U << EXTI_CFGR_MEMMODE_Pos)        ///< EXTI_Memory Remap Config Mode 0
#define EXTI_CFGR_SYSTEM_MEMORY     (0x01U << EXTI_CFGR_MEMMODE_Pos)        ///< EXTI_Memory Remap Config Mode 1
#define EXTI_CFGR_SRAM_MEMORY       (0x03U << EXTI_CFGR_MEMMODE_Pos)        ///< EXTI_Memory Remap Config Mode 3
#define EXTI_CFGR_ADCDMA_Pos        (8)
#define EXTI_CFGR_ADCDMA            (0x01U << EXTI_CFGR_ADCDMA_Pos)         ///< ADC DMA remap
#define EXTI_CFGR_TIM16DMA_Pos      (11)
#define EXTI_CFGR_TIM16DMA          (0x01U << EXTI_CFGR_TIM16DMA_Pos)       ///< Timer 16 DMA remap
#define EXTI_CFGR_TIM17DMA_Pos      (12)
#define EXTI_CFGR_TIM17DMA          (0x01U << EXTI_CFGR_TIM17DMA_Pos)       ///< Timer 17 DMA remap

#define EXTI_CFGR_UART1TXDMA_Pos    (9)
#define EXTI_CFGR_UART1TXDMA        (0x01U << EXTI_CFGR_UART1TXDMA_Pos)     ///< UART1 TX DMA remap
#define EXTI_CFGR_UART1RXDMA_Pos    (10)
#define EXTI_CFGR_UART1RXDMA        (0x01U << EXTI_CFGR_UART1RXDMA_Pos)     ///< UART1 RX DMA remap


////////////////////////////////////////////////////////////////////////////////
/// @brief EXTI_CR1 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define EXTI_CR1_EXTI0_Pos          (0)
#define EXTI_CR1_EXTI0              (0x0FU << EXTI_CR1_EXTI0_Pos)           ///< EXTI 0 configuration
#define EXTI_CR1_EXTI0_PA           (0x00U << EXTI_CR1_EXTI0_Pos)           ///< PA[0] pin
#define EXTI_CR1_EXTI0_PB           (0x01U << EXTI_CR1_EXTI0_Pos)           ///< PB[0] pin
#define EXTI_CR1_EXTI0_PC           (0x02U << EXTI_CR1_EXTI0_Pos)           ///< PC[0] pin
#define EXTI_CR1_EXTI0_PD           (0x03U << EXTI_CR1_EXTI0_Pos)           ///< PD[0] pin

#define EXTI_CR1_EXTI1_Pos          (4)
#define EXTI_CR1_EXTI1              (0x0FU << EXTI_CR1_EXTI1_Pos)           ///< EXTI 1 configuration
#define EXTI_CR1_EXTI1_PA           (0x00U << EXTI_CR1_EXTI1_Pos)           ///< PA[1] pin
#define EXTI_CR1_EXTI1_PB           (0x01U << EXTI_CR1_EXTI1_Pos)           ///< PB[1] pin
#define EXTI_CR1_EXTI1_PC           (0x02U << EXTI_CR1_EXTI1_Pos)           ///< PC[1] pin
#define EXTI_CR1_EXTI1_PD           (0x03U << EXTI_CR1_EXTI1_Pos)           ///< PD[1] pin

#define EXTI_CR1_EXTI2_Pos          (8)
#define EXTI_CR1_EXTI2              (0x0FU << EXTI_CR1_EXTI2_Pos)           ///< EXTI 2 configuration
#define EXTI_CR1_EXTI2_PA           (0x00U << EXTI_CR1_EXTI2_Pos)           ///< PA[2] pin
#define EXTI_CR1_EXTI2_PB           (0x01U << EXTI_CR1_EXTI2_Pos)           ///< PB[2] pin
#define EXTI_CR1_EXTI2_PC           (0x02U << EXTI_CR1_EXTI2_Pos)           ///< PC[2] pin
#define EXTI_CR1_EXTI2_PD           (0x03U << EXTI_CR1_EXTI2_Pos)           ///< PD[2] pin

#define EXTI_CR1_EXTI3_Pos          (12)
#define EXTI_CR1_EXTI3              (0x0FU << EXTI_CR1_EXTI3_Pos)           ///< EXTI 3 configuration
#define EXTI_CR1_EXTI3_PA           (0x00U << EXTI_CR1_EXTI3_Pos)           ///< PA[3] pin
#define EXTI_CR1_EXTI3_PB           (0x01U << EXTI_CR1_EXTI3_Pos)           ///< PB[3] pin
#define EXTI_CR1_EXTI3_PC           (0x02U << EXTI_CR1_EXTI3_Pos)           ///< PC[3] pin
#define EXTI_CR1_EXTI3_PD           (0x03U << EXTI_CR1_EXTI3_Pos)           ///< PD[3] pin

////////////////////////////////////////////////////////////////////////////////
/// @brief EXTI_CR2 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define EXTI_CR2_EXTI4_Pos          (0)
#define EXTI_CR2_EXTI4              (0x0FU << EXTI_CR2_EXTI4_Pos)           ///< EXTI 4 configuration
#define EXTI_CR2_EXTI4_PA           (0x00U << EXTI_CR2_EXTI4_Pos)           ///< PA[4] pin
#define EXTI_CR2_EXTI4_PB           (0x01U << EXTI_CR2_EXTI4_Pos)           ///< PB[4] pin
#define EXTI_CR2_EXTI4_PC           (0x02U << EXTI_CR2_EXTI4_Pos)           ///< PC[4] pin
#define EXTI_CR2_EXTI4_PD           (0x03U << EXTI_CR2_EXTI4_Pos)           ///< PD[4] pin

#define EXTI_CR2_EXTI5_Pos          (4)
#define EXTI_CR2_EXTI5              (0x0FU << EXTI_CR2_EXTI5_Pos)           ///< EXTI 5 configuration
#define EXTI_CR2_EXTI5_PA           (0x00U << EXTI_CR2_EXTI5_Pos)           ///< PA[5] pin
#define EXTI_CR2_EXTI5_PB           (0x01U << EXTI_CR2_EXTI5_Pos)           ///< PB[5] pin
#define EXTI_CR2_EXTI5_PC           (0x02U << EXTI_CR2_EXTI5_Pos)           ///< PC[5] pin
#define EXTI_CR2_EXTI5_PD           (0x03U << EXTI_CR2_EXTI5_Pos)           ///< PD[5] pin

#define EXTI_CR2_EXTI6_Pos          (8)
#define EXTI_CR2_EXTI6              (0x0FU << EXTI_CR2_EXTI6_Pos)           ///< EXTI 6 configuration
#define EXTI_CR2_EXTI6_PA           (0x00U << EXTI_CR2_EXTI6_Pos)           ///< PA[6] pin
#define EXTI_CR2_EXTI6_PB           (0x01U << EXTI_CR2_EXTI6_Pos)           ///< PB[6] pin
#define EXTI_CR2_EXTI6_PC           (0x02U << EXTI_CR2_EXTI6_Pos)           ///< PC[6] pin
#define EXTI_CR2_EXTI6_PD           (0x03U << EXTI_CR2_EXTI6_Pos)           ///< PD[6] pin

#define EXTI_CR2_EXTI7_Pos          (12)
#define EXTI_CR2_EXTI7              (0x0FU << EXTI_CR2_EXTI7_Pos)           ///< EXTI 7 configuration
#define EXTI_CR2_EXTI7_PA           (0x00U << EXTI_CR2_EXTI7_Pos)           ///< PA[7] pin
#define EXTI_CR2_EXTI7_PB           (0x01U << EXTI_CR2_EXTI7_Pos)           ///< PB[7] pin
#define EXTI_CR2_EXTI7_PC           (0x02U << EXTI_CR2_EXTI7_Pos)           ///< PC[7] pin
#define EXTI_CR2_EXTI7_PD           (0x03U << EXTI_CR2_EXTI7_Pos)           ///< PD[7] pin

////////////////////////////////////////////////////////////////////////////////
/// @brief EXTI_CR3 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define EXTI_CR3_EXTI8_Pos          (0)
#define EXTI_CR3_EXTI8              (0x0FU << EXTI_CR3_EXTI8_Pos)           ///< EXTI 8 configuration
#define EXTI_CR3_EXTI8_PA           (0x00U << EXTI_CR3_EXTI8_Pos)           ///< PA[8] pin
#define EXTI_CR3_EXTI8_PB           (0x01U << EXTI_CR3_EXTI8_Pos)           ///< PB[8] pin
#define EXTI_CR3_EXTI8_PC           (0x02U << EXTI_CR3_EXTI8_Pos)           ///< PC[8] pin
#define EXTI_CR3_EXTI8_PD           (0x03U << EXTI_CR3_EXTI8_Pos)           ///< PD[8] pin

#define EXTI_CR3_EXTI9_Pos          (4)
#define EXTI_CR3_EXTI9              (0x0FU << EXTI_CR3_EXTI9_Pos)           ///< EXTI 9 configuration
#define EXTI_CR3_EXTI9_PA           (0x00U << EXTI_CR3_EXTI9_Pos)           ///< PA[9] pin
#define EXTI_CR3_EXTI9_PB           (0x01U << EXTI_CR3_EXTI9_Pos)           ///< PB[9] pin
#define EXTI_CR3_EXTI9_PC           (0x02U << EXTI_CR3_EXTI9_Pos)           ///< PC[9] pin
#define EXTI_CR3_EXTI9_PD           (0x03U << EXTI_CR3_EXTI9_Pos)           ///< PD[9] pin

#define EXTI_CR3_EXTI10_Pos         (8)
#define EXTI_CR3_EXTI10             (0x0FU << EXTI_CR3_EXTI10_Pos)          ///< EXTI 10 configuration
#define EXTI_CR3_EXTI10_PA          (0x00U << EXTI_CR3_EXTI10_Pos)          ///< PA[10] pin
#define EXTI_CR3_EXTI10_PB          (0x01U << EXTI_CR3_EXTI10_Pos)          ///< PB[10] pin
#define EXTI_CR3_EXTI10_PC          (0x02U << EXTI_CR3_EXTI10_Pos)          ///< PC[10] pin
#define EXTI_CR3_EXTI10_PD          (0x03U << EXTI_CR3_EXTI10_Pos)          ///< PD[10] pin

#define EXTI_CR3_EXTI11_Pos         (12)
#define EXTI_CR3_EXTI11             (0x0FU << EXTI_CR3_EXTI11_Pos)          ///< EXTI 11 configuration
#define EXTI_CR3_EXTI11_PA          (0x00U << EXTI_CR3_EXTI11_Pos)          ///< PA[11] pin
#define EXTI_CR3_EXTI11_PB          (0x01U << EXTI_CR3_EXTI11_Pos)          ///< PB[11] pin
#define EXTI_CR3_EXTI11_PC          (0x02U << EXTI_CR3_EXTI11_Pos)          ///< PC[11] pin
#define EXTI_CR3_EXTI11_PD          (0x03U << EXTI_CR3_EXTI11_Pos)          ///< PD[11] pin

////////////////////////////////////////////////////////////////////////////////
/// @brief EXTI_CR4 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define EXTI_CR4_EXTI12_Pos         (0)
#define EXTI_CR4_EXTI12             (0x0FU << EXTI_CR4_EXTI12_Pos)          ///< EXTI 12 configuration
#define EXTI_CR4_EXTI12_PA          (0x00U << EXTI_CR4_EXTI12_Pos)          ///< PA[12] pin
#define EXTI_CR4_EXTI12_PB          (0x01U << EXTI_CR4_EXTI12_Pos)          ///< PB[12] pin
#define EXTI_CR4_EXTI12_PC          (0x02U << EXTI_CR4_EXTI12_Pos)          ///< PC[12] pin
#define EXTI_CR4_EXTI12_PD          (0x03U << EXTI_CR4_EXTI12_Pos)          ///< PD[12] pin

#define EXTI_CR4_EXTI13_Pos         (4)
#define EXTI_CR4_EXTI13             (0x0FU << EXTI_CR4_EXTI13_Pos)          ///< EXTI 13 configuration
#define EXTI_CR4_EXTI13_PA          (0x00U << EXTI_CR4_EXTI13_Pos)          ///< PA[13] pin
#define EXTI_CR4_EXTI13_PB          (0x01U << EXTI_CR4_EXTI13_Pos)          ///< PB[13] pin
#define EXTI_CR4_EXTI13_PC          (0x02U << EXTI_CR4_EXTI13_Pos)          ///< PC[13] pin
#define EXTI_CR4_EXTI13_PD          (0x03U << EXTI_CR4_EXTI13_Pos)          ///< PD[13] pin

#define EXTI_CR4_EXTI14_Pos         (8)
#define EXTI_CR4_EXTI14             (0x0FU << EXTI_CR4_EXTI14_Pos)          ///< EXTI 14 configuration
#define EXTI_CR4_EXTI14_PA          (0x00U << EXTI_CR4_EXTI14_Pos)          ///< PA[14] pin
#define EXTI_CR4_EXTI14_PB          (0x01U << EXTI_CR4_EXTI14_Pos)          ///< PB[14] pin
#define EXTI_CR4_EXTI14_PC          (0x02U << EXTI_CR4_EXTI14_Pos)          ///< PC[14] pin
#define EXTI_CR4_EXTI14_PD          (0x03U << EXTI_CR4_EXTI14_Pos)          ///< PD[14] pin

#define EXTI_CR4_EXTI15_Pos         (12)
#define EXTI_CR4_EXTI15             (0x0FU << EXTI_CR4_EXTI15_Pos)          ///< EXTI 15 configuration
#define EXTI_CR4_EXTI15_PA          (0x00U << EXTI_CR4_EXTI15_Pos)          ///< PA[15] pin
#define EXTI_CR4_EXTI15_PB          (0x01U << EXTI_CR4_EXTI15_Pos)          ///< PB[15] pin
#define EXTI_CR4_EXTI15_PC          (0x02U << EXTI_CR4_EXTI15_Pos)          ///< PC[15] pin
#define EXTI_CR4_EXTI15_PD          (0x03U << EXTI_CR4_EXTI15_Pos)          ///< PD[15] pin

////////////////////////////////////////////////////////////////////////////////
/// @brief EXTI_IMR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define EXTI_IMR_0_Pos              (0)
#define EXTI_IMR_0                  (0x01U << EXTI_IMR_0_Pos)               ///< Interrupt Mask on line 0
#define EXTI_IMR_1_Pos              (1)
#define EXTI_IMR_1                  (0x01U << EXTI_IMR_1_Pos)               ///< Interrupt Mask on line 1
#define EXTI_IMR_2_Pos              (2)
#define EXTI_IMR_2                  (0x01U << EXTI_IMR_2_Pos)               ///< Interrupt Mask on line 2
#define EXTI_IMR_3_Pos              (3)
#define EXTI_IMR_3                  (0x01U << EXTI_IMR_3_Pos)               ///< Interrupt Mask on line 3
#define EXTI_IMR_4_Pos              (4)
#define EXTI_IMR_4                  (0x01U << EXTI_IMR_4_Pos)               ///< Interrupt Mask on line 4
#define EXTI_IMR_5_Pos              (5)
#define EXTI_IMR_5                  (0x01U << EXTI_IMR_5_Pos)               ///< Interrupt Mask on line 5
#define EXTI_IMR_6_Pos              (6)
#define EXTI_IMR_6                  (0x01U << EXTI_IMR_6_Pos)               ///< Interrupt Mask on line 6
#define EXTI_IMR_7_Pos              (7)
#define EXTI_IMR_7                  (0x01U << EXTI_IMR_7_Pos)               ///< Interrupt Mask on line 7
#define EXTI_IMR_8_Pos              (8)
#define EXTI_IMR_8                  (0x01U << EXTI_IMR_8_Pos)               ///< Interrupt Mask on line 8
#define EXTI_IMR_9_Pos              (9)
#define EXTI_IMR_9                  (0x01U << EXTI_IMR_9_Pos)               ///< Interrupt Mask on line 9
#define EXTI_IMR_10_Pos             (10)
#define EXTI_IMR_10                 (0x01U << EXTI_IMR_10_Pos)              ///< Interrupt Mask on line 10
#define EXTI_IMR_11_Pos             (11)
#define EXTI_IMR_11                 (0x01U << EXTI_IMR_11_Pos)              ///< Interrupt Mask on line 11
#define EXTI_IMR_12_Pos             (12)
#define EXTI_IMR_12                 (0x01U << EXTI_IMR_12_Pos)              ///< Interrupt Mask on line 12
#define EXTI_IMR_13_Pos             (13)
#define EXTI_IMR_13                 (0x01U << EXTI_IMR_13_Pos)              ///< Interrupt Mask on line 13
#define EXTI_IMR_14_Pos             (14)
#define EXTI_IMR_14                 (0x01U << EXTI_IMR_14_Pos)              ///< Interrupt Mask on line 14
#define EXTI_IMR_15_Pos             (15)
#define EXTI_IMR_15                 (0x01U << EXTI_IMR_15_Pos)              ///< Interrupt Mask on line 15
#define EXTI_IMR_16_Pos             (16)
#define EXTI_IMR_16                 (0x01U << EXTI_IMR_16_Pos)              ///< Interrupt Mask on line 16


#define EXTI_IMR_19_Pos             (19)
#define EXTI_IMR_19                 (0x01U << EXTI_IMR_19_Pos)              ///< Interrupt Mask on line 19



#define EXTI_IMR_24_Pos             (24)
#define EXTI_IMR_24                 (0x01U << EXTI_IMR_24_Pos)              ///< Interrupt Mask on line 24

////////////////////////////////////////////////////////////////////////////////
/// @brief EXTI_EMR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define EXTI_EMR_0_Pos              (0)
#define EXTI_EMR_0                  (0x01U << EXTI_EMR_0_Pos)               ///< Event Mask on line 0
#define EXTI_EMR_1_Pos              (1)
#define EXTI_EMR_1                  (0x01U << EXTI_EMR_1_Pos)               ///< Event Mask on line 1
#define EXTI_EMR_2_Pos              (2)
#define EXTI_EMR_2                  (0x01U << EXTI_EMR_2_Pos)               ///< Event Mask on line 2
#define EXTI_EMR_3_Pos              (3)
#define EXTI_EMR_3                  (0x01U << EXTI_EMR_3_Pos)               ///< Event Mask on line 3
#define EXTI_EMR_4_Pos              (4)
#define EXTI_EMR_4                  (0x01U << EXTI_EMR_4_Pos)               ///< Event Mask on line 4
#define EXTI_EMR_5_Pos              (5)
#define EXTI_EMR_5                  (0x01U << EXTI_EMR_5_Pos)               ///< Event Mask on line 5
#define EXTI_EMR_6_Pos              (6)
#define EXTI_EMR_6                  (0x01U << EXTI_EMR_6_Pos)               ///< Event Mask on line 6
#define EXTI_EMR_7_Pos              (7)
#define EXTI_EMR_7                  (0x01U << EXTI_EMR_7_Pos)               ///< Event Mask on line 7
#define EXTI_EMR_8_Pos              (8)
#define EXTI_EMR_8                  (0x01U << EXTI_EMR_8_Pos)               ///< Event Mask on line 8
#define EXTI_EMR_9_Pos              (9)
#define EXTI_EMR_9                  (0x01U << EXTI_EMR_9_Pos)               ///< Event Mask on line 9
#define EXTI_EMR_10_Pos             (10)
#define EXTI_EMR_10                 (0x01U << EXTI_EMR_10_Pos)              ///< Event Mask on line 10
#define EXTI_EMR_11_Pos             (11)
#define EXTI_EMR_11                 (0x01U << EXTI_EMR_11_Pos)              ///< Event Mask on line 11
#define EXTI_EMR_12_Pos             (12)
#define EXTI_EMR_12                 (0x01U << EXTI_EMR_12_Pos)              ///< Event Mask on line 12
#define EXTI_EMR_13_Pos             (13)
#define EXTI_EMR_13                 (0x01U << EXTI_EMR_13_Pos)              ///< Event Mask on line 13
#define EXTI_EMR_14_Pos             (14)
#define EXTI_EMR_14                 (0x01U << EXTI_EMR_14_Pos)              ///< Event Mask on line 14
#define EXTI_EMR_15_Pos             (15)
#define EXTI_EMR_15                 (0x01U << EXTI_EMR_15_Pos)              ///< Event Mask on line 15
#define EXTI_EMR_16_Pos             (16)
#define EXTI_EMR_16                 (0x01U << EXTI_EMR_16_Pos)              ///< Event Mask on line 16


#define EXTI_EMR_19_Pos             (19)
#define EXTI_EMR_19                 (0x01U << EXTI_EMR_19_Pos)              ///< Event Mask on line 19



#define EXTI_EMR_24_Pos             (24)
#define EXTI_EMR_24                 (0x01U << EXTI_EMR_24_Pos)              ///< Event Mask on line 24

////////////////////////////////////////////////////////////////////////////////
/// @brief EXTI_RTSR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define EXTI_RTSR_0_Pos             (0)
#define EXTI_RTSR_0                 (0x01U << EXTI_RTSR_0_Pos)              ///< Rising trigger event configuration bit of line 0
#define EXTI_RTSR_1_Pos             (1)
#define EXTI_RTSR_1                 (0x01U << EXTI_RTSR_1_Pos)              ///< Rising trigger event configuration bit of line 1
#define EXTI_RTSR_2_Pos             (2)
#define EXTI_RTSR_2                 (0x01U << EXTI_RTSR_2_Pos)              ///< Rising trigger event configuration bit of line 2
#define EXTI_RTSR_3_Pos             (3)
#define EXTI_RTSR_3                 (0x01U << EXTI_RTSR_3_Pos)              ///< Rising trigger event configuration bit of line 3
#define EXTI_RTSR_4_Pos             (4)
#define EXTI_RTSR_4                 (0x01U << EXTI_RTSR_4_Pos)              ///< Rising trigger event configuration bit of line 4
#define EXTI_RTSR_5_Pos             (5)
#define EXTI_RTSR_5                 (0x01U << EXTI_RTSR_5_Pos)              ///< Rising trigger event configuration bit of line 5
#define EXTI_RTSR_6_Pos             (6)
#define EXTI_RTSR_6                 (0x01U << EXTI_RTSR_6_Pos)              ///< Rising trigger event configuration bit of line 6
#define EXTI_RTSR_7_Pos             (7)
#define EXTI_RTSR_7                 (0x01U << EXTI_RTSR_7_Pos)              ///< Rising trigger event configuration bit of line 7
#define EXTI_RTSR_8_Pos             (8)
#define EXTI_RTSR_8                 (0x01U << EXTI_RTSR_8_Pos)              ///< Rising trigger event configuration bit of line 8
#define EXTI_RTSR_9_Pos             (9)
#define EXTI_RTSR_9                 (0x01U << EXTI_RTSR_9_Pos)              ///< Rising trigger event configuration bit of line 9
#define EXTI_RTSR_10_Pos            (10)
#define EXTI_RTSR_10                (0x01U << EXTI_RTSR_10_Pos)             ///< Rising trigger event configuration bit of line 10
#define EXTI_RTSR_11_Pos            (11)
#define EXTI_RTSR_11                (0x01U << EXTI_RTSR_11_Pos)             ///< Rising trigger event configuration bit of line 11
#define EXTI_RTSR_12_Pos            (12)
#define EXTI_RTSR_12                (0x01U << EXTI_RTSR_12_Pos)             ///< Rising trigger event configuration bit of line 12
#define EXTI_RTSR_13_Pos            (13)
#define EXTI_RTSR_13                (0x01U << EXTI_RTSR_13_Pos)             ///< Rising trigger event configuration bit of line 13
#define EXTI_RTSR_14_Pos            (14)
#define EXTI_RTSR_14                (0x01U << EXTI_RTSR_14_Pos)             ///< Rising trigger event configuration bit of line 14
#define EXTI_RTSR_15_Pos            (15)
#define EXTI_RTSR_15                (0x01U << EXTI_RTSR_15_Pos)             ///< Rising trigger event configuration bit of line 15
#define EXTI_RTSR_16_Pos            (16)
#define EXTI_RTSR_16                (0x01U << EXTI_RTSR_16_Pos)             ///< Rising trigger event configuration bit of line 16


#define EXTI_RTSR_19_Pos            (19)
#define EXTI_RTSR_19                (0x01U << EXTI_RTSR_19_Pos)             ///< Rising trigger event configuration bit of line 19



#define EXTI_RTSR_24_Pos            (24)
#define EXTI_RTSR_24                (0x01U << EXTI_RTSR_24_Pos)             ///< Rising trigger event configuration bit of line 24

////////////////////////////////////////////////////////////////////////////////
/// @brief EXTI_FTSR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define EXTI_FTSR_0_Pos             (0)
#define EXTI_FTSR_0                 (0x01U << EXTI_FTSR_0_Pos)              ///< Falling trigger event configuration bit of line 0
#define EXTI_FTSR_1_Pos             (1)
#define EXTI_FTSR_1                 (0x01U << EXTI_FTSR_1_Pos)              ///< Falling trigger event configuration bit of line 1
#define EXTI_FTSR_2_Pos             (2)
#define EXTI_FTSR_2                 (0x01U << EXTI_FTSR_2_Pos)              ///< Falling trigger event configuration bit of line 2
#define EXTI_FTSR_3_Pos             (3)
#define EXTI_FTSR_3                 (0x01U << EXTI_FTSR_3_Pos)              ///< Falling trigger event configuration bit of line 3
#define EXTI_FTSR_4_Pos             (4)
#define EXTI_FTSR_4                 (0x01U << EXTI_FTSR_4_Pos)              ///< Falling trigger event configuration bit of line 4
#define EXTI_FTSR_5_Pos             (5)
#define EXTI_FTSR_5                 (0x01U << EXTI_FTSR_5_Pos)              ///< Falling trigger event configuration bit of line 5
#define EXTI_FTSR_6_Pos             (6)
#define EXTI_FTSR_6                 (0x01U << EXTI_FTSR_6_Pos)              ///< Falling trigger event configuration bit of line 6
#define EXTI_FTSR_7_Pos             (7)
#define EXTI_FTSR_7                 (0x01U << EXTI_FTSR_7_Pos)              ///< Falling trigger event configuration bit of line 7
#define EXTI_FTSR_8_Pos             (8)
#define EXTI_FTSR_8                 (0x01U << EXTI_FTSR_8_Pos)              ///< Falling trigger event configuration bit of line 8
#define EXTI_FTSR_9_Pos             (9)
#define EXTI_FTSR_9                 (0x01U << EXTI_FTSR_9_Pos)              ///< Falling trigger event configuration bit of line 9
#define EXTI_FTSR_10_Pos            (10)
#define EXTI_FTSR_10                (0x01U << EXTI_FTSR_10_Pos)             ///< Falling trigger event configuration bit of line 10
#define EXTI_FTSR_11_Pos            (11)
#define EXTI_FTSR_11                (0x01U << EXTI_FTSR_11_Pos)             ///< Falling trigger event configuration bit of line 11
#define EXTI_FTSR_12_Pos            (12)
#define EXTI_FTSR_12                (0x01U << EXTI_FTSR_12_Pos)             ///< Falling trigger event configuration bit of line 12
#define EXTI_FTSR_13_Pos            (13)
#define EXTI_FTSR_13                (0x01U << EXTI_FTSR_13_Pos)             ///< Falling trigger event configuration bit of line 13
#define EXTI_FTSR_14_Pos            (14)
#define EXTI_FTSR_14                (0x01U << EXTI_FTSR_14_Pos)             ///< Falling trigger event configuration bit of line 14
#define EXTI_FTSR_15_Pos            (15)
#define EXTI_FTSR_15                (0x01U << EXTI_FTSR_15_Pos)             ///< Falling trigger event configuration bit of line 15
#define EXTI_FTSR_16_Pos            (16)
#define EXTI_FTSR_16                (0x01U << EXTI_FTSR_16_Pos)             ///< Falling trigger event configuration bit of line 16


#define EXTI_FTSR_19_Pos            (19)
#define EXTI_FTSR_19                (0x01U << EXTI_FTSR_19_Pos)             ///< Falling trigger event configuration bit of line 19



#define EXTI_FTSR_24_Pos            (24)
#define EXTI_FTSR_24                (0x01U << EXTI_FTSR_24_Pos)             ///< Falling trigger event configuration bit of line 24

////////////////////////////////////////////////////////////////////////////////
/// @brief EXTI_SWIER Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define EXTI_SWIER_0_Pos            (0)
#define EXTI_SWIER_0                (0x01U << EXTI_SWIER_0_Pos)             ///< Software Interrupt on line  0
#define EXTI_SWIER_1_Pos            (1)
#define EXTI_SWIER_1                (0x01U << EXTI_SWIER_1_Pos)             ///< Software Interrupt on line  1
#define EXTI_SWIER_2_Pos            (2)
#define EXTI_SWIER_2                (0x01U << EXTI_SWIER_2_Pos)             ///< Software Interrupt on line  2
#define EXTI_SWIER_3_Pos            (3)
#define EXTI_SWIER_3                (0x01U << EXTI_SWIER_3_Pos)             ///< Software Interrupt on line  3
#define EXTI_SWIER_4_Pos            (4)
#define EXTI_SWIER_4                (0x01U << EXTI_SWIER_4_Pos)             ///< Software Interrupt on line  4
#define EXTI_SWIER_5_Pos            (5)
#define EXTI_SWIER_5                (0x01U << EXTI_SWIER_5_Pos)             ///< Software Interrupt on line  5
#define EXTI_SWIER_6_Pos            (6)
#define EXTI_SWIER_6                (0x01U << EXTI_SWIER_6_Pos)             ///< Software Interrupt on line  6
#define EXTI_SWIER_7_Pos            (7)
#define EXTI_SWIER_7                (0x01U << EXTI_SWIER_7_Pos)             ///< Software Interrupt on line  7
#define EXTI_SWIER_8_Pos            (8)
#define EXTI_SWIER_8                (0x01U << EXTI_SWIER_8_Pos)             ///< Software Interrupt on line  8
#define EXTI_SWIER_9_Pos            (9)
#define EXTI_SWIER_9                (0x01U << EXTI_SWIER_9_Pos)             ///< Software Interrupt on line  9
#define EXTI_SWIER_10_Pos           (10)
#define EXTI_SWIER_10               (0x01U << EXTI_SWIER_10_Pos)            ///< Software Interrupt on line  10
#define EXTI_SWIER_11_Pos           (11)
#define EXTI_SWIER_11               (0x01U << EXTI_SWIER_11_Pos)            ///< Software Interrupt on line  11
#define EXTI_SWIER_12_Pos           (12)
#define EXTI_SWIER_12               (0x01U << EXTI_SWIER_12_Pos)            ///< Software Interrupt on line  12
#define EXTI_SWIER_13_Pos           (13)
#define EXTI_SWIER_13               (0x01U << EXTI_SWIER_13_Pos)            ///< Software Interrupt on line  13
#define EXTI_SWIER_14_Pos           (14)
#define EXTI_SWIER_14               (0x01U << EXTI_SWIER_14_Pos)            ///< Software Interrupt on line  14
#define EXTI_SWIER_15_Pos           (15)
#define EXTI_SWIER_15               (0x01U << EXTI_SWIER_15_Pos)            ///< Software Interrupt on line  15
#define EXTI_SWIER_16_Pos           (16)
#define EXTI_SWIER_16               (0x01U << EXTI_SWIER_16_Pos)            ///< Software Interrupt on line  16


#define EXTI_SWIER_19_Pos           (19)
#define EXTI_SWIER_19               (0x01U << EXTI_SWIER_19_Pos)            ///< Software Interrupt on line  19



#define EXTI_SWIER_24_Pos           (24)
#define EXTI_SWIER_24               (0x01U << EXTI_SWIER_24_Pos)            ///< Software Interrupt on line  24

////////////////////////////////////////////////////////////////////////////////
/// @brief EXTI_PR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define EXTI_PR_0_Pos               (0)
#define EXTI_PR_0                   (0x01U << EXTI_PR_0_Pos)                ///< Pending bit 0
#define EXTI_PR_1_Pos               (1)
#define EXTI_PR_1                   (0x01U << EXTI_PR_1_Pos)                ///< Pending bit 1
#define EXTI_PR_2_Pos               (2)
#define EXTI_PR_2                   (0x01U << EXTI_PR_2_Pos)                ///< Pending bit 2
#define EXTI_PR_3_Pos               (3)
#define EXTI_PR_3                   (0x01U << EXTI_PR_3_Pos)                ///< Pending bit 3
#define EXTI_PR_4_Pos               (4)
#define EXTI_PR_4                   (0x01U << EXTI_PR_4_Pos)                ///< Pending bit 4
#define EXTI_PR_5_Pos               (5)
#define EXTI_PR_5                   (0x01U << EXTI_PR_5_Pos)                ///< Pending bit 5
#define EXTI_PR_6_Pos               (6)
#define EXTI_PR_6                   (0x01U << EXTI_PR_6_Pos)                ///< Pending bit 6
#define EXTI_PR_7_Pos               (7)
#define EXTI_PR_7                   (0x01U << EXTI_PR_7_Pos)                ///< Pending bit 7
#define EXTI_PR_8_Pos               (8)
#define EXTI_PR_8                   (0x01U << EXTI_PR_8_Pos)                ///< Pending bit 8
#define EXTI_PR_9_Pos               (9)
#define EXTI_PR_9                   (0x01U << EXTI_PR_9_Pos)                ///< Pending bit 9
#define EXTI_PR_10_Pos              (10)
#define EXTI_PR_10                  (0x01U << EXTI_PR_10_Pos)               ///< Pending bit 10
#define EXTI_PR_11_Pos              (11)
#define EXTI_PR_11                  (0x01U << EXTI_PR_11_Pos)               ///< Pending bit 11
#define EXTI_PR_12_Pos              (12)
#define EXTI_PR_12                  (0x01U << EXTI_PR_12_Pos)               ///< Pending bit 12
#define EXTI_PR_13_Pos              (13)
#define EXTI_PR_13                  (0x01U << EXTI_PR_13_Pos)               ///< Pending bit 13
#define EXTI_PR_14_Pos              (14)
#define EXTI_PR_14                  (0x01U << EXTI_PR_14_Pos)               ///< Pending bit 14
#define EXTI_PR_15_Pos              (15)
#define EXTI_PR_15                  (0x01U << EXTI_PR_15_Pos)               ///< Pending bit 15
#define EXTI_PR_16_Pos              (16)
#define EXTI_PR_16                  (0x01U << EXTI_PR_16_Pos)               ///< Pending bit 16


#define EXTI_PR_19_Pos              (19)
#define EXTI_PR_19                  (0x01U << EXTI_PR_19_Pos)               ///< Pending bit 19



#define EXTI_PR_24_Pos              (24)
#define EXTI_PR_24                  (0x01U << EXTI_PR_24_Pos)               ///< Pending bit 24





/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
