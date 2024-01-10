#include "../Inc/defines.h"
#include "../Inc/it.h"
#include "../Inc/comms.h"
#include "../Inc/bldc.h"
#include "stdio.h"
#include "string.h"

#ifdef REMOTE_UART

#pragma pack(1)

// Only master communicates with steerin device
#ifdef MASTER_OR_SINGLE
//#define USART_STEER_TX_BYTES 2   // Transmit byte count including start '/' and stop character '\n'
#define USART_STEER_RX_BYTES 7   // Receive byte count including start '/' and stop character '\n'

extern uint8_t usart0_rx_buf[1];
extern uint8_t usart1_rx_buf[1];
//extern uint8_t usartSteer_COM_rx_buf[USART_STEER_COM_RX_BUFFERSIZE];
//static uint8_t aReceiveBuffer[USART_STEER_RX_BYTES];


static int16_t iReceivePos = 0;	

extern int32_t steer;
extern int32_t speed;

extern int32_t iOdom;
extern float batteryVoltage; 							// global variable for battery voltage
extern float currentDC; 									// global variable for current dc
extern float realSpeed; 									// global variable for real Speed
extern DataSlave oDataSlave;
extern uint8_t  wStateSlave;
extern uint8_t  wState;

typedef struct {			// ´#pragma pack(1)´ needed to get correct sizeof()
   uint8_t cStart;		//  = '/';
   //uint16_t cStart;		//  = #define START_FRAME         0xABCD
   int16_t  iSpeed;
   int16_t  iSteer;
   uint8_t  wStateMaster;   // 1=ledGreen, 2=ledOrange, 4=ledRed, 8=ledUp, 16=ledDown   , 32=Battery3Led, 64=Disable, 128=ShutOff
   uint8_t  wStateSlave;   // 1=ledGreen, 2=ledOrange, 4=ledRed, 8=ledUp, 16=ledDown   , 32=Battery3Led, 64=Disable, 128=ShutOff
   uint16_t checksum;
} SerialServer2Hover;

static uint8_t aReceiveBuffer[sizeof(SerialServer2Hover)];

#define START_FRAME         0xABCD       // [-] Start frme definition for reliable serial communication
typedef struct{				// ´#pragma pack(1)´ needed to get correct sizeof()
   uint16_t cStart;
   int16_t iSpeedL;		// 100* km/h
   int16_t iSpeedR;		// 100* km/h
   uint16_t iVolt;		// 100* V
   int16_t iAmpL;			// 100* A
   int16_t iAmpR;			// 100* A
   int32_t iOdomL;		// hall steps
   int32_t iOdomR;		// hall steps
   uint16_t checksum;
} SerialHover2Server;

int16_t aiDebug[7];



//static uint8_t aDebug[sizeof(SerialServer2Hover)];


uint32_t iTimeLastRx = 0;
uint32_t iTimeNextTx = 0;

// Send frame to steer device
void RemoteUpdate(void)
{
	if (millis() - iTimeLastRx > LOST_CONNECTION_STOP_MILLIS)
	{
		speed = steer = 0;
	}

	if (millis() < iTimeNextTx)	
		return;
	iTimeNextTx = millis() + SEND_INTERVAL_MS;
	
	// Ask for steer input
	SerialHover2Server oData;
	oData.cStart = START_FRAME;
	oData.iVolt = (uint16_t)	(batteryVoltage * 100);
	oData.iAmpL = (int16_t) 	(currentDC * 100);
	oData.iSpeedL = (int16_t) (realSpeed * 100);
	oData.iOdomL = (int32_t) iOdom;
	
	#ifdef MASTER_OR_SLAVE
		oData.iAmpR = (int16_t) 	(oDataSlave.currentDC * 100);
		oData.iSpeedR = (int16_t) (oDataSlave.realSpeed * 100);
		oData.iOdomR = (int32_t) oDataSlave.iOdom;
	#else
		oData.iAmpR = 0;
		oData.iSpeedR = 0;
		oData.iOdomR = 0;
	#endif
/*	
	oData.iVolt = aDebug[0];
	oData.iAmpL = aDebug[1];
	oData.iAmpR = aDebug[2];
	oData.iSpeedL = aDebug[3];
	oData.iSpeedR = (int16_t) sizeof(SerialServer2Hover);	// speed
*/

/*
	oData.iVolt = aiDebug[0];
	oData.iAmpL = aiDebug[1];
	oData.iAmpR = aiDebug[2];
	oData.iSpeedL = aiDebug[3];
	oData.iSpeedR = aiDebug[4];
	oData.iOdomL = aiDebug[5];
	oData.iOdomR = aiDebug[6];
*/

	// oDataSlave.wState;

	oData.checksum = 	CalcCRC((uint8_t*) &oData, sizeof(oData) - 2);	// (first bytes except crc)

	#ifdef USART0_REMOTE
		SendBuffer(USART0, (uint8_t*) &oData, sizeof(oData));
	#endif
	#ifdef USART1_REMOTE
		SendBuffer(USART1, (uint8_t*) &oData, sizeof(oData));
	#endif



	//oDataSlave.wState = 11;
}

extern uint32_t steerCounter;								// Steer counter for setting update rate


// Update USART steer input
// static int16_t iReceivePos = -1;		// if >= 0 incoming bytes are recorded until message size reached
void RemoteCallback(void)
{
	#ifdef USART0_REMOTE
		uint8_t cRead = usart0_rx_buf[0];
	#endif
	#ifdef USART1_REMOTE
		uint8_t cRead = usart1_rx_buf[0];
	#endif
	//DEBUG_LedSet((steerCounter%20) < 10,0)	// 	
	if (cRead == '/')	// Start character is captured, start record
	{
		iReceivePos = 0;
	}

	if (iReceivePos >= 0)		// data reading has begun
	{
		aReceiveBuffer[iReceivePos++] = cRead;
		if (iReceivePos == sizeof(SerialServer2Hover))
		{
			iReceivePos = -1;
			SerialServer2Hover* pData = (SerialServer2Hover*) aReceiveBuffer;
				
			//memcpy(aDebug,aReceiveBuffer,sizeof(SerialServer2Hover));
			
			//if (1)
			if (pData->checksum == CalcCRC(aReceiveBuffer, sizeof(SerialServer2Hover) - 2))	//  first bytes except crc
			{
				iTimeLastRx = millis();
				//DEBUG_LedSet(SET,0) // 		(steerCounter%2) < 1
					DEBUG_LedSet(SET,0)
				speed = pData->iSpeed;
				steer = pData->iSteer;
				wState = pData->wStateMaster;
				wStateSlave = pData->wStateSlave;
				//if (speed > 300) speed = 300;	else if (speed < -300) speed = -300;		// for testing this function

				ResetTimeout();	// Reset the pwm timout to avoid stopping motors
			}
		}
	}
}

/*
// Update USART steer input
void RemoteUpdateNew(void)	// get rid of this stupid struct __attribute__((packed, aligned(1))) "bug" by not using uint8_t in struct
{
	#ifdef USART0_REMOTE
		uint8_t cRead = usart0_rx_buf[0];
	#endif
	#ifdef USART1_REMOTE
		uint8_t cRead = usart1_rx_buf[0];
	#endif
	aReceiveBuffer[iReceivePos] = cRead;
	//uint8_t cRead = aReceiveBuffer[iReceivePos] = usartSteer_COM_rx_buf[0];
	switch (iReceivePos)
	{
	case 0:	// waiting for first byte of cStart
		if (cRead == (START_FRAME >> 8)	)	
		{
			iReceivePos++;
			//DEBUG_LedSet(RESET,0)
		}
		break;
	case 1:	// expecting second byte of START_FRAME
		if (cRead == (START_FRAME & 0xff)	)	
		{
			iReceivePos++;	// next reading data from 2 on
		}
		else
			iReceivePos--;	// back to 0
		break;
	default:	// data reading has begun
		if (iReceivePos < sizeof(SerialServer2Hover))
			iReceivePos++;	// not yet finished reading
		else
		{
			iReceivePos = 0;	// reading finished, reset iReceivePos for next transmission
			SerialServer2Hover* pData = (SerialServer2Hover*) aReceiveBuffer;
				
			if (1)	// disable checksum for testing ONLY !
			//if (pData->checksum == CalcCRC(aReceiveBuffer, sizeof(SerialServer2Hover) - 2))	//  first bytes except crc
			{
				//DEBUG_LedSet(SET,0) // 		(steerCounter%2) < 1
				speed = pData->iSpeed;
				steer = pData->iSteer;
				iTimeLastRx = millis();

				if (speed > 300) speed = 300;	else if (speed < -300) speed = -300;		// for testing this function

				ResetTimeout();	// Reset the pwm timout to avoid stopping motors
			}
		}
	}
}
*/

#endif

#endif