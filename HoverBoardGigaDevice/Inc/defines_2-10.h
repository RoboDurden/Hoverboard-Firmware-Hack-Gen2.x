// defines_2-10.h

#ifdef MASTER_OR_SINGLE		// layout 2.2 has buzzer on the slave board.
	#define HAS_BUZZER
#endif

#define TODO_PIN PF4	// PF4 is only accessible on the largest GD32F130Rx LQFP64 pinouts mcu

/* GD32F130 48pin possible IO pins: 
	C13 C14 C15 F0 F1 A0 A1 A2 
	A3 A4 A5 A6 A7 B0 B1 B2 B10 B11
	B12 B13 B14 B15 A8 A9 A10 A11 A12 A13 F6 F7
	A14 A15 B3 B4 B5 B6 B7 B8 B9 
	
	mostly used for 6 BLDC mosfet pins: B13 B14 B15 A8 A9 A10
	mostly used for USART0: B6 B7
	mostly used for USART1: A2 A3
	ST-Flash pins: A13 A14 (also used as green and red led on 2.2)
	
	so mostly available for other use:	
	C13 C14 C15 F0 F1 A0 A1 A4 A5 A6 A7 B0 B1 B2 B10 B11 B12 A11 F6 F7 A12 A15 B3 B4 B5 B8 B9 
	so available for analog input:
	A0 A1 A2 A3 A4 A5 A6 A7 B0 B1 	
*/
	

// LED defines	- thanks to pacraf, transistors are on led module !
#ifdef SLAVE
	#define LED_GREEN 	PA12	
	#define LED_ORANGE 	PA15
	#define LED_RED 		PB3
#else
	#define LED_GREEN 	PB3	
	#define LED_ORANGE 	PA12	// only two led on the cross-like led panel but users may attach other stuff
	#define LED_RED 		PA15		
#endif

#define UPPER_LED PF6	// pacraf: "two line "panel leds goes from PF6. of course via transistor and 1k
//#define UPPER_LED PB4	// pacraf: additional outputs on black dupont female header
#define LOWER_LED PB5	// pacraf: pulldown, additional outputs on black dupont female header

// Mosfet output, little onboard led
#define MOSFET_OUT PF1

// Brushless Control DC (BLDC) defines
#define BLDC_GH PA10		// green	, Tommyboi2001 all bldc pins same as 2.0
#define BLDC_GL PB15		
#define BLDC_BH PA9			// blue
#define BLDC_BL PB14		
#define BLDC_YH PA8			// yellow
#define BLDC_YL PB13		
#define TIMER_BLDC_PULLUP	GPIO_PUPD_NONE	// robo: not sure if some boards indeed nned GPIO_PUPD_PULLUP like 2.2 or 2.3

// Timer BLDC short circuit emergency shutoff define
#define TIMER_BLDC_EMERGENCY_SHUTDOWN PB12	// pacraf: smd transistor connected to BRK = PB12. it is NPN type. robo: so pull down = overcurrent

// Hall sensor defines
#define HALL_A	PA1		// thanks to Tommyboi2001 and pacraf
#define HALL_B 	PA0
#define HALL_C	PB10


// GD32F130 USART0 TX/RX:	(PA9/PA10)AF1	, (PB6/PB7)AF0 , 	(PA2/PA3)AF1 , (PA14/PA15)AF1 GD32F130x4 only!
#define HAS_USART0	// uncomment if this layout has a usart0
#ifdef HAS_USART0
	#define USART0_TX	PB6	// thanks to pacraf
	#define USART0_RX	PB7	// thanks to pacraf
	
	//#define USART0_MASTERSLAVE		// uncomment if this usart is used for master-slave communication
	#define USART0_REMOTE						// uncomment if this usart is used for optional remote control
#endif


// GD32F130 USART1 GD32F130 TX/RX: (PA14/PA15)AF1 , (PA2,PA3)AF1	, (PA8/PB0)AlternateFunction4
#define HAS_USART1	// uncomment if this layout has a usart1
#ifdef HAS_USART1
	#define USART1_TX		PA2	// thanks to pacraf
	#define USART1_RX		PA3	// thanks to pacraf
	
	#define USART1_MASTERSLAVE		// uncomment if this usart is used for master-slave communication
	//#define USART1_REMOTE				// uncomment if this usart is used for optional remote control
#endif


// 2.10 available for analog input:		A4 A6 A7 B0 B1 

// ADC defines
#define VBATT PA4
#define ADC_BATTERY_VOLT      0.0171862875 	

#define CURRENT_DC	PA6	// robo just guessing
#define MOTOR_AMP_CONV_DC_AMP 0.0201465201465  


// Self hold defines
#define SELF_HOLD PB2		// thanks to pacraf

// Button defines
#define BUTTON PA5		// thanks to pacraf :-)


// 2.10 unused/unkown: C13 C14 C15 F0 A4 A5 A6 A7 B0 B1 B11 A11 F7 B8 B9 


#ifdef HAS_BUZZER
	// Buzzer defins
	#define BUZZER	PF0
#endif

#ifdef MASTER
	// Charge state defines
	#define CHARGE_STATE TODO_PIN
#endif


// Debug pin defines -  no longer has any function in code !
#define DEBUG_PIN TODO_PIN
#define DEBUG_PORT TODO_PORT