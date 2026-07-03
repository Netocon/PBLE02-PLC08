#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_


#define NUM_STATES 3

enum{
	STATE_ALARM,
	STATE_TIME,
	STATE_LANGUAGE,
	STATE_FINAL

};

void smLoop(void);

#endif
