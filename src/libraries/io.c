#include "system_LPC11Uxx.h"
#include "LPC11Uxx.h"
#include "bit.h"
#include <stdint.h>

#define PIO0 0
#define PIO1 1
#define OUTPUT 1
#define INPUT 0
#define HIGH 1
#define LOW 0
#define MODE_BIT_FUNC(mode, arg, bit) ((mode == 0) ? (BitClr(arg, bit)) : (BitSet(arg, bit)))

void systemIOInit(void){
	if (~(BitTst(LPC_SYSCON->SYSAHBCLKCTRL, 16))){
		BitSet(LPC_SYSCON->SYSAHBCLKCTRL, 16); //CASO O CLOCK DO AHB PARA O BLOCO IOCON ESTIVER DESLIGADO, LIGA
	}

	if(~(BitTst(LPC_SYSCON->SYSAHBCLKCTRL, 6))){ //CASO O CLOCK DO AHB PARA O BLOCO GPIO ESTIVER DESLIGADO, LIGA
		BitSet(LPC_SYSCON->SYSAHBCLKCTRL, 6);
	}

	BitSet(LPC_SYSCON->SYSAHBCLKCTRL, 19);
	LPC_SYSCON->PINTSEL[0] = 0x7; //CANAL A DO ENCODER
	LPC_SYSCON->PINTSEL[1] = 0x34; //CANAL B DO ENCODER

	BitClr(LPC_GPIO_PIN_INT->ISEL, 0); // CONFIGURA O PINO 0 (CANAL A) DA INTERRUPÇÃO COMO EDGE-SENSITIVE
	BitClr(LPC_GPIO_PIN_INT->ISEL, 1); // CONFIGURA O PINO 1 (CANAL B) DA INTERRUPÇÃO COMO EDGE-SENSITIVE
	BitSet(LPC_GPIO_PIN_INT->IENR, 0);
	BitSet(LPC_GPIO_PIN_INT->IENR, 1);
	BitClr(LPC_GPIO_PIN_INT->CIENR, 0);
	BitClr(LPC_GPIO_PIN_INT->CIENR, 1);




}

void pinMode(uint32_t port, uint32_t bit, uint32_t mode){
	if (( (port == PIO0 )|| (port == PIO1) ) && ( (mode == INPUT) || (mode == OUTPUT) ) ){
		if ((port == PIO0) && (bit <= 23)){
			switch (bit){
				case 0: LPC_IOCON->RESET_PIO0_0 = 0X000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit);break;
				case 1: LPC_IOCON->PIO0_1 = 0x000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit); break;
				case 2: LPC_IOCON->PIO0_2 = 0x000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit); break;
				case 3: LPC_IOCON->PIO0_3 = 0x000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit); break;
				case 4: LPC_IOCON->PIO0_4 = 0x000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit); break;
				case 5: LPC_IOCON->PIO0_5 = 0x000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit); break;
				case 6: LPC_IOCON->PIO0_6 = 0x000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit); break;
				case 7: LPC_IOCON->PIO0_7 = 0x000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit); break;
				case 8: LPC_IOCON->PIO0_8 = 0x000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit); break;
				case 9: LPC_IOCON->PIO0_9 = 0x000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit); break;
				case 10: LPC_IOCON->SWCLK_PIO0_10 = 0x000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit); break;
				case 11: LPC_IOCON->TDI_PIO0_11 = 0x000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit); break;
				case 12: LPC_IOCON->TMS_PIO0_12 = 0x000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit); break;
				case 13: LPC_IOCON->TDO_PIO0_13 = 0x000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit); break;
				case 14: LPC_IOCON->TRST_PIO0_14 = 0x000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit); break;
				case 15: LPC_IOCON->SWDIO_PIO0_15 = 0x000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit); break;
				case 16: LPC_IOCON->PIO0_16 = 0x000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit); break;
				case 17: LPC_IOCON->PIO0_17 = 0x000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit); break;
				case 18: LPC_IOCON->PIO0_18 = 0x000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit); break;
				case 19: LPC_IOCON->PIO0_19 = 0x000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit); break;
				case 20: LPC_IOCON->PIO0_20 = 0x000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit); break;
				case 21: LPC_IOCON->PIO0_21 = 0x000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit);break;
				case 22: LPC_IOCON->PIO0_22 = 0x000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit); break;
				case 23: LPC_IOCON->PIO0_23 = 0x000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit); break;

			}
		}
		if (port == PIO1 && (bit <= 31)){
			switch (bit){
				case 0: LPC_IOCON->PIO1_0 = 0X000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit);break;
				case 1: LPC_IOCON->PIO1_1 = 0X000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit);break;
				case 2: LPC_IOCON->PIO1_2= 0X000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit);break;
				case 3: LPC_IOCON->PIO1_3 = 0X000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit);break;
				case 4: LPC_IOCON->PIO1_4 = 0X000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit);break;
				case 5: LPC_IOCON->PIO1_5 = 0X000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit);break;
				case 6: LPC_IOCON->PIO1_6 = 0X000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit);break;
				case 7: LPC_IOCON->PIO1_7 = 0X000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit);break;
				case 8: LPC_IOCON->PIO1_8 = 0X000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit);break;
				case 9: LPC_IOCON->PIO1_9 = 0X000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit);break;
				case 10: LPC_IOCON->PIO1_10 = 0X000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit);break;
				case 11: LPC_IOCON->PIO1_11 = 0X000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit);break;
				case 12: LPC_IOCON->PIO1_12 = 0X000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit);break;
				case 13: LPC_IOCON->PIO1_13 = 0X000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit);break;
				case 14: LPC_IOCON->PIO1_14 = 0X000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit);break;
				case 15: LPC_IOCON->PIO1_15 = 0X000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit);break;
				case 16: LPC_IOCON->PIO1_16 = 0X000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit);break;
				case 17: LPC_IOCON->PIO1_17 = 0X000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit);break;
				case 18: LPC_IOCON->PIO1_18 = 0X000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit);break;
				case 19: LPC_IOCON->PIO1_19 = 0X000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit);break;
				case 20: LPC_IOCON->PIO1_20 = 0X000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit);break;
				case 21: LPC_IOCON->PIO1_21 = 0X000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit);break;
				case 22: LPC_IOCON->PIO1_22 = 0X000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit);break;
				case 23: LPC_IOCON->PIO1_23 = 0X000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit);break;
				case 24: LPC_IOCON->PIO1_24 = 0X000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit);break;
				case 25: LPC_IOCON->PIO1_25 = 0X000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit);break;
				case 26: LPC_IOCON->PIO1_26 = 0X000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit);break;
				case 27: LPC_IOCON->PIO1_27 = 0X000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit);break;
				case 28: LPC_IOCON->PIO1_28 = 0X000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit);break;
				case 29: LPC_IOCON->PIO1_29 = 0X000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit);break;
				case 30: LPC_IOCON->PIO1_30 = 0X000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit);break;
				case 31: LPC_IOCON->PIO1_31 = 0X000; MODE_BIT_FUNC(mode, LPC_GPIO->DIR[port], bit);break;

			}
		}

	}

}

void digitalWrite(uint32_t port, uint32_t bit, uint32_t mode){
	if (((port == PIO0) || (port == PIO1)) && ((mode == HIGH) || (mode == LOW)) && (bit >= 0)){
		if (BitTst(LPC_GPIO->DIR[port], bit)){
			if (mode == LOW){BitSet(LPC_GPIO->CLR[port], bit);}
			else BitSet(LPC_GPIO->SET[port], bit);

		}
	}
}

int digitalRead(uint32_t port, uint32_t bit){
			if (port == PIO0 && bit <= 23){
				if(BitTst(LPC_GPIO->PIN[0], bit)){
					return 1;
				}
				else return 0;
			}
			if (port == PIO1 && bit <= 31){
				if (BitTst(LPC_GPIO->PIN[1], bit)){
					return 1;
				}
				else return 0;
			}

	return 0;
}
