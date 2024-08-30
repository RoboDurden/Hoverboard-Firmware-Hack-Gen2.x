#ifndef DEFINES_2_1_20_H
#define DEFINES_2_1_20_H

#define LED_RED PB4
#define LED_GREEN PB3
#define UPPER_LED PB2
#define LOWER_LED PB5

#define HALL_A PC13
#define HALL_B PA1
#define HALL_C PC14

#define BUZZER PB9

#define VBATT PA4
#define CURRENT_DC PA0 

#define SELF_HOLD	PB12
#define BUTTON PA12

// Brushless Control DC (BLDC) defines
#define BLDC_GH PA10		// green	, Tommyboi2001 all bldc pins same as 2.0
#define BLDC_GL PB15		
#define BLDC_BH PA9			// blue
#define BLDC_BL PB14		
#define BLDC_YH PA8			// yellow
#define BLDC_YL PB13		
#define TIMER_BLDC_PULLUP	GPIO_PUPD_NONE	// robo: not sure if some boards indeed nned GPIO_PUPD_PULLUP like 2.2 or 2.3

#define HAS_USART1	// tx=PA2,rx=PA3	uncomment to connect via 19200 baud serial
// GD32F130 USART1 GD32F130 TX/RX: (PA14/PA15)AF1 , (PA2,PA3)AF1	, (PA8/PB0)AlternateFunction4
#ifdef HAS_USART1
	#define USART1_TX		PA2
	#define USART1_RX		PA3
	
	#define USART1_MASTERSLAVE		// uncomment if this usart is used for master-slave communication
#endif

#endif