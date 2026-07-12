#include "libraries/keys.h"
#include "libraries/encoder.h"
#include "libraries/serial.h"
#include "variables.h"
#include "output.h"
#include "event.h"
#include "stateMachine.h"
#include <stdlib.h>

unsigned char __CHANGER_FLAG__ = 0;
unsigned char __WAIT_COMMAND_FLAG__ = 0;
unsigned char __UPPER_LIMIT_FLAG__ = 1;
unsigned char __LOWER_LIMIT_FLAG__ = 0;
unsigned char __ALARM_TRIGGERED_FLAG__ = 0;
static unsigned char encoderPos = 0;

void smInit(void){
	keysInit();
}

void smLoop(void){
	unsigned char event;
	unsigned char i = 0;
	char c;
	char buffer[5];

	event = eventRead();

	state_List_Node *state_Node = getNode();
	if (__CHANGER_FLAG__ == 0 && __WAIT_COMMAND_FLAG__ == 0){
		if (event == EV_RIGHT){
			state_Node = state_Node->next;
			setState(state_Node);
		}
		if (event == EV_LEFT){
			state_Node = state_Node->prev;
			setState(state_Node);
		}
		if (event == EV_ENTER){
			if (getState() < NUM_STATES){
			state_Node = state_Node->subList;
			}
			if (getState() >= NUM_STATES){
				state_Node = state_Node->main;
			}
			setState(state_Node);
		}
	}
	if (event == EV_ENCODER_ENTER && ((getState() >= NUM_STATES) && __WAIT_COMMAND_FLAG__ == 0)){
			switch(getState()){
				case SUB_STATE_ALARM:
					if (__CHANGER_FLAG__ == 1){
						__CHANGER_FLAG__ = 0;
					}else{
						__CHANGER_FLAG__ = 1;
					}
					break;
				case SUB_STATE_TIME:
					if (__CHANGER_FLAG__ == 1){
						__CHANGER_FLAG__ = 0;
					}else{
						__CHANGER_FLAG__ = 1;
					}
					break;
				case SUB_STATE_LANGUAGE_1:
					setLanguage(PORTUGUESE);
					break;
				case SUB_STATE_LANGUAGE_2:
					setLanguage(ENGLISH);
					break;
				case SUB_STATE_LANGUAGE_3:
					setLanguage(FRENCH);
					break;
				case SUB_STATE_LANGUAGE_4:
					setLanguage(GERMAN);
					break;
				case SUB_STATE_LANGUAGE_5:
					setLanguage(ITALIAN);
					break;

			}
	}
	if (__CHANGER_FLAG__ != 0 && __WAIT_COMMAND_FLAG__ == 0){


		if (getEncoderPosition() > encoderPos){
			if (__UPPER_LIMIT_FLAG__ == 1){
				addUpperLimit();
			}else{
				addLowerLimit();
			}


		}
		if (getEncoderPosition() < encoderPos ){
			if (__UPPER_LIMIT_FLAG__ == 1){
				subtractUpperLimit();
			}
			else{
				subtractLowerLimit();
			}


		}

		if (event == EV_RIGHT){
			if (__UPPER_LIMIT_FLAG__ == 1){
				__UPPER_LIMIT_FLAG__ = 0;
				__LOWER_LIMIT_FLAG__ = 1;
			}
			else{
				__UPPER_LIMIT_FLAG__ = 1;
				__LOWER_LIMIT_FLAG__ = 0;
			}
		}

		if (event == EV_LEFT){
			if (__UPPER_LIMIT_FLAG__ == 1){
				__UPPER_LIMIT_FLAG__ = 0;
				__LOWER_LIMIT_FLAG__ = 1;
			}
			else{
				__UPPER_LIMIT_FLAG__ = 1;
				__LOWER_LIMIT_FLAG__ = 0;
			}
		}
		encoderPos = getEncoderPosition();

	}
	if (event == EV_WAIT_COMMAND_START){
		__WAIT_COMMAND_FLAG__ = 1;

	}
	if (__WAIT_COMMAND_FLAG__ != 0){
		if (event == EV_UPPER_LIMIT_COMMAND){
			i = 0;
			while (i < 4){
				c = readChar();

				if (c == '\r' || c == '\n'){
					__WAIT_COMMAND_FLAG__ = 0;
					break;
				}

				if ( c != 0 && ((c < 48 || c > 57) && (c != '\r' && c != '\n') && (c != 127 && c != 8))){
					sendString("Invalid character!");
				}
				else{
					if(c >= 48 && c <= 57){
						buffer[i] = c;
						i++;
					}
				}
			}
			buffer[i] = '\0';

			if ((i - 1) >= 0){
				setUpperLimit(atoi(buffer));
			}
		}
		if (event == EV_LOWER_LIMIT_COMMAND){
			i = 0;
			while (i < 4){
				c = readChar();

				if (c == '\r' || c == '\n'){
					__WAIT_COMMAND_FLAG__ = 0;
					break;
				}

				if ( c != 0 && ((c < 48 || c > 57) && (c != '\r' && c != '\n') && (c != 127 && c != 8))){
					sendString("Invalid character!");
				}
				else{
					if(c >= 48 && c <= 57){
						buffer[i] = c;
						i++;
					}
				}
			}
			buffer[i] = '\0';

			if ((i - 1) >= 0){
				setLowerLimit(atoi(buffer));
			}
		}
		if (event == EV_LAST_ALARM_TRIGGERED_COMMAND){
			sendChar(((getLastHrAlarmTriggered() / 10)) + 48);
			sendChar(((getLastHrAlarmTriggered() / 1) % 10) + 48);
			sendChar(':');
			sendChar(((getLastMinAlarmTriggered() / 10)) + 48);
			sendChar(((getLastMinAlarmTriggered() / 1) % 10) + 48);
			sendChar(':');
			sendChar(((getLastSegAlarmTriggered() / 10)) + 48);
			sendChar(((getLastSegAlarmTriggered() / 1) % 10) + 48);
			sendChar(' ');
			__WAIT_COMMAND_FLAG__ = 0;
		}
	}
	if (event == EV_ALARM_TRIGGERED){
		__ALARM_TRIGGERED_FLAG__ = 1;
		setLastSegAlarmTriggered(getSeg());
		setLastMinAlarmTriggered(getMin());
		setLastHrAlarmTriggered(getHr());

	}
	else{
		__ALARM_TRIGGERED_FLAG__ = 0;
	}


	outputPrint(getState(), getLanguage());

}
