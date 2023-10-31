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
	#define pinMode(pin,mode) \
	{\
		gpio_mode_set(pin&0xffffff00U, mode, GPIO_PUPD_NONE,pin&0x000000ffU);	\
		gpio_output_options_set(pin&0xffffff00U, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, pin&0x000000ffU);\
	}

	#define digitalWrite(pin,set) \
	{\
		gpio_bit_write(pin&0xffffff00U, pin&0x000000ffU, set);\
	}


	#define PA15 ( GPIOA | GPIO_PIN_15 )
	#define PA12 ( GPIOA | GPIO_PIN_12 )
	#define PB3 ( GPIOB | GPIO_PIN_3 )
	
#endif	
	
	

	
	
	