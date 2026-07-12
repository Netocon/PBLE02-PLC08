#include "LPC11Uxx.h"
#include "system_LPC11Uxx.h"
#include "bit.h"
#include "timer.h"


void i2cInit(void){

	BitSet(LPC_SYSCON->SYSAHBCLKCTRL, 16); // Habilitar o clock para o bloco IOCON

	LPC_IOCON->PIO0_4 = 0X01; // Configurar o pino como SCL em modo I2C padrão (I2CMODE=00)
	LPC_IOCON->PIO0_5 = 0x01; // Configurar o pino como SDA em modo I2C padrão (I2CMODE=00)

	BitSet(LPC_SYSCON->SYSAHBCLKCTRL, 5); // Habilitar o clock para o bloco I2C

	BitSet(LPC_SYSCON->PRESETCTRL, 1);  // Garantir que o periférico I2C não esteja em estado de reset

	 LPC_I2C->SCLH = 240; // Estipular o clock I2C para 100kHz
	 LPC_I2C->SCLL = 240;

	BitSet(LPC_I2C->CONSET, 6); // HABILITA A INTERFACE I2C (I2EN)

}


void i2cSend(unsigned char address, unsigned char *data, unsigned char qtd){
	unsigned char i;

	/*Definir este bit faz com que a interface I2C entre no modo mestre e
	transmita uma condição de START ou uma condição de START repetido, caso já esteja
	no modo mestre.*/
	BitSet(LPC_I2C->CONSET, 5);

	while((LPC_I2C->STAT != 0x08) && (LPC_I2C->STAT != 0x10)); // Esperar pelo pelo fim do evento de START

	LPC_I2C->DAT = (address << 1); // Enviar o endereço do dispositivo escravo(SLA) + Bit de escrita (W)
	LPC_I2C->CONCLR = (1 << 3) | (1 << 5); // Limpar a sinalizações SI e START

	 while(LPC_I2C->STAT != 0x18){   // Esperar por um estado 0x18 (ACK recebido)
		 if (LPC_I2C->STAT == 0x20) return;
	 }

	 for (i = 0; i < qtd; i++){
		 LPC_I2C->DAT = data[i];
		 LPC_I2C->CONCLR = (1 << 3); // Limpar a sinalização SI


		 while(LPC_I2C->STAT != 0x28){ // Esperar por um estado 0x28 (ACK recebido)
			 if(LPC_I2C->STAT == 0x30) return;
		 }
	 }
	    LPC_I2C->CONSET = (1 << 4); // Requisitar o evento de STOP
	    LPC_I2C->CONCLR = (1 << 3); // Limpar a sinalização SI
}

void i2cReceive(unsigned char address, unsigned char *data, unsigned char qtd){
	unsigned char i;

	BitSet(LPC_I2C->CONSET, 5);

	while((LPC_I2C->STAT != 0x08) && (LPC_I2C->STAT != 0x10)); // Esperar pelo pelo fim do evento de START


	LPC_I2C->DAT = (address << 1) | 1; // Enviar o endereço do dispositivo escravo(SLA) + Bit de leitura (R)
	LPC_I2C->CONCLR = (1 << 3) | (1 << 5); // Limpar a sinalizações SI e START


	 while(LPC_I2C->STAT != 0x40){   // Esperar por um estado 0x40 (ACK recebido)
		 if (LPC_I2C->STAT == 0x48) return;
	 }

	 for (i = 0; i < qtd; i++){
		 if (i < qtd - 1){
			 LPC_I2C->CONSET = (1 << 2); // AA = 1 (ACK)
		 }
		 else{
			 LPC_I2C->CONCLR = (1 << 2); // AA = 0 (NACK)
		 }

		 LPC_I2C->CONCLR = (1 << 3); // Limpar a sinalização SI

		 while((LPC_I2C->STAT != 0x50) && (LPC_I2C->STAT != 0x58));

		 data[i] = LPC_I2C->DAT; // Ler o dado recebido
	 }

	 LPC_I2C->CONSET = (1 << 4); // Requisitar o evento de STOP
	 LPC_I2C->CONCLR = (1 << 3); // Limpar a sinalização SI

}

unsigned char i2cReadReg(unsigned char addr, unsigned char reg){
    unsigned char data;

    i2cSend(addr, &reg, 1); // Enviar o endereço do registrador
    i2cReceive(addr, &data, 1); // Ler o dado do registrador

    return data;
}

void i2cWriteReg(unsigned char addr, unsigned char reg, unsigned char data){
    unsigned char buffer[2];

    buffer[0] = reg; // Endereço do registrador
    buffer[1] = data; // Dado a ser escrito

    i2cSend(addr, buffer, 2); // Enviar o endereço do registrador e o dado
}

