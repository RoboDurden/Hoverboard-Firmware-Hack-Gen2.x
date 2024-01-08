////////////////////////////////////////////////////////////////////////////////
/// @file     reg_common.h
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

#ifndef __REG_COMMON_H
#define __REG_COMMON_H

// Files includes
#include <stdint.h>
#include <stdbool.h>
#include "types.h"


#if defined ( __CC_ARM )
#pragma anon_unions
#endif

#ifndef HSE_STARTUP_TIMEOUT
#define HSE_STARTUP_TIMEOUT     (0x0500U)                                       ///< Time out for HSE start up.
#endif
#ifdef  CLOCK_12MHz
#ifndef HSE_VALUE
#define HSE_VALUE               (12000000U)                                     ///< Value of the External oscillator in Hz.
#endif
#else
#ifndef HSE_VALUE
#define HSE_VALUE               (8000000U)                                      ///< Value of the External oscillator in Hz.
#endif
#endif




//#define HSI_VALUE_PLL_ON      (72000000 / 4)                                  ///< Value of the Internal
// oscillator in Hz. #define HSI_VALUE_PLL_OFF      (72000000 / 6)              ///<
// Value of the Internal oscillator in Hz.

#define HSI_72MHz               (72000000U)                                     ///< Value of the Internal oscillator in Hz.
#define HSI_48MHz               (48000000U)                                     ///< Value of the Internal oscillator in Hz.

#define HSI_72MHz_DIV6          (12000000U)                                     ///< Value of the Internal oscillator in Hz.
#define HSI_48MHz_DIV6          (8000000U)                                      ///< Value of the Internal oscillator in Hz.


#define LSI_VALUE               (40000U)                                        ///< Value of the Internal oscillator in Hz.





#ifndef HSI_VALUE
#ifdef CLOCK_UPDATE_72MHz
#define HSI_VALUE               HSI_72MHz_DIV6
#else
#define HSI_VALUE               HSI_48MHz_DIV6
#endif
#endif










#define __MPU_PRESENT               (0)                                     ///< Cortex-M0 does not provide a MPU present or not
#ifndef __NVIC_PRIO_BITS
#define __NVIC_PRIO_BITS            (2)                                     ///< Cortex-M0 uses 2 Bits for the Priority Levels
//#warning "__NVIC_PRIO_BITS not defined in device header file; using default!"
#endif
#define __Vendor_SysTickConfig      (0)                                     ///< Set to 1 if different SysTick Config is used

////////////////////////////////////////////////////////////////////////////////
/// @brief  MM32 MCU Interrupt Handle
////////////////////////////////////////////////////////////////////////////////
typedef enum IRQn {

    NonMaskableInt_IRQn             = -14,                                  ///< 2 Non Maskable Interrupt
    HardFault_IRQn                  = -13,                                  ///< 3 Cortex-M0 Hard Fault Interrupt
    MemoryManagement_IRQn           = -12,                                  ///< 4 Cortex-M0 Memory Management Interrupt
    BusFault_IRQn                   = -11,                                  ///< 5 Cortex-M0 Bus Fault Interrupt
    UsageFault_IRQn                 = -10,                                  ///< 6 Cortex-M0 Usage Fault Interrupt
    SVC_IRQn                        = -5,                                   ///< 11 Cortex-M0 SV Call Interrupt
    DebugMonitor_IRQn               = -4,                                   ///< 12 Cortex-M0 Debug Monitor Interrupt
    PendSV_IRQn                     = -2,                                   ///< 14 Cortex-M0 Pend SV Interrupt
    SysTick_IRQn                    = -1,                                   ///< 15 Cortex-M0 System Tick Interrupt
    WWDG_IWDG_IRQn                  = 0,                                    ///< WatchDog Interrupt
    WWDG_IRQn                       = 0,                                    ///< Window WatchDog Interrupt
    PVD_IRQn                        = 1,                                    ///< PVD through EXTI Line detect Interrupt
    FLASH_IRQn                      = 3,                                    ///< FLASH Interrupt
    RCC_IRQn                        = 4,                                    ///< RCC Interrupt
    EXTI0_1_IRQn                    = 5,                                    ///< EXTI Line 0 and 1 Interrupts
    EXTI2_3_IRQn                    = 6,                                    ///< EXTI Line 2 and 3 Interrupts
    EXTI4_15_IRQn                   = 7,                                    ///< EXTI Line 4 to 15 Interrupts
    HWDIV_IRQn                      = 8,                                    ///< HWDIV Global Interuupt
    DMA1_Channel1_IRQn              = 9,                                    ///< DMA Channel 1 Interrupt
    DMA1_Channel2_3_IRQn            = 10,                                   ///< DMA Channel 2 and Channel 3 Interrupts
    DMA1_Channel4_5_IRQn            = 11,                                   ///< DMA Channel 4 and Channel 5 Interrupts
    ADC_COMP_IRQn                   = 12,                                   ///< ADC & COMP Interrupts
    ADC_IRQn                        = 12,                                   ///< ADC Interrupts
    ADC1_IRQn                       = 12,                                   ///< ADC Interrupts
    TIM1_BRK_UP_TRG_COM_IRQn        = 13,                                   ///< TIM1 Break, Update, Trigger and Commutation Interrupts
    TIM1_CC_IRQn                    = 14,                                   ///< TIM1 Capture Compare Interrupt
    TIM2_IRQn                       = 15,                                   ///< TIM2 Interrupt
    TIM3_IRQn                       = 16,                                   ///< TIM3 Interrupt
    TIM14_IRQn                      = 19,                                   ///< TIM14 Interrupt
    TIM16_IRQn                      = 21,                                   ///< TIM16 Interrupt
    TIM17_IRQn                      = 22,                                   ///< TIM17 Interrupt
    I2C1_IRQn                       = 23,                                   ///< I2C1 Interrupt
    SPI1_IRQn                       = 25,                                   ///< SPI1 Interrupt
    SPI2_IRQn                       = 26,                                   ///< SPI2 Interrupt
    UART1_IRQn                      = 27,                                   ///< UART1 Interrupt
    UART2_IRQn                      = 28,                                   ///< UART2 Interrupt
} IRQn_Type;





#include <core_cm0.h>


#define PERIPH_BASE                     (0x40000000U)                           ///< Peripheral base address in the alias region




#define APB1PERIPH_BASE                 (PERIPH_BASE + 0x00000000)
#define APB2PERIPH_BASE                 (PERIPH_BASE + 0x00010000)
#define AHBPERIPH_BASE                  (PERIPH_BASE + 0x00020000)
#define APB3PERIPH_BASE                 (PERIPH_BASE + 0x00030000)
#define AHB2PERIPH_BASE                 (PERIPH_BASE + 0x08000000)




////////////////////////////////////////////////////////////////////////////////
/// @brief UID type pointer Definition
////////////////////////////////////////////////////////////////////////////////
#define UID_BASE                        (0x1FFFF7E8U)                           ///< Unique device ID register base address








///////////////////////////////////////////////////////////////////////////////
/// @brief Nested Vectored Interrupt Controller
///////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/// @brief NVIC_ISER Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define NVIC_ISER_SETENA                (0xFFFFFFFFU)                           ///< Interrupt set enable bits
#define NVIC_ISER_SETENA_0              (0x00000001U)                           ///< bit 0
#define NVIC_ISER_SETENA_1              (0x00000002U)                           ///< bit 1
#define NVIC_ISER_SETENA_2              (0x00000004U)                           ///< bit 2
#define NVIC_ISER_SETENA_3              (0x00000008U)                           ///< bit 3
#define NVIC_ISER_SETENA_4              (0x00000010U)                           ///< bit 4
#define NVIC_ISER_SETENA_5              (0x00000020U)                           ///< bit 5
#define NVIC_ISER_SETENA_6              (0x00000040U)                           ///< bit 6
#define NVIC_ISER_SETENA_7              (0x00000080U)                           ///< bit 7
#define NVIC_ISER_SETENA_8              (0x00000100U)                           ///< bit 8
#define NVIC_ISER_SETENA_9              (0x00000200U)                           ///< bit 9
#define NVIC_ISER_SETENA_10             (0x00000400U)                           ///< bit 10
#define NVIC_ISER_SETENA_11             (0x00000800U)                           ///< bit 11
#define NVIC_ISER_SETENA_12             (0x00001000U)                           ///< bit 12
#define NVIC_ISER_SETENA_13             (0x00002000U)                           ///< bit 13
#define NVIC_ISER_SETENA_14             (0x00004000U)                           ///< bit 14
#define NVIC_ISER_SETENA_15             (0x00008000U)                           ///< bit 15
#define NVIC_ISER_SETENA_16             (0x00010000U)                           ///< bit 16
#define NVIC_ISER_SETENA_17             (0x00020000U)                           ///< bit 17
#define NVIC_ISER_SETENA_18             (0x00040000U)                           ///< bit 18
#define NVIC_ISER_SETENA_19             (0x00080000U)                           ///< bit 19
#define NVIC_ISER_SETENA_20             (0x00100000U)                           ///< bit 20
#define NVIC_ISER_SETENA_21             (0x00200000U)                           ///< bit 21
#define NVIC_ISER_SETENA_22             (0x00400000U)                           ///< bit 22
#define NVIC_ISER_SETENA_23             (0x00800000U)                           ///< bit 23
#define NVIC_ISER_SETENA_24             (0x01000000U)                           ///< bit 24
#define NVIC_ISER_SETENA_25             (0x02000000U)                           ///< bit 25
#define NVIC_ISER_SETENA_26             (0x04000000U)                           ///< bit 26
#define NVIC_ISER_SETENA_27             (0x08000000U)                           ///< bit 27
#define NVIC_ISER_SETENA_28             (0x10000000U)                           ///< bit 28
#define NVIC_ISER_SETENA_29             (0x20000000U)                           ///< bit 29
#define NVIC_ISER_SETENA_30             (0x40000000U)                           ///< bit 30
#define NVIC_ISER_SETENA_31             (0x80000000U)                           ///< bit 31

////////////////////////////////////////////////////////////////////////////////
/// @brief NVIC_ICER Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define NVIC_ICER_CLRENA                (0xFFFFFFFFU)                           ///< Interrupt clear-enable bits
#define NVIC_ICER_CLRENA_0              (0x00000001U)                           ///< bit 0
#define NVIC_ICER_CLRENA_1              (0x00000002U)                           ///< bit 1
#define NVIC_ICER_CLRENA_2              (0x00000004U)                           ///< bit 2
#define NVIC_ICER_CLRENA_3              (0x00000008U)                           ///< bit 3
#define NVIC_ICER_CLRENA_4              (0x00000010U)                           ///< bit 4
#define NVIC_ICER_CLRENA_5              (0x00000020U)                           ///< bit 5
#define NVIC_ICER_CLRENA_6              (0x00000040U)                           ///< bit 6
#define NVIC_ICER_CLRENA_7              (0x00000080U)                           ///< bit 7
#define NVIC_ICER_CLRENA_8              (0x00000100U)                           ///< bit 8
#define NVIC_ICER_CLRENA_9              (0x00000200U)                           ///< bit 9
#define NVIC_ICER_CLRENA_10             (0x00000400U)                           ///< bit 10
#define NVIC_ICER_CLRENA_11             (0x00000800U)                           ///< bit 11
#define NVIC_ICER_CLRENA_12             (0x00001000U)                           ///< bit 12
#define NVIC_ICER_CLRENA_13             (0x00002000U)                           ///< bit 13
#define NVIC_ICER_CLRENA_14             (0x00004000U)                           ///< bit 14
#define NVIC_ICER_CLRENA_15             (0x00008000U)                           ///< bit 15
#define NVIC_ICER_CLRENA_16             (0x00010000U)                           ///< bit 16
#define NVIC_ICER_CLRENA_17             (0x00020000U)                           ///< bit 17
#define NVIC_ICER_CLRENA_18             (0x00040000U)                           ///< bit 18
#define NVIC_ICER_CLRENA_19             (0x00080000U)                           ///< bit 19
#define NVIC_ICER_CLRENA_20             (0x00100000U)                           ///< bit 20
#define NVIC_ICER_CLRENA_21             (0x00200000U)                           ///< bit 21
#define NVIC_ICER_CLRENA_22             (0x00400000U)                           ///< bit 22
#define NVIC_ICER_CLRENA_23             (0x00800000U)                           ///< bit 23
#define NVIC_ICER_CLRENA_24             (0x01000000U)                           ///< bit 24
#define NVIC_ICER_CLRENA_25             (0x02000000U)                           ///< bit 25
#define NVIC_ICER_CLRENA_26             (0x04000000U)                           ///< bit 26
#define NVIC_ICER_CLRENA_27             (0x08000000U)                           ///< bit 27
#define NVIC_ICER_CLRENA_28             (0x10000000U)                           ///< bit 28
#define NVIC_ICER_CLRENA_29             (0x20000000U)                           ///< bit 29
#define NVIC_ICER_CLRENA_30             (0x40000000U)                           ///< bit 30
#define NVIC_ICER_CLRENA_31             (0x80000000U)                           ///< bit 31

////////////////////////////////////////////////////////////////////////////////
/// @brief NVIC_ISPR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define NVIC_ISPR_SETPEND               (0xFFFFFFFFU)                           ///< Interrupt set-pending bits
#define NVIC_ISPR_SETPEND_0             (0x00000001U)                           ///< bit 0
#define NVIC_ISPR_SETPEND_1             (0x00000002U)                           ///< bit 1
#define NVIC_ISPR_SETPEND_2             (0x00000004U)                           ///< bit 2
#define NVIC_ISPR_SETPEND_3             (0x00000008U)                           ///< bit 3
#define NVIC_ISPR_SETPEND_4             (0x00000010U)                           ///< bit 4
#define NVIC_ISPR_SETPEND_5             (0x00000020U)                           ///< bit 5
#define NVIC_ISPR_SETPEND_6             (0x00000040U)                           ///< bit 6
#define NVIC_ISPR_SETPEND_7             (0x00000080U)                           ///< bit 7
#define NVIC_ISPR_SETPEND_8             (0x00000100U)                           ///< bit 8
#define NVIC_ISPR_SETPEND_9             (0x00000200U)                           ///< bit 9
#define NVIC_ISPR_SETPEND_10            (0x00000400U)                           ///< bit 10
#define NVIC_ISPR_SETPEND_11            (0x00000800U)                           ///< bit 11
#define NVIC_ISPR_SETPEND_12            (0x00001000U)                           ///< bit 12
#define NVIC_ISPR_SETPEND_13            (0x00002000U)                           ///< bit 13
#define NVIC_ISPR_SETPEND_14            (0x00004000U)                           ///< bit 14
#define NVIC_ISPR_SETPEND_15            (0x00008000U)                           ///< bit 15
#define NVIC_ISPR_SETPEND_16            (0x00010000U)                           ///< bit 16
#define NVIC_ISPR_SETPEND_17            (0x00020000U)                           ///< bit 17
#define NVIC_ISPR_SETPEND_18            (0x00040000U)                           ///< bit 18
#define NVIC_ISPR_SETPEND_19            (0x00080000U)                           ///< bit 19
#define NVIC_ISPR_SETPEND_20            (0x00100000U)                           ///< bit 20
#define NVIC_ISPR_SETPEND_21            (0x00200000U)                           ///< bit 21
#define NVIC_ISPR_SETPEND_22            (0x00400000U)                           ///< bit 22
#define NVIC_ISPR_SETPEND_23            (0x00800000U)                           ///< bit 23
#define NVIC_ISPR_SETPEND_24            (0x01000000U)                           ///< bit 24
#define NVIC_ISPR_SETPEND_25            (0x02000000U)                           ///< bit 25
#define NVIC_ISPR_SETPEND_26            (0x04000000U)                           ///< bit 26
#define NVIC_ISPR_SETPEND_27            (0x08000000U)                           ///< bit 27
#define NVIC_ISPR_SETPEND_28            (0x10000000U)                           ///< bit 28
#define NVIC_ISPR_SETPEND_29            (0x20000000U)                           ///< bit 29
#define NVIC_ISPR_SETPEND_30            (0x40000000U)                           ///< bit 30
#define NVIC_ISPR_SETPEND_31            (0x80000000U)                           ///< bit 31

////////////////////////////////////////////////////////////////////////////////
/// @brief NVIC_ICPR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define NVIC_ICPR_CLRPEND               (0xFFFFFFFFU)                           ///< Interrupt clear-pending bits
#define NVIC_ICPR_CLRPEND_0             (0x00000001U)                           ///< bit 0
#define NVIC_ICPR_CLRPEND_1             (0x00000002U)                           ///< bit 1
#define NVIC_ICPR_CLRPEND_2             (0x00000004U)                           ///< bit 2
#define NVIC_ICPR_CLRPEND_3             (0x00000008U)                           ///< bit 3
#define NVIC_ICPR_CLRPEND_4             (0x00000010U)                           ///< bit 4
#define NVIC_ICPR_CLRPEND_5             (0x00000020U)                           ///< bit 5
#define NVIC_ICPR_CLRPEND_6             (0x00000040U)                           ///< bit 6
#define NVIC_ICPR_CLRPEND_7             (0x00000080U)                           ///< bit 7
#define NVIC_ICPR_CLRPEND_8             (0x00000100U)                           ///< bit 8
#define NVIC_ICPR_CLRPEND_9             (0x00000200U)                           ///< bit 9
#define NVIC_ICPR_CLRPEND_10            (0x00000400U)                           ///< bit 10
#define NVIC_ICPR_CLRPEND_11            (0x00000800U)                           ///< bit 11
#define NVIC_ICPR_CLRPEND_12            (0x00001000U)                           ///< bit 12
#define NVIC_ICPR_CLRPEND_13            (0x00002000U)                           ///< bit 13
#define NVIC_ICPR_CLRPEND_14            (0x00004000U)                           ///< bit 14
#define NVIC_ICPR_CLRPEND_15            (0x00008000U)                           ///< bit 15
#define NVIC_ICPR_CLRPEND_16            (0x00010000U)                           ///< bit 16
#define NVIC_ICPR_CLRPEND_17            (0x00020000U)                           ///< bit 17
#define NVIC_ICPR_CLRPEND_18            (0x00040000U)                           ///< bit 18
#define NVIC_ICPR_CLRPEND_19            (0x00080000U)                           ///< bit 19
#define NVIC_ICPR_CLRPEND_20            (0x00100000U)                           ///< bit 20
#define NVIC_ICPR_CLRPEND_21            (0x00200000U)                           ///< bit 21
#define NVIC_ICPR_CLRPEND_22            (0x00400000U)                           ///< bit 22
#define NVIC_ICPR_CLRPEND_23            (0x00800000U)                           ///< bit 23
#define NVIC_ICPR_CLRPEND_24            (0x01000000U)                           ///< bit 24
#define NVIC_ICPR_CLRPEND_25            (0x02000000U)                           ///< bit 25
#define NVIC_ICPR_CLRPEND_26            (0x04000000U)                           ///< bit 26
#define NVIC_ICPR_CLRPEND_27            (0x08000000U)                           ///< bit 27
#define NVIC_ICPR_CLRPEND_28            (0x10000000U)                           ///< bit 28
#define NVIC_ICPR_CLRPEND_29            (0x20000000U)                           ///< bit 29
#define NVIC_ICPR_CLRPEND_30            (0x40000000U)                           ///< bit 30
#define NVIC_ICPR_CLRPEND_31            (0x80000000U)                           ///< bit 31

////////////////////////////////////////////////////////////////////////////////
/// @brief NVIC_IABR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define NVIC_IABR_ACTIVE                (0xFFFFFFFFU)                           ///< Interrupt active flags
#define NVIC_IABR_ACTIVE_0              (0x00000001U)                           ///< bit 0
#define NVIC_IABR_ACTIVE_1              (0x00000002U)                           ///< bit 1
#define NVIC_IABR_ACTIVE_2              (0x00000004U)                           ///< bit 2
#define NVIC_IABR_ACTIVE_3              (0x00000008U)                           ///< bit 3
#define NVIC_IABR_ACTIVE_4              (0x00000010U)                           ///< bit 4
#define NVIC_IABR_ACTIVE_5              (0x00000020U)                           ///< bit 5
#define NVIC_IABR_ACTIVE_6              (0x00000040U)                           ///< bit 6
#define NVIC_IABR_ACTIVE_7              (0x00000080U)                           ///< bit 7
#define NVIC_IABR_ACTIVE_8              (0x00000100U)                           ///< bit 8
#define NVIC_IABR_ACTIVE_9              (0x00000200U)                           ///< bit 9
#define NVIC_IABR_ACTIVE_10             (0x00000400U)                           ///< bit 10
#define NVIC_IABR_ACTIVE_11             (0x00000800U)                           ///< bit 11
#define NVIC_IABR_ACTIVE_12             (0x00001000U)                           ///< bit 12
#define NVIC_IABR_ACTIVE_13             (0x00002000U)                           ///< bit 13
#define NVIC_IABR_ACTIVE_14             (0x00004000U)                           ///< bit 14
#define NVIC_IABR_ACTIVE_15             (0x00008000U)                           ///< bit 15
#define NVIC_IABR_ACTIVE_16             (0x00010000U)                           ///< bit 16
#define NVIC_IABR_ACTIVE_17             (0x00020000U)                           ///< bit 17
#define NVIC_IABR_ACTIVE_18             (0x00040000U)                           ///< bit 18
#define NVIC_IABR_ACTIVE_19             (0x00080000U)                           ///< bit 19
#define NVIC_IABR_ACTIVE_20             (0x00100000U)                           ///< bit 20
#define NVIC_IABR_ACTIVE_21             (0x00200000U)                           ///< bit 21
#define NVIC_IABR_ACTIVE_22             (0x00400000U)                           ///< bit 22
#define NVIC_IABR_ACTIVE_23             (0x00800000U)                           ///< bit 23
#define NVIC_IABR_ACTIVE_24             (0x01000000U)                           ///< bit 24
#define NVIC_IABR_ACTIVE_25             (0x02000000U)                           ///< bit 25
#define NVIC_IABR_ACTIVE_26             (0x04000000U)                           ///< bit 26
#define NVIC_IABR_ACTIVE_27             (0x08000000U)                           ///< bit 27
#define NVIC_IABR_ACTIVE_28             (0x10000000U)                           ///< bit 28
#define NVIC_IABR_ACTIVE_29             (0x20000000U)                           ///< bit 29
#define NVIC_IABR_ACTIVE_30             (0x40000000U)                           ///< bit 30
#define NVIC_IABR_ACTIVE_31             (0x80000000U)                           ///< bit 31

////////////////////////////////////////////////////////////////////////////////
/// @brief NVIC_PRI0 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define NVIC_IPR0_PRI_0                 (0x000000FFU)                           ///< Priority of interrupt 0
#define NVIC_IPR0_PRI_1                 (0x0000FF00U)                           ///< Priority of interrupt 1
#define NVIC_IPR0_PRI_2                 (0x00FF0000U)                           ///< Priority of interrupt 2
#define NVIC_IPR0_PRI_3                 (0xFF000000U)                           ///< Priority of interrupt 3

////////////////////////////////////////////////////////////////////////////////
/// @brief NVIC_PRI1 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define NVIC_IPR1_PRI_4                 (0x000000FFU)                           ///< Priority of interrupt 4
#define NVIC_IPR1_PRI_5                 (0x0000FF00U)                           ///< Priority of interrupt 5
#define NVIC_IPR1_PRI_6                 (0x00FF0000U)                           ///< Priority of interrupt 6
#define NVIC_IPR1_PRI_7                 (0xFF000000U)                           ///< Priority of interrupt 7

////////////////////////////////////////////////////////////////////////////////
/// @brief NVIC_PRI2 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define NVIC_IPR2_PRI_8                 (0x000000FFU)                           ///< Priority of interrupt 8
#define NVIC_IPR2_PRI_9                 (0x0000FF00U)                           ///< Priority of interrupt 9
#define NVIC_IPR2_PRI_10                (0x00FF0000U)                           ///< Priority of interrupt 10
#define NVIC_IPR2_PRI_11                (0xFF000000U)                           ///< Priority of interrupt 11

////////////////////////////////////////////////////////////////////////////////
/// @brief NVIC_PRI3 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define NVIC_IPR3_PRI_12                (0x000000FFU)                           ///< Priority of interrupt 12
#define NVIC_IPR3_PRI_13                (0x0000FF00U)                           ///< Priority of interrupt 13
#define NVIC_IPR3_PRI_14                (0x00FF0000U)                           ///< Priority of interrupt 14
#define NVIC_IPR3_PRI_15                (0xFF000000U)                           ///< Priority of interrupt 15

////////////////////////////////////////////////////////////////////////////////
/// @brief NVIC_PRI4 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define NVIC_IPR4_PRI_16                (0x000000FFU)                           ///< Priority of interrupt 16
#define NVIC_IPR4_PRI_17                (0x0000FF00U)                           ///< Priority of interrupt 17
#define NVIC_IPR4_PRI_18                (0x00FF0000U)                           ///< Priority of interrupt 18
#define NVIC_IPR4_PRI_19                (0xFF000000U)                           ///< Priority of interrupt 19

////////////////////////////////////////////////////////////////////////////////
/// @brief NVIC_PRI5 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define NVIC_IPR5_PRI_20                (0x000000FFU)                           ///< Priority of interrupt 20
#define NVIC_IPR5_PRI_21                (0x0000FF00U)                           ///< Priority of interrupt 21
#define NVIC_IPR5_PRI_22                (0x00FF0000U)                           ///< Priority of interrupt 22
#define NVIC_IPR5_PRI_23                (0xFF000000U)                           ///< Priority of interrupt 23

////////////////////////////////////////////////////////////////////////////////
/// @brief NVIC_PRI6 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define NVIC_IPR6_PRI_24                (0x000000FFU)                           ///< Priority of interrupt 24
#define NVIC_IPR6_PRI_25                (0x0000FF00U)                           ///< Priority of interrupt 25
#define NVIC_IPR6_PRI_26                (0x00FF0000U)                           ///< Priority of interrupt 26
#define NVIC_IPR6_PRI_27                (0xFF000000U)                           ///< Priority of interrupt 27

////////////////////////////////////////////////////////////////////////////////
/// @brief NVIC_PRI7 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define NVIC_IPR7_PRI_28                (0x000000FFU)                           ///< Priority of interrupt 28
#define NVIC_IPR7_PRI_29                (0x0000FF00U)                           ///< Priority of interrupt 29
#define NVIC_IPR7_PRI_30                (0x00FF0000U)                           ///< Priority of interrupt 30
#define NVIC_IPR7_PRI_31                (0xFF000000U)                           ///< Priority of interrupt 31

////////////////////////////////////////////////////////////////////////////////
/// @brief NVIC_PRI8 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define NVIC_IPR7_PRI_32                (0x000000FFU)                           ///< Priority of interrupt 32
#define NVIC_IPR7_PRI_33                (0x0000FF00U)                           ///< Priority of interrupt 33
#define NVIC_IPR7_PRI_34                (0x00FF0000U)                           ///< Priority of interrupt 34
#define NVIC_IPR7_PRI_35                (0xFF000000U)                           ///< Priority of interrupt 35

////////////////////////////////////////////////////////////////////////////////
/// @brief NVIC_PRI9 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define NVIC_IPR7_PRI_36                (0x000000FFU)                           ///< Priority of interrupt 36
#define NVIC_IPR7_PRI_37                (0x0000FF00U)                           ///< Priority of interrupt 37
#define NVIC_IPR7_PRI_38                (0x00FF0000U)                           ///< Priority of interrupt 38
#define NVIC_IPR7_PRI_39                (0xFF000000U)                           ///< Priority of interrupt 39

////////////////////////////////////////////////////////////////////////////////
/// @brief NVIC_PRI10 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define NVIC_IPR7_PRI_40                (0x000000FFU)                           ///< Priority of interrupt 40
#define NVIC_IPR7_PRI_41                (0x0000FF00U)                           ///< Priority of interrupt 41
#define NVIC_IPR7_PRI_42                (0x00FF0000U)                           ///< Priority of interrupt 42
#define NVIC_IPR7_PRI_43                (0xFF000000U)                           ///< Priority of interrupt 43

////////////////////////////////////////////////////////////////////////////////
/// @brief NVIC_PRI11 Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define NVIC_IPR7_PRI_44                (0x000000FFU)                           ///< Priority of interrupt 44
#define NVIC_IPR7_PRI_45                (0x0000FF00U)                           ///< Priority of interrupt 45
#define NVIC_IPR7_PRI_46                (0x00FF0000U)                           ///< Priority of interrupt 46
#define NVIC_IPR7_PRI_47                (0xFF000000U)                           ///< Priority of interrupt 47

////////////////////////////////////////////////////////////////////////////////
/// @brief SCB_CPUID Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SCB_CPUID_REVISION              (0x0000000FU)                           ///< Implementation defined revision number
#define SCB_CPUID_PARTNO                (0x0000FFF0U)                           ///< Number of processor within family
#define SCB_CPUID_Constant              (0x000F0000U)                           ///< Reads as 0x0F
#define SCB_CPUID_VARIANT               (0x00F00000U)                           ///< Implementation defined variant number
#define SCB_CPUID_IMPLEMENTER           (0xFF000000U)                           ///< Implementer code. ARM is 0x41

////////////////////////////////////////////////////////////////////////////////
/// @brief SCB_ICSR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SCB_ICSR_VECTACTIVE             (0x000001FFU)                           ///< Active ISR number field
#define SCB_ICSR_RETTOBASE              (0x00000800U)                           ///< All active exceptions minus the IPSR_current_exception yields the empty set
#define SCB_ICSR_VECTPENDING            (0x003FF000U)                           ///< Pending ISR number field
#define SCB_ICSR_ISRPENDING             (0x00400000U)                           ///< Interrupt pending flag
#define SCB_ICSR_ISRPREEMPT             (0x00800000U)                           ///< It indicates that a pending interrupt becomes active in the next running cycle
#define SCB_ICSR_PENDSTCLR              (0x02000000U)                           ///< Clear pending SysTick bit
#define SCB_ICSR_PENDSTSET              (0x04000000U)                           ///< Set pending SysTick bit
#define SCB_ICSR_PENDSVCLR              (0x08000000U)                           ///< Clear pending pendSV bit
#define SCB_ICSR_PENDSVSET              (0x10000000U)                           ///< Set pending pendSV bit
#define SCB_ICSR_NMIPENDSET             (0x80000000U)                           ///< Set pending NMI bit

////////////////////////////////////////////////////////////////////////////////
/// @brief SCB_VTOR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SCB_VTOR_TBLOFF                 (0x1FFFFF80U)                           ///< Vector table base offset field
#define SCB_VTOR_TBLBASE                (0x20000000U)                           ///< Table base in code(0) or RAM(1)

////////////////////////////////////////////////////////////////////////////////
/// @brief SCB_AIRCR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SCB_AIRCR_VECTRESET             (0x00000001U)                           ///< System Reset bit
#define SCB_AIRCR_VECTCLRACTIVE         (0x00000002U)                           ///< Clear active vector bit
#define SCB_AIRCR_SYSRESETREQ           (0x00000004U)                           ///< Requests chip control logic to generate a reset
#define SCB_AIRCR_PRIGROUP              (0x00000700U)                           ///< PRIGROUP[2:0] bits (Priority group)
#define SCB_AIRCR_PRIGROUP_0            (0x00000100U)                           ///< Bit 0
#define SCB_AIRCR_PRIGROUP_1            (0x00000200U)                           ///< Bit 1
#define SCB_AIRCR_PRIGROUP_2            (0x00000400U)                           ///< Bit 2

#define SCB_AIRCR_PRIGROUP0             (0x00000000U)                           ///< Priority group=0 (7 bits of pre-emption priority, 1 bit of subpriority)
#define SCB_AIRCR_PRIGROUP1             (0x00000100U)                           ///< Priority group=1 (6 bits of pre-emption priority, 2 bits of subpriority)
#define SCB_AIRCR_PRIGROUP2             (0x00000200U)                           ///< Priority group=2 (5 bits of pre-emption priority, 3 bits of subpriority)
#define SCB_AIRCR_PRIGROUP3             (0x00000300U)                           ///< Priority group=3 (4 bits of pre-emption priority, 4 bits of subpriority)
#define SCB_AIRCR_PRIGROUP4             (0x00000400U)                           ///< Priority group=4 (3 bits of pre-emption priority, 5 bits of subpriority)
#define SCB_AIRCR_PRIGROUP5             (0x00000500U)                           ///< Priority group=5 (2 bits of pre-emption priority, 6 bits of subpriority)
#define SCB_AIRCR_PRIGROUP6             (0x00000600U)                           ///< Priority group=6 (1 bit of pre-emption priority, 7 bits of subpriority)
#define SCB_AIRCR_PRIGROUP7             (0x00000700U)                           ///< Priority group=7 (no pre-emption priority, 8 bits of subpriority)

#define SCB_AIRCR_ENDIANESS             (0x00008000U)                           ///< Data endianness bit
#define SCB_AIRCR_VECTKEY               (0xFFFF0000U)                           ///< Register key (VECTKEY) - Reads as 0xFA05 (VECTKEYSTAT)

////////////////////////////////////////////////////////////////////////////////
/// @brief SCB_SCR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SCB_SCR_SLEEPONEXIT             (0x02U)                                 ///< Sleep on exit bit
#define SCB_SCR_SLEEPDEEP               (0x04U)                                 ///< Sleep deep bit
#define SCB_SCR_SEVONPEND               (0x10U)                                 ///< Wake up from WFE

////////////////////////////////////////////////////////////////////////////////
/// @brief SCB_CCR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SCB_CCR_NONBASETHRDENA          (0x0001U)                               ///< Thread mode can be entered from any level in Handler mode by controlled return value
#define SCB_CCR_USERSETMPEND            (0x0002U)                               ///< Enables user code to write the Software Trigger Interrupt register to trigger (pend) a Main exception
#define SCB_CCR_UNALIGN_TRP             (0x0008U)                               ///< Trap for unaligned access
#define SCB_CCR_DIV_0_TRP               (0x0010U)                               ///< Trap on Divide by 0
#define SCB_CCR_BFHFNMIGN               (0x0100U)                               ///< Handlers running at priority -1 and -2
#define SCB_CCR_STKALIGN                (0x0200U)                               ///< On exception entry, the SP used prior to the exception is adjusted to be 8-byte aligned

////////////////////////////////////////////////////////////////////////////////
/// @brief SCB_SHPR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SCB_SHPR_PRI_N                  (0x000000FFU)                           ///< Priority of system handler 4,8, and 12. Mem Manage, reserved and Debug Monitor
#define SCB_SHPR_PRI_N1                 (0x0000FF00U)                           ///< Priority of system handler 5,9, and 13. Bus Fault, reserved and reserved
#define SCB_SHPR_PRI_N2                 (0x00FF0000U)                           ///< Priority of system handler 6,10, and 14. Usage Fault, reserved and PendSV
#define SCB_SHPR_PRI_N3                 (0xFF000000U)                           ///< Priority of system handler 7,11, and 15. Reserved, SVCall and SysTick

////////////////////////////////////////////////////////////////////////////////
/// @brief SCB_SHCSR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SCB_SHCSR_MEMFAULTACT           (0x00000001U)                           ///< MemManage is active
#define SCB_SHCSR_BUSFAULTACT           (0x00000002U)                           ///< BusFault is active
#define SCB_SHCSR_USGFAULTACT           (0x00000008U)                           ///< UsageFault is active
#define SCB_SHCSR_SVCALLACT             (0x00000080U)                           ///< SVCall is active
#define SCB_SHCSR_MONITORACT            (0x00000100U)                           ///< Monitor is active
#define SCB_SHCSR_PENDSVACT             (0x00000400U)                           ///< PendSV is active
#define SCB_SHCSR_SYSTICKACT            (0x00000800U)                           ///< SysTick is active
#define SCB_SHCSR_USGFAULTPENDED        (0x00001000U)                           ///< Usage Fault is pended
#define SCB_SHCSR_MEMFAULTPENDED        (0x00002000U)                           ///< MemManage is pended
#define SCB_SHCSR_BUSFAULTPENDED        (0x00004000U)                           ///< Bus Fault is pended
#define SCB_SHCSR_SVCALLPENDED          (0x00008000U)                           ///< SVCall is pended
#define SCB_SHCSR_MEMFAULTENA           (0x00010000U)                           ///< MemManage enable
#define SCB_SHCSR_BUSFAULTENA           (0x00020000U)                           ///< Bus Fault enable
#define SCB_SHCSR_USGFAULTENA           (0x00040000U)                           ///< UsageFault enable

////////////////////////////////////////////////////////////////////////////////
/// @brief SCB_CFSR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
///< MFSR
#define SCB_CFSR_IACCVIOL               (0x00000001U)                           ///< Instruction access violation
#define SCB_CFSR_DACCVIOL               (0x00000002U)                           ///< Data access violation
#define SCB_CFSR_MUNSTKERR              (0x00000008U)                           ///< Unstacking error
#define SCB_CFSR_MSTKERR                (0x00000010U)                           ///< Stacking error
#define SCB_CFSR_MMARVALID              (0x00000080U)                           ///< Memory Manage Address Register address valid flag
///< BFSR
#define SCB_CFSR_IBUSERR                (0x00000100U)                           ///< Instruction bus error flag
#define SCB_CFSR_PRECISERR              (0x00000200U)                           ///< Precise data bus error
#define SCB_CFSR_IMPRECISERR            (0x00000400U)                           ///< Imprecise data bus error
#define SCB_CFSR_UNSTKERR               (0x00000800U)                           ///< Unstacking error
#define SCB_CFSR_STKERR                 (0x00001000U)                           ///< Stacking error
#define SCB_CFSR_BFARVALID              (0x00008000U)                           ///< Bus Fault Address Register address valid flag
///< UFSR
#define SCB_CFSR_UNDEFINSTR             (0x00010000U)                           ///< The processor attempt to excecute an undefined instruction
#define SCB_CFSR_INVSTATE               (0x00020000U)                           ///< Invalid combination of EPSR and instruction
#define SCB_CFSR_INVPC                  (0x00040000U)                           ///< Attempt to load EXC_RETURN into pc illegally
#define SCB_CFSR_NOCP                   (0x00080000U)                           ///< Attempt to use a coprocessor instruction
#define SCB_CFSR_UNALIGNED              (0x01000000U)                           ///< Fault occurs when there is an attempt to make an unaligned memory access
#define SCB_CFSR_DIVBYZERO              (0x02000000U)                           ///< Fault occurs when SDIV or DIV instruction is used with a divisor of 0

////////////////////////////////////////////////////////////////////////////////
/// @brief SCB_HFSR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SCB_HFSR_VECTTBL                (0x00000002U)                           ///< Fault occures because of vector table read on exception processing
#define SCB_HFSR_FORCED                 (0x40000000U)                           ///< Hard Fault activated when a configurable Fault was received and cannot activate
#define SCB_HFSR_DEBUGEVT               (0x80000000U)                           ///< Fault related to debug

////////////////////////////////////////////////////////////////////////////////
/// @brief SCB_DFSR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SCB_DFSR_HALTED                 (0x01U)                                 ///< Halt request flag
#define SCB_DFSR_BKPT                   (0x02U)                                 ///< BKPT flag
#define SCB_DFSR_DWTTRAP                (0x04U)                                 ///< Data Watchpoint and Trace (DWT) flag
#define SCB_DFSR_VCATCH                 (0x08U)                                 ///< Vector catch flag
#define SCB_DFSR_EXTERNAL               (0x10U)                                 ///< External debug request flag

////////////////////////////////////////////////////////////////////////////////
/// @brief SCB_MMFAR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SCB_MMFAR_ADDRESS               (0xFFFFFFFFU)                           ///< Mem Manage fault address field

////////////////////////////////////////////////////////////////////////////////
/// @brief SCB_BFAR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SCB_BFAR_ADDRESS                (0xFFFFFFFFU)                           ///< Bus fault address field

////////////////////////////////////////////////////////////////////////////////
/// @brief SCB_AFSR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define SCB_AFSR_IMPDEF                 (0xFFFFFFFFU)                           ///< Implementation defined



#endif
/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
