#ifndef DEFINES_H
#define DEFINES_H

#include "../Inc/target.h"
#include "../Inc/setup.h"
#include "../Inc/config.h"
#include "../Inc/remote.h"

#if LAYOUT == 0
	#include "defines_2-0.h"		// https://github.com/flo199213/Hoverboard-Firmware-Hack-Gen2
#elif LAYOUT == 1
	#include "defines_2-1.h"		// https://github.com/krisstakos/Hoverboard-Firmware-Hack-Gen2.1
#elif LAYOUT == 2
	#include "defines_2-2.h"		// https://github.com/krisstakos/Hoverboard-Firmware-Hack-Gen2.1
#elif LAYOUT == 3
	#include "defines_2-3.h"		// https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x/issues/20
#elif LAYOUT == 4
	#include "defines_2-4.h"		// https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x/issues/3
#elif LAYOUT == 7
	#include "defines_2-7.h"		// https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x/issues/16
#elif LAYOUT == 11
	#include "defines_2-11.h"		// https://github.com/RoboDurden/Hoverboard-Firmware-Hack-Gen2.x/issues/16
#endif


/*
#ifdef DEBUG_LED_PIN
  #define DEBUG_LedSet(bSet){gpio_bit_write(DEBUG_LED_PORT, DEBUG_LED_PIN, bSet);}
#else
  #define DEBUG_LedSet(bSet)
#endif
*/

#ifdef DEBUG_LED
#define DEBUG_LedSet(bSet,iCol){gpio_bit_write(iCol==0 ? LED_GREEN_PORT : (iCol==1 ? LED_ORANGE_PORT : LED_RED_PORT), iCol==0 ? LED_GREEN : (iCol==1 ? LED_ORANGE : LED_RED), bSet);}
#else
  #define DEBUG_LedSet(bSet,iCol)
#endif


#if defined(MASTER_OR_SLAVE) && (!defined(USART0_MASTERSLAVE)) && (!defined(USART1_MASTERSLAVE))
	#error "MASTER or SLAVE set in config.h but no USART0_MASTERSLAVE or USART1_MASTERSLAVE uncommeted in your defines_2-?.h"
#endif

#if defined(REMOTE_UART) || defined(REMOTE_UARTBUS) || defined(REMOTE_CRSF)
	#if !defined(USART0_REMOTE) && !defined(USART1_REMOTE)
		#error "a usart remote selected in config.h but neither USART0_REMOTE nor USART1_REMOTE in your defines_2-?.h
	#endif
#endif

#ifdef USART0_REMOTE	
	#if defined(MASTER_OR_SINGLE) && defined(REMOTE_BAUD)
		#define USART0_BAUD REMOTE_BAUD		// defined in remoteUart.h or remoteCrsf.h or remoteUartBus.h
	#endif
#elif defined(USART0_MASTERSLAVE)
	#ifdef MASTER_OR_SLAVE
		#define USART0_BAUD 115200
		#define USART_MASTERSLAVE USART0
	#endif
#endif

#ifdef USART1_REMOTE	
	#if defined(MASTER_OR_SINGLE) && defined(REMOTE_BAUD)
		#define USART1_BAUD REMOTE_BAUD		// defined in remoteUart.h or remoteCrsf.h or remoteUartBus.h
	#endif
#elif defined(USART1_MASTERSLAVE)
	#ifdef MASTER_OR_SLAVE
		#define USART1_BAUD 115200
		#define USART_MASTERSLAVE USART1
	#endif
#endif


/*
#ifdef HAS_USART0
	#ifdef REMOTE_BAUD
		#define USART0_REMOTE
		#define USART0_BAUD REMOTE_BAUD
	#else
		#if defined(MASTER) || defined(SLAVE)
			#define USART0_MASTERSLAVE
			#define USART_MASTERSLAVE USART0
			#define USART0_BAUD 115200
		#endif
	#endif
#endif

#ifdef HAS_USART1
	#if defined(REMOTE_BAUD) && (!defined(USART0_REMOTE))
		#define USART1_REMOTE
		#define USART1_BAUD REMOTE_BAUD
	#else
		#if (!defined(USART_MASTERSLAVE)) && (	defined(MASTER) || defined(SLAVE)	)
			#define USART1_MASTERSLAVE
			#define USART_MASTERSLAVE USART1
			#define USART1_BAUD 115200
		#endif
	#endif
#endif
*/
	
// ADC value conversion defines
#ifndef MOTOR_AMP_CONV_DC_AMP
	#define MOTOR_AMP_CONV_DC_AMP 0.201465201465  // 3,3V * 1/3 - 0,004Ohm * IL(ampere) = (ADC-Data/4095) *3,3V
#endif
#ifndef ADC_BATTERY_VOLT
	#define ADC_BATTERY_VOLT      0.024169921875 	// V_Batt to V_BattMeasure = factor 30: ( (ADC-Data/4095) *3,3V *30 )
#endif


// Useful math function defines
#define ABS(a) (((a) < 0.0) ? -(a) : (a))
#define CLAMP(x, low, high) (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))
#define MAX(x, high) (((x) > (high)) ? (high) : (x))
#define MAP(x, xMin, xMax, yMin, yMax) ((x - xMin) * (yMax - yMin) / (xMax - xMin) + yMin)

// ################################################################################

// ADC buffer struct
typedef struct
{
  uint16_t v_batt;
	uint16_t current_dc;
} adc_buf_t;

//#pragma pack(1)
typedef struct
{
  uint8_t wState;
	float currentDC; 									// global variable for current dc
	float realSpeed; 									// global variable for real Speed
	int32_t iOdom;	
} DataSlave;



#endif		// DEFINES_H
