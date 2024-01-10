#include "../Inc/defines.h"
#include "../Inc/it.h"
#include "../Inc/comms.h"
#include "../Inc/bldc.h"
#include "stdio.h"
#include "string.h"

#ifdef REMOTE_UARTBUS

#pragma pack(1)

// Only master communicates with steerin device
#ifdef MASTER_OR_SINGLE

extern uint8_t usart0_rx_buf[1];
extern uint8_t usart1_rx_buf[1];


static int16_t iReceivePos = 0;	

extern int32_t steer;
extern int32_t speed;
extern uint8_t  wState;
extern uint8_t  wStateSlave;

extern int32_t iOdom;
extern float batteryVoltage; 							// global variable for battery voltage
extern float currentDC; 									// global variable for current dc
extern float realSpeed; 									// global variable for real Speed

typedef struct {			// ´#pragma pack(1)´ needed to get correct sizeof()
   uint8_t cStart;			//  = '/';
   //uint16_t cStart;		//  = #define START_FRAME         0xABCD
   uint8_t  iDataType;  //  0 = unique id for this data struct
   uint8_t iSlave;			//  contains the slave id this message is intended for
   int16_t  iSpeed;
   uint8_t  wState;   // 1=ledGreen, 2=ledOrange, 4=ledRed, 8=ledUp, 16=ledDown   , 32=Battery3Led, 64=Disable, 128=ShutOff
   uint16_t checksum;
} SerialServer2Hover;
typedef struct {			// ´#pragma pack(1)´ needed to get correct sizeof()
   uint8_t cStart;			//  = '/';
   //uint16_t cStart;		//  = #define START_FRAME         0xABCD
   uint8_t  iDataType;  //  1 = unique id for this data struct
   uint8_t 	iSlave;			//  contains the slave id this message is intended for
   int16_t  iSpeed;
   int16_t  iSteer;
   uint8_t  wState;   // 1=ledGreen, 2=ledOrange, 4=ledRed, 8=ledUp, 16=ledDown   , 32=Battery3Led, 64=Disable, 128=ShutOff
   uint8_t  wStateSlave;   // 1=ledGreen, 2=ledOrange, 4=ledRed, 8=ledUp, 16=ledDown   , 32=Battery3Led, 64=Disable, 128=ShutOff
   uint16_t checksum;
} SerialServer2HoverMaster;
typedef struct {			// ´#pragma pack(1)´ needed to get correct sizeof()
   uint8_t cStart;			//  = '/';
   //uint16_t cStart;		//  = #define START_FRAME         0xABCD
   uint8_t  iDataType;  //  2 = unique id for this data struct
   uint8_t 	iSlave;			//  contains the slave id this message is intended for
   float  fBatteryVoltage;	// 10s LiIon = 10*3.6 = 36;
   uint8_t 	iDivemode;			//  0=pwm, 1=speed/10, 3=torque, 4=iOdometer
   uint16_t checksum;
} SerialServer2HoverConfig;

static uint8_t aReceiveBuffer[255];	//sizeof(SerialServer2Hover)

#define START_FRAME         0xABCD       // [-] Start frme definition for reliable serial communication
typedef struct{				// ´#pragma pack(1)´ needed to get correct sizeof()
   uint16_t cStart;
   uint8_t iSlave;		//  the slave id this message is sent from
   int16_t iSpeed;		// 100* km/h
   uint16_t iVolt;		// 100* V
   int16_t iAmp;			// 100* A
   int32_t iOdom;		// hall steps
   uint16_t checksum;
} SerialHover2Server;



//static uint8_t aDebug[sizeof(SerialServer2Hover)];

uint32_t iTimeLastRx = 0;

// Send frame to steer device
void RemoteUpdate(void)
{
	if (millis() - iTimeLastRx > LOST_CONNECTION_STOP_MILLIS)
	{
		speed = steer = 0;
	}
}

extern 	uint32_t steerCounter;

uint32_t iAnswerMaster = 0;

void AnswerMaster(void)
{
	
	// Ask for steer input
	SerialHover2Server oData;
	oData.cStart = START_FRAME;
	oData.iSlave = SLAVE_ID;
	oData.iVolt = (uint16_t)	(batteryVoltage * 100);
	oData.iAmp = (int16_t) 	(currentDC * 100);
	oData.iSpeed = (int16_t) (realSpeed * 100);
	oData.iOdom = (int32_t) iOdom;
	oData.iOdom = iAnswerMaster++;

	oData.checksum = 	CalcCRC((uint8_t*) &oData, sizeof(oData) - 2);	// (first bytes except crc)

	#ifdef USART0_REMOTE
		SendBuffer(USART0, (uint8_t*) &oData, sizeof(oData));
	#endif
	#ifdef USART1_REMOTE
		SendBuffer(USART1, (uint8_t*) &oData, sizeof(oData));
	#endif

}

extern uint32_t steerCounter;								// Steer counter for setting update rate

uint8_t iRxDataType;
uint8_t iRxDataSize;

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
	
	if (iReceivePos < 0)		// data reading not yet begun
	{
		if (cRead == '/')	// Start character is captured, start record
			iReceivePos = 0;
		else	
			return;
	}
	
	aReceiveBuffer[iReceivePos++] = cRead;
	
	if (iReceivePos == 1)	// '/' read
			return;

	if (iReceivePos == 2)	// iDataType read
	{
		iRxDataType = aReceiveBuffer[1];
		switch (iRxDataType)
		{
			case 0: iRxDataSize = sizeof(SerialServer2Hover);	break;
			case 1: iRxDataSize = sizeof(SerialServer2HoverMaster);	break;
			case 2: iRxDataSize = sizeof(SerialServer2HoverConfig);	break;
		}
		return;
	}
	
	if (iReceivePos < iRxDataSize)
		return;
		
		
	//memcpy(aDebug,aReceiveBuffer,sizeof(SerialServer2Hover));
	
	//if (1)
	uint16_t iCRC = (aReceiveBuffer[iReceivePos-1] << 8) | aReceiveBuffer[iReceivePos-2];
	iReceivePos = -1;
	if (iCRC == CalcCRC(aReceiveBuffer, iRxDataSize - 2))	//  first bytes except crc
	{
		if (aReceiveBuffer[2] == SLAVE_ID)
		{
			DEBUG_LedSet(SET,0)
			iTimeLastRx = millis();
			
			switch (iRxDataType)
			{
				case 0:
				{
					SerialServer2Hover* pData = (SerialServer2Hover*) aReceiveBuffer;
					speed = pData->iSpeed;
					wState = pData->wState;
					break;
				}
				case 1: 
				{
					SerialServer2HoverMaster* pData = (SerialServer2HoverMaster*) aReceiveBuffer;
					speed = pData->iSpeed;
					steer = pData->iSteer;
					wState = pData->wState;
					wStateSlave = pData->wStateSlave;
					break;
				}
				case 2: 
				{
					SerialServer2HoverConfig* pData = (SerialServer2HoverConfig*) aReceiveBuffer;
					break;
				}
			}
			
			//if (speed > 300) speed = 300;	else if (speed < -300) speed = -300;		// for testing this function
			AnswerMaster();
			ResetTimeout();	// Reset the pwm timout to avoid stopping motors
		}
	}
}

/* not yet ported from remoteUART

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
				if (speed > 300) speed = 300;	else if (speed < -300) speed = -300;		// for testing this function

				ResetTimeout();	// Reset the pwm timout to avoid stopping motors
			}
		}
	}
}
*/
#endif

#endif