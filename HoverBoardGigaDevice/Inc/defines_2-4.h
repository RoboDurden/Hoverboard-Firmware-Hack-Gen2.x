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

// LED defines
#define LED_GREEN PC15	// Batman313v, color might be wrong
#define LED_ORANGE PC14	// Batman313v, color might be wrong
#define LED_RED PC13		// Batman313v, color might be wrong

#define UPPER_LED PF1	// Batman313v, color might be wrong
#define LOWER_LED PF0	// Batman313v, color might be wrong

// Mosfet output
// seems to be an ordinary LED output ?
// led.c:91	gpio_bit_write(MOSFET_OUT_PORT, MOSFET_OUT, counter_Blue >= setValue_Blue ? RESET : SET); 
#define MOSFET_OUT TODO_PIN		

// Brushless Control DC (BLDC) defines
// Channel G
#define BLDC_GH PA10	//SAME AS 2.0 :-)
#define BLDC_GL PB15	//SAME AS 2.0 :-)
// Channel B
#define BLDC_BH PA9	//SAME AS 2.0 :-)
#define BLDC_BL PB4	//SAME AS 2.0 :-)
// Channel Y
#define BLDC_YH PA8	//SAME AS 2.0 :-)
#define BLDC_YL PB13	//SAME AS 2.0 :-)

#define TIMER_BLDC_PULLUP	GPIO_PUPD_NONE	// robo

// Timer BLDC short circuit emergency shutoff define
// Is initialized here but never used somewhere else in code.
// setup.c:176	gpio_mode_set(TIMER_BLDC_EMERGENCY_SHUTDOWN_PORT , GPIO_MODE_AF, GPIO_PUPD_NONE, TIMER_BLDC_EMERGENCY_SHUTDOWN);  
#define TIMER_BLDC_EMERGENCY_SHUTDOWN TODO_PIN

// Hall sensor defines
#define HALL_A PB0	// Batman313v
#define HALL_B PB5	// Batman313v
#define HALL_C PB4	// Batman313v

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


// ADC defines
#define VBATT	PA0			// Batman313v, might be CURRENT_DC !!!
#define CURRENT_DC	PA1		// Batman313v, might be VBATT !!!

// Self hold defines
// important pin keeps the mosfet open after the on/off button got pushed !
// main.c:306: gpio_bit_write(SELF_HOLD_PORT, SELF_HOLD, SET); 
// and turns off power on Shutdown:
// main.c:513:	 gpio_bit_write(SELF_HOLD_PORT, SELF_HOLD, RESET); 
#define SELF_HOLD PA6		// Batman313v

// Button defines
// on/off (POW) push-button. So also a connection (i guess with some smd resistor in between) to a MCU pin.
// main.c:457: if (gpio_input_bit_get(BUTTON_PORT, BUTTON)) 
#define BUTTON PA5		// Batman313v


#ifdef BUZZER
	// Buzzer defines
	#define BUZZER PB8		// Batman313v
#endif

#ifdef MASTER
	// Charge state defines
	// This seems to be a digital input that hast to be high in order to enable the motors. 
	// main.c:381: chargeStateLowActive = gpio_input_bit_get(CHARGE_STATE_PORT, CHARGE_STATE);
	// If not found it should be okay to simply comment this line because chargeStateLowActive in initialised as set = true
	#define CHARGE_STATE TODO_PIN
#endif

// Debug pin defines - seems to be never used in code.
#define DEBUG_PIN TODO_PIN

