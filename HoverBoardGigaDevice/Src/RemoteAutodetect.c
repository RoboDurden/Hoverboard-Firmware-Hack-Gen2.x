#include "../Inc/defines.h"
#include "../Inc/it.h"
#include "../Inc/comms.h"
#include "../Inc/bldc.h"
#include "stdio.h"
#include "string.h"

#ifdef REMOTE_AUTODETECT


extern uint32_t msTicks;

char asStage[9][10] = {"do all","VBatt","Hold","Button","Led","Hall","HallOrder","CurrentDc","Results"};
uint16_t wMenuStage = MENU_INIT;
													
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

typedef struct {
   uint32_t i;
   char*  s;
   uint8_t  wState;   // 1=adc
   int16_t  iAdc;  
} PinAD;

#define STATE_ADC 1
#define STATE_HIDE 2
#define STATE_OFF 4
#define STATE_OFF2 8
#define STATE_ON 16
#define STATE_ON2 32

//#define TEST

#ifdef TEST
	#define COUNT_PinDigital 22
	PinAD aoPin[COUNT_PinDigital] = {	// 2.13 pins removed for testing: led + buzzer + vbatt + currentDC
			{PC14,"C14",0}	,{PF1,"F1",0}		,{PB11,"B11",1}	,{PF0,"F0",0}		, 
			{PA5,"A5",1} 		, {PC13,"C13",0}	 ,{PC15,"C15",0}	,
			{PA7,"A7",1}		,{PB0,"B0",1}		,{PB1,"B1",1}		,{PB2,"B2",0}	,{PB10,"B10",0}	,
			{PB12,"B12",0}	,{PA11,"A11",0}	,{PF6,"F6",0}	,{PF7,"F7",0} 	,
			{PB4,"B4",0}		,{PB5,"B5",0}		,
			{PB6,"B6",0}		,{PB7,"B7",0}		,{PB8,"B8",0}		,{PB9,"B9",0}	};
#else

	#ifdef GD32F103	// no PF0 and PF1 on 48 pin package
		#define COUNT_PinDigital 29
		PinAD aoPin[COUNT_PinDigital] = {
				{PC13,"C13",0}	,{PC14,"C14",0}	,{PC15,"C15",0}			,
				{PA0,"A0",1}		,{PB11,"B11",0}		,{PA4,"A4",1}		,{PA5,"A5",1}	,{PA6,"A6",1} 	,
				{PA7,"A7",1}		,{PB0,"B0",1}		,{PB1,"B1",1}		,{PB2,"B2",0}	,{PB10,"B10",0}	,
				{PA1,"A1",1}	,{PB12,"B12",0}	,{PA11,"A11",0}	,{PF6,"F6",0}	,{PF7,"F7",0} 	,
				{PA12,"A12",0}	,{PA15,"A15",0}	,{PB3,"B3",0}		,{PB4,"B4",0}	,{PB5,"B5",0}	,
				{PB6,"B6",0}		,{PB7,"B7",0}		,{PB8,"B8",0}		,{PB9,"B9",0}	,{PA2,"A2",1}	,
				{PA3,"A3",1}
				};

	#else
		#define COUNT_PinDigital 31
		PinAD aoPin[COUNT_PinDigital] = {
				{PC13,"C13",0}	,{PC14,"C14",0}	,{PC15,"C15",0}	,{PF0,"F0",0}	,{PF1,"F1",0}		,
				{PA0,"A0",1}		,{PB11,"B11",0}		,{PA4,"A4",1}		,{PA5,"A5",1}	,{PA6,"A6",1} 	,
				{PA7,"A7",1}		,{PB0,"B0",1}		,{PB1,"B1",1}		,{PB2,"B2",0}	,{PB10,"B10",0}	,
				{PA1,"A1",1}	,{PB12,"B12",0}	,{PA11,"A11",0}	,{PF6,"F6",0}	,{PF7,"F7",0} 	,
				{PA12,"A12",0}	,{PA15,"A15",0}	,{PB3,"B3",0}		,{PB4,"B4",0}	,{PB5,"B5",0}	,
				{PB6,"B6",0}		,{PB7,"B7",0}		,{PB8,"B8",0}		,{PB9,"B9",0}	,{PA2,"A2",1}	,
				{PA3,"A3",1}
				};
	#endif
#endif


#define PINS_DETECT 18
const char* asScan[PINS_DETECT] = {"HALL_A","HALL_B","HALL_C","PHASE_A","PHASE_B","PHASE_C","LED_RED","LED_ORANGE","LED_GREEN","UPPER_LED","LOWER_LED","ONBOARD_LED","BUZZER","VBATT","CURRENT_DC","SELF_HOLD","BUTTON","BUTTON_PU"};
uint32_t aiPinScan[PINS_DETECT] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};		// the found pins

uint8_t HidePinDigital(uint32_t iValue )
{
	if (!iValue)
			return 0;
	uint8_t i;
	for (i = 0; i<COUNT_PinDigital; i++)
	{
		if (aoPin[i].i == iValue)
		{
			aoPin[i].wState |= STATE_HIDE;
			return 1;
		}
	}	
	return 0;
}

const char* sTodoPin = "??";
const char* GetPinName(uint32_t iPin)
{
	uint8_t i;	
	for (i = 0; i<COUNT_PinDigital; i++)
	{
		if (aoPin[i].i == iPin)
		{
			return aoPin[i].s;
		}
	}
	return sTodoPin;
}

void ListFound(uint8_t iFrom, uint8_t iTo)
{
	uint8_t i;
	bMessageWait = 1;
	sprintf(sMessage,"\r\n");
	for (i=iFrom; i<iTo; i++)
		sprintf(sMessage,"%s%s#define %s\t\tP%s\r\n",sMessage,(aiPinScan[i] ? "" : "//"),asScan[i],GetPinName(aiPinScan[i]));

	bMessageWait = 0;
}

	
typedef struct {			// ´#pragma pack(1)´ needed to get correct sizeof()
  uint8_t cStart;		//  = '/';
	uint8_t wCmd;
}	HeaderData;

enum{	DATA_None=0, DATA_Request=1, DATA_Save=2};
HeaderData oDataHeader = {0x01,DATA_Request};	// wenn autodetect.ino receives 0x01 it stores the incoming data or returns it's storage


uint8_t bMessageWait = 0;
char sMessage[512];


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
	if (oDataHeader.wCmd)
	{
		#ifdef USART_REMOTE
			//oDataHeader.wCmd = 42;
			SendBuffer(USART_REMOTE, (uint8_t *)&oDataHeader, sizeof(oDataHeader));
			//if (oDataHeader.wCmd>DATA_Request)
			{
				SendBuffer(USART_REMOTE, (uint8_t *)aiPinScan, sizeof(aiPinScan));
			}
		#endif
		oDataHeader.wCmd = DATA_None;
		return;
	}
	
	if (!strlen(sMessage) || bMessageWait)
			return;
	
	#ifdef USART_REMOTE
		SendBuffer(USART_REMOTE, (uint8_t *)sMessage, strlen(sMessage));
	#endif
	
	sMessage[0] = '\0';
}

char cCommand = 0;
char cRxLast = ' ';

HeaderData oHeaderRx;
uint8_t aBufferData[sizeof(oHeaderRx)+sizeof(aiPinScan)];
uint8_t iBufferData = 0;

void AutoDetectHallOrderInit(uint8_t iTestSet);

// Update USART steer input
void RemoteCallback(void)
{
	#ifdef USART0_REMOTE
		uint8_t cRead = usart0_rx_buf[0];
	#endif
	#ifdef USART1_REMOTE
		uint8_t cRead = usart1_rx_buf[0];
	#endif
	
	if (iBufferData>0)
	{
		aBufferData[iBufferData++] = cRead;
		if (iBufferData == sizeof(aBufferData))
		{
			memcpy(	((uint8_t*)&oHeaderRx), aBufferData, sizeof(oHeaderRx)	);
			memcpy(	(uint8_t*)aiPinScan, aBufferData+sizeof(oHeaderRx), sizeof(aiPinScan)	); 
			
			if (aiPinScan[SCAN_SELF_HOLD])
			{
				wMenuStage |= AUTODETECT_Stage_Button;
				ListFound(SCAN_SELF_HOLD,SCAN_SELF_HOLD+1);
			}
			if (aiPinScan[SCAN_HALL_A] && aiPinScan[SCAN_HALL_B] && aiPinScan[SCAN_HALL_C])
			{
				wMenuStage |= AUTODETECT_Stage_HallOrder|AUTODETECT_Stage_CurrentDC;
				AutoDetectHallOrderInit(0);				
			}
			uint8_t i;
			for (i=0; i<=SCAN_BUTTON_PULLUP; i++)
			{
				if (aiPinScan[i])
				{
					HidePinDigital(aiPinScan[i]);
				}
			}
			iBufferData = 0;
			//ListFound(0,3);
		}
		//else	sprintf(sMessage, "iBufferData: %i = %i\r\n",iBufferData,sizeof(aBufferData));
		return;
	}
	else if (cRead == 0x01)	// incoming HeaderData + aiPinScan
	{
		iBufferData = 1;	   // 0x01 at 0 already read
		return;
	}
	
	
	if (	(cRead == 13) || (cRead == 10) )
	{
		cCommand = cRxLast;
	}
	else
		cRxLast = cRead;
		
	//sprintf(sMessage, "rx: %c\r\n",cRead);

	//DEBUG_LedSet((steerCounter%20) < 10,0)	// 	
}



uint32_t HALL_A = TODO_PIN;
uint32_t HALL_B = TODO_PIN;
uint32_t HALL_C = TODO_PIN;






			
			
		


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

	//adc_regular_channel_config(1, ADC_CHANNEL_18, ADC_SAMPLETIME_13POINT5);	// ADC_CHANNEL_18 = VBAT
		// at AUTODETECT_Stage_Hold the minimal VBAT=ADC_CHANNEL_18 value iVBatMin will be needed..
}

uint16_t wStage = AUTODETECT_Stage_Startup;		// main stages like hall pin detect, led pin detect, etc.
uint16_t wStageOld = -1;

uint32_t msTicksTest,msTicksWait,msTicksTestNext;
uint8_t iTest = 0;		// an index pointer testing different positbilities
uint8_t iTestPin = 0;	// a pin variable used while testing
int8_t iTestStart = -1;		// an index pointer to the first pin tested in a stage
//int8_t iTestInitOld = -1;

uint8_t iRepeat = 0;	// a counter to repeat before some finding is accepted
int16_t iAverage = 0;	// a variable to averarge over some reading
int16_t iAverageMax = -32767;	// a variable to stor the maximun averarge 
uint8_t iPhaseCurrent = 0;	// an index for the phase current detected

void AutoDetectSetStage(uint16_t iSet)
{
	iTest = iRepeat = iPhaseCurrent = 0;
	iTestPin = 0;
	//iTestInitOld = -1;
	wStage = iSet;
	msTicksWait = msTicks + 300;	// to allow sMessage of last stage to be sent via serial
	
}

uint8_t bReturnToMenu = 0;
void AutoDetectNextStage()
{
	if (wStage >= AUTODETECT_Stage_Finished)
		bReturnToMenu = 1;
	AutoDetectSetStage(bReturnToMenu ? AUTODETECT_Stage_Menu : wStage<<1);
}



uint8_t aHallOrder[6][3] = {{0,1,2},{0,2,1},{1,0,2},{2,0,1},{1,2,0},{2,1,0}};	// possible permutations to test


uint8_t SetNextTestPin()
{
	//if (!iMove)	return 1;
			
	uint8_t iTestOld = iTest;
	do
	{
		iTest = (iTest + 1) % COUNT_PinDigital;		// try next io pin for this hall position
		
		if (iTest == iTestOld) 
		{
			//sprintf(sMessage,"\r\nno more pins found\r\n");
			//AutoDetectSetStage(AUTODETECT_Stage_Results);
			return 0;	// one loop and no pin found -> exit
		}
		if (aoPin[iTest].wState & STATE_HIDE)
				continue;
		if (	(wStage & (AUTODETECT_Stage_Led|AUTODETECT_Stage_Hold|AUTODETECT_Stage_Button|AUTODETECT_Stage_Hall)) || (aoPin[iTest].wState & STATE_ADC))
			return 1;	// Stage_Led accepts any io pin, stage_Adc only adc-pins
		
	} while (1);
}

uint16_t iVBatMinTest = 65535;
float fVBattOld,fVBattFound=26.0;	// fVBattVar,
uint16_t iHoldAutofind = 100;		// time interval (100 = 100 * 1/16000 seconds) to turn off a pin. 0 = manual mode
uint8_t bCurrentManualMode = 0;

void ScanInit(uint8_t iTestNew)
{
	iTest = iTestNew;
	uint8_t i;
	switch (wStage)
	{
	case AUTODETECT_Stage_Button:

		pinModePull(aiPinScan[SCAN_SELF_HOLD],GPIO_MODE_INPUT,GPIO_PUPD_PULLUP);
		//pinMode(aiPinScan[SCAN_SELF_HOLD],GPIO_MODE_OUTPUT);
		//digitalWrite(aiPinScan[SCAN_SELF_HOLD],1);	// SELF_HOLD pin to high
		for (i=0;i<COUNT_PinDigital; i++)	
		{
			if (!(aoPin[i].wState & STATE_HIDE))
			{
				//gpio_deinit(aoPin[i].i);
				//pinMode(aoPin[i].i,GPIO_MODE_INPUT);
				pinModePull(aoPin[i].i,GPIO_MODE_INPUT,iRepeat%2 ? GPIO_PUPD_PULLUP : GPIO_PUPD_PULLDOWN);
			}
		}
		break;
	case AUTODETECT_Stage_Hold:
		if (iHoldAutofind == 3000)
		{
			aiPinScan[SCAN_SELF_HOLD] = aoPin[iTestNew].i;
			oDataHeader.wCmd = DATA_Save;
			msTicksWait = msTicks + 100;		// to let sMessage send via serial
		}
		for (i=0;i<COUNT_PinDigital; i++)	
		{
			if (!(aoPin[i].wState & STATE_HIDE))
			{
				//gpio_deinit(aoPin[i].i);
				pinModePull(aoPin[i].i,GPIO_MODE_INPUT,GPIO_PUPD_PULLUP);
				//pinMode(aoPin[i].i,GPIO_MODE_OUTPUT);
				//digitalWrite(aoPin[iTest].i,1);	// every remaining io pin might be the SELF_HOLD pin
			}
		}
		iVBatMinTest = 65535;
		//pinMode(VBAT, GPIO_MODE_ANALOG);
		//adc_regular_channel_config(1, ADC_CHANNEL_18, ADC_SAMPLETIME_13POINT5);	// ADC_CHANNEL_18 = VBAT
		adc_regular_channel_config(0, PIN_TO_CHANNEL(PF4), ADC_SAMPLETIME_13POINT5);
		//adc_regular_channel_config(1, PIN_TO_CHANNEL(PF4), ADC_SAMPLETIME_13POINT5);
		break;
	default:
		for (i=0;i<COUNT_PinDigital; i++)	
		{
			if (!(aoPin[i].wState & STATE_HIDE))
			{
				//gpio_deinit(aoPin[i].i);
				//pinMode(aoPin[i].i,GPIO_MODE_INPUT);
				pinModePull(aoPin[i].i,GPIO_MODE_INPUT,GPIO_PUPD_NONE);
			}
		}
	}
	
	uint32_t iPinNew = aoPin[iTest].i;
	msTicksTestNext = 1000;		// default time interval
	switch(wStage)
	{
	case AUTODETECT_Stage_Led:
		//gpio_deinit(iPinNew);
		//pinMode(iPinNew,GPIO_MODE_OUTPUT);
		break;
	case AUTODETECT_Stage_Hold:
		//iTestPin = iTest;
		msTicksTestNext = (iHoldAutofind == 3000) ? 250 : 100;		// default time interval
	
		break;
	case AUTODETECT_Stage_Button:
		msTicksTestNext = 20;		// default time interval
		break;
	default:	
		if ((aoPin[iTest].wState & STATE_ADC) == 0)	// this is not an adc pin
		{
			if (!SetNextTestPin())	// will find next adc pin
				return;	// no more adc pins left
		}
		//gpio_deinit(iPinNew);
		/*
		if (iTestInitOld >= 0)
		{
			pinMode(aoPin[iTestInitOld].i,GPIO_MODE_OUTPUT);
			digitalWrite(aoPin[iTestInitOld].i,1);
			//pinModePull(aoPin[iTestInitOld].i,GPIO_MODE_INPUT,GPIO_PUPD_PULLUP);
		}
		*/
		//VBATT = iPinNew;
		//ADC_init();
		pinMode(iPinNew, GPIO_MODE_ANALOG);
		adc_regular_channel_config(0, PIN_TO_CHANNEL(iPinNew), ADC_SAMPLETIME_13POINT5);
		//adc_regular_channel_config(1, PIN_TO_CHANNEL(iPinNew), ADC_SAMPLETIME_13POINT5);
		msTicksTestNext = (wStage == AUTODETECT_Stage_VBatt ? 2000 : 4000);
		iAverage = iRepeat = 0;
	}
	
	//iTestInitOld = iTest;
	fVBattOld = -42;
}


/*
void ScanList(uint8_t bLed)
{
	if (bLed)
	{
		sprintf(sMessage, "#define LED_RED\t\t%s\r\n#define LED_ORANGE\t%s\r\n#define LED_GREEN\t%s\r\n#define UPPER_LED\t%s\r\n#define LOWER_LED\t%s\r\n#define BUZZER\t%s\r\n"
				,	GetPinName(aiPinScan[0]),	GetPinName(aiPinScan[1]),	GetPinName(aiPinScan[2]),	GetPinName(aiPinScan[3]),	GetPinName(aiPinScan[4]),	GetPinName(aiPinScan[5])	);
	}
	else
	{
		sprintf(sMessage, "\r\n#define VBATT\t\t%s\r\n#define CURRENT_DC\t%s\r\n#define SELF_HOLD\t%s\r\n#define BUTTON\t\t%s\r\n"
				,	GetPinName(aiPinScan[6]),	GetPinName(aiPinScan[7]),	GetPinName(aiPinScan[SCAN_SELF_HOLD]),	GetPinName(aiPinScan[9]));
	}

}
*/



extern float currentDC;
extern int16_t bldc_outputFilterPwm;
extern adc_buf_t adc_buffer;
float fVBatt;
float fCurrentDC;
int16_t iOffsetDC;
uint8_t bWait4Enter=0;

void AutodetectScan(uint16_t buzzerTimer)
{
	if (wStage & (AUTODETECT_Stage_Hall|AUTODETECT_Stage_HallOrder)	)	// AUTODETECT_Stage_Startup|
		return;

	if (msTicksWait > msTicks)	// wait for last sMessage to be sent
		return;

	if (wStage == AUTODETECT_Stage_Results)
	{
		SetPWM(0);
		switch(iRepeat)
		{
		case 0:	ListFound(0,6);	break;
		case 1:	ListFound(6,13);	break;
		case 2:	ListFound(13,PINS_DETECT);	break;
		case 3:	wStageOld = -1; AutoDetectSetStage(AUTODETECT_Stage_Menu);	return;
		}
		msTicksWait = msTicks + 200;
		iRepeat++;
		return;
	}
	
	if (wStage == AUTODETECT_Stage_Finished)
	{
		SetPWM(0);
		//digitalWrite(aiPinScan[SCAN_SELF_HOLD],0);	// SELF_HOLD pin to high
		AutoDetectSetStage(AUTODETECT_Stage_Menu);
		return;
	}

	SetPWM(0);		// default speed -200
	
	uint8_t i;
	// AUTODETECT_Stage_Led or AUTODETECT_Stage_VBatt or AUTODETECT_Stage_CurrentDC or AUTODETECT_Stage_Hold
	uint8_t iFrom,iTo,bNeverLeave=1;
	switch (wStage)
	{
		case AUTODETECT_Stage_Startup: 		iFrom = 0; iTo = 0; break;
		case AUTODETECT_Stage_Led: 				iFrom = SCAN_LED_RED; iTo = SCAN_VBATT; break;
		case AUTODETECT_Stage_VBatt: 			iFrom = SCAN_VBATT; iTo = SCAN_CURRENT_DC; break;
		case AUTODETECT_Stage_CurrentDC: 	iFrom = SCAN_CURRENT_DC; iTo = SCAN_SELF_HOLD; bNeverLeave=0;	break;
		case AUTODETECT_Stage_Hold: 			
			iFrom = SCAN_SELF_HOLD; iTo = SCAN_BUTTON; 
			if (iHoldAutofind) bNeverLeave=0;
			break;
		case AUTODETECT_Stage_Button: 		iFrom = SCAN_BUTTON; iTo = SCAN_BUTTON_PULLUP+1; bNeverLeave=0;	break;
	}
	//if (!(wStage & (AUTODETECT_Stage_CurrentDC|AUTODETECT_Stage_Button))	)	//AUTODETECT_Stage_Hold|
	if (bNeverLeave)
		msTicksTest = msTicks + 50;	// never 
	
	char cCmd = 0;
	if (cCommand)
	{
		cCmd = cCommand;
		cCommand = 0;
		cRxLast = ' ';	// so a single return will pause/unpause
		switch(cCmd)	// general serial commands that apply to all stages
		{
		case 'l': ListFound(iFrom,iTo); break;
		case ' ': 
			if (bWait4Enter)
			{
				bWait4Enter = 0;
				msTicksTest = msTicks + msTicksTestNext;
			}
			else
				msTicksTest = 0; // skip this test interval
			break;
		case 'x': 
			HidePinDigital(aoPin[iTest].i); 
			if (iTest == iTestStart)	iTestStart = -1;
			msTicksTest = 0; // skip this test interval
			break;
		case 'c': 
			for (i=iFrom;i<iTo;i++)	aiPinScan[i] = 0; 
			wMenuStage = MENU_INIT;
			ScanInit(0);
			msTicksTest = msTicks + msTicksTestNext;
			sprintf(sMessage, "all pins cleared.");
			break;
		case 's': 	// save
				ListFound(iFrom,iTo);
				for (i=iFrom;i<iTo;i++)	HidePinDigital(aiPinScan[i]); 
				AutoDetectNextStage();
				bWait4Enter = 0;
				return;
		case 'q': 	// menu
				wStageOld = -1;
				AutoDetectSetStage(AUTODETECT_Stage_Menu);
				bWait4Enter = 0;
				//oDataHeader.wCmd = DATA_Request;		// only for testing ?
				return;
		case 't': 
			iHoldAutofind = iHoldAutofind ? 0 : 100;
			sprintf(sMessage, "auto find: %i\r\n",iHoldAutofind);
		case 'm': 
			if (bCurrentManualMode)
			{
				bCurrentManualMode = 0;
				iTestStart = iTest;
			}
			else	bCurrentManualMode = 1;
			
			sprintf(sMessage, "manual mode: %i\r\n",bCurrentManualMode);
			break;
		}
	}
	
	if (bWait4Enter)
	{
		switch (bWait4Enter)
		{
		case 1: 
			msTicksWait = msTicks + 100; 
			bWait4Enter++;
			return;
		case 2:	
			sprintf(sMessage,"\r\nENTER to begin, 's' for next stage, 'q' for menu\r\n");
			msTicksWait = msTicks + 100;
			bWait4Enter++;
			return;
		}
		return;
	}
		
	if (wStageOld != wStage)
	{
		wStageOld = wStage;
		
		//for (i=iFrom;i<iTo;i++)	aiPinScan[i] = 0; 

		ScanInit(0);
		switch (wStage)
		{
			case AUTODETECT_Stage_Led: sprintf(sMessage,"'r'=red,\t'o'=orange,\t'g'=green,\t'u'=up,\t'd'=down,\t'p'=pcb led,\t'b'=buzzer"); break;
			case AUTODETECT_Stage_VBatt: 
				sprintf(sMessage,"'f'=battery voltage"); 
				bWait4Enter = 1;
				break;
		}
		switch (wStage)
		{
			case AUTODETECT_Stage_Startup:
				//oDataHeader.wCmd = DATA_Request;
				sprintf(sMessage,"hit ENTER:\r\n"); 
				//oDataHeader.wCmd = DATA_Request;
				break;
			case AUTODETECT_Stage_Menu:
				sprintf(sMessage,"autodetect menu:\r\n"); 
				uint16_t iStage;
				for (iStage=0; iStage < 9; iStage++)
				{
					if (wMenuStage & (2 << iStage)	)
						sprintf(sMessage,"%s%i: %s\r\n",sMessage,iStage,asStage[iStage]);
				}
				//bWait4Enter = 1;
				break;

			case AUTODETECT_Stage_Hold: 
				sprintf(sMessage,"now detecting SELF_HOLD pin,\r\nbridge the onOff button\r\n't' to toggle manual mode."); 
				bWait4Enter = 1;
				break;
			case AUTODETECT_Stage_Button: 
				sprintf(sMessage,"now detecting BUTTON pin,\r\nrelease OnOff button"); 
				bWait4Enter = 1;
				break;
			case AUTODETECT_Stage_CurrentDC: 
				sprintf(sMessage,"current_DC: wait one cycle :-)\r\n\tWARNING: strongly mount the motor or 'm' to toggle manual mode!!!"); 
				bWait4Enter = 1;
				break;
			default:	
				sprintf(sMessage,"%s\r\n'x'=delete pin\t'l'=list,\t'c'=reset and 's'=next stage, 'q' for menu\r\nENTER for next pin\r\nnow %s",sMessage,aoPin[iTest].s);
		}
		if (!bWait4Enter)
			msTicksTest = msTicks + msTicksTestNext;
		
		iTestStart = iTest;
		msTicksWait = msTicks + 300;
		return;	// to allow sMessage to be sent
	}
	
	int8_t iFound = -1;
	uint16_t iTimeCountdown = msTicksTest-msTicks;
	switch (wStage)
	{
	case AUTODETECT_Stage_Startup:
		if (!(buzzerTimer%16000) )	// 16 kHz
		{
			if (0 == iRepeat--)
			{
				iRepeat = 20;
				sprintf(sMessage,":-)\n");
			}
			else	sprintf(sMessage,"\r:-)");
		}
		if (cCmd)
			AutoDetectNextStage();
		return;
	case AUTODETECT_Stage_Menu:
		if (	(cCmd >= 48) && (cCmd < 58) )
		{
			uint16_t iStageNew = cCmd - 48;
			if (iStageNew)
			{
				iStageNew = 1 << (iStageNew +1);
				bReturnToMenu = 1;
			}
			else
			{
				iStageNew = AUTODETECT_Stage_VBatt;
				bReturnToMenu = 0;
			}
			AutoDetectSetStage(iStageNew); 
		}
		return;	// no further function for menu
	case AUTODETECT_Stage_Led:
		//digitalWrite(aoPin[iTest].i,(msTicks%4)>0 ? 1 : 0);	// 250 Hz 75% pwm ratio
		pinModePull(aoPin[iTest].i,GPIO_MODE_INPUT,(msTicks%4)>0  ? GPIO_PUPD_PULLDOWN : GPIO_PUPD_PULLUP);
	
		switch(cCmd)
		{
		case 'r': iFound = SCAN_LED_RED; break;
		case 'o': iFound = SCAN_LED_ORANGE; break;
		case 'g': iFound = SCAN_LED_GREEN; break;
		case 'u': iFound = SCAN_UPPER_LED; break;
		case 'd': iFound = SCAN_LOWER_LED; break;
		case 'p': iFound = SCAN_ONBOARD_LED; break;
		case 'b': iFound = SCAN_BUZZER; break;
		}
		break;
	case AUTODETECT_Stage_VBatt:
		SetPWM(	(msTicks % 4000) < 2000 ? -300 : 0);	// strong motor to see a load when hand on motor
		fVBatt = fVBatt * 0.9 + ((float)adc_buffer.v_batt * ADC_BATTERY_VOLT) * 0.1;
		//pinModePull(aoPin[iTest].i,GPIO_MODE_INPUT,(buzzerTimer%32000 < 16000) ? GPIO_PUPD_PULLDOWN : GPIO_PUPD_PULLUP);
		if (buzzerTimer % 16000 == 0)	// 16 kHz
		{
			float fDelta = (fVBattOld == -42) ? 0 : ABS(fVBattOld-fVBatt);
			sprintf(sMessage,"P%s: %.2f V +- %.2f\r\n", aoPin[iTest].s,fVBatt,fDelta);
			fVBattOld = fVBatt;
		}
		
		switch(cCmd)
		{
		case 'f': 
			iFound = SCAN_VBATT; 
			fVBattFound = fVBatt;
			msTicksTest = 0; 
			break;
		}
		break;
	case AUTODETECT_Stage_CurrentDC:
		if (iTimeCountdown>3000)
		{
			SetPWM(0);
			if (iTimeCountdown>3500)	// wait 0,5s to let the motor stop
			{
				iOffsetDC = 2000;	// reset 
			}
			else
			{
				iOffsetDC = (adc_buffer.v_batt + iOffsetDC) / 2;
				iAverage = 0; 	// initialize value
			}
		}
		else
		{
			fCurrentDC = ((adc_buffer.v_batt - iOffsetDC) * MOTOR_AMP_CONV_DC_AMP);
			if (bCurrentManualMode)
			{
				SetPWM(iTimeCountdown>2000 ? 0 : -300);	// strong motor to see a load when hand on motor
				if (buzzerTimer % 3200 == 0)	// 16 kHz
				{
					sprintf(sMessage,"%s: CURRENT_DC ?= %.2f\r\n",aoPin[iTest].s,fCurrentDC);
				}
			}
			else
			{
				#define MS_INTERVAL 500
				uint16_t iInterval = MS_INTERVAL - (iTimeCountdown % MS_INTERVAL);
				int16_t iPwm = iInterval<(MS_INTERVAL/2) ? -700 : 700;
				SetPWM(	iPwm);	// strong motor to see a load when hand on motor
				
				iInterval = iInterval % (MS_INTERVAL/2);
				if ( (iInterval>20) && (iInterval<60) ) // regenerative current due to rotation change
				{
					if (	(fCurrentDC < 0) && (fCurrentDC > -0.5)	)
					{
							if (iAverage < 32767)	iAverage++;
					}
					else
					{
							if (iAverage > -32767)	iAverage--;
					}
				}
			}
		}
		switch(cCmd)
		{
			case 'f': iFound = SCAN_CURRENT_DC; msTicksTest = 0; break;
		}
		break;
	case AUTODETECT_Stage_Hold:
		//digitalWrite(aoPin[iTest].i,(buzzerTimer%3000) < 100 ? 0 : 1);	// relase SELF_HOLD for a short time
		//pinMode(aoPin[iTest].i,GPIO_MODE_INPUT);
		if (iHoldAutofind) 
		{
			if (iVBatMinTest > adc_buffer.v_batt)		// try to detect the "(buzzerTimer%100) < 3000 " voltage dip 
				iVBatMinTest = adc_buffer.v_batt;
			pinModePull(aoPin[iTest].i,GPIO_MODE_INPUT,(buzzerTimer%3000) < iHoldAutofind ? GPIO_PUPD_PULLDOWN : GPIO_PUPD_PULLUP);			
		}
		else	pinModePull(aoPin[iTest].i,GPIO_MODE_INPUT,GPIO_PUPD_PULLDOWN);
			
		switch(cCmd)
		{
			case 'f': 
				iFound = SCAN_SELF_HOLD; msTicksTest = 0; 
				wMenuStage |= AUTODETECT_Stage_Button;
				break;
		}
		
		break;
		
	case AUTODETECT_Stage_Button:
		SetPWM(0);
		uint8_t bOn = digitalRead(aoPin[iTest].i);
		uint8_t wSet = STATE_OFF << iRepeat;		// STATE_OFF , STATE_OFF2, STATE_ON, STATE_ON2
		aoPin[iTest].wState = (aoPin[iTest].wState & ~wSet) | bOn * wSet;
	
	/*
		if (iRepeat)
		{
			aoPin[iTest].wState = (aoPin[iTest].wState & ~STATE_ON) | bOn * STATE_ON;
		}
		else
		{
			aoPin[iTest].wState = (aoPin[iTest].wState & ~STATE_OFF) | bOn * STATE_OFF;
		}
		*/
		break;
	}
	
	if (iFound >= 0)
	{
		aiPinScan[iFound] = aoPin[iTest].i;
		for (i=iFrom;i<iTo;i++)	HidePinDigital(aiPinScan[i]); 
		
		sprintf(sMessage, "%s = %s\r\n",	asScan[iFound],GetPinName(aoPin[iTest].i)	);
		msTicksTest = 0; // skip this test interval
		oDataHeader.wCmd = DATA_Save;
	}
	if (msTicks > msTicksTest)
	{
		switch (wStage)
		{
//		case AUTODETECT_Stage_VBatt:
//			pinModePull(aoPin[iTest].i,GPIO_MODE_INPUT,GPIO_PUPD_PULLUP);
//			break;
		case AUTODETECT_Stage_CurrentDC:
			if (!bCurrentManualMode)
			{
				if (iAverageMax < iAverage)
				{
					iTestPin = iTest;
					iAverageMax = iAverage;
				}
			}
			break;
		case AUTODETECT_Stage_Hold:
			if (!iHoldAutofind)
				break;
			if(iRepeat)
			{
				aoPin[iTest].iAdc -= iVBatMinTest;
				sprintf(sMessage,"-%i = %i",iVBatMinTest,aoPin[iTest].iAdc);
			}
			else
			{
				sprintf(sMessage,"%i",iVBatMinTest);
				aoPin[iTest].iAdc = iVBatMinTest;
			}
			break;
		}

		if (SetNextTestPin())
		{
			if (iTestStart < 0) iTestStart = iTest;
			switch (wStage)
			{
			case AUTODETECT_Stage_Hold:
				if (iTest == iTestStart)	// a complete cycle of available adc pins
				{
					if(iRepeat)
					{
						iRepeat = 0;
						uint16_t iMax = 0;
						for (i=0;i<COUNT_PinDigital; i++)	
						{
							if (!(aoPin[i].wState & STATE_HIDE))
							{
								uint16_t iDelta = ABS(aoPin[i].iAdc);
								if ( (iDelta > 10) && (iDelta < 1000) && (iMax < iDelta)	)	// voltage drop can not be larger then 1000/4096 * 3.3V
								{
									iMax = iDelta;
									iTestPin = i;
								}
							}
						}
						if (iMax)
						{
							aiPinScan[SCAN_SELF_HOLD] = aoPin[iTestPin].i;
							oDataHeader.wCmd = DATA_Save;
							wMenuStage |= AUTODETECT_Stage_Button;
							sprintf(sMessage,"%s\r\nSELF_HOLD P%s //%i\r\nbridge OnOff button",sMessage,GetPinName(aiPinScan[SCAN_SELF_HOLD]),iMax);
						}
						else
						{
							sprintf(sMessage,"%s\r\nnothing found. Keep OnOff button released. board will shut off..",sMessage);
							iHoldAutofind = 3000;
						}
					}
					else
					{
						iRepeat++;
						sprintf(sMessage,"%s\r\nrelease OnOff button",sMessage);
						
					}
					bWait4Enter = 1;
					break;
				}
				sprintf(sMessage,"%s\r\n%i now %s : ",sMessage,iRepeat,aoPin[iTest].s);
				break;
			case AUTODETECT_Stage_CurrentDC:
				if (bCurrentManualMode)
					break;

				if (iTest == iTestStart)	// a complete cycle of available adc pins
				{
					sprintf(sMessage," : %i\r\nCURRENT_DC = %s //%i\r\nnow %s",iAverage,aoPin[iTestPin].s,iAverageMax,aoPin[iTest].s);
					aiPinScan[SCAN_CURRENT_DC] = aoPin[iTestPin].i;
					oDataHeader.wCmd = DATA_Save;
					iTestPin = iAverage = 0;	// reset for next cycle
					iAverageMax =-32767;
				}
				else
					sprintf(sMessage," : %i\r\nnow %s",iAverage,aoPin[iTest].s);
				break;
			case AUTODETECT_Stage_Button:
				if (iTest == iTestStart)	// a complete cycle of available adc pins
				{						
					iRepeat++;
					if(iRepeat == 4)
					{
						sprintf(sMessage,"");
						uint8_t iFound = 0;
						for (i=0;i<COUNT_PinDigital; i++)	
						{
							if (!(aoPin[i].wState & STATE_HIDE))
							{
								int8_t iScanPin = -1;
								if (!(aoPin[i].wState & STATE_OFF) && (aoPin[i].wState & STATE_ON))
									iScanPin = SCAN_BUTTON;
								if	(!(aoPin[i].wState & STATE_OFF2) && (aoPin[i].wState & STATE_ON2))
									iScanPin = SCAN_BUTTON_PULLUP;
								if (iScanPin >= 0)
								{
									aiPinScan[iScanPin] = aoPin[i].i;
									oDataHeader.wCmd = DATA_Save;
									sprintf(sMessage,"\r\n%s%s\t%s",sMessage,asScan[iScanPin],aoPin[i].s);
									iFound++;
								}
							}
						}
						sprintf(sMessage,"%s\r\n%i pins found. release OnOff button",sMessage,iFound);
						iRepeat = 0;
						bWait4Enter = 1;
					}
					else if (iRepeat == 2)
					{
						sprintf(sMessage,"\r\nbridge OnOff button");
						bWait4Enter = 1;
					}
					else sprintf(sMessage, "\r\n%s",aoPin[iTest].s);
				}
				else sprintf(sMessage, " %s",aoPin[iTest].s);
				break;
			default:
				sprintf(sMessage, "try %s\r\n",aoPin[iTest].s);
			}		
			
			ScanInit(iTest);
			msTicksTest = msTicks + msTicksTestNext;
		}
		else
		{
			
			AutoDetectNextStage();
			sprintf(sMessage, "no more free pins ! now stage %i\r\n",wStage);
		}
	}
}



	

uint8_t bHallOld = 2;
//uint8_t iHall = 0;


uint32_t msTicksAuto = 0;
uint8_t posAuto = 1;
uint8_t posOld = 0;
uint32_t msTicksOld;


void AutoDetectHallInit()
{
	//gpio_deinit(aoPin[iTest].i);
	pinMode(aoPin[iTest].i,GPIO_MODE_INPUT);
	//gpio_mode_set(aoPin[iTest].i&0xffffff00U, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP,BIT(aoPin[iTest].i&0xfU) );
	//gpio_output_options_set(aoPin[iTest].i&0xffffff00U, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, BIT(aoPin[iTest].i&0xfU));

	msTicksOld = 0;
	iRepeat = 0;
	msTicksWait = msTicks + 50;		// to let sMessage send via serial
	msTicksTest = msTicksWait + 1000;
}

void AutoDetectHallOrderInit(uint8_t iTestSet)	// iTestSet = 0..5 = 6 possible permutations
{
	iTest = iTestSet;
	
	HALL_A = aiPinScan[ aHallOrder[iTest][0] ];
	HALL_B = aiPinScan[ aHallOrder[iTest][1] ];
	HALL_C = aiPinScan[ aHallOrder[iTest][2] ];

	msTicksTest = msTicks + 1000;
	msTicksOld = 0;
	iRepeat = 0;
}




uint8_t AutodetectBldc(uint8_t posNew,uint16_t buzzerTimer)
{
	/*
		// AUTODETECT_Stage_Startup
		if (wStage == AUTODETECT_Stage_Startup	)
		{
			SetPWM(0);
			if (msTicks > 500)
				AutoDetectNextStage();
			return posNew;
		}
	*/
		if (0 == (wStage & (AUTODETECT_Stage_Startup|AUTODETECT_Stage_Hall
												|AUTODETECT_Stage_HallOrder|AUTODETECT_Stage_VBatt))	)
			return posNew;

		//SetPWM(msTicks > 500 ? -200 : (int32_t)msTicks * -2 / 5);
		//SetPWM(fVBattFound > 30 ? -150 : -200);
		SetPWM(-120 - 4*(42-(int16_t)fVBattFound));		// lower vbatt needs higher pwm to make motor spin

		if (msTicks - msTicksAuto >= 15)
		{
			posAuto++;
			if (posAuto == 7)	posAuto = 1;
			//pos = posAuto;
			msTicksAuto = msTicks;
		}

		if (msTicksWait > msTicks)	// wait for last sMessage to be sent
			return posAuto;

		
		// AUTODETECT_Stage_Hall
		if (wStage == AUTODETECT_Stage_Hall)		// find the three hall pins :-)
		{
			if (wStageOld != wStage)
			{
				AutoDetectHallInit();
				iTest = COUNT_PinDigital-1;
				SetNextTestPin();
				iTestStart = iTest;
				sprintf(sMessage, "\r\nhall and phase currents: 'r'=restart\t's'=save\r\ntry %i = %s\t",iTest,aoPin[iTest].s);

				wStageOld = wStage;
			}

			switch(cCommand)
			{
			case 'r': 
				wStageOld = AUTODETECT_Stage_Startup;
				//sprintf(sMessage, "\trestart\r\n");
				AutoDetectSetStage(AUTODETECT_Stage_Hall);
				break;
			case 's': 
				if (iTestPin == 3)
				{
					//HallList();
					ListFound(0,3);
					AutoDetectNextStage();
				}
				break;
			}
			if (cCommand)
			{
				cCommand = 0;
				cRxLast = ' ';	// so a single return will pause/unpause
			}
			
			char* sFound = "";
			
			uint8_t bHall = digitalRead(aoPin[iTest].i);
			if (bHall != bHallOld)
			{
				uint16_t iTime = msTicks-msTicksOld;
				if (!bHall)	// rotor has left the hall sensor
				{
					if (	(iTime > 5) && (iTime < 50)	)	// the hall on-time should match the rotation speed
					{
						//sprintf(sMessage, "repeat %i = %s : %i ms %i\r\n",iTest,aoPin[iTestPin].s,iTime,iRepeat);
						if (5 == iRepeat++)
						{
							if (iTestPin < 3)
							{
								aiPinScan[iTestPin] = aoPin[iTest].i;
								//sprintf(sMessage, "hall %i = %s : %i ms\r\n",iTestPin,aoPin[iTest].s,iTime);
								
							}
							else
							{
								//sprintf(sMessage, "%i hall inputs :-/ %s : %i ms\r\n",iTestPin,aoPin[iTest].s,iTime);
							}
						
							sFound = "HALL";
							iTestPin++;	// next hall sensor
							msTicksTest = 0;
						}
					}
					else if (	(iTime < 3) && (aoPin[iTest].wState & STATE_ADC) 	)	// could be a adc phase current pin
					{
						//sprintf(sMessage, "repeat %i = %s : %i ms %i\r\n",iTest,aoPin[iTestPin].s,iTime,iRepeat);
						if (5 == iRepeat++)
						{
							if (iPhaseCurrent < 3)
							{
								aiPinScan[3+iPhaseCurrent] = aoPin[iTest].i;
							}
							//sprintf(sMessage, "phase current %i = %s\r\n",iPhaseCurrent,aoPin[iTestPin].s);
							sFound = "PHASE";
							iPhaseCurrent++;
							msTicksTest = 0;
						}
					}
					else
					{
						//sprintf(sMessage, "%i\r\n",iTime);
						//sprintf(sMessage, "%i: %i = %s : wrong %i ms\r\n",iTestPin,iTest,aoPin[iTest].s,iTime);
						iRepeat = 0;
					}
				}
				else
				{
						//sprintf(sMessage, "nono %i = %s : %i ms\r\n",iTest,aoPin[iTestPin].s,iTime);
				}
				bHallOld  = bHall;
				msTicksOld = msTicks;
			}
			
			if (msTicks > msTicksTest)
			{
				//uint8_t iTestOld = iTest;
				if (!SetNextTestPin())
					return posAuto;	// no more pins left
				
				if (iTestStart != iTest)
				{
					//sprintf(sMessage, "%i try %i\r\n",iTest,iTestPin);
					sprintf(sMessage, "%s\r\ntry %i = %s\t",sFound,iTest,aoPin[iTest].s);
					AutoDetectHallInit();
				}
				else
				{
					if (iTestPin == 3)
					{
							//HallList();
							ListFound(0,3);
							wMenuStage |= AUTODETECT_Stage_HallOrder;
							AutoDetectNextStage();
					}
					else
					{
						sprintf(sMessage,"not 3 hall pins found.\r\n");
						AutoDetectSetStage(AUTODETECT_Stage_Menu);	// too less or too many pins found :-(
					}
				}
			}
			return posAuto;
		}
		
		// AUTODETECT_Stage_HallOrder
		if (wStage == AUTODETECT_Stage_HallOrder)
		{
			if (wStageOld != wStage)
			{
				AutoDetectHallOrderInit(0);
				wStageOld = wStage;
			}
			
			if (posNew != posOld)
			{
				uint16_t iTime = msTicks-msTicksOld;
				if (buzzerTimer % 3000 == 0)	// 16 kHz
					sprintf(sMessage, "%i: %i -> %i \t%i\r\n",posAuto,posNew,posOld,iTime);
				if (	(posOld == posAuto) && 
							(	((posOld == 6) && (posNew == 1)) || (posNew == posOld+1) )
						)	// valid hall input
				{
					if (20 < iRepeat++)
					{
						aiPinScan[SCAN_HALL_A] = HALL_A;
						aiPinScan[SCAN_HALL_B] = HALL_B;
						aiPinScan[SCAN_HALL_C] = HALL_C;
						oDataHeader.wCmd = DATA_Save;
						
						ListFound(0,6);

						uint8_t i;
						for (i=0; i<3+iPhaseCurrent; i++)	HidePinDigital(aiPinScan[i]);
						wMenuStage |= AUTODETECT_Stage_CurrentDC;
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
							sprintf(sMessage, "wrong oder %i\r\n",iTest);
							AutoDetectHallOrderInit(iTest+1);	// test next permutation
						}
						else
						{
							sprintf(sMessage, "no hall oder found: %i\r\n",iTest);
							AutoDetectSetStage(AUTODETECT_Stage_Menu);	// no more hall permutations to test :-/
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
