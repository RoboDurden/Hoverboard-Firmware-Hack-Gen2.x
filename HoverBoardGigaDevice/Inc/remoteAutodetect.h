#ifndef REMOTE_AUTODETECT_H
#define REMOTE_AUTODETECT_H


#define REMOTE_BAUD 19200

#define SEND_INTERVAL_MS	100	// sending SerialHover2Server data every 100 ms to ESP32/Arduino

#define LOST_CONNECTION_STOP_MILLIS 500		// set speed to 0 when 500 ms no command received

#define COUNT_PinDigital 27

#define AUTODETECT_Stage_Startup 0
#define AUTODETECT_Stage_Hall 1

// Only master communicates with steering device
#ifdef MASTER




#endif	// MASTER

#endif