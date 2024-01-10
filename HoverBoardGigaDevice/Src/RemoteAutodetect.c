#include "../Inc/defines.h"
#include "../Inc/it.h"
#include "../Inc/comms.h"
#include "../Inc/bldc.h"
#include "stdio.h"
#include "string.h"

#ifdef REMOTE_AUTODETECT

uint16_t iAutoDetectStage = 0;
uint16_t iAutoDetectStageStep = 0;

uint32_t LED_GREEN = PA15;
uint32_t LED_ORANGE = PA12;
uint32_t LED_RED = PB3;

uint32_t HALL_A	= TODO_PIN;
uint32_t HALL_B	= TODO_PIN;
uint32_t HALL_C	= TODO_PIN;

uint32_t aPinHall[3] = {0,0,0};

uint32_t aPinDigital[COUNT_PinDigital] = 
						{	PC13,PC14,PC15,PF0 ,PF1 ,PA0 ,PA1 ,PA4 ,PA5 ,PA6 ,
							PA7 ,PB0 ,PB1 ,PB2 ,PB10,PB11,PB12,PA11,PF6 ,PF7 ,
							PA12,PA15,PB3,PB4,PB5,PB8,PB9};

const char *aPinName[COUNT_PinDigital] = 
									{	"C13","C14","C15","F0" ,"F1" ,"A0" ,"A1" ,"A4" ,"A5","A6" ,
										"A7" ,"B0" ,"B1" ,"B2" ,"B10","B11","B12","A11","F6","F7" ,
										"A12","A15","B3" ,"B4" ,"B5" ,"B8" ,"B9"};
													
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

char sMessage[255];


//uint32_t iTimeLastRx = 0;
uint32_t iTimeNextTx = 0;

// Send frame to steer device
void RemoteUpdate(void)
{
	speed = 200;
	steer = 0;

/*	if (millis() < iTimeNextTx)	
		return;
	iTimeNextTx = millis() + SEND_INTERVAL_MS;
	
	sprintf(sMessage, "speed: %i\t%.3f V\t%.3f A\r\n",speed,batteryVoltage,currentDC);
	
*/
	if (!strlen(sMessage))
			return;
	
	#ifdef USART0_REMOTE
		SendBuffer(USART0, (uint8_t *)sMessage, strlen(sMessage));
	#endif
	#ifdef USART1_REMOTE
		SendBuffer(USART1, (uint8_t *)sMessage, strlen(sMessage));
	#endif
	
	sMessage[0] = '\0';
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