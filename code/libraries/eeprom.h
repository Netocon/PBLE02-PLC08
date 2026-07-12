
#ifndef EEPROM_H_
#define EEPROM_H_

#include <stdint.h>

void EEPROM_Init(void);
void EEPROM_WriteByte(uint16_t address, uint8_t data);
uint8_t EEPROM_ReadByte(uint16_t address);



#endif
