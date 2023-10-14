// from https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x/issues/20

#ifdef MASTER	// this layout has buzzer on the master board !
	#define BUZZER
#endif

#define TODO_PORT 	GPIOF		// this should be a pin that does no harm if input or output
#define TODO_PIN	GPIO_PIN_4	// PF4 is only accessible on the largest GD32F130Rx LQFP64 pinouts mcu


// LED defines, colors probably mismatch !
#define LED_GREEN 			GPIO_PIN_15
#define LED_GREEN_PORT 	GPIOA
#define LED_ORANGE 			GPIO_PIN_14
#define LED_ORANGE_PORT	GPIOA
#define LED_RED 				GPIO_PIN_3
#define LED_RED_PORT 		GPIOB

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
// mateuszfcg tested with PA1,PA2,PA0 
#define HALL_A_PIN	GPIO_PIN_0	// robo from front+back-photo
#define HALL_A_PORT	GPIOB
#define HALL_B_PIN	GPIO_PIN_1	// robo from front+back-photo
#define HALL_B_PORT	GPIOB
#define HALL_C_PIN	GPIO_PIN_5	// robo from front+back-photo
#define HALL_C_PORT	GPIOA

// GD32F130 USART0 TX/RX:	(PA9/PA10)AF1	, (PB6/PB7)AF0 , 	(PA2/PA3)AF1 , (PA14/PA15)AF1 GD32F130x4 only!
//#define HAS_USART0	// uncomment if this layout has a usart0
#ifdef HAS_USART0
	#define USART0_TX_PIN		TODO_PIN
	#define USART0_TX_PORT	TODO_PORT
	#define USART0_RX_PIN		TODO_PIN
	#define USART0_RX_PORT	TODO_PORT
	
	#define USART0_MASTERSLAVE		// uncomment if this usart is used for master-slave communication
	//#define USART0_REMOTE						// uncomment if this usart is used for optional remote control
#endif

// GD32F130 USART1 GD32F130 TX/RX: (PA14/PA15)AF1 , (PA2,PA3)AF1	, (PA8/PB0)AlternateFunction4
#define HAS_USART1	// uncomment if this layout has a usart1
#ifdef HAS_USART1
	#define USART1_TX_PIN		GPIO_PIN_2
	#define USART1_TX_PORT	GPIOA
	#define USART1_RX_PIN		GPIO_PIN_3
	#define USART1_RX_PORT	GPIOA
	
	#define USART1_MASTERSLAVE		// uncomment if this usart is used for master-slave communication
	//#define USART0_REMOTE				// uncomment if this usart is used for optional remote control
#endif

// ADC defines
//#define VBATT_PIN	GPIO_PIN_0		// uncomment this line when you have verified the pin/port
#define VBATT_PORT GPIOA			
#define VBATT_CHANNEL ADC_CHANNEL_17
//#define CURRENT_DC_PIN	GPIO_PIN_1	// uncomment this line when you have verified the pin/port
#define CURRENT_DC_PORT GPIOA
#define CURRENT_DC_CHANNEL ADC_CHANNEL_2

// Self hold defines
// important pin keeps the mosfet open after the on/off button got pushed !
// main.c:306: gpio_bit_write(SELF_HOLD_PORT, SELF_HOLD_PIN, SET); 
// and turns off power on Shutdown:
// main.c:513:	 gpio_bit_write(SELF_HOLD_PORT, SELF_HOLD_PIN, RESET); 
#define SELF_HOLD_PIN		TODO_PIN
#define SELF_HOLD_PORT	TODO_PORT

// Button defines
// on/off (POW) push-button. So also a connection (i guess with some smd resistor in between) to a MCU pin.
// main.c:457: if (gpio_input_bit_get(BUTTON_PORT, BUTTON_PIN)) 
#define BUTTON_PIN	TODO_PIN
#define BUTTON_PORT	TODO_PORT


#ifdef BUZZER
	// Buzzer defines
	#define BUZZER_PIN	TODO_PIN
	#define BUZZER_PORT	TODO_PORT
#endif

#ifdef MASTER

	// Charge state defines
	// This seems to be a digital input that hast to be high in order to enable the motors. 
	// main.c:381: chargeStateLowActive = gpio_input_bit_get(CHARGE_STATE_PORT, CHARGE_STATE_PIN);
	// If not found it should be okay to simply comment this line because chargeStateLowActive in initialised as set = true
	#define CHARGE_STATE_PIN TODO_PIN
	#define CHARGE_STATE_PORT TODO_PORT
#endif

// photo diodes / light barriers on the backside
#define PHOTO_L_PIN		TODO_PIN
#define PHOTO_L_PORT	TODO_PORT
#define PHOTO_R_PIN		TODO_PIN
#define PHOTO_R_PORT	TODO_PORT



// Debug pin defines - seems to be never used in code.
#define DEBUG_PIN TODO_PIN	// TODO
#define DEBUG_PORT TODO_PORT			// TODO`