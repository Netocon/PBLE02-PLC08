#include "systeM_LPC11Uxx.h"
#include "LPC11Uxx.h"
#include "i2c.h"
#include "io.h"
#include "timer.h"
#include <stdint.h>

#define EEPROM_ADDR 0x50
#define EEPROM_WP_PORT 1
#define EEPROM_WP_PIN 19


void EEPROM_Init(void){
	systemIOInit();
	i2cInit();

	pinMode(EEPROM_WP_PORT, EEPROM_WP_PIN, OUTPUT);

	digitalWrite(EEPROM_WP_PORT, EEPROM_WP_PIN, HIGH);

}

void EEPROM_WriteByte(uint16_t address, uint8_t data){
	digitalWrite(EEPROM_WP_PORT, EEPROM_WP_PIN, LOW);

	unsigned char buffer[3];
	buffer[0] = (address >> 8) & 0xFF;
	buffer[1] = address & 0xFF;
	buffer[2] = data;

	i2cSend(EEPROM_ADDR, buffer, 3);

	delay(10);

	digitalWrite(EEPROM_WP_PORT, EEPROM_WP_PIN, HIGH);
}


uint8_t EEPROM_ReadByte(uint16_t address){
	unsigned char buffer[2];

	unsigned char data;

	buffer[0] = (address >> 8) & 0xFF;
	buffer[1] = address & 0XFF;

	i2cSend(EEPROM_ADDR, buffer, 2);
	i2cReceive(EEPROM_ADDR, &data, 1);

	return data;
}
