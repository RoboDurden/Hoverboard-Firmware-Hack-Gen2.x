// from https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x/issues/20
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


// LED defines, colors probably mismatch !
#define LED_GREEN 			GPIO_PIN_3
#define LED_GREEN_PORT 	GPIOB
#define LED_ORANGE 			GPIO_PIN_4
#define LED_ORANGE_PORT	GPIOB
#define LED_RED 				GPIO_PIN_15
#define LED_RED_PORT 		GPIOA

#define UPPER_LED_PIN 	GPIO_PIN_4
#define UPPER_LED_PORT 	GPIOB
#define LOWER_LED_PIN 	GPIO_PIN_5
#define LOWER_LED_PORT 	GPIOB


// Mosfet output
// seems to be an ordinary LED output ?
// led.c:91	gpio_bit_write(MOSFET_OUT_PORT, MOSFET_OUT_PIN, counter_Blue >= setValue_Blue ? RESET : SET); 
#define MOSFET_OUT_PIN TODO_PIN		// TODO
#define MOSFET_OUT_PORT TODO_PORT	// TODO

// Brushless Control DC (BLDC) defines
#define TIMER_BLDC_PULLUP	GPIO_PUPD_PULLUP	// robo, based on Herleybob:defines.h
// Channel G
#define RCU_TIMER_BLDC RCU_TIMER0
#define TIMER_BLDC TIMER0
#define TIMER_BLDC_CHANNEL_G TIMER_CH_2
#define TIMER_BLDC_GH_PIN		GPIO_PIN_8		// channels G=green and Y=yellow swopped compared to 2.0
#define TIMER_BLDC_GH_PORT	GPIOA
#define TIMER_BLDC_GL_PIN		GPIO_PIN_13
#define TIMER_BLDC_GL_PORT	GPIOB
// Channel B
#define TIMER_BLDC_CHANNEL_B TIMER_CH_1
#define TIMER_BLDC_BH_PIN		GPIO_PIN_9
#define TIMER_BLDC_BH_PORT	GPIOA
#define TIMER_BLDC_BL_PIN		GPIO_PIN_14
#define TIMER_BLDC_BL_PORT	GPIOB
// Channel Y
#define TIMER_BLDC_CHANNEL_Y TIMER_CH_0
#define TIMER_BLDC_YH_PIN		GPIO_PIN_10
#define TIMER_BLDC_YH_PORT	GPIOA
#define TIMER_BLDC_YL_PIN		GPIO_PIN_15
#define TIMER_BLDC_YL_PORT	GPIOB

// Timer BLDC short circuit emergency shutoff define
// Is initialized here but never used somewhere else in code.
// setup.c:176	gpio_mode_set(TIMER_BLDC_EMERGENCY_SHUTDOWN_PORT , GPIO_MODE_AF, GPIO_PUPD_NONE, TIMER_BLDC_EMERGENCY_SHUTDOWN_PIN);  
#define TIMER_BLDC_EMERGENCY_SHUTDOWN_PIN		TODO_PIN	// TODO
#define TIMER_BLDC_EMERGENCY_SHUTDOWN_PORT	TODO_PORT		// TODO

// Hall sensor defines
// Der_Pinguin tested with PA0,PA1,PA2 and it works fine now 
#define HALL_A_PIN	GPIO_PIN_0
#define HALL_A_PORT	GPIOA
#define HALL_B_PIN	GPIO_PIN_1
#define HALL_B_PORT	GPIOA
#define HALL_C_PIN	GPIO_PIN_2
#define HALL_C_PORT	GPIOA

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
//#define HAS_USART1	// uncomment if this layout has a usart0
#ifdef HAS_USART1
	#define USART1_TX_PIN		TODO_PIN
	#define USART1_TX_PORT	TODO_PORT
	#define USART1_RX_PIN		TODO_PIN
	#define USART1_RX_PORT	TODO_PORT
	
	//#define USART0_MASTERSLAVE		// uncomment if this usart is used for master-slave communication
	//#define USART0_REMOTE						// uncomment if this usart is used for optional remote control
#endif


#define VBATT_PIN GPIO_PIN_5
#define VBATT_PORT GPIOA
#define VBATT_CHANNEL ADC_CHANNEL_5
#define CURRENT_DC_PIN GPIO_PIN_6
#define CURRENT_DC_PORT GPIOA
#define CURRENT_DC_CHANNEL ADC_CHANNEL_6

#define ADC_BATTERY_VOLT      0.025656547849	// V_Batt to V_BattMeasure = factor 30: ( (ADC-Data/4095) *3,3V *30 )


// Self hold defines
// important pin keeps the mosfet open after the on/off button got pushed !
// main.c:306: gpio_bit_write(SELF_HOLD_PORT, SELF_HOLD_PIN, SET); 
// and turns off power on Shutdown:
// main.c:513:	 gpio_bit_write(SELF_HOLD_PORT, SELF_HOLD_PIN, RESET); 
#define SELF_HOLD_PIN		GPIO_PIN_3		// lerwinDE: master: A11 is used a hold bin, slave: A11 is buzzer pini
#define SELF_HOLD_PORT	GPIOA				// TODO

// Button defines
// on/off (POW) push-button. So also a connection (i guess with some smd resistor in between) to a MCU pin.
// main.c:457: if (gpio_input_bit_get(BUTTON_PORT, BUTTON_PIN)) 
#define BUTTON_PIN	GPIO_PIN_4			// robo, based on Herleybob:defines.h
#define BUTTON_PORT	GPIOA						// robo, based on Herleybob:defines.h

#ifdef BUZZER
	// Buzzer defines
	#define BUZZER_PIN	GPIO_PIN_11		// robo, based on Herleybob:defines.h
	#define BUZZER_PORT	GPIOA				// robo, based on Herleybob:defines.h
#endif

#ifdef MASTER

	// Charge state defines
	// This seems to be a digital input that hast to be high in order to enable the motors. 
	// main.c:381: chargeStateLowActive = gpio_input_bit_get(CHARGE_STATE_PORT, CHARGE_STATE_PIN);
	// If not found it should be okay to simply comment this line because chargeStateLowActive in initialised as set = true
	#define CHARGE_STATE_PIN GPIO_PIN_0		// TODO
	#define CHARGE_STATE_PORT GPIOF				// TODO
#endif

// photo diodes / light barriers on the backside
#define PHOTO_L_PIN		GPIO_PIN_15
#define PHOTO_L_PORT	GPIOC
#define PHOTO_R_PIN		GPIO_PIN_14
#define PHOTO_R_PORT	GPIOC

#define DATA_PIN		GPIO_PIN_11	// empty header to the left/down has only one data pin :-/
#define DATA_PORT	GPIOB					// could be used as I2C1_SDA (AF1 = alternate function 1)
																// but PB10 = I2C1_SCL is not routed to some header ?
// Debug pin defines - seems to be never used in code.
#define DEBUG_PIN TODO_PIN	// TODO
#define DEBUG_PORT TODO_PORT			// TODO`