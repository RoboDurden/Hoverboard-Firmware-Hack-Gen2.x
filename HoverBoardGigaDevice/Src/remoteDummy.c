#include "../Inc/defines.h"

#ifdef REMOTE_DUMMY


extern int32_t steer;
extern int32_t speed;
extern uint32_t msTicks;

void RemoteUpdate(void)
{
	#ifdef MASTER_OR_SINGLE
		speed = 3 * (ABS((	((int32_t)msTicks/30+100) % 400) - 200) - 100);
		speed = CLAMP(speed , -1000, 1000);
		//speed = 100;
		//speed = 0;	// uncomment this to turn the motor manually when TEST_HALL2LED
	#else
		SetEnable(SET);
		SetPWM(-speed);
		ResetTimeout();
	#endif
	
	
}

void RemoteCallback(void){};

#endif