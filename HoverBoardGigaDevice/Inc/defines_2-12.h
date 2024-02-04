#ifndef DEFINES_2_12_H
#define DEFINES_2_12_H

#ifdef MASTER_OR_SINGLE		// layout 2.2 and 2.7 have buzzer on the slave board.
	#define HAS_BUZZER
#endif

// add autodetect #defines below and rename to defines_2-xy.h
// then add another
//	#elif LAYOUT == xy
//		#include "defines_2-xy.h"		// https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x/issues/40
// to defines.h and set #define LAYOUT xy in config.h in your chosen GD32E230/MM32SPIN05/GD32F103/GD32F130 target section

// autodetect 2.13 as example only !!!!!!!!!!!!!!!!!!!!!!! begin
#define HALL_A		PB11
#define HALL_B		PC14
#define HALL_C		PF1
#define PHASE_A		PB0
#define PHASE_B		PB1
//#define PHASE_C		P??

#define LED_RED		PB3
#define LED_ORANGE		PA12
#define LED_GREEN		PA15
#define UPPER_LED		PA1
#define LOWER_LED		PA0
//#define ONBOARD_LED		P??
#define BUZZER		PB10

#define VBATT		PA4
#define CURRENT_DC		PA6
#define SELF_HOLD		PB2
#define BUTTON		PC15
// autodetect 2.13 as example only !!!!!!!!!!!!!!!!!!!!!!! end


// Brushless Control DC (BLDC) defines
#define BLDC_GH PA10		// green	, Tommyboi2001 all bldc pins same as 2.0
#define BLDC_GL PB15		
#define BLDC_BH PA9			// blue
#define BLDC_BL PB14		
#define BLDC_YH PA8			// yellow
#define BLDC_YL PB13		
#define TIMER_BLDC_PULLUP	GPIO_PUPD_NONE	// robo: not sure if some boards indeed nned GPIO_PUPD_PULLUP like 2.2 or 2.3


// Timer BLDC short circuit emergency shutoff define
//#define TIMER_BLDC_EMERGENCY_SHUTDOWN	P_UNKOWN


// choose the serial ports available (and set them to Remote or MasterSlave below)

#define HAS_USART0	// tx=PB6,rx=PB7	uncomment to connect via 19200 baud serial
// GD32F130 USART0 TX/RX:	(PA9/PA10)AF1	, (PB6/PB7)AF0 , 	(PA2/PA3)AF1 , (PA14/PA15)AF1 GD32F130x4 only!
#ifdef HAS_USART0
	#define USART0_TX	PB6
	#define USART0_RX	PB7
	
	//#define USART0_MASTERSLAVE		// uncomment if this usart is used for master-slave communication
	#define USART0_REMOTE						// uncomment if this usart is used for optional remote control
#endif


#define HAS_USART1	// tx=PA2,rx=PA3	uncomment to connect via 19200 baud serial
// GD32F130 USART1 GD32F130 TX/RX: (PA14/PA15)AF1 , (PA2,PA3)AF1	, (PA8/PB0)AlternateFunction4
#ifdef HAS_USART1
	#define USART1_TX		PA2
	#define USART1_RX		PA3
	
	#define USART1_MASTERSLAVE		// uncomment if this usart is used for master-slave communication
	//#define USART1_REMOTE				// uncomment if this usart is used for optional remote control
#endif


#endif