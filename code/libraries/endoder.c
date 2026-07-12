#include <stdint.h>
#include "bit.h"
#include "timer.h"
#include "io.h"

#define SW9_BIT 20
#define SW8_BIT 27
#define SW7_BIT 26
#define CHANEL_B 28
#define CHANEL_A 7

static unsigned char encoderPos = 0;

void encoderInit(void) {
	systemIOInit();

	pinMode(PIO0, CHANEL_A, INPUT);
	pinMode(PIO1, CHANEL_B, INPUT);

	encoderPos = 0;
}

void encoderRotation(void) {
	unsigned char current_Signal;
	int t = 0;
	static unsigned char last_Signal = 0x00;
	unsigned char signal_A = digitalRead(PIO0, CHANEL_A);
	unsigned char signal_B = digitalRead(PIO1, CHANEL_B);
	current_Signal = (signal_A << 1) | signal_B;

	if (current_Signal != last_Signal) {
		if ((current_Signal == 0b10 && last_Signal == 0b00)
				|| (current_Signal == 0b11 && last_Signal == 0b10)
				|| (current_Signal == 0b01 && last_Signal == 0b11)
				|| (current_Signal == 0b00 && last_Signal == 0b01)) {

			encoderPos++;

		}

		if ((current_Signal == 0b01 && last_Signal == 0b00)
				|| (current_Signal == 0b11 && last_Signal == 0b01)
				|| (current_Signal == 0b10 && last_Signal == 0b11)
				|| (current_Signal == 0b00 && last_Signal == 0b10)) {

			encoderPos--;

		}
	}

	last_Signal = current_Signal;

}

unsigned char getEncoderPosition(void) {
	return encoderPos;
}

