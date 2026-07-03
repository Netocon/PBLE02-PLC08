#include "timer.h"
#include "LPC11Uxx.h"
#include "system_LPC11Uxx.h"
#include "io.h"
#include "bit.h"

#define D4_PIN 16 // PORTA 1
#define D5_PIN 17 // PORTA 0
#define D6_PIN 15 //PORTA 1
#define D7_PIN 23 //PORTA 0
#define RS_PIN 25 // PORTA 1
#define E_PIN 3 // PORTA 0

void send4Bits(char c);

void sendNibble(char c);
void lcdCommand(char command);

void clockEnablePin(void) {

	//delay_us(1);
	digitalWrite(PIO0, E_PIN, HIGH);
	//delay_us(1);
	digitalWrite(PIO0, E_PIN, LOW);
}

void lcdInit(void) {

	systemIOInit();

	pinMode(PIO1, D4_PIN, OUTPUT);
	pinMode(PIO0, D5_PIN, OUTPUT);
	pinMode(PIO1, D6_PIN, OUTPUT);
	pinMode(PIO0, D7_PIN, OUTPUT);
	pinMode(PIO1, RS_PIN, OUTPUT);
	pinMode(PIO0, E_PIN, OUTPUT);
	delay(50);

	// SETA O TAMANHO DOS DADOS PARA 8 BITS (FUCTION SET)
	// 0b000011****

	sendNibble(0x03);

//	digitalWrite(PIO1, D4_PIN, HIGH);
//	digitalWrite(PIO0, D5_PIN, HIGH);
//	digitalWrite(PIO1, D6_PIN, LOW);
//	digitalWrite(PIO0, D7_PIN, LOW);
//	digitalWrite(PIO1, RS_PIN, LOW);
//
//
//
//	clockEnablePin();

	delay(5);
	// SETA O TAMANHO DOS DADOS PARA 8 BITS (FUCTION SET)
	// 0b000011****

	sendNibble(0x03);

//	digitalWrite(PIO1, D4_PIN, HIGH);
//	digitalWrite(PIO0, D5_PIN, HIGH);
//	digitalWrite(PIO1, D6_PIN, LOW);
//	digitalWrite(PIO0, D7_PIN, LOW);
//	digitalWrite(PIO1, RS_PIN, LOW);
//
//
//
//	clockEnablePin();

	delay_us(160);
	// SETA O TAMANHO DOS DADOS PARA 8 BITS (FUCTION SET)
	// 0b000011****

	sendNibble(0x03);

//	digitalWrite(PIO1, D4_PIN, HIGH);
//	digitalWrite(PIO0, D5_PIN, HIGH);
//	digitalWrite(PIO1, D6_PIN, LOW);
//	digitalWrite(PIO0, D7_PIN, LOW);
//	digitalWrite(PIO1, RS_PIN, LOW);
//
//;
//
//	clockEnablePin();

	delay_us(160);
//*******************************************************************
	// SETA O TAMANHO DO DADO PARA 4 BITS (FUCTION SET)
	//0b000010****

	sendNibble(0x02);

//	digitalWrite(PIO1, D4_PIN, LOW);
//	digitalWrite(PIO0, D5_PIN, HIGH);
//	digitalWrite(PIO1, D6_PIN, LOW);
//	digitalWrite(PIO0, D7_PIN, LOW);
//	digitalWrite(PIO1, RS_PIN, LOW);
//
//
//
//	clockEnablePin();
	delay(10);
//****************************************************************************************
	// SETA O TIPO DE FONTE PARA 5x8 (F) DOT E HABILITA AS DUAS LINHAS DO DISLPAY (N)
	//0b00NF******
	//lcdCommand(0b10000010);

	lcdCommand(0x28);

//	digitalWrite(PIO1, D4_PIN, LOW);
//	digitalWrite(PIO0, D5_PIN, HIGH);
//	digitalWrite(PIO1, D6_PIN, LOW); // SETA O TIPO DE FONTE PARA 5x8 DOT
//	digitalWrite(PIO0, D7_PIN, LOW); // HABILITA AS DUAS LINHAS DO DISLPAY
//	digitalWrite(PIO1, RS_PIN, LOW);
//
//	clockEnablePin();
//
////	digitalWrite(PIO1, RS_PIN, LOW);
////	send4Bits(0x08);
//
//	delay_us(45);
//
//
//
//	digitalWrite(PIO1, D4_PIN, LOW);
//	digitalWrite(PIO0, D5_PIN, LOW);
//	digitalWrite(PIO1, D6_PIN, LOW);
//	digitalWrite(PIO0, D7_PIN, HIGH);
//	digitalWrite(PIO1, RS_PIN, LOW);
//
//	clockEnablePin();


	//****************************************************************************************


	//LIGA O DISPLAY (D), O CURSOR E O PISCA DO CURSOR (B) - PRIMEIROS 4 BITS
	// 0b000000****

	lcdCommand(0x0C);

//	digitalWrite(PIO1, D4_PIN, LOW);
//	digitalWrite(PIO0, D5_PIN, LOW);
//	digitalWrite(PIO1, D6_PIN, LOW);
//	digitalWrite(PIO0, D7_PIN, LOW);
//	digitalWrite(PIO1, RS_PIN, LOW);
//
//	clockEnablePin();
////
//
//
//	//LIGA O DISPLAY (D), O CURSOR E O PISCA DO CURSOR (B) - ULTIMOS 4 BITS
//	// 0b001DCB****
//
//	digitalWrite(PIO1, D4_PIN, HIGH);
//	digitalWrite(PIO0, D5_PIN, HIGH);
//	digitalWrite(PIO1, D6_PIN, HIGH);
//	digitalWrite(PIO0, D7_PIN, HIGH);
//	digitalWrite(PIO1, RS_PIN, LOW);
//
//	clockEnablePin();

	delay_us(45);
	//****************************************************************************************

	// LIMPA O DISPLAY (DIPLAY CLEAR) - PRIMEIRO 4 BITS
	//0b000000****

	lcdCommand(0x01);

//	digitalWrite(PIO1, D4_PIN, LOW);
//	digitalWrite(PIO0, D5_PIN, LOW);
//	digitalWrite(PIO1, D6_PIN, LOW);
//	digitalWrite(PIO0, D7_PIN, LOW);
//	digitalWrite(PIO1, RS_PIN, LOW);
//
//	delay_us(2);
//	clockEnablePin();
//
//	delay_us(2);
//
//	// LIMPA O DISPLAY (DIPLAY CLEAR) - ULTIMOS 4 BITS
//	//0b000001****
//
//	digitalWrite(PIO1, D4_PIN, HIGH);
//	digitalWrite(PIO0, D5_PIN, LOW);
//	digitalWrite(PIO1, D6_PIN, LOW);
//	digitalWrite(PIO0, D7_PIN, LOW);
//	digitalWrite(PIO1, RS_PIN, LOW);
//
//	clockEnablePin();


	delay(3);
	//****************************************************************************************

	// CONIGURA O CURSOR DO DISPLAY PARA IR PARA DIREITA APOS O ENVIO DE 1 CARACTER - PRIMEIROS 4 BITS
	//0b000000****


	lcdCommand(0x06);;

//	digitalWrite(PIO1, D4_PIN, LOW);
//	digitalWrite(PIO0, D5_PIN, LOW);
//	digitalWrite(PIO1, D6_PIN, LOW);
//	digitalWrite(PIO0, D7_PIN, LOW);
//	digitalWrite(PIO1, RS_PIN, LOW);
//
//	clockEnablePin();
//
//	//****************************************************************************************
//
//	// CONIGURA O CURSOR DO DISPLAY PARA IR PARA DIREITA APOS O ENVIO DE 1 CARACTER - ULTIMOS 4 BITS
//	// 0b000110****
//
//	digitalWrite(PIO1, D4_PIN, LOW);
//	digitalWrite(PIO0, D5_PIN, HIGH);
//	digitalWrite(PIO1, D6_PIN, HIGH);
//	digitalWrite(PIO0, D7_PIN, LOW);
//	digitalWrite(PIO1, RS_PIN, LOW);
//
//	clockEnablePin();
//
////
	delay(2);

}

void sendNibble(char c) {

	if (BitTst(c, 0)) {
		digitalWrite(PIO1, D4_PIN, HIGH);
	} else {
		digitalWrite(PIO1, D4_PIN, LOW);
	}
	if (BitTst(c, 1)) {
		digitalWrite(PIO0, D5_PIN, HIGH);
	} else {
		digitalWrite(PIO0, D5_PIN, LOW);
	}
	if (BitTst(c, 2)) {
		digitalWrite(PIO1, D6_PIN, HIGH);
	} else {
		digitalWrite(PIO1, D6_PIN, LOW);
	}
	if (BitTst(c, 3)) {
		digitalWrite(PIO0, D7_PIN, HIGH);
	} else {
		digitalWrite(PIO0, D7_PIN, LOW);
	}

	clockEnablePin();
	//delay_us(2);
}

void lcdChar(char c) {
	digitalWrite(PIO1, RS_PIN, HIGH);

	char mask = 0x00;



	mask = (c >> 4) & 0x0F;

	sendNibble(mask);

	mask = c & 0x0F;

	sendNibble(mask);

	delay_us(50);

}

void lcdString(char *s) {
	digitalWrite(PIO1, RS_PIN, HIGH);
	int i = 0;

	while (s[i] != '\0') {

		lcdChar(s[i]);
		i++;
	}

}

void lcdCommand(char command) {
	digitalWrite(PIO1, RS_PIN, LOW);

	char mask = 0x00;

	mask = (command >> 4) & 0x0F;

	sendNibble(mask);

	mask = 0x00;

	mask = command & 0x0F;

	sendNibble(mask);

	delay(2);

}

void lcdSetCursor(unsigned char row, unsigned char col){
	const unsigned char rowOffsets[] = {0x00, 0x40};
	lcdCommand(0x80 | (rowOffsets[row] + col));
}

