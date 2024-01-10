// improved and unified serial communication by Robo Durden :-)
#include "../Inc/defines.h"
#include "../Inc/it.h"
#include "../Inc/comms.h"
#include "../Inc/commsMasterSlave.h"
#include "../Inc/bldc.h"
#include "stdio.h"
#include "string.h"

FlagStatus mosfetOutMaster = RESET;
FlagStatus beepsBackwardsMaster = RESET;

//----------------------------------------------------------------------------
// Send buffer via USART
//----------------------------------------------------------------------------
void SendBuffer(uint32_t usart_periph, uint8_t buffer[], uint8_t length)
{
	uint8_t index = 0;
	
	for(; index < length; index++)
	{
    usart_data_transmit(usart_periph, buffer[index]);
    while (usart_flag_get(usart_periph, USART_FLAG_TC) == RESET) {}
	}
}

//----------------------------------------------------------------------------
// Calculate CRC
//----------------------------------------------------------------------------
uint16_t CalcCRC(uint8_t *ptr, int count)
{
  uint16_t  crc;
  uint8_t i;
  crc = 0;
  while (--count >= 0)
  {
    crc = crc ^ (uint16_t) *ptr++ << 8;
    i = 8;
    do
    {
      if (crc & 0x8000)
      {
        crc = crc << 1 ^ 0x1021;
      }
      else
      {
        crc = crc << 1;
      }
    } while(--i);
  }
  return (crc);
}



// Sets beepsBackwards value which will be send to master
void SetBeepsBackwardsMaster(FlagStatus value)
{
	beepsBackwardsMaster = value;
}

// Returns beepsBackwardsMaster value sent by master
FlagStatus GetBeepsBackwardsMaster(void)
{
	return beepsBackwardsMaster;
}


#ifdef MASTER_OR_SLAVE

#pragma pack(1)

	typedef struct {			// �#pragma pack(1)� needed to get correct sizeof()
		uint8_t cStart;		//  = '/';
		uint8_t	wState;
		float currentDC; 									// global variable for current dc
		float realSpeed; 									// global variable for real Speed
		int32_t iOdom;	
		uint16_t checksum;
	} SerialSlave2Master;

	typedef struct {			// �#pragma pack(1)� needed to get correct sizeof()
		uint8_t cStart;		//  = '/';
		int16_t	iPwmSlave;
		uint8_t	wState;
		uint16_t checksum;
	} SerialMaster2Slave;



#ifdef MASTER
	#define SerialReceive SerialSlave2Master
	#define SerialSend SerialMaster2Slave

	// Variables which will be written by slave frame
	extern FlagStatus beepsBackwards;
	extern DataSlave oDataSlave;
	extern uint8_t  wStateSlave;
	
	
#else
	#define SerialReceive SerialMaster2Slave
	#define SerialSend SerialSlave2Master

	extern float currentDC; 									// global variable for current dc
	extern float realSpeed; 									// global variable for real Speed
	extern int32_t iOdom;
	extern uint8_t  wState;   // 1=ledGreen, 2=ledOrange, 4=ledRed, 8=ledUp, 16=ledDown   , 32=Battery3Led, 64=Disable, 128=ShutOff
	extern int16_t pwmSlave;


	void CheckGeneralValue(uint8_t identifier, int16_t value);
#endif

extern uint8_t usart0_rx_buf[1];
extern uint8_t usart1_rx_buf[1];
//extern uint8_t usartMasterSlave_rx_buf[USART_MASTERSLAVE_RX_BUFFERSIZE];

void SendBuffer(uint32_t usart_periph, uint8_t buffer[], uint8_t length);
uint16_t CalcCRC(uint8_t *ptr, int count);

//----------------------------------------------------------------------------
// Update USART master slave input
//----------------------------------------------------------------------------


static uint8_t aReceiveBuffer[sizeof(SerialReceive)];
static int16_t iReceivePos = -1;		// if >= 0 incoming bytes are recorded until message size reached
void ProessReceived(SerialReceive* pData);
//int16_t swap_int16( int16_t val ) 	{	return (val << 8) | ((val >> 8) & 0xFF);	}

// Update USART steer input
void UpdateUSARTMasterSlaveInput(void)
{
	
	//uint8_t cRead = usartMasterSlave_rx_buf[0];
	#ifdef USART0_MASTERSLAVE
		uint8_t cRead = usart0_rx_buf[0];
	#endif
	#ifdef USART1_MASTERSLAVE
		uint8_t cRead = usart1_rx_buf[0];
	#endif
	
	if (cRead == '/')	// Start character is captured, start record
		iReceivePos = 0;

	if (iReceivePos >= 0)		// data reading has begun
	{
		aReceiveBuffer[iReceivePos++] = cRead;
		if (iReceivePos == sizeof(SerialReceive))
		{
			iReceivePos = -1;
			
			SerialReceive* pData = (SerialReceive*) aReceiveBuffer;
			if ( pData->checksum == CalcCRC(aReceiveBuffer, sizeof(SerialReceive) - 2))	// first bytes except crc
			{
				ProessReceived(pData);
			}
		}
	}
}

void ProessReceived(SerialReceive* pData)
{
#ifdef MASTER
	// Result variables
	//FlagStatus upperLED = RESET;
	//FlagStatus lowerLED = RESET;
	//FlagStatus mosfetOut = RESET;
	
	// Auxiliary variables
	uint8_t byte;
#else
	// Result variables
	//int16_t pwmSlave = 0;
	FlagStatus enable = RESET;
	FlagStatus shutoff = RESET;
	FlagStatus chargeStateLowActive = SET;
	
	// Auxiliary variables
	uint8_t identifier = 0;
	int16_t value = 0;
	uint8_t byte;
#endif
	// Auxiliary variables
	uint16_t crc;
	
	
#ifdef MASTER

	// old protocol not yet ported :-/
	//beepsBackwards = (pData->wState & BIT(3)) ? SET : RESET;
	//mosfetOut = (pData->wState & BIT(2)) ? SET : RESET;

	oDataSlave.wState 	= pData->wState;	// = 17;
	oDataSlave.currentDC = pData->currentDC;
	oDataSlave.realSpeed = pData->realSpeed;
	oDataSlave.iOdom 		= pData->iOdom;

	// Set functions according to the variables
	//digitalWrite(UPPER_LED, upperLED);
	//digitalWrite(LOWER_LED, lowerLED);
	//digitalWrite(MOSFET_OUT, mosfetOut);
	//gpio_bit_write(MOSFET_OUT_PORT, MOSFET_OUT_PIN, mosfetOut);
	//gpio_bit_write(UPPER_LED_PORT, UPPER_LED_PIN, upperLED);
	//gpio_bit_write(LOWER_LED_PORT, LOWER_LED_PIN, lowerLED);

#else

	pwmSlave = CLAMP(pData->iPwmSlave,-1000,1000);
	wState = pData->wState;
	
	// Send answer
	
	//SendMaster(upperLEDMaster, lowerLEDMaster, mosfetOutMaster, beepsBackwardsMaster);
	SendMaster(GetUpperLEDMaster(), GetLowerLEDMaster(), mosfetOutMaster, beepsBackwardsMaster);
	
	// Reset the pwm timout to avoid stopping motors
	ResetTimeout();
#endif
}


#ifdef MASTER

void SendSlave(int16_t pwmSlave)
{
	SerialSend oData;
	oData.cStart 	= '/';
	oData.iPwmSlave 	= CLAMP(pwmSlave, -1000, 1000);
	oData.wState 			= wStateSlave;	//sendByte;
	
	oData.checksum = 	CalcCRC((uint8_t*) &oData, sizeof(oData) - 2);	// (first bytes except crc)
	SendBuffer(USART_MASTERSLAVE, (uint8_t*) &oData, sizeof(oData));
	//oDataSlave.wState = 11;
}

#else	// SLAVE

void SendMaster(FlagStatus upperLEDMaster, FlagStatus lowerLEDMaster, FlagStatus mosfetOutMaster, FlagStatus beepsBackwards)
{
	uint8_t sendByte = 0;
	sendByte |= (0 << 7);
	sendByte |= (0 << 6);
	sendByte |= (0 << 5);
	sendByte |= (0 << 4);
	sendByte |= (beepsBackwards << 3);
	sendByte |= (mosfetOutMaster << 2);
	sendByte |= (lowerLEDMaster << 1);
	sendByte |= (upperLEDMaster << 0);

	SerialSend oData;
	oData.cStart 	= '/';
	oData.wState 			= sendByte;
	oData.currentDC = currentDC;
	oData.realSpeed = realSpeed;
	oData.iOdom = iOdom;
	
	oData.checksum = 	CalcCRC((uint8_t*) &oData, sizeof(oData) - 2);	// (first bytes except crc)
	SendBuffer(USART_MASTERSLAVE, (uint8_t*) &oData, sizeof(oData));
}




//----------------------------------------------------------------------------
// Sets mosfetOut value which will be send to master
//----------------------------------------------------------------------------
void SetMosfetOutMaster(FlagStatus value)
{
	mosfetOutMaster = value;
}

//----------------------------------------------------------------------------
// Returns MosfetOut value sent by master
//----------------------------------------------------------------------------
FlagStatus GetMosfetOutMaster(void)
{
	return mosfetOutMaster;
}

#endif

#endif