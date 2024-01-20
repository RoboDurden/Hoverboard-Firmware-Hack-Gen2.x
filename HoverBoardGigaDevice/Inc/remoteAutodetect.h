#ifndef REMOTE_AUTODETECT_H
#define REMOTE_AUTODETECT_H


#define REMOTE_BAUD 19200

#define SEND_INTERVAL_MS	100	// sending SerialHover2Server data every 100 ms to ESP32/Arduino

#define LOST_CONNECTION_STOP_MILLIS 500		// set speed to 0 when 500 ms no command received

#define TODO_PIN PF4	// PF4 is only accessible on the largest GD32F130Rx LQFP64 pinouts mcu

static uint8_t bMessageWait = 0;
static char sMessage[512];


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
#define SCAN_BUZZER				11
#define SCAN_VBATT				12
#define SCAN_CURRENT_DC		13
#define SCAN_SELF_HOLD		14
#define SCAN_BUTTON				15


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
	#define AUTODETECT_Stage_Startup 1
	#define AUTODETECT_Stage_Hall 4
	#define AUTODETECT_Stage_HallOrder 8
	#define AUTODETECT_Stage_Led 16
	#define AUTODETECT_Stage_VBatt 2
	#define AUTODETECT_Stage_CurrentDC 32
	#define AUTODETECT_Stage_Hold 64
	#define AUTODETECT_Stage_Button 128
	#define AUTODETECT_Stage_Results 256
	#define AUTODETECT_Stage_Finished 512
#endif

uint8_t AutodetectBldc(uint8_t posNew,uint16_t buzzerTimer);
void AutodetectScan(uint16_t buzzerTimer);

void AutodetectMain();

void AutodetectInit();

// Only master communicates with steering device
#ifdef MASTER




#endif	// MASTER

#endif