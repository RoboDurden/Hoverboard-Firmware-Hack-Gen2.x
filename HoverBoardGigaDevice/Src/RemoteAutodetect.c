#include "../Inc/defines.h"
#include "../Inc/it.h"
#include "../Inc/comms.h"
#include "../Inc/bldc.h"
#include "stdio.h"
#include "string.h"

#ifdef REMOTE_AUTODETECT


extern uint32_t msTicks;

													
#pragma pack(1)

// Only master communicates with steerin device

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
	//speed = (msTicks > 500) ? 200 : msTicks * 2 / 5;
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

char cCommand = 0;
char cRxLast = ' ';

// Update USART steer input
void RemoteCallback(void)
{
	#ifdef USART0_REMOTE
		uint8_t cRead = usart0_rx_buf[0];
	#endif
	#ifdef USART1_REMOTE
		uint8_t cRead = usart1_rx_buf[0];
	#endif
	
	if (	(cRead == 13) || (cRead == 10) )
	{
		cCommand = cRxLast;
	}
	else
		cRxLast = cRead;
		
	//sprintf(sMessage, "rx: %c\n",cRead);

	//DEBUG_LedSet((steerCounter%20) < 10,0)	// 	
}



uint32_t HALL_A = TODO_PIN;
uint32_t HALL_B = TODO_PIN;
uint32_t HALL_C = TODO_PIN;





#define COUNT_PinDigital 29
uint8_t iPinCount = COUNT_PinDigital;

typedef struct {
   uint32_t i;
   char*  s;
   uint8_t  wState;   // 1=adc
} PinAD;

#define STATE_ADC 1
#define STATE_HIDE 2

PinAD aoPin[COUNT_PinDigital] = {
		{PC13,"PC13",0}	,{PC14,"PC14",0}	,{PC15,"PC15",0}	,{PF0,"PF0",0}	,{PF1,"PF1",0}		,
		{PA0,"PA0",1}		,{PB11,"PB11",1}		,{PA4,"PA4",1}		,{PA5,"PA5",1}	,{PA6,"PA6",1} 	,
		{PA7,"PA7",1}		,{PB0,"PB0",1}		,{PB1,"PB1",1}		,{PB2,"PB2",0}	,{PB10,"PB10",0}	,
		{PA1,"PA1",0}	,{PB12,"PB12",0}	,{PA11,"PA11",0}	,{PF6,"PF6",0}	,{PF7,"PF7",0} 	,
		{PA12,"PA12",0}	,{PA15,"PA15",0}	,{PB3,"PB3",0}		,{PB4,"PB4",0}	,{PB5,"PB5",0}	,
		{PB6,"PB6",0}		,{PB7,"PB7",0}		,{PB8,"PB8",0}		,{PB9,"PB9",0}	};


const char* sTodoPin = "TODO_PIN";
		
/*
uint32_t aiPinCount[COUNT_PinDigital] = // all possible io pins for GD32 48pin mcu
						{	PC13,PC14,PC15,PF0 ,PF1 ,PA0 ,PA1 ,PA4 ,PA5 ,PA6 ,
							PA7 ,PB0 ,PB1 ,PB2 ,PB10,PB11,PB12,PA11,PF6 ,PF7 ,
							PA12,PA15,PB3,PB4,PB5,PB8,PB9};

char* asPinDigital[COUNT_PinDigital] = 
									{	"C13","C14","C15","F0" ,"F1" ,"A0" ,"A1" ,"A4" ,"A5","A6" ,
										"A7" ,"B0" ,"B1" ,"B2" ,"B10","B11","B12","A11","F6","F7" ,
										"A12","A15","B3" ,"B4" ,"B5" ,"B8" ,"B9"};
*/

const char* GetPinName(uint32_t iPin)
{
	uint8_t i;	
	for (i = 0; i<iPinCount; i++)
	{
		if (aoPin[i].i == iPin)
		{
			return aoPin[i].s;
		}
	}
	return sTodoPin;
}
		
uint8_t HidePinDigital(uint32_t iValue )
{
	if (!iValue)
			return 0;
	uint8_t i;
	for (i = 0; i<iPinCount; i++)
	{
		if (aoPin[i].i == iValue)
		{
			aoPin[i].wState |= STATE_HIDE;
			return 1;
		}
	}	
	return 0;
}

/*
uint8_t RemovePinDigital(uint32_t iValue )
{
	if (!iValue)
			return 0;
	uint8_t i;
	for (i = 0; i<iPinCount; i++)
	{
		if (aoPin[i].i == iValue)
		{
			for (i++; i<iPinCount; i++)
			{
				aoPin[i-1] = aoPin[i];
			}
			iPinCount--;
			//sprintf(sMessage,"new size %i",iPinCount);
			return 1;
		}
	}	
	return 0;
}
*/

void AutodetectInit()
{
	#ifdef HAS_USART0
		HidePinDigital(USART0_TX);
		HidePinDigital(USART0_RX);
	#endif
	#ifdef HAS_USART1
		HidePinDigital(USART1_TX);
		HidePinDigital(USART1_RX);
	#endif
}

uint16_t iStage = 0;		// main stages like hall pin detect, led pin detect, etc.
uint16_t iStageOld = -1;

uint32_t msTicksTest;
uint8_t iTest = 0;		// an index pointer testing different positbilities
uint8_t iTestPin = 0;	// a pin variable used while testing
uint8_t iRepeat = 0;	// a counter to repeat before some finding is accepted

void AutoDetectSetStage(uint8_t iSet)
{
	iTest = iRepeat = 0;
	iTestPin = 0;
	iStage = iSet;
	msTicksTest = msTicks + 500;	// to allow sMessage of last stage to be sent via serial
	
}
void AutoDetectNextStage()
{
	AutoDetectSetStage(iStage+1);
}


const char* asScan[8] = {"LED_GREEN","LED_ORANGE","LED_RED","UPPER_LED","LOWER_LED","BUZZER","VBATT","CURRENT_DC"};
uint32_t aiPinScan[8] = {0,0,0,0,0,0,0,0};		// the found led pins: red , orange , green, up , down

int8_t iMove = +1;
uint8_t SetNextTestPin()
{
	if (!iMove)	return 1;
			
	uint8_t iTestOld = iTest;
	do
	{
		if (iMove > 0)
			iTest = (iTest + iMove) % iPinCount;		// try next io pin for this hall position
		else if (iTest == 0)
				iTest = iPinCount-1;
		else
			iTest--;
		
		if (iTest == iTestOld) 
			return 0;	// one loop and no pin found -> exit
		if (aoPin[iTest].wState & STATE_HIDE)
				continue;
		if (	(iStage == AUTODETECT_Stage_Led) || (aoPin[iTest].wState & STATE_ADC))
			return 1;	// Stage_Led accepts any io pin, stage_Adc only adc-pins
		
	} while (1);
}

void ScanInit(uint8_t iTestNew)
{
	iTest = iTestNew;
	uint8_t i;
	for (i=0;i<iPinCount; i++)	
		if (!(aoPin[i].wState & STATE_HIDE))
			pinMode(aoPin[i].i,GPIO_MODE_INPUT);

	uint32_t iPinNew = aoPin[iTest].i;
	if (iStage == AUTODETECT_Stage_Led)
	{
		pinMode(iPinNew,GPIO_MODE_OUTPUT);
		msTicksTest = msTicks + 1000;
	}
	else
	{
		if ((aoPin[iTest].wState & STATE_ADC) == 0)	// this is not an adc pin
		{
			if (!SetNextTestPin())	// will find next adc pin
			{
				AutoDetectNextStage();	// no more adc pins left
				return;
			}
		}
		pinMode(iPinNew, GPIO_MODE_ANALOG);
		adc_regular_channel_config(0, PIN_TO_CHANNEL(iPinNew), ADC_SAMPLETIME_13POINT5);
		msTicksTest = msTicks + (iStage == AUTODETECT_Stage_VBatt ? 2000 : 8000);
	}
}



void ScanList()
{
	if (iStage == AUTODETECT_Stage_Led)
	{
		sprintf(sMessage, "#define LED_RED\t\t%s\n#define LED_ORANGE\t%s\n#define LED_GREEN\t%s\n#define UPPER_LED\t%s\n#define LOWER_LED\t%s\n#define BUZZER\t%s\n"
				,	GetPinName(aiPinScan[0]),	GetPinName(aiPinScan[1]),	GetPinName(aiPinScan[2]),	GetPinName(aiPinScan[3]),	GetPinName(aiPinScan[4]),	GetPinName(aiPinScan[5])	);
	}
	else
	{
		sprintf(sMessage, "\n#define VBATT\t\t%s\n#define CURRENT_DC\t%s\n"
				,	GetPinName(aiPinScan[6]),	GetPinName(aiPinScan[7]));
	}
		
}


extern float currentDC;
extern int16_t bldc_outputFilterPwm;
extern adc_buf_t adc_buffer;
float fVBatt;
float fCurrentDC;
int16_t iOffsetDC;

void AutodetectScan(uint16_t buzzerTimer)
{
	uint8_t i;
	
	if (iStage == AUTODETECT_Stage_Finished)
	{
		SetPWM(0);
		return;
	}
	
	uint8_t iFrom,iTo;
	if (iStage == AUTODETECT_Stage_Led)
	{
		iFrom = 0; iTo = 6;
	}
	else if (iStage == AUTODETECT_Stage_VBatt)
	{
		iFrom = 6; iTo = 7;
	}
	else
	{
		iFrom = 7; iTo = 8;
	}
		
	
	// AUTODETECT_Stage_Led or AUTODETECT_Stage_VBatt or AUTODETECT_Stage_CurrentDC
	if (	(iStage >= AUTODETECT_Stage_Led) && (iStage <= AUTODETECT_Stage_CurrentDC)	)
	{
		SetPWM(-200);
		
		if (iStageOld != iStage)
		{
			if (msTicksTest > msTicks)	// wait for last sMessage to be sent
				return;
			iStageOld = iStage;
			
			//for (i=iFrom;i<iTo;i++)	aiPinScan[i] = 0; 

			if (iStage == AUTODETECT_Stage_Led)
			{
				sprintf(sMessage,"'r'=red,\t'o'=orange,\t'g'=green,\t'u'=up,\t'd'=down,\t'b'=buzzer");
			}
			else if (iStage == AUTODETECT_Stage_VBatt)
			{
				sprintf(sMessage,"'f'=battery voltage");
			}
			else
			{
				sprintf(sMessage,"'f'=current DC");
			}
				
			sprintf(sMessage,"%s\nRET to pause,\t'-' to toggle direction,\t'l' to list\n'c' to reset, 'x' to delete and 's' when finished.\n",sMessage);
			
			ScanInit(0);
			return;	// to allow sMessage to be sent
		}
		
		int8_t iFound = -1;
		uint8_t bCommand = 2;	// decremented to 0 if the two switch sections have no case
		if (iStage == AUTODETECT_Stage_Led)
		{
			digitalWrite(aoPin[iTest].i,(msTicks%4)>0 ? 1 : 0);	// 250 Hz 75% pwm ratio
			switch(cCommand)
			{
			case 'r': iFound = 0; break;
			case 'o': iFound = 1; break;
			case 'g': iFound = 2; break;
			case 'u': iFound = 3; break;
			case 'd': iFound = 4; break;
			case 'b': iFound = 5; break;
			default : bCommand--;
			}
		}
		else if (iStage == AUTODETECT_Stage_VBatt)
		{
			fVBatt = fVBatt * 0.99 + ((float)adc_buffer.v_batt * ADC_BATTERY_VOLT) * 0.01;
			if (buzzerTimer % 16000 == 0)	// 16 kHz
				sprintf(sMessage,"%s: VBATT ?= %.2f\n",aoPin[iTest].s,fVBatt);
			
			switch(cCommand)
			{
			case 'f': iFound = 6; msTicksTest = 0; break;
			default : bCommand--;
			}
		}
		else // AUTODETECT_Stage_CurrentDC
		{
			uint16_t iTime = msTicksTest-msTicks;
			if (iTime>6000)
			{
				SetPWM(0);
				if (iTime>7500)	// wait 0,5s to let the motor stop
				{
					iOffsetDC = 2000;	// reset 
				}
				else
					iOffsetDC = (adc_buffer.v_batt + iOffsetDC) / 2;
			}
			else
			{
				SetPWM(-700);	// strong motor to see a load when hand on motor
				fCurrentDC = ABS((adc_buffer.v_batt - iOffsetDC) * MOTOR_AMP_CONV_DC_AMP);
				if (buzzerTimer % 16000 == 0)	// 16 kHz
					sprintf(sMessage,"%s: CURRENT_DC ?= %.2f\t\n",aoPin[iTest].s,fCurrentDC);
				
			}
			switch(cCommand)
			{
			case 'f': iFound = 7; msTicksTest = 0; break;
			default : bCommand--;
			}
			
		}

		switch(cCommand)
		{
		case 'l': ScanList(); break;
		case ' ': 
			if (!iMove)
			{
				iMove=1; sprintf(sMessage, "continue\n");
			}
			else
			{
				iMove=0; sprintf(sMessage, "pause\n");
			}
			break;
		case '-': iMove *= -1; sprintf(sMessage, "direction: %i\n",iMove); break;
		case 'x': HidePinDigital(aoPin[iTest].i); msTicksTest = 0; break;
		case 'c': 
			for (i=iFrom;i<iTo;i++)	aiPinScan[i] = 0; 
				
			iMove = +1;
			ScanInit(0);
			sprintf(sMessage, "all pins cleared.");
			break;
		case 's': 
				ScanList();
				for (i=iFrom;i<iTo;i++)	HidePinDigital(aiPinScan[i]); 
				AutoDetectNextStage();
				break;
		default : bCommand--;
		}
		
		if (bCommand) 
		{
			cCommand = 0;
			cRxLast = ' ';	// so a single return will pause/unpause
		}
		
		if (iFound >= 0)
		{
			aiPinScan[iFound] = aoPin[iTest].i;
			sprintf(sMessage, "%s = %s\n",	asScan[iFound],GetPinName(aoPin[iTest].i)	);
		}
		else if (msTicks > msTicksTest)
		{
			if (SetNextTestPin())
			{
				ScanInit(iTest);
				sprintf(sMessage, "try %s\n",aoPin[iTest].s);
			}
			else
			{
				AutoDetectNextStage();
				sprintf(sMessage, "now stage %i\n",iStage);
			}
		}
	}
}



uint32_t aPinHall[3] = {0,0,0};		// the found hall pins (aoPin will map to PA1, etc
uint8_t aHallOrder[6][3] = {{0,2,1},{2,0,1},{0,1,2},{1,2,0},{1,0,2},{2,1,0}};	// possible permutations to test

	

uint8_t bHallOld = 2;
//uint8_t iHall = 0;


uint32_t msTicksAuto = 0;
uint8_t posAuto = 1;
uint8_t posOld = 0;
uint32_t msTicksOld;



void AutoDetectHallInit()
{
	pinMode(aoPin[iTest].i,GPIO_MODE_INPUT);
	msTicksTest = msTicks + 1000;
	msTicksOld = 0;
	iRepeat = 0;
}
void AutoDetectHallOrderInit(uint8_t iTestSet)	// iTestSet = 0..5 = 6 possible permutations
{
	iTest = iTestSet;
	
	HALL_A = aoPin[ aPinHall[ aHallOrder[iTest][0] ] ].i;
	HALL_B = aoPin[ aPinHall[ aHallOrder[iTest][1] ] ].i;
	HALL_C = aoPin[ aPinHall[ aHallOrder[iTest][2] ] ].i;

	msTicksTest = msTicks + 1000;
	msTicksOld = 0;
	iRepeat = 0;
}



uint8_t AutodetectBldc(uint8_t posNew)
{
		if (iStage > AUTODETECT_Stage_HallOrder)	// simulate hall 
		{
			return posNew;
		}

		SetPWM(msTicks > 500 ? -200 : (int32_t)msTicks * -2 / 5);
		
		if (msTicks - msTicksAuto >= 15)
		{
			posAuto++;
			if (posAuto == 7)	posAuto = 1;
			//pos = posAuto;
			msTicksAuto = msTicks;
		}
		
		// AUTODETECT_Stage_Startup
		if (	(iStage == AUTODETECT_Stage_Startup) && (msTicks > 1000)	)
		{
			AutoDetectNextStage();
		}
		
		// AUTODETECT_Stage_Hall
		if (iStage == AUTODETECT_Stage_Hall)		// find the three hall pins :-)
		{
			if (iStageOld != iStage)
			{
				AutoDetectHallInit();
				iStageOld = iStage;
			}
			
			uint8_t bHall = digitalRead(aoPin[iTestPin].i);
			if (bHall != bHallOld)
			{
				if (!bHall)	// rotor has left the hall sensor
				{
					uint16_t iTime = msTicks-msTicksOld;
					if (	(iTime > 2) && (iTime < 7)	)	// the hall on-time should match the rotation speed
					{
						if (5 == iRepeat++)
						{
							aPinHall[iTest] = iTestPin;
							//sprintf(sMessage, "hall %i=%i : %i ms\n",iTest,iTestPin,iTime);
							sprintf(sMessage, "hall %i = %s : %i ms\n",iTest,aoPin[iTestPin].s,iTime);
							
							iTest++;	// next hall sensor
							if (iTest < 3)
							{
								iTestPin++;
								if (iTestPin < iPinCount)
								{
									AutoDetectHallInit();
								}
								else
								{
									AutoDetectSetStage(AUTODETECT_Stage_Startup);	// no more io pins to test :-/
								}
							}
							else	// finished with this stage
							{
								AutoDetectNextStage();
								//sprintf(sMessage, "%i,%i,%i\n",HALL_A,HALL_B,HALL_C);

							}
						}
					}
					else
					{
						//if (	(iTime > 1) && (iTime < 50)	)	// the hall on-time should match the rotation speed							
						//	sprintf(sMessage, "hall %i,%i : %i ms\n",iTest,iTestPin,iTime);
						iRepeat = 0;
					}
				}
				bHallOld  = bHall;
				msTicksOld = msTicks;
			}
			else if (msTicks > msTicksTest)
			{
				iTestPin++;		// try next io pin for this hall position
				if (iTestPin < iPinCount)
				{
					//sprintf(sMessage, "%i try %i\n",iTest,iTestPin);
					sprintf(sMessage, "%i try %i = %s\n",iTest,iTestPin,aoPin[iTestPin].s);
					AutoDetectHallInit();
				}
				else
				{
					AutoDetectSetStage(AUTODETECT_Stage_Startup);	// no more io pins to test :-/
				}
			}
			
			if (posAuto != posOld)
			{
				posOld = posAuto;
				msTicksOld = msTicks;
			}
			return posAuto;
		}
		
		// AUTODETECT_Stage_HallOrder
		if (iStage == AUTODETECT_Stage_HallOrder)
		{
			if (iStageOld != iStage)
			{
				AutoDetectHallOrderInit(0);
				iStageOld = iStage;
			}
			
			if (posNew != posOld)
			{
				//sprintf(sMessage, "%i != %i\n",posNew,posOld);
				if (	(posOld == posAuto) && 
							(	((posOld == 6) && (posNew == 1)) || (posNew == posOld+1) )
						)	// valid hall input
				{
					if (20 < iRepeat++)
					{
						uint16_t iTime = msTicks-msTicksOld;
						
						
						//sprintf(sMessage, "hall oder: %i = %i,%i,%i\n",iTest,aHallOrder[iTest][0],aHallOrder[iTest][1],aHallOrder[iTest][2]);
						sprintf(sMessage, "hall oder %i :\n#define HALL_A = %s\n#define HALL_B = %s\n#define HALL_C = %s\n",iTest
							, aoPin[aPinHall[ aHallOrder[iTest][0] ] ].s
							, aoPin[aPinHall[ aHallOrder[iTest][1] ] ].s
							, aoPin[aPinHall[ aHallOrder[iTest][2] ] ].s	);
						//sprintf(sMessage, " auto %i: %i %i\n",posAuto,posOld,posNew);

						uint8_t i;
						for (i=0; i<3; i++)	HidePinDigital(aoPin[aPinHall[i]].i);
						
						
						//iStage++;
						AutoDetectNextStage();
					}
				}
				else
				{
					iRepeat = 0;
					if (msTicks > msTicksTest)
					{
						if (iTest < 5)
						{
							sprintf(sMessage, "wrong oder %i\n",iTest);
							AutoDetectHallOrderInit(iTest+1);	// test next permutation
						}
						else
						{
							sprintf(sMessage, "no hall oder found: %i\n",iTest);
							AutoDetectSetStage(AUTODETECT_Stage_Startup);	// no more hall permutations to test :-/
						}
					}
				}
				posOld = posNew;
				msTicksOld = msTicks;
			}
		}
		return posAuto;
}

#endif
