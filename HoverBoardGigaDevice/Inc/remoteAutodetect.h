#ifndef REMOTE_AUTODETECT_H
#define REMOTE_AUTODETECT_H


#define REMOTE_BAUD 19200

#define SEND_INTERVAL_MS	100	// sending SerialHover2Server data every 100 ms to ESP32/Arduino

#define LOST_CONNECTION_STOP_MILLIS 500		// set speed to 0 when 500 ms no command received

#define TODO_PIN PF4	// PF4 is only accessible on the largest GD32F130Rx LQFP64 pinouts mcu

static char sMessage[512];


extern uint32_t HALL_A;
extern uint32_t HALL_B;
extern uint32_t HALL_C;


#define AUTODETECT_Stage_Startup 0
#define AUTODETECT_Stage_Hall 1
#define AUTODETECT_Stage_HallOrder 2
#define AUTODETECT_Stage_Led 3
#define AUTODETECT_Stage_VBatt 4
#define AUTODETECT_Stage_CurrentDC 5
#define AUTODETECT_Stage_Finished 6

uint8_t AutodetectBldc(uint8_t posNew);

void AutodetectMain();

void AutodetectInit();

// Only master communicates with steering device
#ifdef MASTER




#endif	// MASTER

#endif