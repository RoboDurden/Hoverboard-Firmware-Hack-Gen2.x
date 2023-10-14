#ifndef REMOTE_UART_H
#define REMOTE_UART_H


#define REMOTE_BAUD 19200

// Only master communicates with steering device
#ifdef MASTER_OR_SINGLE

void AnswerMaster(void);


#endif	// MASTER

#endif