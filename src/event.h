#ifndef EVENT_H_
#define EVENT_H_

enum{
	EV_UP,
	EV_DOWN,
	EV_RIGHT,
	EV_LEFT,
	EV_ENTER,
	EV_NOEVENT
};

void eventInit(void);
unsigned int eventRead(void);


#endif
