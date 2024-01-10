#ifdef SLAVE		// layout 2.7 has buzzer on the slave board.
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
#define LED_GREEN GPIO_PIN_3				
#define LED_GREEN_PORT GPIOB	
#define LED_ORANGE GPIO_PIN_4				
#define LED_ORANGE_PORT GPIOB	
#define LED_RED GPIO_PIN_5					
#define LED_RED_PORT GPIOB

#define UPPER_LED_PIN GPIO_PIN_0		
#define UPPER_LED_PORT GPIOF	
#define LOWER_LED_PIN GPIO_PIN_1		
#define LOWER_LED_PORT GPIOF	

// Mosfet output
// seems to be an ordinary LED output ?
// led.c:91	gpio_bit_write(MOSFET_OUT_PORT, MOSFET_OUT_PIN, counter_Blue >= setValue_Blue ? RESET : SET); 
#define MOSFET_OUT_PIN TODO_PIN		
#define MOSFET_OUT_PORT TODO_PORT	


// Brushless Control DC (BLDC) defines
#define TIMER_BLDC_PULLUP	GPIO_PUPD_NONE	// robo
// Channel G
#define RCU_TIMER_BLDC RCU_TIMER0
#define TIMER_BLDC TIMER0
#define TIMER_BLDC_CHANNEL_G TIMER_CH_2 // PB15-TIMER0_CH2_ON (GPIO_AF_2), PA10-TIMER0_CH2 (GPIO_AF_2)  SAME AS 2.0 :-)
#define TIMER_BLDC_GH_PIN GPIO_PIN_15		// PB15 - Hi Lo Swapped from 2.0
#define TIMER_BLDC_GH_PORT GPIOB				// PB15 - Hi Lo Swapped from 2.0
#define TIMER_BLDC_GL_PIN GPIO_PIN_10		// PA10 - Hi Lo Swapped from 2.0
#define TIMER_BLDC_GL_PORT GPIOA				// PA10 - Hi Lo Swapped from 2.0
// Channel B
#define TIMER_BLDC_CHANNEL_B TIMER_CH_1 // PB14-TIMER0_CH1_ON (GPIO_AF_2), PA9-TIMER0_CH1 (GPIO_AF_2)  SAME AS 2.0 :-)
#define TIMER_BLDC_BH_PIN GPIO_PIN_14		// PB14 - Hi Lo Swapped from 2.0
#define TIMER_BLDC_BH_PORT GPIOB				// PB14 - Hi Lo Swapped from 2.0
#define TIMER_BLDC_BL_PIN GPIO_PIN_9		// PA9 - Hi Lo Swapped from 2.0
#define TIMER_BLDC_BL_PORT GPIOA				// PA9 - Hi Lo Swapped from 2.0
// Channel Y
#define TIMER_BLDC_CHANNEL_Y TIMER_CH_0 // PB13-TIMER0_CH0_ON (GPIO_AF_2), PA8-TIMER0_CH0 (GPIO_AF_2)  SAME AS 2.0 :-)
#define TIMER_BLDC_YH_PIN GPIO_PIN_13		// PB13 - Hi Lo Swapped from 2.0
#define TIMER_BLDC_YH_PORT GPIOB				// PB13 - Hi Lo Swapped from 2.0
#define TIMER_BLDC_YL_PIN GPIO_PIN_8		// PA8 - Hi Lo Swapped from 2.0
#define TIMER_BLDC_YL_PORT GPIOA				// PA8 - Hi Lo Swapped from 2.0

// Timer BLDC short circuit emergency shutoff define
// Is initialized here but never used somewhere else in code.
// setup.c:176	gpio_mode_set(TIMER_BLDC_EMERGENCY_SHUTDOWN_PORT , GPIO_MODE_AF, GPIO_PUPD_NONE, TIMER_BLDC_EMERGENCY_SHUTDOWN_PIN);  
#define TIMER_BLDC_EMERGENCY_SHUTDOWN_PIN TODO_PIN //GPIO_PIN_12	// NC
#define TIMER_BLDC_EMERGENCY_SHUTDOWN_PORT TODO_PORT //GPIOB		// NC

// Hall sensor defines
#define HALL_A_PIN GPIO_PIN_1	  // PA1 - GREEN
#define HALL_A_PORT GPIOA				// PA1 - GREEN
#define HALL_B_PIN GPIO_PIN_14	// PC14 - BLUE
#define HALL_B_PORT GPIOC				// PC14 - BLUE
#define HALL_C_PIN GPIO_PIN_11	// PB11 - YELLOW
#define HALL_C_PORT GPIOB				// PB11 - YELLOW


// GD32F130 USART0 TX/RX:	(PA9/PA10)AF1	, (PB6/PB7)AF0 , 	(PA2/PA3)AF1 , (PA14/PA15)AF1 GD32F130x4 only!
#define HAS_USART0	// uncomment if this layout has a usart0
#ifdef HAS_USART0
	#define USART0_TX_PIN	GPIO_PIN_6
	#define USART0_TX_PORT	GPIOB
	#define USART0_RX_PIN	GPIO_PIN_7
	#define USART0_RX_PORT	GPIOB
	
	//#define USART0_MASTERSLAVE		// uncomment if this usart is used for master-slave communication
	#define USART0_REMOTE						// uncomment if this usart is used for optional remote control
#endif

// GD32F130 USART1 GD32F130 TX/RX: (PA14/PA15)AF1 , (PA2,PA3)AF1	, (PA8/PB0)AlternateFunction4
#define HAS_USART1	// uncomment if this layout has a usart1
#ifdef HAS_USART1
	#define USART1_TX_PIN		GPIO_PIN_2
	#define USART1_TX_PORT	GPIOA
	#define USART1_RX_PIN		GPIO_PIN_3
	#define USART1_RX_PORT	GPIOA
	
	#define USART1_MASTERSLAVE		// uncomment if this usart is used for master-slave communication
	//#define USART1_REMOTE				// uncomment if this usart is used for optional remote control
#endif


// ADC defines
#define VBATT_PIN	GPIO_PIN_4				//PA4
#define VBATT_PORT GPIOA						//PA4
#define VBATT_CHANNEL ADC_CHANNEL_4
#define CURRENT_DC_PIN	GPIO_PIN_6	//PA6
#define CURRENT_DC_PORT GPIOA				//PA6
#define CURRENT_DC_CHANNEL ADC_CHANNEL_6

// Self hold defines
// important pin keeps the mosfet open after the on/off button got pushed !
// main.c:306: gpio_bit_write(SELF_HOLD_PORT, SELF_HOLD_PIN, SET); 
// and turns off power on Shutdown:
// main.c:513:	 gpio_bit_write(SELF_HOLD_PORT, SELF_HOLD_PIN, RESET); 
#define SELF_HOLD_PIN GPIO_PIN_2		// PB2
#define SELF_HOLD_PORT GPIOB				// PB2

// Button defines
// on/off (POW) push-button. So also a connection (i guess with some smd resistor in between) to a MCU pin.
// main.c:457: if (gpio_input_bit_get(BUTTON_PORT, BUTTON_PIN)) 
#define BUTTON_PIN GPIO_PIN_5			// PA5
#define BUTTON_PORT GPIOA					// PA5


#ifdef BUZZER
	// Buzzer defines
	#define BUZZER_PIN GPIO_PIN_4		// PB4
	#define BUZZER_PORT GPIOB				// PB4
#endif

#ifdef MASTER
	// Charge state defines
	// This seems to be a digital input that hast to be high in order to enable the motors. 
	// main.c:381: chargeStateLowActive = gpio_input_bit_get(CHARGE_STATE_PORT, CHARGE_STATE_PIN);
	// If not found it should be okay to simply comment this line because chargeStateLowActive in initialised as set = true
	#define CHARGE_STATE_PIN GPIO_PIN_15
	#define CHARGE_STATE_PORT GPIOC
#endif

// Debug pin defines - seems to be never used in code.
#define DEBUG_PIN TODO_PIN
#define DEBUG_PORT TODO_PORT

