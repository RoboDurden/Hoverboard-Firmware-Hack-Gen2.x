#ifdef GD32E230
	#include "gd32e23x.h"
	#define TARGET_nvic_irq_enable(a, b, c){nvic_irq_enable(a, b);}
	#define TARGET_nvic_priority_group_set(a)	// that function does not exist for this target = not needed ?
	#define TARGET_adc_vbat_disable()
#else
	#include "gd32f1x0.h"
	
	#define TARGET_nvic_irq_enable(a, b, c){nvic_irq_enable(a, b, c);}
	#define TARGET_nvic_priority_group_set(a){nvic_priority_group_set(a);}
	#define TARGET_adc_vbat_disable(){adc_vbat_disable();}
#endif


#ifndef pinMode
	
	/* GD32F130 and GD32E230
		#define GPIO_PIN_15 	BIT(15)
	
		#define GPIOA         (GPIO_BASE + 0x00000000U)
		#define GPIOB					(GPIO_BASE + 0x00000400U)
		#define GPIOC         (GPIO_BASE + 0x00000800U)
		#define GPIOD         (GPIO_BASE + 0x00000C00U)
		#define GPIOF         (GPIO_BASE + 0x00001400U)
	
		#define GPIO_BASE     (AHB2_BUS_BASE + 0x00000000U)  // !< GPIO base address
		#define AHB2_BUS_BASE ((uint32_t)0x48000000U)        //!< ahb2 base address
	*/
	
	// GD32F130 has 10 channels PA0..PA7 = 0..7 and PB0,PB1 = 8,9 . Only 64 pin MCU has further adc on GPIOC
	#define PIN_TO_CHANNEL(pin) ((pin&0xffffff00U) ==  GPIOA ? (pin&0xfU) : (pin&0xfU+8) )
	
	#define pinMode(pin,mode) \
	{\
		gpio_mode_set(pin&0xffffff00U, mode, GPIO_PUPD_NONE,BIT(pin&0xfU) );	\
		gpio_output_options_set(pin&0xffffff00U, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, BIT(pin&0xfU));\
	}
	#define pinModePull(pin,mode,pull) \
	{\
		gpio_mode_set(pin&0xffffff00U, mode, pull,BIT(pin&0xfU) );	\
		gpio_output_options_set(pin&0xffffff00U, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, BIT(pin&0xfU));\
	}
	#define pinModeSpeed(pin,mode,speed) \
	{\
		gpio_mode_set(pin&0xffffff00U, mode, GPIO_PUPD_NONE,BIT(pin&0xfU) );	\
		gpio_output_options_set(pin&0xffffff00U, GPIO_OTYPE_PP, speed, BIT(pin&0xfU));\
	}

	
	// AF = AlternateFunction
	#define pinModeAF(pin, AF, pullUpDown) \
	{\
		gpio_mode_set(pin&0xffffff00U , GPIO_MODE_AF, pullUpDown, BIT(pin&0xfU));	\
		gpio_output_options_set(pin&0xffffff00U, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, BIT(pin&0xfU));	\
		gpio_af_set(pin&0xffffff00U, AF(pin), BIT(pin&0xfU));		\
	}
	#define AF_TIMER0_BRKIN(pin)	(pin==PA6 ? GPIO_AF_2 : GPIO_AF_2)	// GD32F130: AF2 = PA6 or PB12
	#define AF_USART0_TX(pin)	(pin==PB6 ? GPIO_AF_0 : GPIO_AF_2)			// GD32F130: AF0 = PB6 , AF1 = PA2 or PA9 or PA14
	#define AF_USART0_RX(pin)	(pin==PB7 ? GPIO_AF_0 : GPIO_AF_2)			// GD32F130: AF0 = PB7 , AF1 = PA3 or PA15 
	#define AF_USART1_TX(pin)	(pin==PA8 ? GPIO_AF_4 : GPIO_AF_1)		// GD32F130: AF4 = PA8 , AF1 = PA2 or PA14
	#define AF_USART1_RX(pin)	(pin==PB0 ? GPIO_AF_4 : GPIO_AF_1)		// GD32F130: AF4 = PB0 , AF1 = PA3 or PA15

	#define digitalWrite(pin,set) gpio_bit_write(pin&0xffffff00U, BIT(pin&0xfU), set)
	#define digitalRead(pin) 			gpio_input_bit_get(pin&0xffffff00U, BIT(pin&0xfU))

	
	#define PA15	( GPIOA | 15 )
	#define PA14	( GPIOA | 14 )
	#define PA13	( GPIOA | 13 )
	#define PA12	( GPIOA | 12 )
	#define PA11	( GPIOA | 11 )
	#define PA10	( GPIOA | 10 )
	#define PA9		( GPIOA | 9 )
	#define PA8		( GPIOA | 8 )
	#define PA7		( GPIOA | 7 )
	#define PA6		( GPIOA | 6 )
	#define PA5		( GPIOA | 5 )
	#define PA4		( GPIOA | 4 )
	#define PA3		( GPIOA | 3 )
	#define PA2		( GPIOA | 2 )
	#define PA1		( GPIOA | 1 )
	#define PA0		( GPIOA | 0 )

	#define PB15	( GPIOB | 15 )
	#define PB14	( GPIOB | 14 )
	#define PB13	( GPIOB | 13 )
	#define PB12	( GPIOB | 12 )
	#define PB11	( GPIOB | 11 )
	#define PB10	( GPIOB | 10 )
	#define PB9		( GPIOB | 9 )
	#define PB8		( GPIOB | 8 )
	#define PB7		( GPIOB | 7 )
	#define PB6		( GPIOB | 6 )
	#define PB5		( GPIOB | 5 )
	#define PB4		( GPIOB | 4 )
	#define PB3		( GPIOB | 3 )
	#define PB2		( GPIOB | 2 )
	#define PB1		( GPIOB | 1 )
	#define PB0		( GPIOB | 0 )

	#define PC15	( GPIOC | 15 )
	#define PC14	( GPIOC | 14 )
	#define PC13	( GPIOC | 13 )

	#define PF4	( GPIOC | 4 )
	#define PF1	( GPIOC | 1 )
	#define PF0	( GPIOC | 0 )

#endif	
	
	

	
	
	