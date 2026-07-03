#ifndef SERIAL_H_
#define SERIAL_H_

	void serialInit(void);
	void sendChar(char c);
	void sendString(char *s);
	char readChar(void);

#endif
