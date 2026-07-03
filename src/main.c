#ifdef __USE_CMSIS
#include "LPC11Uxx.h"
#endif

#include "libraries/timer.h"
#include "libraries/serial.h"
#include "libraries/io.h"
#include "libraries/keys.h"
#include "libraries/system_LPC11Uxx.h"
#include <cr_section_macros.h>
#include "libraries/lcd.h"
#include <stdbool.h>
#include "output.h"
#include "event.h"
#include "stateMachine.h"
#include "variables.h"
#include "libraries/bit.h"

#define PINO_LED1 22
#define PINO_LED2 14

#define SW9_BIT 20
#define SW8_BIT 27
#define SW7_BIT 26

int main(void) {
	timerInit();
	serialInit();
	systemIOInit();
	lcdInit();
	varInit();
	eventInit();
	keysInit();

	pinMode(PIO1, PINO_LED1, OUTPUT);
	pinMode(PIO1, PINO_LED2, OUTPUT);

	unsigned char key1, key2, key3, key4;
	unsigned char prev_key = 0;

	key1 = digitalRead(PIO1, SW9_BIT);
	key2 = digitalRead(PIO1, SW8_BIT);
	key3 = digitalRead(PIO1, SW7_BIT);

	key4 = keyRead();


	for (;;){

//		key4 = keyRead();
//
//
//		if (key4 != prev_key){
//			sendString("A");
//			if (BitTst(key4, 0)){
//				sendString("+1");
//			}
//		}

//		if (digitalRead(PIO1,SW7_BIT) != key1){
//			if (digitalRead(PIO1,SW7_BIT) ==0){
//
//			}
//			key1 = digitalRead(PIO1, SW7_BIT);
//			sendString("+1");
//		}



		keysDebounce();

//		if (digitalRead(PIO1,SW9_BIT) != key1){
//			if (digitalRead(PIO1,SW9_BIT) ==0){
//
//			}
//			key1 = digitalRead(PIO1, SW9_BIT);
//			sendString("+1");
//		}
//
//		if (digitalRead(PIO1, SW8_BIT)!= key2){
//			sendString("+2");
//		}
//
//		if (digitalRead(PIO1, SW7_BIT)!= key3){
//			sendString("+3");
//		}

//		prev_key = key4;

		smLoop();

	}

    return 0 ;
}
