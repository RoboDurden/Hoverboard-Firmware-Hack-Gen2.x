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
		
	//sprintf(sMessage, "rx: %c\r\n",cRead);

	//DEBUG_LedSet((steerCounter%20) < 10,0)	// 	
}



uint32_t HALL_A = TODO_PIN;
uint32_t HALL_B = TODO_PIN;
uint32_t HALL_C = TODO_PIN;






typedef struct {
   uint32_t i;
   char*  s;
   uint8_t  wState;   // 1=adc
   int16_t  iAdc;  
} PinAD;

#define STATE_ADC 1
#define STATE_HIDE 2
#define STATE_OFF 4
#define STATE_ON 8

//#define TEST

#ifdef TEST
	#define COUNT_PinDigital 22
	PinAD aoPin[COUNT_PinDigital] = {	// 2.13 pins removed for testing: led + buzzer + vbatt + currentDC
			{PC14,"PC14",0}	,{PF1,"PF1",0}		,{PB11,"PB11",1}	,{PF0,"PF0",0}		, 
			{PA5,"PA5",1} 		, {PC13,"PC13",0}	 ,{PC15,"PC15",0}	,
			{PA7,"PA7",1}		,{PB0,"PB0",1}		,{PB1,"PB1",1}		,{PB2,"PB2",0}	,{PB10,"PB10",0}	,
			{PB12,"PB12",0}	,{PA11,"PA11",0}	,{PF6,"PF6",0}	,{PF7,"PF7",0} 	,
			{PB4,"PB4",0}		,{PB5,"PB5",0}		,
			{PB6,"PB6",0}		,{PB7,"PB7",0}		,{PB8,"PB8",0}		,{PB9,"PB9",0}	};
#else

	#define COUNT_PinDigital 31

	PinAD aoPin[COUNT_PinDigital] = {
			{PC13,"PC13",0}	,{PC14,"PC14",0}	,{PC15,"PC15",0}	,{PF0,"PF0",0}	,{PF1,"PF1",0}		,
			{PA0,"PA0",1}		,{PB11,"PB11",0}		,{PA4,"PA4",1}		,{PA5,"PA5",1}	,{PA6,"PA6",1} 	,
			{PA7,"PA7",1}		,{PB0,"PB0",1}		,{PB1,"PB1",1}		,{PB2,"PB2",0}	,{PB10,"PB10",0}	,
			{PA1,"PA1",1}	,{PB12,"PB12",0}	,{PA11,"PA11",0}	,{PF6,"PF6",0}	,{PF7,"PF7",0} 	,
			{PA12,"PA12",0}	,{PA15,"PA15",0}	,{PB3,"PB3",0}		,{PB4,"PB4",0}	,{PB5,"PB5",0}	,
			{PB6,"PB6",0}		,{PB7,"PB7",0}		,{PB8,"PB8",0}		,{PB9,"PB9",0}	,{PA2,"PA2",1}	,
			{PA3,"PA3",1}
			};
#endif
			
			
const char* sTodoPin = "TODO_PIN";
		

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

	adc_regular_channel_config(1, ADC_CHANNEL_18, ADC_SAMPLETIME_13POINT5);	// ADC_CHANNEL_18 = VBAT
		// at AUTODETECT_Stage_Hold the minimal VBAT=ADC_CHANNEL_18 value iVBatMin will be needed..
}

uint16_t wStage = AUTODETECT_Stage_Startup;		// main stages like hall pin detect, led pin detect, etc.
uint16_t wStageOld = -1;

uint32_t msTicksTest,msTicksWait;
uint8_t iTest = 0;		// an index pointer testing different positbilities
uint8_t iTestPin = 0;	// a pin variable used while testing
int8_t iTestStart = -1;		// an index pointer to the first pin tested in a stage

uint8_t iRepeat = 0;	// a counter to repeat before some finding is accepted
int16_t iAverage = 0;	// a variable to averarge over some reading
int16_t iAverageMax = -32767;	// a variable to stor the maximun averarge 

void AutoDetectSetStage(uint16_t iSet)
{
	iTest = iRepeat = 0;
	iTestPin = 0;
	wStage = iSet;
	msTicksWait = msTicks + 300;	// to allow sMessage of last stage to be sent via serial
	
}
void AutoDetectNextStage()
{
	AutoDetectSetStage(wStage<<1);
}


const char* asScan[10] = {"LED_RED","LED_ORANGE","LED_GREEN","UPPER_LED","LOWER_LED","BUZZER","VBATT","CURRENT_DC","SELF_HOLD","BUTTON"};
uint32_t aiPinScan[10] = {0,0,0,0,0,0,0,0,0,0};		// the found led pins

uint32_t aPinHall[6] = {0,0,0,0,0,0};		// the found hall pins (aoPin will map to PA1, etc) and up to 3 phase currents
uint8_t aHallOrder[6][3] = {{0,2,1},{2,0,1},{0,1,2},{1,2,0},{1,0,2},{2,1,0}};	// possible permutations to test

void HallList()
{
	//sprintf(sMessage, "hall oder: %i = %i,%i,%i\r\n",iTest,aHallOrder[iTest][0],aHallOrder[iTest][1],aHallOrder[iTest][2]);
	sprintf(sMessage, "\r\n#define HALL_A = %s\r\n#define HALL_B = %s\r\n#define HALL_C = %s\r\n#define PHASE_A = %s\r\n#define PHASE_A = %s\r\n#define PHASE_C = %s\r\n"
		, aoPin[aPinHall[ aHallOrder[iTest][0] ] ].s
		, aoPin[aPinHall[ aHallOrder[iTest][1] ] ].s
		, aoPin[aPinHall[ aHallOrder[iTest][2] ] ].s
		,	GetPinName(aPinHall[3])
		,	GetPinName(aPinHall[4])
		,	GetPinName(aPinHall[5])
	);
}


#define SCAN_AutoInc 1
uint8_t wScanConfig = 0;
int8_t iMove = +1;
uint8_t SetNextTestPin()
{
	if (!iMove)	return 1;
			
	uint8_t iTestOld = iTest;
	do
	{
		if (iMove > 0)
			iTest = (iTest + iMove) % COUNT_PinDigital;		// try next io pin for this hall position
		else if (iTest == 0)
				iTest = COUNT_PinDigital-1;
		else
			iTest--;
		
		if (iTest == iTestOld) 
		{
			sprintf(sMessage,"\r\nno more pins found\r\n");
			AutoDetectSetStage(AUTODETECT_Stage_Results);
			return 0;	// one loop and no pin found -> exit
		}
		if (aoPin[iTest].wState & STATE_HIDE)
				continue;
		if (	(wStage & (AUTODETECT_Stage_Led|AUTODETECT_Stage_Hold|AUTODETECT_Stage_Button|AUTODETECT_Stage_Hall)) || (aoPin[iTest].wState & STATE_ADC))
			return 1;	// Stage_Led accepts any io pin, stage_Adc only adc-pins
		
	} while (1);
}

uint16_t iVBatMinTest = 65535;

void ScanInit(uint8_t iTestNew)
{
	iTest = iTestNew;
	uint8_t i;
	switch (wStage)
	{
	case AUTODETECT_Stage_Button:

		//gpio_deinit(aiPinScan[8]);
		pinMode(aiPinScan[8],GPIO_MODE_OUTPUT);
		digitalWrite(aiPinScan[8],1);	// SELF_HOLD pin to high
		for (i=0;i<COUNT_PinDigital; i++)	
		{
			if (!(aoPin[i].wState & STATE_HIDE))
			{
				//gpio_deinit(aoPin[i].i);
				pinMode(aoPin[i].i,GPIO_MODE_INPUT);
			}
		}
		break;
	case AUTODETECT_Stage_Hold:
		for (i=0;i<COUNT_PinDigital; i++)	
		{
			if (!(aoPin[i].wState & STATE_HIDE))
			{
				//gpio_deinit(aoPin[i].i);
				pinMode(aoPin[i].i,GPIO_MODE_OUTPUT);
				digitalWrite(aoPin[iTest].i,1);	// every remaining io pin might be the SELF_HOLD pin
			}
		}
		iVBatMinTest = 65535;
		//pinMode(VBAT, GPIO_MODE_ANALOG);
		adc_regular_channel_config(0, ADC_CHANNEL_18, ADC_SAMPLETIME_13POINT5);	// ADC_CHANNEL_18 = VBAT
		break;
	default:
		for (i=0;i<COUNT_PinDigital; i++)	
		{
			if (!(aoPin[i].wState & STATE_HIDE))
			{
				//gpio_deinit(aoPin[i].i);
				pinMode(aoPin[i].i,GPIO_MODE_INPUT);
			}
		}
	}
	
	uint32_t iPinNew = aoPin[iTest].i;
	msTicksTest = msTicks + 1000;		// default time interval
	switch(wStage)
	{
	case AUTODETECT_Stage_Led:
		//gpio_deinit(iPinNew);
		pinMode(iPinNew,GPIO_MODE_OUTPUT);
		break;
	case AUTODETECT_Stage_Hold:
		//iTestPin = iTest;
		msTicksTest = msTicks + 100;		// default time interval
		break;
	case AUTODETECT_Stage_Button:
		msTicksTest = msTicks + 100;		// default time interval
		break;
	default:	
		if ((aoPin[iTest].wState & STATE_ADC) == 0)	// this is not an adc pin
		{
			if (!SetNextTestPin())	// will find next adc pin
				return;	// no more adc pins left
		}
		//gpio_deinit(iPinNew);
		pinMode(iPinNew, GPIO_MODE_ANALOG);
		adc_regular_channel_config(0, PIN_TO_CHANNEL(iPinNew), ADC_SAMPLETIME_13POINT5);
		msTicksTest = msTicks + (wStage == AUTODETECT_Stage_VBatt ? 2000 : 4000);
	}
}

void ListFound(uint8_t iFrom, uint8_t iTo)
{
	uint8_t i;
	sprintf(sMessage,"");
	for (i=iFrom; i<iTo; i++)
		sprintf(sMessage,"%s#define %s\t\t%s\r\n",sMessage,asScan[i],GetPinName(aiPinScan[i]));
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
				,	GetPinName(aiPinScan[6]),	GetPinName(aiPinScan[7]),	GetPinName(aiPinScan[8]),	GetPinName(aiPinScan[9]));
	}

}
*/



extern float currentDC;
extern int16_t bldc_outputFilterPwm;
extern adc_buf_t adc_buffer;
float fVBatt;
float fCurrentDC;
int16_t iOffsetDC;

void AutodetectScan(uint16_t buzzerTimer)
{
	if (msTicksWait > msTicks)	// wait for last sMessage to be sent
		return;

	
	if (wStage == AUTODETECT_Stage_Results)
	{
		SetPWM(0);
		switch(iRepeat)
		{
		case 0:
			ListFound(6,10);
			break;
		case 1:
			HallList();
			AutoDetectNextStage();
			break;
		}
		msTicksWait = msTicks + 300;
		iRepeat++;
		return;
	}
	
	if (wStage == AUTODETECT_Stage_Finished)
	{
		SetPWM(0);
		return;
	}
	
	
	if (	(wStage < AUTODETECT_Stage_Led) || (wStage > AUTODETECT_Stage_Button)	)
		return;

	uint8_t i;
	// AUTODETECT_Stage_Led or AUTODETECT_Stage_VBatt or AUTODETECT_Stage_CurrentDC or AUTODETECT_Stage_Hold
	uint8_t iFrom,iTo;
	switch (wStage)
	{
		case AUTODETECT_Stage_Led: 			iFrom = 0; iTo = 6; break;
		case AUTODETECT_Stage_VBatt: 		iFrom = 6; iTo = 7; break;
		case AUTODETECT_Stage_CurrentDC: iFrom = 7; iTo = 8; break;
		case AUTODETECT_Stage_Hold: 		iFrom = 8; iTo = 9; break;
		case AUTODETECT_Stage_Button: 		iFrom = 9; iTo = 10; break;
	}
		
	SetPWM(0);		// default speed -200
	if (wStageOld != wStage)
	{
		wStageOld = wStage;
		
		//for (i=iFrom;i<iTo;i++)	aiPinScan[i] = 0; 

		ScanInit(0);
		switch (wStage)
		{
			case AUTODETECT_Stage_Led: sprintf(sMessage,"'r'=red,\t'o'=orange,\t'g'=green,\t'u'=up,\t'd'=down,\t'b'=buzzer"); break;
			case AUTODETECT_Stage_VBatt: sprintf(sMessage,"'v'=battery voltage"); break;
			case AUTODETECT_Stage_CurrentDC: sprintf(sMessage,"current_DC: wait one cycle :-)"); break;
		}
		switch (wStage)
		{
			case AUTODETECT_Stage_Hold: 
				sprintf(sMessage,"now detecting SELF_HOLD pin,\r\nbridge the onOff button and hit ENTER\r\n"); 
				break;
			case AUTODETECT_Stage_Button: sprintf(sMessage,"now 'b'=BUTTON pin,\r\nrelease OnOff button and hit ENTER\r\n"); break;
			default:	
				sprintf(sMessage,"%s\r\n'i'=toggle auto-next-pin,\t'-'=toggle direction,\t'x'=delete pin\r\n'l'=list,\t'c'=reset and 's'=next stage",sMessage);
				if (wScanConfig & SCAN_AutoInc)
					sprintf(sMessage,"%s\r\nRET to pause/continue\r\nnow %s",sMessage,aoPin[iTest].s);
				else
					sprintf(sMessage,"%s\r\nRET for next pin\r\nnow %s",sMessage,aoPin[iTest].s);
		}
		//sprintf(sMessage,"\r\nnow %s",aoPin[iTest].s);

		iTestStart = iTest;
		msTicksWait = msTicks + 300;
		return;	// to allow sMessage to be sent
	}
	
	int8_t iFound = -1;
	uint8_t bCommand = 2;	// decremented to 0 if the two switch sections have no case
	uint16_t iTimeCountdown = msTicksTest-msTicks;
	switch (wStage)
	{
	case AUTODETECT_Stage_Led:
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
		break;
	case AUTODETECT_Stage_VBatt:
		fVBatt = fVBatt * 0.9 + ((float)adc_buffer.v_batt * ADC_BATTERY_VOLT) * 0.1;
		if (buzzerTimer % 16000 == 0)	// 16 kHz
			sprintf(sMessage,"%s: VBATT ?= %.2f\r\n",aoPin[iTest].s,fVBatt);
		
		switch(cCommand)
		{
		case 'v': iFound = 6; msTicksTest = 0; break;
		default : bCommand--;
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
			#define MS_INTERVAL 500
			uint16_t iInterval = MS_INTERVAL - (iTimeCountdown % MS_INTERVAL);
			int16_t iPwm = iInterval<(MS_INTERVAL/2) ? -700 : 700;
			SetPWM(	iPwm);	// strong motor to see a load when hand on motor
			fCurrentDC = ((adc_buffer.v_batt - iOffsetDC) * MOTOR_AMP_CONV_DC_AMP);
			
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
			
			//if (buzzerTimer % 1500 == 0)	// 16 kHz
			//	sprintf(sMessage,"%s: CURRENT_DC ?= %.2f %i %i %i\r\n",aoPin[iTest].s,fCurrentDC,iPwm,iInterval,iAverage);
			
		}
		switch(cCommand)
		{
			case 'f': iFound = 7; msTicksTest = 0; break;
			default : bCommand--;
		}
		break;
	case AUTODETECT_Stage_Hold:
		
		switch (iRepeat)
		{
		case 1:
		case 3:
			if (iVBatMinTest > adc_buffer.current_dc)
				iVBatMinTest = adc_buffer.current_dc;
			
			//digitalWrite(aoPin[iTest].i,1);	// relase SELF_HOLD for a short time
			digitalWrite(aoPin[iTest].i,(buzzerTimer%8000) < 500 ? 0 : 1);	// relase SELF_HOLD for a short time
			break;
		}

		switch(cCommand)
		{
		case ' ': 
			if (	(iRepeat==0) || (iRepeat==2)	)
			{
				iRepeat++;
				iTestStart = iTest; 
				msTicksTest = msTicks+100; 
				sprintf(sMessage,"\r\n%i now %s : ",iRepeat,aoPin[iTest].s);
				
			}
			cCommand = 0;
			break;
		default : bCommand--;
		}
		break;
	case AUTODETECT_Stage_Button:
		SetPWM(0);
		uint8_t bOn = digitalRead(aoPin[iTest].i);
		switch (iRepeat)
		{
		case 1:
			aoPin[iTest].wState = (aoPin[iTest].wState & ~STATE_OFF) | bOn * STATE_OFF;
			break;
		case 3:
			aoPin[iTest].wState = (aoPin[iTest].wState & ~STATE_ON) | bOn * STATE_ON;
			break;
		}

		switch(cCommand)
		{
		case ' ': 
			if (	(iRepeat==0) || (iRepeat==2)	)
			{
				iRepeat++;
				iTestStart = iTest; 
				msTicksTest = msTicks+100; 
			}
			cCommand = 0;
			break;
		default : bCommand--;
		}
		
		break;
	}

	
	if (!(wScanConfig & SCAN_AutoInc) && !(wStage & (AUTODETECT_Stage_CurrentDC|AUTODETECT_Stage_Hold|AUTODETECT_Stage_Button))	)
		msTicksTest = msTicks + 50;	// never 
	
	switch(cCommand)	// general serial commands that apply to all stages
	{
	case 'l': ListFound(iFrom,iTo); break;
	case 'i': 
			if (wScanConfig & SCAN_AutoInc)
					wScanConfig -= SCAN_AutoInc;
			else
					wScanConfig |= SCAN_AutoInc;
			
			sprintf(sMessage, (wScanConfig & SCAN_AutoInc) ? "auto inc\r\n" : "manual inc\r\n");
		break;
	case ' ': 
		if (wScanConfig & SCAN_AutoInc)
		{
			if (!iMove)
			{
				iMove=1; sprintf(sMessage, "continue\r\n");
			}
			else
			{
				iMove=0; sprintf(sMessage, "pause\r\n");
			}
		}
		else
		{
			msTicksTest = 0; // skip this test interval
		}
		break;
	case '-': iMove *= -1; sprintf(sMessage, "direction: %i\r\n",iMove); break;
	case 'x': 
		HidePinDigital(aoPin[iTest].i); 
		if (iTest == iTestStart)	iTestStart = -1;
		msTicksTest = 0; // skip this test interval
		break;
	case 'c': 
		for (i=iFrom;i<iTo;i++)	aiPinScan[i] = 0; 
			
		iMove = +1;
		ScanInit(0);
		sprintf(sMessage, "all pins cleared.");
		break;
	case 's': 	// save
			ListFound(iFrom,iTo);
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
		sprintf(sMessage, "%s = %s\r\n",	asScan[iFound],GetPinName(aoPin[iTest].i)	);
		
		if (!(wScanConfig & SCAN_AutoInc))
		{
			msTicksTest = 0; // skip this test interval
		}
	}
	if (msTicks > msTicksTest)
	{
		switch (wStage)
		{
		case AUTODETECT_Stage_CurrentDC:
			if (iAverageMax < iAverage)
			{
				iTestPin = iTest;
				iAverageMax = iAverage;
			}
			break;
		case AUTODETECT_Stage_Hold:
			switch (iRepeat)
			{
			case 1:
				sprintf(sMessage,"%i",iVBatMinTest);
				aoPin[iTest].iAdc = iVBatMinTest;
				break;
			case 3:
				aoPin[iTest].iAdc -= iVBatMinTest;
				sprintf(sMessage,"-%i = %i",iVBatMinTest,aoPin[iTest].iAdc);
				break;
			default: return;
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
					switch (iRepeat)
					{
					case 1:
						iRepeat++;
						sprintf(sMessage,"%s\r\nrelease OnOff button and hit ENTER",sMessage);
						break;
					case 3:
						iRepeat = 0;
						uint16_t iMax = 0;
						for (i=0;i<COUNT_PinDigital; i++)	
						{
							if (!(aoPin[i].wState & STATE_HIDE))
							{
								uint16_t iDelta = ABS(aoPin[i].iAdc);
								if ( (iDelta < 1000) && (iMax < iDelta)	)	// voltage drop can not be larger then 1000/4096 * 3.3V
								{
									iMax = iDelta;
									iTestPin = i;
								}
							}
						}
						aiPinScan[8] = aoPin[iTestPin].i;
						sprintf(sMessage,"%s\r\n#define SELF_HOLD %s //%i\r\nbridge OnOff button and hit ENTER",sMessage,aoPin[iTestPin].s,iMax);
						break;
					}
					break;
				}
				sprintf(sMessage,"%s\r\n%i now %s : ",sMessage,iRepeat,aoPin[iTest].s);
				break;
			case AUTODETECT_Stage_CurrentDC:
				if (iTest == iTestStart)	// a complete cycle of available adc pins
				{
					sprintf(sMessage," : %i\r\n#define CURRENT_DC = %s //%i\r\nnow %s",iAverage,aoPin[iTestPin].s,iAverageMax,aoPin[iTest].s);
					aiPinScan[7] = aoPin[iTestPin].i;
					iTestPin = iAverage = 0;	// reset for next cycle
					iAverageMax =-32767;
				}
				else
					sprintf(sMessage," : %i\r\nnow %s",iAverage,aoPin[iTest].s);
				break;
			case AUTODETECT_Stage_Button:
				if (iTest == iTestStart)	// a complete cycle of available adc pins
				{
					switch (iRepeat)
					{
					case 1:
						sprintf(sMessage,"bridge OnOff button and hit ENTER\r\n");
						//msTicksWait = msTicks + 300;
						iRepeat = 2;
						break;
					case 3:
						sprintf(sMessage,"");
						for (i=0;i<COUNT_PinDigital; i++)	
						{
							if (!(aoPin[i].wState & STATE_HIDE))
							{
								if (!(aoPin[i].wState & STATE_OFF) && (aoPin[i].wState & STATE_ON))
								{
									aiPinScan[9] = aoPin[i].i;
									sprintf(sMessage,"%s#define BUTTON\t%s\r\n",sMessage,aoPin[i].s);
								}
							}
						}
						sprintf(sMessage,"%srelease OnOff button and hit ENTER\r\n",sMessage);
						//msTicksWait = msTicks + 300;
						iRepeat = 0;
					}
				}
				break;
			default:
				sprintf(sMessage, "try %s\r\n",aoPin[iTest].s);
			}		
			
			ScanInit(iTest);
		}
		else
		{
			
			AutoDetectNextStage();
			sprintf(sMessage, "now stage %i\r\n",wStage);
		}
	}
}



	

uint8_t bHallOld = 2;
//uint8_t iHall = 0;


uint32_t msTicksAuto = 0;
uint8_t posAuto = 1;
uint8_t posOld = 0;
uint32_t msTicksOld;
uint8_t iPhaseCurrent = 0;


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
	
	HALL_A = aoPin[ aPinHall[ aHallOrder[iTest][0] ] ].i;
	HALL_B = aoPin[ aPinHall[ aHallOrder[iTest][1] ] ].i;
	HALL_C = aoPin[ aPinHall[ aHallOrder[iTest][2] ] ].i;

	msTicksTest = msTicks + 1000;
	msTicksOld = 0;
	iRepeat = 0;
}




uint8_t AutodetectBldc(uint8_t posNew,uint16_t buzzerTimer)
{
		if (!(wStage & AUTODETECT_Stage_HallOrder|AUTODETECT_Stage_HallOrder))
			return posNew;
		
		
		SetPWM(msTicks > 500 ? -150 : (int32_t)msTicks * -2 / 5);

		if (msTicks - msTicksAuto >= 15)
		{
			posAuto++;
			if (posAuto == 7)	posAuto = 1;
			//pos = posAuto;
			msTicksAuto = msTicks;
		}

		if (msTicksWait > msTicks)	// wait for last sMessage to be sent
			return posAuto;
		
		// AUTODETECT_Stage_Startup
		if (	(wStage == AUTODETECT_Stage_Startup) && (msTicks > 1000)	)
		{
			AutoDetectNextStage();
		}

		
		// AUTODETECT_Stage_Hall
		if (wStage == AUTODETECT_Stage_Hall)		// find the three hall pins :-)
		{
			if (wStageOld != wStage)
			{
				AutoDetectHallInit();
				iTestPin = iPhaseCurrent = 0;
				iTest = COUNT_PinDigital-1;
				iMove = 1;
				SetNextTestPin();
				iTestStart = iTest;
				sprintf(sMessage, "\r\nhall and phase currents: 'r'=restart\t's'=save\r\ntry %i = %s\t",iTest,aoPin[iTest].s);

				wStageOld = wStage;
			}

			uint8_t bCommand = 1;
			switch(cCommand)
			{
			case 'r': 
				wStage = AUTODETECT_Stage_Startup;
				//sprintf(sMessage, "\trestart\r\n");
				AutoDetectSetStage(AUTODETECT_Stage_Hall);
				break;
			case 's': 
				if (iTestPin == 3)
				{
					HallList();
					AutoDetectNextStage();
				}
				break;
			default : bCommand--;
			}
			
			if (bCommand) 
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
					if (	(iTime > 8) && (iTime < 50)	)	// the hall on-time should match the rotation speed
					{
						//sprintf(sMessage, "repeat %i = %s : %i ms %i\r\n",iTest,aoPin[iTestPin].s,iTime,iRepeat);
						if (5 == iRepeat++)
						{
							if (iTestPin < 3)
							{
								aPinHall[iTestPin] = iTest;
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
					else if (	(iTime < 2) && (aoPin[iTest].wState & STATE_ADC) 	)	// could be a adc phase current pin
					{
						//sprintf(sMessage, "repeat %i = %s : %i ms %i\r\n",iTest,aoPin[iTestPin].s,iTime,iRepeat);
						if (5 == iRepeat++)
						{
							if (iPhaseCurrent < 3)
							{
								aPinHall[3+iPhaseCurrent] = aoPin[iTest].i;
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
							HallList();
							AutoDetectNextStage();
					}
					else
					{
						AutoDetectSetStage(AUTODETECT_Stage_Startup);	// try again :-/
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
						
						HallList();

						uint8_t i;
						for (i=0; i<3; i++)	HidePinDigital(aoPin[aPinHall[i]].i);
						
						
						//wStage++;
						//AutoDetectSetStage(AUTODETECT_Stage_Hold);	// jump ahead for testing a specific stage
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
