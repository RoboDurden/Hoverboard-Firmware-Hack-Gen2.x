#ifndef DEFINES_2_x_H
#define DEFINES_2_x_H

#ifdef MASTER_OR_SINGLE		// layout 2.2 and 2.7 have buzzer on the slave board.
	#define HAS_BUZZER
#endif
#define TODO_PIN PF4


// by AILIFE4798

#define HALL_A		PA0
#define HALL_B		PA1
#define HALL_C		PB11
#define PHASE_A		PB1
#define PHASE_B		PB0
#define PHASE_C		PA7

#define LED_RED		PA15
#define LED_ORANGE		PB3
#define LED_GREEN		PB4
#define UPPER_LED		PB5
#define LOWER_LED		PB8
#define BUZZER		PB9
#define VBATT		PA4
#define CURRENT_DC		PA6
#define SELF_HOLD		PB2
#define BUTTON		PA5


#define HAS_USART0	// tx=PB6,rx=PB7	uncomment to connect via 19200 baud serial
#define HAS_USART1	// tx=PA2,rx=PA3	uncomment to connect via 19200 baud serial





// Brushless Control DC (BLDC) defines
#define BLDC_GH PA8		// green	, Tommyboi2001 all bldc pins same as 2.0
#define BLDC_GL PB13		
#define BLDC_BH PA9			// blue
#define BLDC_BL PB14		
#define BLDC_YH PA10			// yellow
#define BLDC_YL PB15		
#define TIMER_BLDC_PULLUP	GPIO_PUPD_NONE	// robo: not sure if some boards indeed nned GPIO_PUPD_PULLUP like 2.2 or 2.3


// Timer BLDC short circuit emergency shutoff define
//#define TIMER_BLDC_EMERGENCY_SHUTDOWN	P_UNKOWN


// GD32F130 USART0 TX/RX:	(PA9/PA10)AF1	, (PB6/PB7)AF0 , 	(PA2/PA3)AF1 , (PA14/PA15)AF1 GD32F130x4 only!
#ifdef HAS_USART0
	#define USART0_TX	PB6
	#define USART0_RX	PB7
	
	//#define USART0_MASTERSLAVE		// uncomment if this usart is used for master-slave communication
	#define USART0_REMOTE						// uncomment if this usart is used for optional remote control
#endif


// GD32F130 USART1 GD32F130 TX/RX: (PA14/PA15)AF1 , (PA2,PA3)AF1	, (PA8/PB0)AlternateFunction4
#ifdef HAS_USART1
	#define USART1_TX		PA3
	#define USART1_RX		PA2
	
	#define USART1_MASTERSLAVE		// uncomment if this usart is used for master-slave communication
	//#define USART1_REMOTE				// uncomment if this usart is used for optional remote control
#endif


#endif