#ifdef MASTER_OR_SINGLE		// layout 2.2 and 2.7 have buzzer on the slave board.
	#define HAS_BUZZER
#endif

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

#define TODO_PIN PF4	// PF4 is only accessible on the largest GD32F130Rx LQFP64 pinouts mcu


// LED defines CORRECT
#define LED_GREEN PB3
#define LED_ORANGE PB4
#define LED_RED PA5

#define UPPER_LED PB5
#define LOWER_LED PB8


// Mosfet output CORRECT
#define MOSFET_OUT PC13

// Brushless Control DC (BLDC) defines
#define TIMER_BLDC_PULLUP	GPIO_PUPD_NONE	// robo
// Channel G CORRECT
#define BLDC_GH PA10
#define BLDC_GL PB15
// Channel B CORRECT
#define BLDC_BH PA9
#define BLDC_BL PB14
// Channel Y CORRECT
#define BLDC_YH PA8
#define BLDC_YL PB13

// Timer BLDC short circuit emergency shutoff define LOOKS LIKE
#define TIMER_BLDC_EMERGENCY_SHUTDOWN PB12

// Hall sensor defines CORRECT
#define HALL_A PA0
#define HALL_C PB11
#define HALL_B PA1


// GD32F130 USART0 TX/RX:	(PA9/PA10)AF1	, (PB6/PB7)AF0 , 	(PA2/PA3)AF1 , (PA14/PA15)AF1 GD32F130x4 only!
#define HAS_USART0	// uncomment if this layout has a usart0
#ifdef HAS_USART0
	#define USART0_TX	PB6
	#define USART0_RX	PB7
	
	//#define USART0_MASTERSLAVE		// uncomment if this usart is used for master-slave communication
	#define USART0_REMOTE						// uncomment if this usart is used for optional remote control
#endif

// GD32F130 USART1 GD32F130 TX/RX: (PA14/PA15)AF1 , (PA2,PA3)AF1	, (PA8/PB0)AlternateFunction4
#define HAS_USART1	// uncomment if this layout has a usart1
#ifdef HAS_USART1
	#define USART1_TX		PA2
	#define USART1_RX		PA3
	
	#define USART1_MASTERSLAVE		// uncomment if this usart is used for master-slave communication
	//#define USART1_REMOTE				// uncomment if this usart is used for optional remote control
#endif


// ADC defines CORRECT
#define VBATT	PA4
#define CURRENT_DC PA6

// Self hold defines CORRECT
#define SELF_HOLD PB2

// Button defines CORRECT - voltage is too low
#define BUTTON PA5


#ifdef BUZZER
	// Buzzer defins CORRECT
	#define BUZZER PB9
#endif

#ifdef MASTER
	// Charge state defines CORRECT
	#define CHARGE_STATE PC15
#endif

