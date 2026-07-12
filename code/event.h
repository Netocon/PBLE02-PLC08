#ifndef EVENT_H_
#define EVENT_H_

enum{
	EV_UP,
	EV_DOWN,
	EV_RIGHT,
	EV_LEFT,
	EV_ENTER,
	EV_ENCODER_ENTER,
	EV_ENCODER_RIGHT,
	EV_ENCODER_LEFT,
	EV_WAIT_COMMAND_START,
	EV_UPPER_LIMIT_COMMAND,
	EV_LOWER_LIMIT_COMMAND,
	EV_LAST_ALARM_TRIGGERED_COMMAND,
	EV_ALARM_TRIGGERED,
	EV_NOEVENT
};

void eventInit(void);
unsigned int eventRead(void);
extern char serial_char;
extern unsigned int adc_value;


#endif
