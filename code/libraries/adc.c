#include "bit.h"
#include "system_LPC11Uxx.h"
#include "LPC11Uxx.h"

void adcInit(void){
    BitSet(LPC_SYSCON->SYSAHBCLKCTRL, 16); // IOCON
    BitSet(LPC_SYSCON->SYSAHBCLKCTRL, 13); // ADC

    BitClr(LPC_SYSCON->PDRUNCFG, 4);   // ativar o AD

    LPC_IOCON->TDI_PIO0_11 = 0x2;

    // selecionar o canal AD0 e configurar seu clock para 4 MHz (UM10398, 25.5.1)
    // SEL = canal AD0, // CLKDIV = 11 → 48 MHz / 12 = 4 MHz
    LPC_ADC->CR = (1 << 0) | (11 << 8);

}

unsigned int adcRead(void){
    LPC_ADC->CR |= (1 << 24); // inicia conversão (bit START)

    while ((LPC_ADC->DR[0] & (1 << 31)) == 0); // espera fim (bit DONE)

    return (LPC_ADC->DR[0] >> 6) & 0x3FF; // extrai os 10 bits (resultado)
    //return 800;
}

void uint_to_str(unsigned int valor, char *buffer) {
    char temp[6];  // suficiente até 65535
    int t = 0;
    int i = 0;

    if (valor == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }

    while (valor > 0) {
        temp[t++] = (valor % 10) + '0';
        valor /= 10;
    }

    while (t > 0) {
        buffer[i++] = temp[--t];
    }
    buffer[i] = '\0';
}
