#ifndef I2C_H_
#define I2C_H_


void i2cInit(void);
void i2cSend(unsigned char adress, unsigned char *data, unsigned char qtd);
void i2cReceive(unsigned char adress, unsigned char *data, unsigned char qtd);
unsigned char i2cReadReg(unsigned char addr, unsigned char reg);
void i2cWriteReg(unsigned char addr, unsigned char reg, unsigned char data);

#endif
