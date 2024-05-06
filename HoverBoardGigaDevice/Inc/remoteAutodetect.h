#ifndef REMOTE_AUTODETECT_H
#define REMOTE_AUTODETECT_H


#define REMOTE_BAUD 19200

#define SEND_INTERVAL_MS	100	// sending SerialHover2Server data every 100 ms to ESP32/Arduino

#define LOST_CONNECTION_STOP_MILLIS 500		// set speed to 0 when 500 ms no command received

#define TODO_PIN PF4	// PF4 is only accessible on the largest GD32F130Rx LQFP64 pinouts mcu

extern uint8_t bMessageWait;
extern char sMessage[512];


extern uint32_t HALL_A;
extern uint32_t HALL_B;
extern uint32_t HALL_C;


#define SCAN_HALL_A			0
#define SCAN_HALL_B			1
#define SCAN_HALL_C			2
#define SCAN_PHASE_A		3
#define SCAN_PHASE_B		4
#define SCAN_PHASE_C		5
#define SCAN_LED_RED		6
#define SCAN_LED_ORANGE	7
#define SCAN_LED_GREEN		8
#define SCAN_UPPER_LED		9
#define SCAN_LOWER_LED		10
#define SCAN_ONBOARD_LED	11
#define SCAN_BUZZER				12
#define SCAN_VBATT				13
#define SCAN_CURRENT_DC		14
#define SCAN_SELF_HOLD		15
#define SCAN_BUTTON				16
#define SCAN_BUTTON_PULLUP	17


//#define STAGE_TEST
#ifdef STAGE_TEST
	#define AUTODETECT_Stage_Startup 		1
	#define AUTODETECT_Stage_Led 				2
	#define AUTODETECT_Stage_VBatt 			8
	#define AUTODETECT_Stage_Hold 			4
	#define AUTODETECT_Stage_Button 		16
	#define AUTODETECT_Stage_Hall 			32
	#define AUTODETECT_Stage_HallOrder 	64
	#define AUTODETECT_Stage_CurrentDC 	128
	#define AUTODETECT_Stage_Results 		256
	#define AUTODETECT_Stage_Finished 	512
#else
	#define AUTODETECT_Stage_Startup 	1
	#define AUTODETECT_Stage_Menu 		2
	#define AUTODETECT_Stage_VBatt 		4
	#define AUTODETECT_Stage_Hold 			8
	#define AUTODETECT_Stage_Button 		16
	#define AUTODETECT_Stage_Led 				32
	#define AUTODETECT_Stage_Hall 			64
	#define AUTODETECT_Stage_HallOrder 	128
	#define AUTODETECT_Stage_CurrentDC 256
	#define AUTODETECT_Stage_Results 	512
	#define AUTODETECT_Stage_Finished	1024

	#define AUTODETECT_Stage_None	2048
	
	
#endif

#define MENU_INIT (2|AUTODETECT_Stage_VBatt|AUTODETECT_Stage_Hold|AUTODETECT_Stage_Led|AUTODETECT_Stage_Hall|AUTODETECT_Stage_Results)
	// stages shown in menu right from start, 2 stands for 'do all'

uint8_t AutodetectBldc(uint8_t posNew,uint16_t buzzerTimer);
void AutodetectScan(uint16_t buzzerTimer);

void AutodetectMain();

void AutodetectInit();

// Only master communicates with steering device
#ifdef MASTER




#endif	// MASTER

#endif