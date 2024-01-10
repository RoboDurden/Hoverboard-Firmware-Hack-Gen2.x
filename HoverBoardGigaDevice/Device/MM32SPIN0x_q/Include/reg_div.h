////////////////////////////////////////////////////////////////////////////////
/// @file     reg_div.h
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

#ifndef __REG_DIV_H
#define __REG_DIV_H

// Files includes

#include <stdint.h>
#include <stdbool.h>
#include "types.h"




#if defined ( __CC_ARM )
#pragma anon_unions
#endif








////////////////////////////////////////////////////////////////////////////////
/// @brief DIV Base Address Definition
////////////////////////////////////////////////////////////////////////////////
#define DIV_BASE                        (0x40030000UL + 0x0000)              ///< Base Address: 0x40030000



////////////////////////////////////////////////////////////////////////////////
/// @brief DIV Register Structure Definition
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    union {
        __IO u32 DVD;                                                               ///< Divider data register,                         offset: 0x00
        __IO u32 DVDR;
    };
    union {
        __IO u32 DVS;                                                               ///< Divisor register,                              offset: 0x04
        __IO u32 DVSR;
    };
    union {
        __IO u32 QUOT;                                                              ///< Quotient register,                             offset: 0x08
        __IO u32 QUOTR;
    };
    union {
        __IO u32 RMD;                                                               ///< Remainder register,                            offset: 0x0C
        __IO u32 RMDR;
    };
    union {
        __IO u32 STATUS;                                                            ///< Status register,                               offset: 0x10
        __IO u32 SR;
    };
    union {
        __IO u32 DIVCON;                                                            ///< Control register,                              offset: 0x14
        __IO u32 CR;
    };
} DIVIDER_TypeDef, DIV_TypeDef;




////////////////////////////////////////////////////////////////////////////////
/// @brief HWDIV type pointer Definition
////////////////////////////////////////////////////////////////////////////////
#define HWDIV                       ((DIVIDER_TypeDef*) DIV_BASE)
#define DIV                         ((DIV_TypeDef*) DIV_BASE)



////////////////////////////////////////////////////////////////////////////////
/// @brief HWDIV_DVDR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define  DIV_DVDR_DIVIDEND_Pos      (0)
#define  DIV_DVDR_DIVIDEND          (0xFFFFU << DIV_DVDR_DIVIDEND_Pos)      ///< Dividend data register

////////////////////////////////////////////////////////////////////////////////
/// @brief HWDIV_DVSR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define  DIV_DVSR_DIVISOR_Pos       (0)
#define  DIV_DVSR_DIVISOR           (0xFFFFU << DIV_DVSR_DIVISOR_Pos)       ///< Divisor data register

////////////////////////////////////////////////////////////////////////////////
/// @brief HWDIV_QUOTR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define  DIV_QUOTR_QUOTIENT_Pos     (0)
#define  DIV_QUOTR_QUOTIENT         (0xFFFFU << DIV_QUOTR_QUOTIENT_Pos)     ///< Quotient data register

////////////////////////////////////////////////////////////////////////////////
/// @brief HWDIV_RMDR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define  DIV_RMDR_REMAINDER_Pos     (0)
#define  DIV_RMDR_REMAINDER         (0xFFFFU << DIV_RMDR_REMAINDER_Pos)     ///< Remainder data register

////////////////////////////////////////////////////////////////////////////////
/// @brief HWDIV_SR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define  DIV_SR_OVF_Pos             (0)
#define  DIV_SR_OVF                 (0x01U << DIV_SR_OVF_Pos)               ///< Overflow state bit

////////////////////////////////////////////////////////////////////////////////
/// @brief HWDIV_CR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define  DIV_CR_USIGN_Pos           (0)
#define  DIV_CR_USIGN               (0x01U << DIV_CR_USIGN_Pos)             ///< Unsigned enable
#define  DIV_CR_OVFE_Pos            (1)
#define  DIV_CR_OVFE                (0x01U << DIV_CR_OVFE_Pos)              ///< Overflow interruput enable





/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
