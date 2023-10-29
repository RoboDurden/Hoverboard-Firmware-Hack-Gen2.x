// defines_2-10.h

#ifdef MASTER_OR_SINGLE		// layout 2.2 has buzzer on the slave board.
	#define BUZZER
#endif

#define TODO_PORT 	GPIOF		// this should be a pin that does no harm if input or output
#define TODO_PIN	GPIO_PIN_4	// PF4 is only accessible on the largest GD32F130Rx LQFP64 pinouts mcu

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
	

// LED defines
#define LED_GREEN GPIO_PIN_12		// thanks to pacraf, transistors are on led module !
#define LED_GREEN_PORT GPIOA
#define LED_ORANGE GPIO_PIN_15	// thanks to pacraf, transistors are on led module !
#define LED_ORANGE_PORT GPIOA
#define LED_RED GPIO_PIN_3		// thanks to pacraf, transistors are on led module !
#define LED_RED_PORT GPIOB

#define UPPER_LED_PIN GPIO_PIN_4	// pacraf: additional outputs on black dupont female header
#define UPPER_LED_PORT GPIOB
#define LOWER_LED_PIN GPIO_PIN_5	// pacraf: pulldown, additional outputs on black dupont female header
#define LOWER_LED_PORT GPIOB



// Brushless Control DC (BLDC) defines
#define TIMER_BLDC_PULLUP	GPIO_PUPD_NONE	// robo
// Channel G
#define RCU_TIMER_BLDC RCU_TIMER0
#define TIMER_BLDC TIMER0
#define TIMER_BLDC_CHANNEL_G TIMER_CH_2
#define TIMER_BLDC_GH_PIN GPIO_PIN_10		// all bldc pins same as 2.0, thanks to Tommyboi2001
#define TIMER_BLDC_GH_PORT GPIOA
#define TIMER_BLDC_GL_PIN GPIO_PIN_15
#define TIMER_BLDC_GL_PORT GPIOB
// Channel B
#define TIMER_BLDC_CHANNEL_B TIMER_CH_1
#define TIMER_BLDC_BH_PIN GPIO_PIN_9
#define TIMER_BLDC_BH_PORT GPIOA
#define TIMER_BLDC_BL_PIN GPIO_PIN_14
#define TIMER_BLDC_BL_PORT GPIOB
// Channel Y
#define TIMER_BLDC_CHANNEL_Y TIMER_CH_0
#define TIMER_BLDC_YH_PIN GPIO_PIN_8
#define TIMER_BLDC_YH_PORT GPIOA
#define TIMER_BLDC_YL_PIN GPIO_PIN_13
#define TIMER_BLDC_YL_PORT GPIOB


// Hall sensor defines
#define HALL_A_PIN GPIO_PIN_0		// thanks to Tommyboi2001. robo: A and C might be reversed
#define HALL_A_PORT GPIOA
#define HALL_B_PIN GPIO_PIN_1
#define HALL_B_PORT GPIOA
#define HALL_C_PIN GPIO_PIN_10	// robo: A and C might be reversed, no colors on hall cables..
#define HALL_C_PORT GPIOB


// GD32F130 USART0 TX/RX:	(PA9/PA10)AF1	, (PB6/PB7)AF0 , 	(PA2/PA3)AF1 , (PA14/PA15)AF1 GD32F130x4 only!
#define HAS_USART0	// uncomment if this layout has a usart0
#ifdef HAS_USART0
	#define USART0_TX_PIN	GPIO_PIN_6	// thanks to pacraf
	#define USART0_TX_PORT	GPIOB
	#define USART0_RX_PIN	GPIO_PIN_7
	#define USART0_RX_PORT	GPIOB
	
	//#define USART0_MASTERSLAVE		// uncomment if this usart is used for master-slave communication
	#define USART0_REMOTE						// uncomment if this usart is used for optional remote control
#endif


// GD32F130 USART1 GD32F130 TX/RX: (PA14/PA15)AF1 , (PA2,PA3)AF1	, (PA8/PB0)AlternateFunction4
#define HAS_USART1	// uncomment if this layout has a usart1
#ifdef HAS_USART1
	#define USART1_TX_PIN		GPIO_PIN_2	// thanks to pacraf
	#define USART1_TX_PORT	GPIOA
	#define USART1_RX_PIN		GPIO_PIN_3
	#define USART1_RX_PORT	GPIOA
	
	#define USART1_MASTERSLAVE		// uncomment if this usart is used for master-slave communication
	//#define USART0_REMOTE				// uncomment if this usart is used for optional remote control
#endif


// 2.10 available for analog input:		A4 A6 A7 B0 B1 

// ADC defines
#define VBATT_PIN	GPIO_PIN_4	// robo just guessing
#define VBATT_PORT GPIOA
#define VBATT_CHANNEL ADC_CHANNEL_4
#define CURRENT_DC_PIN	GPIO_PIN_6	// robo just guessing
#define CURRENT_DC_PORT GPIOA
#define CURRENT_DC_CHANNEL ADC_CHANNEL_6

// Self hold defines
#define SELF_HOLD_PIN GPIO_PIN_12		// thanks to pacraf
#define SELF_HOLD_PORT GPIOB

// Button defines
#define BUTTON_PIN GPIO_PIN_5		// thanks to pacraf :-)
#define BUTTON_PORT GPIOA


// 2.10 unused/unkown: C13 C14 C15 F0 F1 A4 A5 A6 A7 B0 B1 B2 B11 A11 F6 F7 B8 B9 

#ifdef BUZZER
	// Buzzer defins
	#define BUZZER_PIN GPIO_PIN_0
	#define BUZZER_PORT GPIOF
#endif

#ifdef MASTER
	// Charge state defines
	#define CHARGE_STATE_PIN TODO_PIN
	#define CHARGE_STATE_PORT TODO_PORT
#endif

// Mosfet output
#define MOSFET_OUT_PIN TODO_PIN
#define MOSFET_OUT_PORT TODO_PORT

// Timer BLDC short circuit emergency shutoff define
#define TIMER_BLDC_EMERGENCY_SHUTDOWN_PIN TODO_PIN
#define TIMER_BLDC_EMERGENCY_SHUTDOWN_PORT TODO_PORT

// Debug pin defines
#define DEBUG_PIN TODO_PIN
#define DEBUG_PORT TODO_PORT

