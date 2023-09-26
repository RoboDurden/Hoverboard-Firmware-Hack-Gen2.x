

#ifndef CONFIG_H
#define CONFIG_H

//#include "gd32f1x0.h"

// ################################################################################
// select one of the supported circuit boards and whether to compile the slave- or master board
// only the master has a buzzer :-)

// LAYOUT_2_X is used in defines.h
#ifdef GD32E230
	#define LAYOUT_2_7	// https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x/issues/16
#else
	#define LAYOUT_2_0	// https://github.com/flo199213/Hoverboard-Firmware-Hack-Gen2
	//#define LAYOUT_2_1	// https://github.com/krisstakos/Hoverboard-Firmware-Hack-Gen2.1
	//#define LAYOUT_2_2	// motor is spinning but needs a push to startup :-/
	//#define LAYOUT_2_3	// 2023/09/19 motor does not run stable (sound like skipping steps in a stepper motor but it is rotating). mosfets heating up :-(
	//#define LAYOUT_2_4	// NOT READY !!! https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x/issues/3
	//#define LAYOUT_2_11	// NOT READY !!! https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x/issues/27
#endif


#define MASTER		// uncomment if firmware is for slave board


#define REMOTE_DUMMY
//#define REMOTE_UART
//#define REMOTE_CRSF

#define TEST_HALL2LED	// led the 3-led panel blink according to the hall sensors

#ifdef MASTER

	#define SPEED_COEFFICIENT   -1
	#define STEER_COEFFICIENT   1
	
	#define CHECK_BUTTON		// disable = add '//' if you use a slave board as master
#else
	#define SLAVE 												// Select if firmware is for master or slave board
#endif


// ################################################################################

#define PWM_FREQ         		16000     // PWM frequency in Hz
#define DEAD_TIME        		60        // PWM deadtime (60 = 1�s, measured by oscilloscope)

#define DC_CUR_LIMIT     		15        // Motor DC current limit in amps

#define BAT_CELLS         	5        // battery number of cells. Normal Hoverboard battery: 10s

//#define BLDC_WEAKENING		// some kind of field weaking added by HarleyBob for his gen2.2 firmware ?

// ################################################################################

#define DELAY_IN_MAIN_LOOP 	5         // Delay in ms

#define TIMEOUT_MS          2000      // Time in milliseconds without steering commands before pwm emergency off

#ifdef MASTER
	#define INACTIVITY_TIMEOUT 	8        	// Minutes of not driving until poweroff (not very precise)

	// ################################################################################


	#define CELL_LOW_LVL1     3.5       // Gently beeps, show green battery symbol above this Level.
	#define CELL_LOW_LVL2     3.3       // Battery almost empty, show orange battery symbol above this Level. Charge now! 
	#define CELL_LOW_DEAD     3.1       // Undervoltage lockout, show red battery symbol above this Level.

	#define BAT_LOW_LVL1     BAT_CELLS * CELL_LOW_LVL1
	#define BAT_LOW_LVL2     BAT_CELLS * CELL_LOW_LVL2
	#define BAT_LOW_DEAD     BAT_CELLS * CELL_LOW_DEAD

	/*
	#define BAT_LOW_LVL1     35.0       // Gently beeps, show green battery symbol above this Level.
	#define BAT_LOW_LVL2     33.0       // Battery almost empty, show orange battery symbol above this Level. Charge now! 
	#define BAT_LOW_DEAD     31.0       // Undervoltage lockout, show red battery symbol above this Level.
	// ONLY DEBUG-LEVEL!!!
	//#define BAT_LOW_LVL1     29.0
	//#define BAT_LOW_LVL2     28.0
	//#define BAT_LOW_DEAD     27.0
	*/

	// ################################################################################
#endif

// ###### ARMCHAIR ######
#define FILTER_SHIFT 12 						// Low-pass filter for pwm, rank k=12


#endif
