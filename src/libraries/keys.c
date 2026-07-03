#include "system_LPC11Uxx.h"
#include "LPC11Uxx.h"
#include <stdint.h>
#include <stdbool.h>
#include "bit.h"
#include "timer.h"
#include "io.h"
#include "serial.h"
const int numKeys = 3;
unsigned char debouncedKeys = 0;
int t;

void keysInit(void) {
	systemIOInit();

	pinMode(PIO1, SW9_BIT, INPUT);
	pinMode(PIO1, SW8_BIT, INPUT);
	pinMode(PIO1, SW7_BIT, INPUT);

}

unsigned char keyRead(void) {
	return debouncedKeys;
}

void keysDebounce(void) {
	int keysBits[] = { SW7_BIT, SW8_BIT, SW9_BIT };
	static unsigned char prevKey = 0x00;
	static unsigned char currentKey = 0x00;

	for (int i = 0; i < numKeys; i++) {
		if (digitalRead(PIO1, keysBits[i]))
			BitClr(currentKey, i);
		else
			BitSet(currentKey, i);
	}

	if (currentKey != prevKey) {
		t = 0;
	} else {
		t++;
		if (t == 2) {
			debouncedKeys = prevKey;
		}
	}
	prevKey = currentKey;

}
