#ifndef REMOTE_H
#define REMOTE_H

	void RemoteCallback(void);		// must be implemented by all remotes
	void RemoteUpdate(void);			// must be implemented by all remotes


	#ifdef REMOTE_UART
		#include "../Inc/remoteUart.h"
	#endif
	#ifdef REMOTE_UARTBUS
		#include "../Inc/remoteUartBus.h"
	#endif
	#ifdef REMOTE_CRSF
		#include "../Inc/remoteCrsf.h"
	#endif
	#ifdef REMOTE_DUMMY
		#include "../Inc/remoteDummy.h"
	#endif

#endif