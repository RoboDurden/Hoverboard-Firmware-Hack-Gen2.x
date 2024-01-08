////////////////////////////////////////////////////////////////////////////////
/// @file     reg_adc.h
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

#ifndef __REG_ADC_H
#define __REG_ADC_H

// Files includes

#include <stdint.h>
#include <stdbool.h>
#include "types.h"




#if defined ( __CC_ARM )
#pragma anon_unions
#endif






////////////////////////////////////////////////////////////////////////////////
/// @brief ADC Base Address Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC1_BASE                       (0x40010000UL + 0x2400)              ///< Base Address: 0x40012400





////////////////////////////////////////////////////////////////////////////////
/// @brief Analog-to-Digital Converter register
////////////////////////////////////////////////////////////////////////////////
#define USENCOMBINEREGISTER
#ifdef USENCOMBINEREGISTER

typedef struct {
    union {
        __IO u32 DR;                                                                ///< ADC data register,                             offset: 0x00
        __IO u32 ADDATA;
    };
    union {
        __IO u32 CFGR;                                                              ///< ADC configuration register,                    offset: 0x04
        __IO u32 ADCFG;
    };
    union {
        __IO u32 CR;                                                                ///< ADC control register,                          offset: 0x08
        __IO u32 ADCR;
    };
    union {
        __IO u32 CHSR;                                                              ///< ADC channel selection register,                offset: 0x0C
        __IO u32 ADCHS;
    };
    union {
        __IO u32 CMPR;                                                              ///< ADC window compare register,                   offset: 0x10
        __IO u32 ADCMPR;
    };
    union {
        __IO u32 SR;                                                                ///< ADC status register,                           offset: 0x14
        __IO u32 ADSTA;
    };
    union {
        __IO u32 CH0DR;                                                             ///< ADC channel0 data register,                    offset: 0x18
        __IO u32 ADDR0;
    };
    union {
        __IO u32 CH1DR;                                                             ///< ADC channel1 data register,                    offset: 0x1C
        __IO u32 ADDR1;
    };
    union {
        __IO u32 CH2DR;                                                             ///< ADC channel2 data register,                    offset: 0x20
        __IO u32 ADDR2;
    };
    union {
        __IO u32 CH3DR;                                                             ///< ADC channel3 data register,                    offset: 0x24
        __IO u32 ADDR3;
    };
    union {
        __IO u32 CH4DR;                                                             ///< ADC channel4 data register,                    offset: 0x28
        __IO u32 ADDR4;
    };
    union {
        __IO u32 CH5DR;                                                             ///< ADC channel5 data register,                    offset: 0x2C
        __IO u32 ADDR5;
    };
    union {
        __IO u32 CH6DR;                                                             ///< ADC channel6 data register,                    offset: 0x30
        __IO u32 ADDR6;
    };
    union {
        __IO u32 CH7DR;                                                             ///< ADC channel7 data register,                    offset: 0x34
        __IO u32 ADDR7;
    };
    union {
        __IO u32 CH8DR;                                                             ///< ADC channel8 data register,                    offset: 0x38
        __IO u32 ADDR8;
    };
    union {
        __IO u32 CH9DR;                                                         ///< ADC channel9 data register,                    offset: 0x3C
        __IO u32 ADDR9;
    };
    union {
        __IO u32 CH10DR;                                                        ///< ADC channel10 data register,                   offset: 0x40
        __IO u32 ADDR10;
    };
    union {
        __IO u32 CH11DR;                                                        ///< ADC channel11 data register,                   offset: 0x44
        __IO u32 ADDR11;
    };
    __IO u32 RESERVED0;                                                         ///<                                                offset: 0x48
    union {
        __IO u32 CH13DR;                                                        ///< ADC channel13 data register,                   offset: 0x4C
        __IO u32 ADDR13;
    };
    union {
        __IO u32 CH14DR;                                                        ///< ADC channel14 data register,                   offset: 0x50
        __IO u32 ADDR14;
    };
    union {
        __IO u32 CH15DR;                                                        ///< ADC channel15 data register,                   offset: 0x54
        __IO u32 ADDR15;
    };
    __IO u32 SREXT;                                                             ///< ADC Extended Status Register,                  offset: 0x58
} ADC_TypeDef;

#endif
#ifdef USENNEWREGISTER
////////////////////////////////////////////////////////////////////////////////
/// @brief Analog-to-Digital Converter register
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    __IO u32 DR;                                                                ///< ADC data register,                             offset: 0x00
    __IO u32 CFGR;                                                              ///< ADC configuration register,                    offset: 0x04
    __IO u32 CR;                                                                ///< ADC control register,                          offset: 0x08
    __IO u32 CHSR;                                                              ///< ADC channel selection register,                offset: 0x0C
    __IO u32 CMPR;                                                              ///< ADC window compare register,                   offset: 0x10
    __IO u32 SR;                                                                ///< ADC status register,                           offset: 0x14
    __IO u32 CH0DR;                                                             ///< ADC channel0 data register,                    offset: 0x18
    __IO u32 CH1DR;                                                             ///< ADC channel1 data register,                    offset: 0x1C
    __IO u32 CH2DR;                                                             ///< ADC channel2 data register,                    offset: 0x20
    __IO u32 CH3DR;                                                             ///< ADC channel3 data register,                    offset: 0x24
    __IO u32 CH4DR;                                                             ///< ADC channel4 data register,                    offset: 0x28
    __IO u32 CH5DR;                                                             ///< ADC channel5 data register,                    offset: 0x2C
    __IO u32 CH6DR;                                                             ///< ADC channel6 data register,                    offset: 0x30
    __IO u32 CH7DR;                                                             ///< ADC channel7 data register,                    offset: 0x34
    __IO u32 CH8DR;                                                             ///< ADC channel8 data register,                    offset: 0x38
    __IO u32 CH9DR;                                                             ///< ADC channel9 data register,                    offset: 0x3C
    __IO u32 CH10DR;                                                            ///< ADC channel10 data register,                   offset: 0x40
    __IO u32 CH11DR;                                                            ///< ADC channel11 data register,                   offset: 0x44
    __IO u32 RESERVED0;                                                         ///<                                                offset: 0x48
    __IO u32 CH13DR;                                                            ///< ADC channel13 data register,                   offset: 0x4C
    __IO u32 CH14DR;                                                            ///< ADC channel14 data register,                   offset: 0x50
    __IO u32 CH15DR;                                                            ///< ADC channel15 data register,                   offset: 0x54
    __IO u32 SREXT;                                                             ///< ADC Extended Status Register,                  offset: 0x58
} ADC_TypeDef;
#endif
#ifdef USENOLDREGISTER
typedef struct {
    __IO u32 ADDATA;                                                            ///< ADC data register,                             offset: 0x00
    __IO u32 ADCFG;                                                             ///< ADC configuration register,                    offset: 0x04
    __IO u32 ADCR;                                                              ///< ADC control register,                          offset: 0x08
    __IO u32 ADCHS;                                                             ///< ADC channel selection register,                offset: 0x0C
    __IO u32 ADCMPR;                                                            ///< ADC window compare register,                   offset: 0x10
    __IO u32 ADSTA;                                                             ///< ADC status register,                           offset: 0x14
    __IO u32 ADDR0;                                                             ///< ADC channel0 data register,                    offset: 0x18
    __IO u32 ADDR1;                                                             ///< ADC channel1 data register,                    offset: 0x1C
    __IO u32 ADDR2;                                                             ///< ADC channel2 data register,                    offset: 0x20
    __IO u32 ADDR3;                                                             ///< ADC channel3 data register,                    offset: 0x24
    __IO u32 ADDR4;                                                             ///< ADC channel4 data register,                    offset: 0x28
    __IO u32 ADDR5;                                                             ///< ADC channel5 data register,                    offset: 0x2C
    __IO u32 ADDR6;                                                             ///< ADC channel6 data register,                    offset: 0x30
    __IO u32 ADDR7;                                                             ///< ADC channel7 data register,                    offset: 0x34
    __IO u32 ADDR8;                                                             ///< ADC channel8 data register,                    offset: 0x38
    __IO u32 ADDR9;                                                             ///< ADC channel9 data register,                    offset: 0x3C
    __IO u32 ADDR10;                                                            ///< ADC channel10 data register,                   offset: 0x40
    __IO u32 ADDR11;                                                            ///< ADC channel11 data register,                   offset: 0x44
    __IO u32 RESERVED0;                                                         ///<                                                offset: 0x48
    __IO u32 ADDR13;                                                            ///< ADC channel13 data register,                   offset: 0x4C
    __IO u32 ADDR14;                                                            ///< ADC channel14 data register,                   offset: 0x50
    __IO u32 ADDR15;                                                            ///< ADC channel15 data register,                   offset: 0x54
    __IO u32 SREXT;                                                             ///< ADC Extended Status Register,                  offset: 0x58
} ADC_TypeDef;
#endif



////////////////////////////////////////////////////////////////////////////////
/// @brief ADC type pointer Definition
////////////////////////////////////////////////////////////////////////////////
#define ADC1                            ((ADC_TypeDef*) ADC1_BASE)


////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_DR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define  ADC_DR_DATA_Pos                (0)
#define  ADC_DR_DATA                    (0xFFFFU << ADC_DR_DATA_Pos)            ///< ADC 12bit convert data

#define  ADC_DR_CH_Pos                  (16)
#define  ADC_DR_CH                      (0x0FU <<  ADC_DR_CH_Pos)               ///< CHANNELSEL[19:16] (ADC current channel convert data)

#define  ADC_DR_CH0                     (0x00U << ADC_DR_CH_Pos)                ///< ADC Channel select  0
#define  ADC_DR_CH1                     (0x01U << ADC_DR_CH_Pos)                ///< ADC Channel select  1
#define  ADC_DR_CH2                     (0x02U << ADC_DR_CH_Pos)                ///< ADC Channel select  2
#define  ADC_DR_CH3                     (0x03U << ADC_DR_CH_Pos)                ///< ADC Channel select  3
#define  ADC_DR_CH4                     (0x04U << ADC_DR_CH_Pos)                ///< ADC Channel select  4
#define  ADC_DR_CH5                     (0x05U << ADC_DR_CH_Pos)                ///< ADC Channel select  5
#define  ADC_DR_CH6                     (0x06U << ADC_DR_CH_Pos)                ///< ADC Channel select  6
#define  ADC_DR_CH7                     (0x07U << ADC_DR_CH_Pos)                ///< ADC Channel select  7

#define  ADC_DR_CH8                     (0x08U << ADC_DR_CH_Pos)                ///< ADC Channel select  8
#define  ADC_DR_CH9                     (0x09U << ADC_DR_CH_Pos)                ///< ADC Channel select  9
#define  ADC_DR_TempSensor              (0x0EU << ADC_DR_CH_Pos)                ///< ADC Channel select  14
#define  ADC_DR_VoltRef                 (0x0FU << ADC_DR_CH_Pos)                ///< ADC Channel select  15

#define  ADC_DR_CH10                    (0x0AU << ADC_DR_CH_Pos)                ///< ADC Channel select  10
#define  ADC_DR_CH11                    (0x0BU << ADC_DR_CH_Pos)                ///< ADC Channel select  11
#define  ADC_DR_CH13                    (0x0CU << ADC_DR_CH_Pos)                ///< ADC Channel select  13

#define  ADC_DR_OVERRUN_Pos             (20)
#define  ADC_DR_OVERRUN                 (0x01U << ADC_DR_OVERRUN_Pos)           ///< ADC data will be cover
#define  ADC_DR_VALID_Pos               (21)
#define  ADC_DR_VALID                   (0x01U << ADC_DR_VALID_Pos)             ///< ADC data[11:0] is valid

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_CFGR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define  ADC_CFGR_ADEN_Pos              (0)
#define  ADC_CFGR_ADEN                  (0x01U << ADC_CFGR_ADEN_Pos)            ///< Enable ADC convert
#define  ADC_CFGR_ADWEN_Pos             (1)
#define  ADC_CFGR_ADWEN                 (0x01U << ADC_CFGR_ADWEN_Pos)           ///< Enable ADC window compare


#define  ADC_CFGR_RSLTCTL_Pos           (7)
#define  ADC_CFGR_RSLTCTL               (0x07U << ADC_CFGR_RSLTCTL_Pos)         ///< ADC resolution select
#define  ADC_CFGR_RSLTCTL_12            (0x00U << ADC_CFGR_RSLTCTL_Pos)         ///< ADC resolution select 12bit
#define  ADC_CFGR_RSLTCTL_11            (0x01U << ADC_CFGR_RSLTCTL_Pos)         ///< ADC resolution select 11bit
#define  ADC_CFGR_RSLTCTL_10            (0x02U << ADC_CFGR_RSLTCTL_Pos)         ///< ADC resolution select 10bit
#define  ADC_CFGR_RSLTCTL_9             (0x03U << ADC_CFGR_RSLTCTL_Pos)         ///< ADC resolution select 9bit
#define  ADC_CFGR_RSLTCTL_8             (0x04U << ADC_CFGR_RSLTCTL_Pos)         ///< ADC resolution select 8bit

#define  ADC_CFGR_SAMCTL_Pos            (10)
#define  ADC_CFGR_SAMCTL                (0x0FU << ADC_CFGR_SAMCTL_Pos)          ///< ADC sample time select
#define  ADC_CFGR_SAMCTL_1_5            (0x00U << ADC_CFGR_SAMCTL_Pos)          ///< ADC sample time select 1.5t
#define  ADC_CFGR_SAMCTL_7_5            (0x01U << ADC_CFGR_SAMCTL_Pos)          ///< ADC sample time select 7.5t
#define  ADC_CFGR_SAMCTL_13_5           (0x02U << ADC_CFGR_SAMCTL_Pos)          ///< ADC sample time select 13.5t
#define  ADC_CFGR_SAMCTL_28_5           (0x03U << ADC_CFGR_SAMCTL_Pos)          ///< ADC sample time select 28.5t
#define  ADC_CFGR_SAMCTL_41_5           (0x04U << ADC_CFGR_SAMCTL_Pos)          ///< ADC sample time select 41.5t
#define  ADC_CFGR_SAMCTL_55_5           (0x05U << ADC_CFGR_SAMCTL_Pos)          ///< ADC sample time select 55.5t
#define  ADC_CFGR_SAMCTL_71_5           (0x06U << ADC_CFGR_SAMCTL_Pos)          ///< ADC sample time select 71.5t
#define  ADC_CFGR_SAMCTL_239_5          (0x07U << ADC_CFGR_SAMCTL_Pos)          ///< ADC sample time select 239.5t
#define ADC_CFGR_SAMCTL_2_5             (0x08U  << ADC_CFGR_SAMCTL_Pos)         ///< ADC sample time select 2.5t
#define ADC_CFGR_SAMCTL_3_5             (0x09U  << ADC_CFGR_SAMCTL_Pos)         ///< ADC sample time select 3.5t
#define ADC_CFGR_SAMCTL_4_5             (0x0AU  << ADC_CFGR_SAMCTL_Pos)         ///< ADC sample time select 4.5t
#define ADC_CFGR_SAMCTL_5_5             (0x0BU  << ADC_CFGR_SAMCTL_Pos)         ///< ADC sample time select 5.5t
#define ADC_CFGR_SAMCTL_6_5             (0x0CU  << ADC_CFGR_SAMCTL_Pos)         ///< ADC sample time select 6.5t

#define  ADC_CFGR_TEN_Pos           (2)
#define  ADC_CFGR_TEN               (0x01U << ADC_CFGR_TEN_Pos)                 ///< Enable ADC temperature sensor
#define  ADC_CFGR_VEN_Pos           (3)
#define  ADC_CFGR_VEN               (0x01U << ADC_CFGR_VEN_Pos)                 ///< Enable ADC voltage reference






#define ADC_CFGR_PRE_Pos            (4)
#define ADC_CFGR_PREL_Pos           (14)
#define ADC_CFGR_PRE                ((0x07U << ADC_CFGR_PRE_Pos) + (0x01U << ADC_CFGR_PREL_Pos))
#define ADC_CFGR_PRE_2              (0x00U  << ADC_CFGR_PRE_Pos)            ///< ADC preclk 2
#define ADC_CFGR_PRE_4              (0x01U  << ADC_CFGR_PRE_Pos)            ///< ADC preclk 4
#define ADC_CFGR_PRE_6              (0x02U  << ADC_CFGR_PRE_Pos)            ///< ADC preclk 6
#define ADC_CFGR_PRE_8              (0x03U  << ADC_CFGR_PRE_Pos)            ///< ADC preclk 8
#define ADC_CFGR_PRE_10             (0x04U  << ADC_CFGR_PRE_Pos)            ///< ADC preclk 10
#define ADC_CFGR_PRE_12             (0x05U  << ADC_CFGR_PRE_Pos)            ///< ADC preclk 12
#define ADC_CFGR_PRE_14             (0x06U  << ADC_CFGR_PRE_Pos)            ///< ADC preclk 14
#define ADC_CFGR_PRE_16             (0x07U  << ADC_CFGR_PRE_Pos)            ///< ADC preclk 16
#define ADC_CFGR_PRE_3              ((0x01U << ADC_CFGR_PREL_Pos) + (0x00U << ADC_CFGR_PRE_Pos))    ///< ADC preclk 3
#define ADC_CFGR_PRE_5              ((0x01U << ADC_CFGR_PREL_Pos) + (0x01U << ADC_CFGR_PRE_Pos))    ///< ADC preclk 5
#define ADC_CFGR_PRE_7              ((0x01U << ADC_CFGR_PREL_Pos) + (0x02U << ADC_CFGR_PRE_Pos))    ///< ADC preclk 7
#define ADC_CFGR_PRE_9              ((0x01U << ADC_CFGR_PREL_Pos) + (0x03U << ADC_CFGR_PRE_Pos))    ///< ADC preclk 9
#define ADC_CFGR_PRE_11             ((0x01U << ADC_CFGR_PREL_Pos) + (0x04U << ADC_CFGR_PRE_Pos))    ///< ADC preclk 11
#define ADC_CFGR_PRE_13             ((0x01U << ADC_CFGR_PREL_Pos) + (0x05U << ADC_CFGR_PRE_Pos))    ///< ADC preclk 13
#define ADC_CFGR_PRE_15             ((0x01U << ADC_CFGR_PREL_Pos) + (0x06U << ADC_CFGR_PRE_Pos))    ///< ADC preclk 15
#define ADC_CFGR_PRE_17             ((0x01U << ADC_CFGR_PREL_Pos) + (0x07U << ADC_CFGR_PRE_Pos))    ///< ADC preclk 17






////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_CR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define  ADC_CR_ADIE_Pos                (0)
#define  ADC_CR_ADIE                    (0x01U << ADC_CR_ADIE_Pos)              ///< ADC interrupt enable
#define  ADC_CR_ADWIE_Pos               (1)
#define  ADC_CR_ADWIE                   (0x01U << ADC_CR_ADWIE_Pos)             ///< ADC window compare interrupt enable
#define  ADC_CR_TRGEN_Pos               (2)
#define  ADC_CR_TRGEN                   (0x01U << ADC_CR_TRGEN_Pos)             ///< extranal trigger single start AD convert
#define  ADC_CR_DMAEN_Pos               (3)
#define  ADC_CR_DMAEN                   (0x01U << ADC_CR_DMAEN_Pos)             ///< ADC DMA enable
#define  ADC_CR_ADST_Pos                (8)
#define  ADC_CR_ADST                    (0x01U << ADC_CR_ADST_Pos)              ///< ADC start convert data
#define  ADC_CR_MODE_Pos                (9)
#define  ADC_CR_MODE                    (0x03U << ADC_CR_MODE_Pos)              ///< ADC convert mode
#define  ADC_CR_IMM                     (0x00U << ADC_CR_MODE_Pos)              ///< ADC imm convert mode
#define  ADC_CR_SCAN                    (0x01U << ADC_CR_MODE_Pos)              ///< ADC scan convert mode
#define  ADC_CR_CONTINUE                (0x02U << ADC_CR_MODE_Pos)              ///< ADC continue scan convert mode
#define  ADC_CR_ALIGN_Pos               (11)
#define  ADC_CR_ALIGN                   (0x01U << ADC_CR_ALIGN_Pos)             ///< ADC data align
#define  ADC_CR_LEFT                    (0x01U << ADC_CR_ALIGN_Pos)             ///< ADC data left align
#define  ADC_CR_RIGHT                   (0x00U << ADC_CR_ALIGN_Pos)             ///< ADC data right align
#define  ADC_CR_CMPCH_Pos               (12)
#define  ADC_CR_CMPCH                   (0x0FU << ADC_CR_CMPCH_Pos)             ///< CMPCH[15:12] ADC window compare channel0 convert data
#define  ADC_CR_CMPCH_0                 (0x00U << ADC_CR_CMPCH_Pos)             ///< Select Compare Channel 0 Conversion Results
#define  ADC_CR_CMPCH_1                 (0x01U << ADC_CR_CMPCH_Pos)             ///< Select Compare Channel 1 Conversion Results
#define  ADC_CR_CMPCH_2                 (0x02U << ADC_CR_CMPCH_Pos)             ///< Select Compare Channel 2 Conversion Results
#define  ADC_CR_CMPCH_4                 (0x04U << ADC_CR_CMPCH_Pos)             ///< Select Compare Channel 4 Conversion Results
#define  ADC_CR_CMPCH_5                 (0x05U << ADC_CR_CMPCH_Pos)             ///< Select Compare Channel 5 Conversion Results
#define  ADC_CR_CMPCH_6                 (0x06U << ADC_CR_CMPCH_Pos)             ///< Select Compare Channel 6 Conversion Results
#define  ADC_CR_CMPCH_7                 (0x07U << ADC_CR_CMPCH_Pos)             ///< Select Compare Channel 7 Conversion Results
#define  ADC_CR_CMPCH_8                 (0x08U << ADC_CR_CMPCH_Pos)             ///< Select Compare Channel 8 Conversion Results
#define  ADC_CR_CMPCH_9                 (0x09U << ADC_CR_CMPCH_Pos)             ///< Select Compare Channel 9 Conversion Results
#define  ADC_CR_CMPCH_10                (0x0AU << ADC_CR_CMPCH_Pos)             ///< Select Compare Channel 10 Conversion Results
#define  ADC_CR_CMPCH_11                (0x0BU << ADC_CR_CMPCH_Pos)             ///< Select Compare Channel 11 Conversion Results
#define  ADC_CR_CMPCH_13                (0x0DU << ADC_CR_CMPCH_Pos)             ///< Select Compare Channel 13 Conversion Results
#define  ADC_CR_CMPCH_14                (0x0EU << ADC_CR_CMPCH_Pos)             ///< Select Compare Channel 14 Conversion Results
#define  ADC_CR_CMPCH_ALL               (0x0FU << ADC_CR_CMPCH_Pos)             ///< Select Compare ALL Channel Conversion Results




#define ADC_CR_TRGSEL_H_Pos         (17)
#define ADC_CR_TRGSEL_L_Pos         (4)
#define ADC_CR_TRGSEL               ((0x03U << ADC_CR_TRGSEL_H_Pos) + (0x07U << ADC_CR_TRGSEL_L_Pos))   ///< TRGSEL[6:4][18:17] ADC external trigger source select
#define ADC_CR_T1_CC1               (0x00U << ADC_CR_TRGSEL_L_Pos)          ///< The external trigger source of the ADC is T1_CC1
#define ADC_CR_T1_CC2               (0x01U << ADC_CR_TRGSEL_L_Pos)          ///< The external trigger source of the ADC is T1_CC2
#define ADC_CR_T1_CC3               (0x02U << ADC_CR_TRGSEL_L_Pos)          ///< The external trigger source of the ADC is T1_CC3
#define ADC_CR_T2_CC2               (0x03U << ADC_CR_TRGSEL_L_Pos)          ///< The external trigger source of the ADC is T2_CC2
#define ADC_CR_T3_TRIG              (0x04U << ADC_CR_TRGSEL_L_Pos)          ///< The external trigger source of the ADC is T3_TRIG
#define ADC_CR_T1_CC4_CC5           (0x05U << ADC_CR_TRGSEL_L_Pos)          ///< The external trigger source of the ADC is T1_CC4_CC5
#define ADC_CR_T3_CC1               (0x06U << ADC_CR_TRGSEL_L_Pos)          ///< The external trigger source of the ADC is T3_CC1
#define ADC_CR_EXTI_11              (0x07U << ADC_CR_TRGSEL_L_Pos)          ///< The external trigger source of the ADC is EXTI_11
#define ADC_CR_T1_TRIG              ((0x01U << ADC_CR_TRGSEL_H_Pos) + (0x00U << ADC_CR_TRGSEL_L_Pos))   ///< The external trigger source of the ADC is T1_TRIG
#define ADC_CR_T2_CC1               ((0x01U << ADC_CR_TRGSEL_H_Pos) + (0x03U << ADC_CR_TRGSEL_L_Pos))   ///< The external trigger source of the ADC is T2_CC1
#define ADC_CR_T3_CC4               ((0x01U << ADC_CR_TRGSEL_H_Pos) + (0x04U << ADC_CR_TRGSEL_L_Pos))   ///< The external trigger source of the ADC is T3_CC4
#define ADC_CR_T2_TRIG              ((0x01U << ADC_CR_TRGSEL_H_Pos) + (0x05U << ADC_CR_TRGSEL_L_Pos))   ///< The external trigger source of the ADC is T2_TRIG
#define ADC_CR_EXTI_15              ((0x01U << ADC_CR_TRGSEL_H_Pos) + (0x07U << ADC_CR_TRGSEL_L_Pos))   ///< The external trigger source of the ADC is EXTI_15
#define ADC_CR_TIM1_CC4             ((0x02U << ADC_CR_TRGSEL_H_Pos) + (0x00U << ADC_CR_TRGSEL_L_Pos))   ///< The external trigger source of the ADC is TIM1_CC4
#define ADC_CR_TIM1_CC5             ((0x02U << ADC_CR_TRGSEL_H_Pos) + (0x01U << ADC_CR_TRGSEL_L_Pos))   ///< The external trigger source of the ADC is TIM1_CC5
#define ADC_CR_SCANDIR_Pos          (16)
#define ADC_CR_SCANDIR              (0x01U << ADC_CR_SCANDIR_Pos)           ///< ADC scan direction
#define ADC_CR_TRGSHIFT_Pos         (19)
#define ADC_CR_TRGSHIFT             (0x07U << ADC_CR_TRGSHIFT_Pos)          ///< External trigger shift sample
#define ADC_CR_TRGSHIFT_0           (0x00U << ADC_CR_TRGSHIFT_Pos)          ///< No shift
#define ADC_CR_TRGSHIFT_4           (0x01U << ADC_CR_TRGSHIFT_Pos)          ///< Shift 4 period
#define ADC_CR_TRGSHIFT_16          (0x02U << ADC_CR_TRGSHIFT_Pos)          ///< Shift 16 period
#define ADC_CR_TRGSHIFT_32          (0x03U << ADC_CR_TRGSHIFT_Pos)          ///< Shift 32 period
#define ADC_CR_TRGSHIFT_64          (0x04U << ADC_CR_TRGSHIFT_Pos)          ///< Shift 64 period
#define ADC_CR_TRGSHIFT_128         (0x05U << ADC_CR_TRGSHIFT_Pos)          ///< Shift 128 period
#define ADC_CR_TRGSHIFT_256         (0x06U << ADC_CR_TRGSHIFT_Pos)          ///< Shift 256 period
#define ADC_CR_TRGSHIFT_512         (0x07U << ADC_CR_TRGSHIFT_Pos)          ///< Shift 512 period

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_CHSR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define  ADC_CHSR_CH0_Pos               (0)
#define  ADC_CHSR_CH0                   (0x01U << ADC_CHSR_CH0_Pos)             ///< Enable ADC channel 0
#define  ADC_CHSR_CH1_Pos               (1)
#define  ADC_CHSR_CH1                   (0x01U << ADC_CHSR_CH1_Pos)             ///< Enable ADC channel 1
#define  ADC_CHSR_CH2_Pos               (2)
#define  ADC_CHSR_CH2                   (0x01U << ADC_CHSR_CH2_Pos)             ///< Enable ADC channel 2
#define  ADC_CHSR_CH3_Pos               (3)
#define  ADC_CHSR_CH3                   (0x01U << ADC_CHSR_CH3_Pos)             ///< Enable ADC channel 3
#define  ADC_CHSR_CH4_Pos               (4)
#define  ADC_CHSR_CH4                   (0x01U << ADC_CHSR_CH4_Pos)             ///< Enable ADC channel 4
#define  ADC_CHSR_CH5_Pos               (5)
#define  ADC_CHSR_CH5                   (0x01U << ADC_CHSR_CH5_Pos)             ///< Enable ADC channel 5
#define  ADC_CHSR_CH6_Pos               (6)
#define  ADC_CHSR_CH6                   (0x01U << ADC_CHSR_CH6_Pos)             ///< Enable ADC channel 6
#define  ADC_CHSR_CH7_Pos               (7)
#define  ADC_CHSR_CH7                   (0x01U << ADC_CHSR_CH7_Pos)             ///< Enable ADC channel 7


#define  ADC_CHSR_CH8_Pos           (8)
#define  ADC_CHSR_CH8               (0x01U << ADC_CHSR_CH8_Pos)             ///< Enable ADC channel 8
#define  ADC_CHSR_CH9_Pos           (9)
#define  ADC_CHSR_CH9               (0x01U << ADC_CHSR_CH9_Pos)             ///< Enable ADC channel 9
#define  ADC_CHSR_CHT_Pos           (14)
#define  ADC_CHSR_CHT               (0x01U << ADC_CHSR_CHT_Pos)             ///< Enable Temperature Sensor
#define  ADC_CHSR_CHV_Pos           (15)
#define  ADC_CHSR_CHV               (0x01U << ADC_CHSR_CHV_Pos)             ///< Enable Voltage Sensor


#define  ADC_CHSR_CH10_Pos          (10)
#define  ADC_CHSR_CH10              (0x01U << ADC_CHSR_CH10_Pos)            ///< Enable ADC channel 10
#define  ADC_CHSR_CH11_Pos          (11)
#define  ADC_CHSR_CH11              (0x01U << ADC_CHSR_CH11_Pos)            ///< Enable ADC channel 11
#define  ADC_CHSR_CHCALIB_Pos       (13)
#define  ADC_CHSR_CHCALIB           (0x01U << ADC_CHSR_CHCALIB_Pos)         ///< Enable ADC internal self-calibration channel
#define  ADC_CHSR_CHALL             (0xEFFFU)                               ///< Enable ADC all channel
////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_CMPR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define  ADC_CMPR_CMPLDATA_Pos          (0)
#define  ADC_CMPR_CMPLDATA              (0x0FFFU << ADC_CMPR_CMPLDATA_Pos)      ///< ADC 12bit window compare DOWN LEVEL DATA
#define  ADC_CMPR_CMPHDATA_Pos          (16)
#define  ADC_CMPR_CMPHDATA              (0x0FFFU << ADC_CMPR_CMPHDATA_Pos)      ///< ADC 12bit window compare UP LEVEL DATA

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_SR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define  ADC_SR_ADIF_Pos                (0)
#define  ADC_SR_ADIF                    (0x01U << ADC_SR_ADIF_Pos)              ///< ADC convert complete flag
#define  ADC_SR_ADWIF_Pos               (1)
#define  ADC_SR_ADWIF                   (0x01U << ADC_SR_ADWIF_Pos)             ///< ADC compare flag
#define  ADC_SR_BUSY_Pos                (2)
#define  ADC_SR_BUSY                    (0x01U << ADC_SR_BUSY_Pos)              ///< ADC busy flag
#define  ADC_SR_CH_Pos                  (4)
#define  ADC_SR_CH                      (0x0FU << ADC_SR_CH_Pos)                ///< CHANNEL[7:4] ADC current channel
#define  ADC_SR_CH0                     (0x00U << ADC_SR_CH_Pos)                ///< Channel 0 is the current conversion channel
#define  ADC_SR_CH1                     (0x01U << ADC_SR_CH_Pos)                ///< Channel 1 is the current conversion channel
#define  ADC_SR_CH2                     (0x02U << ADC_SR_CH_Pos)                ///< Channel 2 is the current conversion channel
#define  ADC_SR_CH3                     (0x03U << ADC_SR_CH_Pos)                ///< Channel 3 is the current conversion channel
#define  ADC_SR_CH4                     (0x04U << ADC_SR_CH_Pos)                ///< Channel 4 is the current conversion channel
#define  ADC_SR_CH5                     (0x05U << ADC_SR_CH_Pos)                ///< Channel 5 is the current conversion channel
#define  ADC_SR_CH6                     (0x06U << ADC_SR_CH_Pos)                ///< Channel 6 is the current conversion channel
#define  ADC_SR_CH7                     (0x07U << ADC_SR_CH_Pos)                ///< Channel 7 is the current conversion channel
#define  ADC_SR_CH8                     (0x08U << ADC_SR_CH_Pos)                ///< Channel 8 is the current conversion channel
#define  ADC_SR_CH9                     (0x09U << ADC_SR_CH_Pos)                ///< Channel 9 is the current conversion channel
#define  ADC_SR_CH10                    (0x0AU << ADC_SR_CH_Pos)                ///< Channel 10 is the current conversion channel
#define  ADC_SR_CH11                    (0x0BU << ADC_SR_CH_Pos)                ///< Channel 11 is the current conversion channel
#define  ADC_SR_CH13                    (0x0DU << ADC_SR_CH_Pos)                ///< Channel 13 is the current conversion channel
#define  ADC_SR_CH14                    (0x0EU << ADC_SR_CH_Pos)                ///< Channel 14 is the current conversion channel
#define  ADC_SR_CH15                    (0x0FU << ADC_SR_CH_Pos)                ///< Channel 15 is the current conversion channel


#define  ADC_SR_VALID_Pos           (8)
#define  ADC_SR_VALID               (0x0FFFU << ADC_SR_VALID_Pos)           ///< VALID[19:8] ADC channel 0..11 valid flag
#define  ADC_SR_OVERRUN_Pos         (20)
#define  ADC_SR_OVERRUN             (0x0FFFU << ADC_SR_OVERRUN_Pos)         ///< OVERRUN[31:20] ADC channel 0..11 data covered flag

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_CHnDR Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define  ADC_CHDR_DATA_Pos          (0)
#define  ADC_CHDR_DATA              (0xFFFFU << ADC_CHDR_DATA_Pos)          ///< ADC channel convert data
#define  ADC_CHDR_OVERRUN_Pos       (20)
#define  ADC_CHDR_OVERRUN           (0x01U << ADC_CHDR_OVERRUN_Pos)         ///< ADC data covered flag
#define  ADC_CHDR_VALID_Pos         (21)
#define  ADC_CHDR_VALID             (0x01U << ADC_CHDR_VALID_Pos)           ///< ADC data valid flag

////////////////////////////////////////////////////////////////////////////////
/// @brief ADC_SREXT Register Bit Definition
////////////////////////////////////////////////////////////////////////////////
#define  ADC_SREXT_VALID_Pos        (0)
#define  ADC_SREXT_VALID            (0x0FU << ADC_SREXT_VALID_Pos)          ///< VALID[3:0] ADC channel 12,14..15 valid flag
#define  ADC_SREXT_OVERRUN_Pos      (4)
#define  ADC_SREXT_OVERRUN          (0x0FU << ADC_SREXT_OVERRUN_Pos)        ///< OVERRUN[7:4] ADC channel 12,14..15 data covered flag










/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
