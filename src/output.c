#include "libraries/bit.h"
#include "libraries/lcd.h"
#include "stateMachine.h"
#include <stdint.h>


#define NUM_LANGUAGES 5
#define STATE 3



static char* msgs[STATE][NUM_LANGUAGES] = {
		{" Alterar alarme ", "  Change alarm  ", "Changer l'alarme", "Alarm ändern", "Cambia allarme"},
		{"Alterar tempo", "  Change time   ", "Changer le temps", "die Zeit ändern", "cambiare l'ora"},
		{"Alterar lingua", "Change language", " Changer langue ", "Sprache ändern", "cambiare lingua"}
};


static char* left_Arrow = "   <-   ";
static char* right_Arrow = "   ->   ";

void outputInit(){
	lcdInit();
}


void outputPrint(int32_t screenNum, int32_t language){


	if (screenNum == STATE_ALARM){
		lcdSetCursor(0, 0);
		lcdString(msgs[screenNum][language]);
		lcdSetCursor(1, 0);
		lcdString(left_Arrow);
		lcdString(right_Arrow);


	}
	if (screenNum == STATE_TIME){
			lcdSetCursor(0, 0);
			lcdString(msgs[screenNum][language]);
			lcdSetCursor(1, 0);
			lcdString(left_Arrow);
			lcdString(right_Arrow);


	}
	if (screenNum == STATE_LANGUAGE){
			lcdSetCursor(0, 0);
			lcdString(msgs[screenNum][language]);
			lcdSetCursor(1, 0);
			lcdString(left_Arrow);
			lcdString(right_Arrow);


	}

}
