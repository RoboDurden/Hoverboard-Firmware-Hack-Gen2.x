#ifdef SLAVE	// this layout has buzzer on the slave board !
	#define HAS_BUZZER
#endif

/* GD32F130 32pin possible IO pins: 
	
	mostly used for 6 BLDC mosfet pins: B13 B14 B15 A8 A9 A10
	mostly used for USART0: B6 B7
	mostly used for USART1: A2 A3
	ST-Flash pins: A13 A14 (also used as green and red led on 2.2)
	
	so mostly available for other use:	
	so available for analog input:
*/

#define TODO_PIN PF4	// PF4 is only accessible on the largest GD32F130Rx LQFP64 pinouts mcu
//#define TODO_PIN PB15	// would also do as 2.2 only as the QFN32 32 pin mcu version


// 2.2 unused/unkown: B4 B5 A6 A2 A0

// LED defines
#define LED_GREEN 			TODO_PIN	//GPIO_PIN_13	// lerwinDE: in conflict with flash pins DIO and CLK !!!
#define LED_GREEN_PORT 	TODO_PORT	//GPIOA				// only auto-flash.bat succeeds after multiple power-on
#define LED_ORANGE 			GPIO_PIN_1	// UPPER_LED with 4x blue led
#define LED_ORANGE_PORT	GPIOF
#define LED_RED 				TODO_PIN	//GPIO_PIN_14	// lerwinDE: in conflict with flash pins DIO and CLK !!!
#define LED_RED_PORT 		TODO_PORT	//GPIOA				// only auto-flash.bat succeeds after multiple power-on

#define UPPER_LED_PIN 	TODO_PIN	
#define UPPER_LED_PORT 	TODO_PORT	
#define LOWER_LED_PIN 	TODO_PIN	
#define LOWER_LED_PORT 	TODO_PORT	


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
#define TIMER_BLDC_GH_PIN GPIO_PIN_8		// GPIO_PIN_8	robo, based on Herleybob:defines.h
#define TIMER_BLDC_GH_PORT GPIOA				// GPIOA robo, based on Herleybob:defines.h
#define TIMER_BLDC_GL_PIN GPIO_PIN_7		// robo, based on Herleybob:defines.h
#define TIMER_BLDC_GL_PORT GPIOA				// robo, based on Herleybob:defines.h
// Channel B
#define TIMER_BLDC_CHANNEL_B TIMER_CH_1
#define TIMER_BLDC_BH_PIN GPIO_PIN_9		// robo, based on Herleybob:defines.h
#define TIMER_BLDC_BH_PORT GPIOA				// robo, based on Herleybob:defines.h
#define TIMER_BLDC_BL_PIN GPIO_PIN_0		// robo, based on Herleybob:defines.h
#define TIMER_BLDC_BL_PORT GPIOB				// robo, based on Herleybob:defines.h
// Channel Y
#define TIMER_BLDC_CHANNEL_Y TIMER_CH_0
#define TIMER_BLDC_YH_PIN GPIO_PIN_10		// robo, based on Herleybob:defines.h
#define TIMER_BLDC_YH_PORT GPIOA				// robo, based on Herleybob:defines.h
#define TIMER_BLDC_YL_PIN GPIO_PIN_1		// robo, based on Herleybob:defines.h
#define TIMER_BLDC_YL_PORT GPIOB				// robo, based on Herleybob:defines.h



//#define BLDC_CUR_G_PIN PA5
//#define BLDC_CUR_B_PIN PA4


// Timer BLDC short circuit emergency shutoff define
// Is initialized here but never used somewhere else in code.
// setup.c:176	gpio_mode_set(TIMER_BLDC_EMERGENCY_SHUTDOWN_PORT , GPIO_MODE_AF, GPIO_PUPD_NONE, TIMER_BLDC_EMERGENCY_SHUTDOWN_PIN);  
#define TIMER_BLDC_EMERGENCY_SHUTDOWN_PIN TODO_PIN	// TODO
#define TIMER_BLDC_EMERGENCY_SHUTDOWN_PORT TODO_PORT		// TODO

// Hall sensor defines
#define HALL_A_PIN GPIO_PIN_8		// robo, based on Herleybob:defines.h A = U ?
#define HALL_A_PORT GPIOB				// robo, based on Herleybob:defines.h A =  U ?
#define HALL_B_PIN GPIO_PIN_12	// robo, based on Herleybob:defines.h B = V ?
#define HALL_B_PORT GPIOA				// robo, based on Herleybob:defines.h B = V ?
#define HALL_C_PIN GPIO_PIN_3		// robo, based on Herleybob:defines.h C = W ?
#define HALL_C_PORT GPIOB				// robo, based on Herleybob:defines.h C = W ?


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
	#define USART1_RX_PIN		GPIO_PIN_15
	#define USART1_RX_PORT	GPIOA
	
	#define USART1_MASTERSLAVE		// uncomment if this usart is used for master-slave communication
	//#define USART1_REMOTE				// uncomment if this usart is used for optional remote control
#endif

//#define USART_REMOTE 			0		// either 0 or 1 if REMOTE_XY needs a USART port
//#define USART_MASTERSLAVE	1		// either 0 or 1 for MASTER or SLAVE



// ADC defines
#define VBATT_PIN	GPIO_PIN_1				// robo, no gpio_mode_set() inHerleybob:setup.c
#define VBATT_PORT GPIOA						// robo, no gpio_mode_set() inHerleybob:setup.c
#define VBATT_CHANNEL ADC_CHANNEL_1	// robo, based on Herleybob:setup.c: adc_regular_channel_config(2,ADC_CHANNEL_17,ADC_SAMPLETIME_13POINT5);
#define ADC_BATTERY_VOLT      0.02500961912134820371101460718516 // V_Batt to V_BattMeasure = factor 30: ( (ADC-Data/4095) *3,3V *30 )

#define CURRENT_DC_PIN	GPIO_PIN_3	// robo, no gpio_mode_set() inHerleybob:setup.c
#define CURRENT_DC_PORT GPIOA				// robo, no gpio_mode_set() inHerleybob:setup.c
#define CURRENT_DC_CHANNEL ADC_CHANNEL_3	// robo, maybe adc_buf_t:adc is potentiometer input

// Self hold defines
// important pin keeps the mosfet open after the on/off button got pushed !
// main.c:306: gpio_bit_write(SELF_HOLD_PORT, SELF_HOLD_PIN, SET); 
// and turns off power on Shutdown:
// main.c:513:	 gpio_bit_write(SELF_HOLD_PORT, SELF_HOLD_PIN, RESET); 
#define SELF_HOLD_PIN GPIO_PIN_11		// lerwinDE: master: A11 is used a hold bin, slave: A11 is buzzer pini
#define SELF_HOLD_PORT GPIOA				// TODO

// Button defines
// on/off (POW) push-button. So also a connection (i guess with some smd resistor in between) to a MCU pin.
// main.c:457: if (gpio_input_bit_get(BUTTON_PORT, BUTTON_PIN)) 
#define BUTTON_PIN GPIO_PIN_2			// robo, based on Herleybob:defines.h
#define BUTTON_PORT GPIOB						// robo, based on Herleybob:defines.h


#ifdef BUZZER
	// Buzzer defines
	#define BUZZER_PIN GPIO_PIN_11		// robo, based on Herleybob:defines.h
	#define BUZZER_PORT GPIOA				// robo, based on Herleybob:defines.h
#endif

#ifdef MASTER

	// Charge state defines
	// This seems to be a digital input that hast to be high in order to enable the motors. 
	// main.c:381: chargeStateLowActive = gpio_input_bit_get(CHARGE_STATE_PORT, CHARGE_STATE_PIN);
	// If not found it should be okay to simply comment this line because chargeStateLowActive in initialised as set = true
	#define CHARGE_STATE_PIN GPIO_PIN_0		// TODO
	#define CHARGE_STATE_PORT GPIOF				// TODO
#endif

// Debug pin defines - seems to be never used in code.
#define DEBUG_PIN TODO_PIN	// TODO
#define DEBUG_PORT TODO_PORT			// TODO

