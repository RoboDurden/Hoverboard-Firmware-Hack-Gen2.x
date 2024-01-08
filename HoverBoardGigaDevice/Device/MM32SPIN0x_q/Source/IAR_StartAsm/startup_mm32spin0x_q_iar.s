; ////////////////////////////////////////////////////////////////////////////////
; /// @file     startup_mm32spin0xx_q_iar.s
; /// @author   AE TEAM
; /// @brief    THIS FILE PROVIDES ALL THE Device Startup File of MM32 Cortex-M
; ///           Core Device for IAR EWARM toolchain.
; ////////////////////////////////////////////////////////////////////////////////
; /// @attention
; ///
; /// THE EXISTING FIRMWARE IS ONLY FOR REFERENCE, WHICH IS DESIGNED TO PROVIDE
; /// CUSTOMERS WITH CODING INFORMATION ABOUT THEIR PRODUCTS SO THEY CAN SAVE
; /// TIME. THEREFORE, MINDMOTION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
; /// CONSEQUENTIAL DAMAGES ABOUT ANY CLAIMS ARISING OUT OF THE CONTENT OF SUCH
; /// HARDWARE AND/OR THE USE OF THE CODING INFORMATION CONTAINED HEREIN IN
; /// CONNECTION WITH PRODUCTS MADE BY CUSTOMERS.
; ///
; /// <H2><CENTER>&COPY; COPYRIGHT MINDMOTION </CENTER></H2>
; ////////////////////////////////////////////////////////////////////////////////
;
; ////////////////////////////////////////////////////////////////////////////////
; /// The modules in this file are included in the libraries, and may be replaced
; /// by any user-defined modules that define the PUBLIC symbol _program_start or
; /// a user defined start symbol.
; /// To override the cstartup defined in the library, simply add your modified
; /// version to the workbench project.
; /// 
; /// The vector table is normally located at address 0.
; /// When debugging in RAM, it can be located in RAM, aligned to at least 2^6.
; /// The name "__vector_table" has special meaning for C-SPY:
; /// it is where the SP start value is found, and the NVIC vector
; /// table register (VTOR) is initialized to this address if != 0.
; ///
; /// Cortex-M version
; ///
; /// This module performs:
; ///                      - Set the initial SP
; ///                      - Set the initial PC == __iar_program_start,
; ///                      - Set the vector table entries with the exceptions ISR
; ///                                address
; ///                      - Configure the system clock (optional)
; ///                      - Branches to main in the C library (which eventually
; ///                                calls main()).
; /// After Reset the Cortex-M processor is in Thread mode,
; /// priority is Privileged, and the Stack is set to Main.
; ////////////////////////////////////////////////////////////////////////////////

                MODULE  ?cstartup

                                                                                ;; Forward declaration of sections.
                SECTION CSTACK:DATA:NOROOT(3)

                SECTION .intvec:CODE:NOROOT(2)

                EXTERN  __iar_program_start
                EXTERN  SystemInit
                PUBLIC  __vector_table
                PUBLIC   __vector_table_0x1c
                PUBLIC   __Vectors
                PUBLIC   __Vectors_End
                PUBLIC   __Vectors_Size

                DATA
__vector_table
                DCD     sfe(CSTACK)                                             ;       Top of Stack
                DCD     Reset_Handler                                           ;       Reset Handler
                DCD     NMI_Handler                                             ; -14   NMI Handler
                DCD     HardFault_Handler                                       ; -13   Hard Fault Handler
                DCD     0                                                       ;       Reserved
                DCD     0                                                       ;       Reserved
                DCD     0                                                       ;       Reserved
__vector_table_0x1c
                DCD     0                                                       ;       Reserved
                DCD     0                                                       ;       Reserved
                DCD     0                                                       ;       Reserved
                DCD     0                                                       ;       Reserved
                DCD     SVC_Handler                                             ;  -5   SVCall Handler
                DCD     0                                                       ;       Reserved
                DCD     0                                                       ;       Reserved
                DCD     PendSV_Handler                                          ;  -2   PendSV Handler
                DCD     SysTick_Handler                                         ;  -1   SysTick Handler

                                                                                ; External Interrupts
                DCD     WWDG_IRQHandler                                         ;   0   Window Watchdog
                DCD     PVD_IRQHandler                                          ;   1   PVD through EXTI Line detect
                DCD     0                                                       ;   Reserved
                DCD     FLASH_IRQHandler                                        ;   3   FLASH
                DCD     RCC_CRS_IRQHandler                                      ;   4   RCC & CRS
                DCD     EXTI0_1_IRQHandler                                      ;   5   EXTI Line 0 and 1
                DCD     EXTI2_3_IRQHandler                                      ;   6   EXTI Line 2 and 3
                DCD     EXTI4_15_IRQHandler                                     ;   7   EXTI Line 4 to 15
                DCD     HWDIV_IRQHandler                                        ;   8   HWDIV
                DCD     DMA1_Channel1_IRQHandler                                ;   9   DMA1 Channel 1
                DCD     DMA1_Channel2_3_IRQHandler                              ;  10   DMA1 Channel 2 and Channel 3
                DCD     DMA1_Channel4_5_IRQHandler                              ;  11   DMA1 Channel 4 and Channel 5
                DCD     ADC1_COMP_IRQHandler                                    ;  12   ADC1 & COMP
                DCD     TIM1_BRK_UP_TRG_COM_IRQHandler                          ;  13   TIM1 Break, Update, Trigger and Commutation
                DCD     TIM1_CC_IRQHandler                                      ;  14   TIM1 Capture Compare
                DCD     TIM2_IRQHandler                                         ;  15   TIM2
                DCD     TIM3_IRQHandler                                         ;  16   TIM3
                DCD     0                                                       ;  17   Reserved
                DCD     0                                                       ;  18   Reserved
                DCD     TIM14_IRQHandler                                        ;  19   TIM14
                DCD     0                                                       ;  20   Reserved
                DCD     TIM16_IRQHandler                                        ;  21   TIM16
                DCD     TIM17_IRQHandler                                        ;  22   TIM17
                DCD     I2C1_IRQHandler                                         ;  23   I2C1
                DCD     0                                                       ;  24   Reserved
                DCD     SPI1_IRQHandler                                         ;  25   SPI1
                DCD     SPI2_IRQHandler                                         ;  26   SPI2
                DCD     UART1_IRQHandler                                        ;  27   UART1
                DCD     UART2_IRQHandler                                        ;  28   UART2
                DCD     0                                                       ;  29   Reserved
                DCD     0                                                       ;  30   Reserved
                DCD     0                                                       ;  31   Reserved

                                                                                ; Total Cortex-M0 32 Interrupts are setting
__Vectors_End

__Vectors       EQU      __vector_table
__Vectors_Size  EQU      __Vectors_End - __Vectors


                THUMB

; Reset Handler

                PUBWEAK Reset_Handler
                SECTION .text:CODE:REORDER:NOROOT(2)
Reset_Handler
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__iar_program_start
                BX      R0


                PUBWEAK NMI_Handler
                PUBWEAK HardFault_Handler
                PUBWEAK SVC_Handler
                PUBWEAK PendSV_Handler
                PUBWEAK SysTick_Handler
                PUBWEAK WWDG_IRQHandler
                PUBWEAK PVD_IRQHandler

                PUBWEAK FLASH_IRQHandler
                PUBWEAK RCC_CRS_IRQHandler
                PUBWEAK EXTI0_1_IRQHandler
                PUBWEAK EXTI2_3_IRQHandler
                PUBWEAK EXTI4_15_IRQHandler
				PUBWEAK HWDIV_IRQHandler
                PUBWEAK DMA1_Channel1_IRQHandler
                PUBWEAK DMA1_Channel2_3_IRQHandler
                PUBWEAK DMA1_Channel4_5_IRQHandler
                PUBWEAK ADC1_COMP_IRQHandler
                PUBWEAK TIM1_BRK_UP_TRG_COM_IRQHandler
                PUBWEAK TIM1_CC_IRQHandler
                PUBWEAK TIM2_IRQHandler
                PUBWEAK TIM3_IRQHandler
                PUBWEAK TIM14_IRQHandler
                PUBWEAK TIM16_IRQHandler
                PUBWEAK TIM17_IRQHandler
                PUBWEAK I2C1_IRQHandler
                PUBWEAK SPI1_IRQHandler
                PUBWEAK SPI2_IRQHandler
                PUBWEAK UART1_IRQHandler
                PUBWEAK UART2_IRQHandler



                SECTION .text:CODE:REORDER:NOROOT(1)
NMI_Handler
HardFault_Handler
SVC_Handler
PendSV_Handler
SysTick_Handler
WWDG_IRQHandler
PVD_IRQHandler
FLASH_IRQHandler
RCC_CRS_IRQHandler
EXTI0_1_IRQHandler
EXTI2_3_IRQHandler
EXTI4_15_IRQHandler
HWDIV_IRQHandler
DMA1_Channel1_IRQHandler
DMA1_Channel2_3_IRQHandler
DMA1_Channel4_5_IRQHandler
ADC1_COMP_IRQHandler
TIM1_BRK_UP_TRG_COM_IRQHandler
TIM1_CC_IRQHandler
TIM2_IRQHandler
TIM3_IRQHandler
TIM14_IRQHandler
TIM16_IRQHandler
TIM17_IRQHandler
I2C1_IRQHandler
SPI1_IRQHandler
SPI2_IRQHandler
UART1_IRQHandler
UART2_IRQHandler

Default_Handler
                B        .
                END





