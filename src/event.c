#include "libraries/keys.h"
#include "event.h"
#include "libraries/bit.h"

static unsigned char prev_Key;

void eventInit(void) {

	void keysInit();
	prev_Key = 0;

}

unsigned int eventRead(void) {
	unsigned char key;
	int event = EV_NOEVENT;

	key = keyRead();

	if (key != prev_Key) {
		if (BitTst(key, 0)) {
			event = EV_RIGHT;

		}
		if (BitTst(key, 1)) {
			event = EV_LEFT;

		}
	}

	prev_Key = key;
	return event;
}
