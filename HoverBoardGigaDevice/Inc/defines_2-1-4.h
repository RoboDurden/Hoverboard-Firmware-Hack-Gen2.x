// from https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x/issues/20
#ifdef MASTER_OR_SINGLE		// layout 2.2 and 2.7 have buzzer on the slave board.
	#define HAS_BUZZER
#endif

// autodetect 2024/04/05 by robo
#define HALL_A		PA0
#define HALL_B		PA1
#define HALL_C		PA2
#define PHASE_A		PA7
#define PHASE_B		PB0
#define PHASE_C		PB1

#define LED_RED		PA15
#define LED_ORANGE		PB4
#define LED_GREEN		PB3
#define UPPER_LED		PC13
#define LOWER_LED		PB5
//#define ONBOARD_LED		P??
#define BUZZER		PA11

#define VBATT		PA5
#define CURRENT_DC		PA6
#define SELF_HOLD		PA3
//#define BUTTON		P??
#define BUTTON_PU		PA4



#define HAS_USART0	// uncomment if this layout has a usart0

#define ADC_BATTERY_VOLT      0.025392524927  	//	robo, calibrated with 27V power supply
#define MOTOR_AMP_CONV_DC_AMP 0.0201465201465		//	robo,  only a very quick comparison to multimeter


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


// manual pin tracing https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x/issues/20


/*

#define TODO_PIN PF4	// PF4 is only accessible on the largest GD32F130Rx LQFP64 pinouts mcu


// LED defines, colors probably mismatch !
#define LED_GREEN 			PB3
#define LED_ORANGE 			PB4
#define LED_RED 				PA15

#define UPPER_LED 	PB4
#define LOWER_LED 	PB5


// Mosfet output, little onboard led
// seems to be an ordinary LED output ?
// led.c:91	gpio_bit_write(MOSFET_OUT_PORT, MOSFET_OUT_PIN, counter_Blue >= setValue_Blue ? RESET : SET); 
#define MOSFET_OUT TODO_PIN		// TODO

// Brushless Control DC (BLDC) defines
#define BLDC_YH PA10		// green	, green and yellow swapped !!! better swap hall sensors !!!
#define BLDC_YL PB15		
#define BLDC_BH PA9			// blue
#define BLDC_BL PB14		
#define BLDC_GH PA8			// yellow
#define BLDC_GL PB13		
#define TIMER_BLDC_PULLUP	GPIO_PUPD_PULLUP	// robo, based on Herleybob:defines.h

// Timer BLDC short circuit emergency shutoff define
#define TIMER_BLDC_EMERGENCY_SHUTDOWN		TODO_PIN	// TODO

// Hall sensor defines
// Der_Pinguin tested with PA0,PA1,PA2 and it works fine now 
#define HALL_A	PA0
#define HALL_B	PA1
#define HALL_C	PA2

// GD32F130 USART0 TX/RX:	(PA9/PA10)AF1	, (PB6/PB7)AF0 , 	(PA2/PA3)AF1 , (PA14/PA15)AF1 GD32F130x4 only!
#define HAS_USART0	// uncomment if this layout has a usart0
#ifdef HAS_USART0
	#define USART0_TX PB6
	#define USART0_RX	PB7
	
	//#define USART0_MASTERSLAVE		// uncomment if this usart is used for master-slave communication
	#define USART0_REMOTE						// uncomment if this usart is used for optional remote control
#endif


// GD32F130 USART1 GD32F130 TX/RX: (PA14/PA15)AF1 , (PA2,PA3)AF1	, (PA8/PB0)AlternateFunction4
//#define HAS_USART1	// uncomment if this layout has a usart0
#ifdef HAS_USART1
	#define USART1_TX	TODO_PIN
	#define USART1_RX	TODO_PIN
	
	//#define USART1_MASTERSLAVE		// uncomment if this usart is used for master-slave communication
	//#define USART1_REMOTE						// uncomment if this usart is used for optional remote control
#endif


#define VBATT	PA5
#define ADC_BATTERY_VOLT      0.025656547849	// V_Batt to V_BattMeasure = factor 30: ( (ADC-Data/4095) *3,3V *30 )

#define CURRENT_DC	PA6


// Self hold defines
// important pin keeps the mosfet open after the on/off button got pushed !
#define SELF_HOLD	PA3	// lerwinDE: master: A11 is used a hold bin, slave: A11 is buzzer pini

// Button defines
// on/off (POW) push-button. So also a connection (i guess with some smd resistor in between) to a MCU pin.
//#define BUTTON	PA4	
#define BUTTON_PU	PA4	// button needs INPUT_PULLUP and when pressed is read as LOW 


#ifdef HAS_BUZZER
	// Buzzer defines
	#define BUZZER	PA11	// robo, based on Herleybob:defines.h
#endif

#ifdef MASTER

	// Charge state defines
	// This seems to be a digital input that hast to be high in order to enable the motors. 
	// main.c:381: chargeStateLowActive = gpio_input_bit_get(CHARGE_STATE_PORT, CHARGE_STATE_PIN);
	// If not found it should be okay to simply comment this line because chargeStateLowActive in initialised as set = true
	#define CHARGE_STATE	TODO_PIN
#endif

// photo diodes / light barriers on the backside
#define PHOTO_L_PIN		PC15
#define PHOTO_R_PIN		PC14

#define DATA_PIN		PB11	// empty header to the left/down has only one data pin :-/
													// could be used as I2C1_SDA (AF1 = alternate function 1)
													// but PB10 = I2C1_SCL is not routed to some header ?
													
// Debug pin defines - seems to be never used in code.
#define DEBUG_PIN TODO_PIN	// TODO

*/