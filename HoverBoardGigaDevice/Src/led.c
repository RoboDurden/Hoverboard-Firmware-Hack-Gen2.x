#include "../Inc/defines.h"
#include "../Inc/led.h"

// Only slave has LED mechanism
#ifdef SLAVE

	// Variables which will be send to master
	FlagStatus upperLEDMaster = RESET;
	FlagStatus lowerLEDMaster = RESET;

// Lookuptable for brightness
static unsigned char su8BrightnessTable[64] = 
	{0,0,1,1,1,2,2,2,2,2,2,3,3,3,3,4,4,4,5,5,6,
	6,7,8,8,9,10,11,12,13,14,15,17,18,20,22,24,
	26,28,31,34,37,40,44,48,52,57,62,68,74,81,89,
	97,106,116,126,138,150,164,179,196,214,234,255};

// Variables for RGB output
uint8_t counter_Red = 0;
uint8_t counter_Green = 0;
uint8_t counter_Blue = 0;
uint8_t setValue_Red = 0;
uint8_t setValue_Green = 0;
uint8_t setValue_Blue = 0;
	
// Variables for HSB calculation
static uint16_t hueValue = 0;
static uint8_t saturationValue = 128;
static uint8_t brightnessValue = 63;
	
// Variable for LED-program
static LED_PROGRAM sLEDProgram = LED_OFF;

// Variables for effects
static uint16_t speedFading = 150;		// Fading-Delay	
static uint16_t speedBlink = 1274;		// Blink-Delay
static uint16_t speedStrobe = 40;			// Strobe-Delay

// Counter for effects
static uint16_t fadingCounter = 0;
static uint16_t blinkCounter = 0;
static uint16_t strobeCounter = 0;
static FlagStatus strobeToggle = RESET;

// Prototypes
uint8_t HSBtoRed(uint16_t hue, uint8_t sat);
uint8_t HSBtoGreen(uint16_t hue, uint8_t sat);
uint8_t HSBtoBlue(uint16_t hue, uint8_t sat);

/* outdated code
//----------------------------------------------------------------------------
// Update RGB LED output with 16kHz
//----------------------------------------------------------------------------
void CalculateLEDPWM(void)
{
	// Upcounting with overflow
	counter_Red++;
	counter_Green++;
	counter_Blue++;
	
	// Set LEDs
	digitalWrite(UPPER_LED, counter_Red >= setValue_Red ? RESET : SET);
	digitalWrite(LOWER_LED, counter_Green >= setValue_Green ? RESET : SET);
	digitalWrite(MOSFET_OUT, counter_Blue >= setValue_Blue ? RESET : SET);
	//gpio_bit_write(UPPER_LED_PORT, UPPER_LED_PIN, counter_Red >= setValue_Red ? RESET : SET);
	//gpio_bit_write(LOWER_LED_PORT, LOWER_LED_PIN, counter_Green >= setValue_Green ? RESET : SET);
	//gpio_bit_write(MOSFET_OUT_PORT, MOSFET_OUT_PIN, counter_Blue >= setValue_Blue ? RESET : SET);
}
*/

//----------------------------------------------------------------------------
// Update RGB LED program every 1ms
//----------------------------------------------------------------------------
void CalculateLEDProgram(void)
{
	if (GetRGBProgram() == LED_HSB_FADE)
	{
		fadingCounter++;
		if(fadingCounter >= GetSpeedFading())
		{
			fadingCounter = 0;
			SetHSBHue(GetHSBHue()+1);
		}
	}
	if (GetRGBProgram() == LED_HSB_BLINK)
	{
		blinkCounter++;
		if(blinkCounter >= GetSpeedBlink())
		{
			blinkCounter = 0;
			SetHSBHue(GetHSBHue()+50);
		}
	}
	if(GetRGBProgram() == LED_HSB_STROBE)
	{
		strobeCounter++;
		if(strobeCounter >= GetSpeedStrobe())
		{
			strobeCounter = 0;
			if(strobeToggle == RESET)
			{
				strobeToggle = SET;
				SetHSBBrightness(0);
			}
			else
			{
				strobeToggle = RESET;
				SetHSBBrightness(63);
			}
		}
	}
}

//----------------------------------------------------------------------------
// Sets LED program
//----------------------------------------------------------------------------
void SetRGBProgram(LED_PROGRAM Program)
{
	// Check program count
	if(!(Program < COUNT_PROGRAMS))
	{
		Program = LED_OFF;
	}

	// Save program for later
	sLEDProgram = Program;

	switch(Program)
	{
		case LED_HSB:
		case LED_HSB_BLINK:
		case LED_HSB_FADE:
		case LED_HSB_STROBE:
			SetHSBHue(hueValue);
			SetHSBSaturation(saturationValue);
			SetHSBBrightness(brightnessValue);
			break;
		case LED_OFF:
		default:
			setValue_Red = 0;
			setValue_Green = 0;
			setValue_Blue = 0;
			break;
	}
}

//----------------------------------------------------------------------------
// Gets LED program
//----------------------------------------------------------------------------
LED_PROGRAM GetRGBProgram(void)
{
	return sLEDProgram;
}

//----------------------------------------------------------------------------
// Sets hue from 0-764
//----------------------------------------------------------------------------
void SetHSBHue(uint16_t hue)
{
	uint8_t brightness = 0;
	
	// Save hue for later
	if (hue > 764)
	{
		hueValue = 0;
	}
	else
	{
		hueValue = hue;
	}

	// Calculate brightness with the lookuptable
	brightness = su8BrightnessTable[brightnessValue];  //input: 0..63 output: 0..255
	
	// Calculate RGB values
	setValue_Red = ((brightness + 1) * HSBtoRed(hueValue, saturationValue)) >> 8;
	setValue_Green = ((brightness + 1) * HSBtoGreen(hueValue, saturationValue)) >> 8;
	setValue_Blue = ((brightness + 1) * HSBtoBlue(hueValue, saturationValue)) >> 8;
}

//----------------------------------------------------------------------------
// Gets hue from 0-764
//----------------------------------------------------------------------------
uint16_t GetHSBHue(void)
{
	return hueValue;
}

//----------------------------------------------------------------------------
// Sets saturation from 0-128
//----------------------------------------------------------------------------
void SetHSBSaturation(uint8_t saturation)
{
	uint8_t brightness = 0;
	
	// Save Saturation for later
	saturationValue = MAX(saturation, 128);

	// Calculate brightness with the lookuptable
	brightness = su8BrightnessTable[brightnessValue];  //input: 0..63 output: 0..255
	
	// Calculate RGB values
	setValue_Red = ((brightness + 1) * HSBtoRed(hueValue, saturationValue)) >> 8;
	setValue_Green = ((brightness + 1) * HSBtoGreen(hueValue, saturationValue)) >> 8;
	setValue_Blue = ((brightness + 1) * HSBtoBlue(hueValue, saturationValue)) >> 8;
}

//----------------------------------------------------------------------------
// Gets saturation from 0-128
//----------------------------------------------------------------------------
uint8_t GetHSBSaturation(void)
{
	return saturationValue;
}

//----------------------------------------------------------------------------
// Sets brightness from 0-63
//----------------------------------------------------------------------------
void SetHSBBrightness(uint8_t brightnessVal)
{
	uint8_t brightness = 0;

	// Save brightness for later
	brightnessValue = MAX(brightnessVal, 63);

		// Calculate brightness with the lookuptable
	brightness = su8BrightnessTable[brightnessValue];  //input: 0..63 output: 0..255
	
	// Calculate RGB values
	setValue_Red = ((brightness + 1) * HSBtoRed(hueValue, saturationValue)) >> 8;
	setValue_Green = ((brightness + 1) * HSBtoGreen(hueValue, saturationValue)) >> 8;
	setValue_Blue = ((brightness + 1) * HSBtoBlue(hueValue, saturationValue)) >> 8;
}

//----------------------------------------------------------------------------
// Gets brightness from 0-63
//----------------------------------------------------------------------------
uint8_t GetHSBBrightness(void)
{
	return brightnessValue;
}

//----------------------------------------------------------------------------
// Sets fading speed from 200-1000
//----------------------------------------------------------------------------
void SetSpeedFading(uint16_t speed)
{
	speedFading = CLAMP(speed, 200, 1000);
}

//----------------------------------------------------------------------------
// Gets fading speed from 200-1000
//----------------------------------------------------------------------------
uint16_t GetSpeedFading(void)
{
	return speedFading;
}

//----------------------------------------------------------------------------
// Sets blink speed from 700-2400
//----------------------------------------------------------------------------
void SetSpeedBlink(uint16_t speed)
{
	speedBlink = CLAMP(speed, 700, 2400);
}

//----------------------------------------------------------------------------
// Gets blink speed from 700-2400
//----------------------------------------------------------------------------
uint16_t GetSpeedBlink(void)
{
	return speedBlink;
}

//----------------------------------------------------------------------------
// Sets strobe speed from 0-1000
//----------------------------------------------------------------------------
void SetSpeedStrobe(uint16_t speed)
{
	speedStrobe = CLAMP(speed, 40, 400);
}

//----------------------------------------------------------------------------
// Gets strobe speed from 0-1000
//----------------------------------------------------------------------------
uint16_t GetSpeedStrobe(void)
{
	return speedStrobe;
}

//----------------------------------------------------------------------------
// Hue to red
//----------------------------------------------------------------------------
uint8_t HSBtoRed(uint16_t hue, uint8_t sat)
{
	unsigned char red_val = 0;

	if (hue > 764)
	{
		hue = 0;
	}
	if (hue < 255) 
	{
	   red_val = (10880 - sat * (hue - 170)) >> 7;
	}
	else if (hue < 510) 
	{
	   red_val = (10880 - sat * 85) >> 7;
	}
	else 
	{
	   red_val = (10880 - sat * (595 - hue)) >> 7;
	}

	return red_val;
}

//----------------------------------------------------------------------------
// Hue to green
//----------------------------------------------------------------------------
uint8_t HSBtoGreen(uint16_t hue, uint8_t sat)
{
	uint8_t green_val = 0;

	if (hue > 764)
	{
		hue = 0;
	}
	if (hue < 255) 
	{
	   green_val = (10880 - sat * (85 - hue)) >> 7;
	}
	else if (hue < 510) 
	{
	   green_val = (10880 - sat * (hue - 425)) >> 7;
	}
	else 
	{
	   green_val = (10880 - sat * 85) >> 7;
	}

	return green_val;
}

//----------------------------------------------------------------------------
// Hue to blue
//----------------------------------------------------------------------------
uint8_t HSBtoBlue(uint16_t hue, uint8_t sat)
{
	uint8_t blue_val = 0;

	if (hue > 764)
	{
		hue = 0;
	}
	if (hue < 255) 
	{
	   blue_val = (10880 - sat * 85) >> 7;
	}
	else if (hue < 510) 
	{
	   blue_val = (10880 - sat * (340 - hue)) >> 7;
	}
	else 
	{
	   blue_val = (10880 - sat * (hue - 680)) >> 7;
	}

	return blue_val;
}

// Sets upper LED value which will be send to master
void SetUpperLEDMaster(FlagStatus value)
{
	upperLEDMaster = value;
}

// Returns upper LED value sent by master
FlagStatus GetUpperLEDMaster(void)
{
	return upperLEDMaster;
}

// Sets lower LED value which will be send to master
void SetLowerLEDMaster(FlagStatus value)
{
	lowerLEDMaster = value;
}

// Returns lower LED value sent by master
FlagStatus GetLowerLEDMaster(void)
{
	return lowerLEDMaster;
}


#endif
