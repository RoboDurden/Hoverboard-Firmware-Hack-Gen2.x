#ifndef REMOTE_UART_H
#define REMOTE_UART_H


#define REMOTE_BAUD 19200

#define LOST_CONNECTION_STOP_MILLIS 500		// set speed to 0 when 500 ms no command received

// Only master communicates with steering device
#ifdef MASTER_OR_SINGLE

void AnswerMaster(void);


#endif	// MASTER

#endif