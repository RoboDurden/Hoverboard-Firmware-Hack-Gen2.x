#include "../Inc/defines.h"
#include "../Inc/it.h"
#include "../Inc/comms.h"
#include "../Inc/bldc.h"
#include "stdio.h"
#include "string.h"

#ifdef REMOTE_AUTODETECT

#pragma pack(1)

// Only master communicates with steerin device
#ifdef MASTER_OR_SINGLE

extern uint8_t usart0_rx_buf[1];
extern uint8_t usart1_rx_buf[1];



extern int32_t steer;
extern int32_t speed;

extern int32_t iOdom;
extern float batteryVoltage; 							// global variable for battery voltage
extern float currentDC; 									// global variable for current dc
extern float realSpeed; 									// global variable for real Speed
extern DataSlave oDataSlave;
extern uint8_t  wStateSlave;
extern uint8_t  wState;

extern uint32_t steerCounter;								// Steer counter for setting update rate



//uint32_t iTimeLastRx = 0;
uint32_t iTimeNextTx = 0;

// Send frame to steer device
void RemoteUpdate(void)
{
	speed = 200;
	steer = 0;

	if (millis() < iTimeNextTx)	
		return;
	iTimeNextTx = millis() + SEND_INTERVAL_MS;

	char buffer[100];
	sprintf(buffer, "speed: %i\t%.3f V\t%.3f A\r\n",speed,batteryVoltage,currentDC);
	#ifdef USART0_REMOTE
		SendBuffer(USART0, (uint8_t *)buffer, strlen(buffer));
	#endif
	#ifdef USART1_REMOTE
		SendBuffer(USART1, (uint8_t *)buffer, strlen(buffer));
	#endif
}



// Update USART steer input
void RemoteCallback(void)
{
	#ifdef USART0_REMOTE
		uint8_t cRead = usart0_rx_buf[0];
	#endif
	#ifdef USART1_REMOTE
		uint8_t cRead = usart1_rx_buf[0];
	#endif
	//DEBUG_LedSet((steerCounter%20) < 10,0)	// 	
}


#endif

#endif