#ifndef DEFINES_2_1_6_H
#define DEFINES_2_1_6_H

// todo: BUTTON not working but hiliving is sure to have traced the pin correctly with the help of ailife


#if LAYOUT_SUB == 1
	// v1.3
	// = 2.1.6.1: https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x/issues/80
#else	// 0
	// v1.1
#endif


#ifdef MASTER_OR_SINGLE		// layout 2.2 and 2.7 have buzzer on the slave board.
	#define HAS_BUZZER
#endif

// autodetect section begin
#define LED_RED		PB4
#define LED_ORANGE PA15		// hiliving 2.1.6.1
#define LED_GREEN		PB3
#define UPPER_LED		PB5		// hiliving 2.1.6.1
//#define LOWER_LED		P??
//#define ONBOARD_LED		P??
#define BUZZER		PB9

#define HALL_A		PC14
#define HALL_B		PA1
#define HALL_C		PB11

#define VBATT	PA4		
#define ADC_BATTERY_VOLT      0.02488682634 	// V_Batt to V_BattMeasure = factor 30: ( (ADC-Data/4095) *3,3V *30 ) 

#define CURRENT_DC	PA6	


#define SELF_HOLD	PB2
#define BUTTON_PU	PA5

// autodetect section end


#define HAS_USART1	// tx=PA2,rx=PA3	uncomment to connect via 19200 baud serial


// Brushless Control DC (BLDC) defines
#define BLDC_GH PA10		// green	, Tommyboi2001 all bldc pins same as 2.0
#define BLDC_GL PB15		
#define BLDC_BH PA9			// blue
#define BLDC_BL PB14		
#define BLDC_YH PA8			// yellow
#define BLDC_YL PB13		
#define TIMER_BLDC_PULLUP	GPIO_PUPD_NONE	// robo: not sure if some boards indeed nned GPIO_PUPD_PULLUP like 2.2 or 2.3


// Timer BLDC short circuit emergency shutoff define
//#define TIMER_BLDC_EMERGENCY_SHUTDOWN	TODO_PIN


// GD32F130 USART0 TX/RX:	(PA9/PA10)AF1	, (PB6/PB7)AF0 , 	(PA2/PA3)AF1 , (PA14/PA15)AF1 GD32F130x4 only!
#ifdef HAS_USART0
	#define USART0_TX	PB6
	#define USART0_RX	PB7
	
	//#define USART0_MASTERSLAVE		// uncomment if this usart is used for master-slave communication
	#define USART0_REMOTE						// uncomment if this usart is used for optional remote control
#endif


// GD32F130 USART1 GD32F130 TX/RX: (PA14/PA15)AF1 , (PA2,PA3)AF1	, (PA8/PB0)AlternateFunction4
#ifdef HAS_USART1
	#define USART1_TX		PA2
	#define USART1_RX		PA3
	
	//#define USART1_MASTERSLAVE		// uncomment if this usart is used for master-slave communication
	#define USART1_REMOTE				// uncomment if this usart is used for optional remote control
#endif

#ifdef MASTER
	// Charge state defines
	#define CHARGE_STATE	PC15		// hiliving ?
#endif

// Timer BLDC short circuit emergency shutoff define
#define TIMER_BLDC_EMERGENCY_SHUTDOWN	PB12	// hiliving ?


#endif