////////////////////////////////////////////////////////////////////////////////
/// @file     hal_div.h
/// @author   AE TEAM
/// @brief    THIS FILE CONTAINS ALL THE FUNCTIONS PROTOTYPES FOR THE DIV
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
#ifndef __HAL_DIV_H
#define __HAL_DIV_H

// Files includes
#include "types.h"
#include "reg_common.h"
#include "reg_div.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup DIV_HAL
/// @brief DIV HAL modules
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup DIV_Exported_Types
/// @{


////////////////////////////////////////////////////////////////////////////////
/// @defgroup CRS_Exported_Constants
/// @{

#define SET_HWDivider(x, y)     DIV->DVDR = x;   DIV->DVSR = y;
#define GET_HWDivider(void)     DIV->QUOTR;
#define GET_Divider(dvd, dvs)   (dvd / dvs)

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup DIV_Exported_Variables
/// @{

#ifdef _HAL_DIV_C_

#define GLOBAL
#else
#define GLOBAL extern
#endif

#undef GLOBAL

/// @}


void HWDivider_Init(bool usign, bool zero);

u32 Divider_Calc(u32 dvd, u32 dvs);
s32 HWDivider_Calc(u32 dvd, u32 dvs);

// HWDivider_Init


/// @}

/// @}

/// @}


////////////////////////////////////////////////////////////////////////////////
#endif // __HAL_DIV_H
////////////////////////////////////////////////////////////////////////////////
