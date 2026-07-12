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
#include "libraries/encoder.h"
#include "libraries/eeprom.h"
#include "libraries/adc.h"

#define PINO_LED1 22
#define PINO_LED2 14

#define SW9_BIT 20
#define SW8_BIT 27
#define SW7_BIT 26

int main(void) {
	EEPROM_Init();
	timerInit();
	encoderInit();
	serialInit();
	systemIOInit();
	lcdInit();
	varInit();
	eventInit();
	keysInit();
	adcInit();

	pinMode(PIO1, PINO_LED1, OUTPUT);
	pinMode(PIO1, PINO_LED2, OUTPUT);



	for (;;){

		adc_value = adcRead();
		serial_char = readChar();
		encoderRotation();
		keysDebounce();
		timerCounter();


		smLoop();

	}

    return 0 ;
}
