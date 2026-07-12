#include "libraries/keys.h"
#include "libraries/encoder.h"
#include "libraries/serial.h"
#include "event.h"
#include "variables.h"
#include "libraries/bit.h"

static unsigned char prev_Key;
static unsigned char prev_encoder_pos;
char serial_char;
unsigned int adc_value;

void eventInit(void) {

	keysInit();
	encoderInit();
	prev_Key = 0;

}

unsigned int eventRead(void) {
	unsigned char key;
	unsigned char encoder_pos;
	unsigned char c;


	int event = EV_NOEVENT;

	key = keyRead();
	encoder_pos = getEncoderPosition();


	if (key != prev_Key) {
		if (BitTst(key, 0)) {
			event = EV_RIGHT;

		}
		if (BitTst(key, 2)) {
			event = EV_LEFT;

		}
		if (BitTst(key, 1)){
			event = EV_ENTER;
		}
		if (BitTst(key, 3)){
			event = EV_ENCODER_ENTER;
		}
	}
	if (encoder_pos > prev_encoder_pos){
		event = EV_ENCODER_RIGHT;
	}
	if (encoder_pos < prev_encoder_pos){
		event =  EV_ENCODER_LEFT;
	}
	if (serial_char == '$' ){
		event = EV_WAIT_COMMAND_START;
	}
	if (serial_char == 'H' || serial_char == 'h'){
		event = EV_UPPER_LIMIT_COMMAND;
	}
	if (serial_char == 'L' || serial_char == 'l'){
		event = EV_LOWER_LIMIT_COMMAND;
	}
	if (serial_char == 'T' || serial_char == 't'){
		event = EV_LAST_ALARM_TRIGGERED_COMMAND;

	}
	if(adc_value <= getLowerLimit() || adc_value >= getUpperLimit()){
		event = EV_ALARM_TRIGGERED;
	}



	prev_Key = key;
	prev_encoder_pos = encoder_pos;
	return event;
}
