////////////////////////////////////////////////////////////////////////////////
/// @file     reg_pwr.h
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

#ifndef __REG_PWR_H
#define __REG_PWR_H

// Files includes

#include <stdint.h>
#include <stdbool.h>
#include "types.h"




#if defined ( __CC_ARM )
#pragma anon_unions
#endif








////////////////////////////////////////////////////////////////////////////////
/// @brief PWR Base Address Definition
////////////////////////////////////////////////////////////////////////////////
#define PWR_BASE                        (0x40000000UL + 0x7000)              ///< Base Address: 0x40007000





////////////////////////////////////////////////////////////////////////////////
/// @brief PWR Register Structure Definition
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    __IO u32 CR;                                                                ///< Control register                               offset: 0x00
    __IO u32 CSR;                                                               ///< Control Status register                        offset: 0x04
} PWR_TypeDef;


////////////////////////////////////////////////////////////////////////////////
/// @brief PWR type pointer Definition
////////////////////////////////////////////////////////////////////////////////
#define PWR                             ((PWR_TypeDef*) PWR_BASE)



////////////////////////////////////////////////////////////////////////////////
/// @brief PWR_CR register Bit definition
////////////////////////////////////////////////////////////////////////////////

#define PWR_CR_PDDS_Pos                 (1)
#define PWR_CR_PDDS                     (0x01U  << PWR_CR_PDDS_Pos)             ///< Power Down Deepsleep
#define PWR_CR_CWUF_Pos                 (2)
#define PWR_CR_CWUF                     (0x01U  << PWR_CR_CWUF_Pos)             ///< Clear Standby Flag
#define PWR_CR_CSBF_Pos                 (3)
#define PWR_CR_CSBF                     (0x01U  << PWR_CR_CSBF_Pos)             ///< Clear Standby Flag
#define PWR_CR_PVDE_Pos                 (4)
#define PWR_CR_PVDE                     (0x01U  << PWR_CR_PVDE_Pos)             ///< Power Voltage Detector Enable


#define PWR_CR_PLS_Pos                  (9)
#define PWR_CR_PLS                      (0x0FU  << PWR_CR_PLS_Pos)
#define PWR_CR_PLS_1V8                  (0x00U  << PWR_CR_PLS_Pos)              ///< PVD level 1.8V
#define PWR_CR_PLS_2V1                  (0x01U  << PWR_CR_PLS_Pos)              ///< PVD level 2.1V
#define PWR_CR_PLS_2V4                  (0x02U  << PWR_CR_PLS_Pos)              ///< PVD level 2.4V
#define PWR_CR_PLS_2V7                  (0x03U  << PWR_CR_PLS_Pos)              ///< PVD level 2.7V
#define PWR_CR_PLS_3V0                  (0x04U  << PWR_CR_PLS_Pos)              ///< PVD level 3.0V
#define PWR_CR_PLS_3V3                  (0x05U  << PWR_CR_PLS_Pos)              ///< PVD level 3.3V
#define PWR_CR_PLS_3V6                  (0x06U  << PWR_CR_PLS_Pos)              ///< PVD level 3.6V
#define PWR_CR_PLS_3V9                  (0x07U  << PWR_CR_PLS_Pos)              ///< PVD level 3.9V
#define PWR_CR_PLS_4V2                  (0x08U  << PWR_CR_PLS_Pos)              ///< PVD level 4.2V
#define PWR_CR_PLS_4V5                  (0x09U  << PWR_CR_PLS_Pos)              ///< PVD level 4.5V
#define PWR_CR_PLS_4V8                  (0x0AU  << PWR_CR_PLS_Pos)              ///< PVD level 4.8V


////////////////////////////////////////////////////////////////////////////////
/// @brief PWR_CSR register Bit definition
////////////////////////////////////////////////////////////////////////////////
#define PWR_CSR_WUF_Pos                 (0)
#define PWR_CSR_WUF                     (0x01U  << PWR_CSR_WUF_Pos)             ///< Wakeup Flag
#define PWR_CSR_SBF_Pos                 (1)
#define PWR_CSR_SBF                     (0x01U  << PWR_CSR_SBF_Pos)             ///< Standby Flag
#define PWR_CSR_PVDO_Pos                (2)
#define PWR_CSR_PVDO                    (0x01U  << PWR_CSR_PVDO_Pos)            ///< PVD Output
#define PWR_CSR_EWU_Pos                 (8)
#define PWR_CSR_EWUP                    (0x01U  << PWR_CSR_EWU_Pos)             ///< Enable WKUP pin





/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
