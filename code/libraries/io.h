#include <stdint.h>

#ifndef IO_H_
#define IO_H_

#define PIO0 0
#define PIO1 1

#define OUTPUT 1
#define INPUT 0

#define HIGH 1
#define LOW 0

#define MODE_BIT_FUNC(mode, arg, bit) ((mode == 0) ? (BitClr(arg, bit)) : (BitSet(arg, bit)))

#define SW9_BIT 20
#define SW8_BIT 27
#define SW7_BIT 26
#define ENCODER_SW_BIT 24

	void systemIOInit(void);
	void pinMode(uint32_t port, uint32_t bit, uint32_t mode);
	void digitalWrite(uint32_t port, uint32_t bit, uint32_t mode);
	int digitalRead(uint32_t port, uint32_t bit);

#endif
