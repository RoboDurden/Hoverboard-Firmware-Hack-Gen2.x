////////////////////////////////////////////////////////////////////////////////
/// @file     hal_misc.c
/// @author   AE TEAM
/// @brief    THIS FILE PROVIDES ALL THE MSIC FIRMWARE FUNCTIONS.
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
#define _HAL_MISC_C_

// Files includes
#include "hal_misc.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MSIC_HAL
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MISC_Exported_Functions
/// @{


////////////////////////////////////////////////////////////////////////////////
/// @brief  NVIC initialization.
/// @param  init_struct
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void NVIC_Init(NVIC_InitTypeDef* init_struct)
{

    if (init_struct->NVIC_IRQChannelCmd != DISABLE) {
        NVIC->IP[init_struct->NVIC_IRQChannel >> 0x02] =
            (NVIC->IP[init_struct->NVIC_IRQChannel >> 0x02] &
             (~(((u32)0xFF) << ((init_struct->NVIC_IRQChannel & 0x03) * 8)))) |
            ((((u32)init_struct->NVIC_IRQChannelPriority << 6) & 0xFF) << ((init_struct->NVIC_IRQChannel & 0x03) * 8));

        NVIC->ISER[0] = 0x01 << (init_struct->NVIC_IRQChannel & 0x1F);
    }
    else {
        NVIC->ICER[0] = 0x01 << (init_struct->NVIC_IRQChannel & 0x1F);
    }
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  NVIC initialized extension function.
/// @param  init_struct
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void exNVIC_Init(exNVIC_Init_TypeDef* init_struct)
{

    if (init_struct->NVIC_IRQChannelCmd != DISABLE) {
        NVIC->IP[init_struct->NVIC_IRQChannel >> 0x02] =
            (NVIC->IP[init_struct->NVIC_IRQChannel >> 0x02] &
             (~(((u32)0xFF) << ((init_struct->NVIC_IRQChannel & 0x03) * 8)))) |
            //           ((((u32)init_struct->NVIC_IRQChannelPriority << 6)
            //& 0xFF)
            ((((u32)init_struct->NVIC_IRQChannelSubPriority << 6) & 0xFF) << ((init_struct->NVIC_IRQChannel & 0x03) * 8));

        NVIC->ISER[0] = 0x01 << (init_struct->NVIC_IRQChannel & 0x1F);
    }
    else {
        NVIC->ICER[0] = 0x01 << (init_struct->NVIC_IRQChannel & 0x1F);
    }
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  System low power mode configuration.
/// @param  low_power_mode
///         This parameter can be any combination of the following values:
///    @arg NVIC_LP_SEVONPEND
///    @arg NVIC_LP_SLEEPDEEP
///    @arg NVIC_LP_SLEEPONEXIT
/// @param  state: new state of the low power mode.
///         This parameter can be: ENABLE or DISABLE.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void NVIC_SystemLPConfig(u8 low_power_mode, FunctionalState state)
{
    (state) ? (SCB->SCR |= low_power_mode) : (SCB->SCR &= ~(u32)low_power_mode);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  SysTick clock source configuration.
/// @param  systick_clk_source
///         This parameter can be any combination of the following values:
///    @arg SysTick_CLKSource_EXTCLK
///    @arg SysTick_CLKSource_HCLK
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void SysTick_CLKSourceConfig(u32 systick_clk_source)
{
    (systick_clk_source == SysTick_CLKSource_HCLK) ? (SysTick->CTRL |= SysTick_CLKSource_HCLK) \
    : (SysTick->CTRL &= ~SysTick_CLKSource_HCLK);
}

/// @}

/// @}

/// @}
