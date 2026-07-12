#include "libraries/bit.h"
#include "libraries/lcd.h"
#include "libraries/io.h"
#include "libraries/timer.h"
#include "stateMachine.h"
#include "variables.h"
#include <stdint.h>


#define NUM_LANGUAGES 5
#define STATE 13



//static char* msgs[STATE][NUM_LANGUAGES] = {
//		{" Alterar alarme ", "  Change alarm  ", "Changer l'alarme", "Alarm ändern", "Cambia allarme"},
//		{"Alterar tempo", "  Change time   ", "Changer le temps", "die Zeit ändern", "cambiare l'ora"},
//		{"Alterar lingua", "Change language", " Changer langue ", "Sprache ändern", "cambiare lingua"}
//"Alterar tempo  ", "Change time     ", "Changer l'heure ", "Zeit andern    ", "Cambiare l'ora "
//};
static char* msgs[STATE][NUM_LANGUAGES] = {

    {"Alterar alarme ", "Change alarm    ", "Changer l'alarme", "Alarm andern   ", "Cambiare allarme"},


    {" Tempo Execucao ", "     Uptime     ", "  Temps Actif   ", "    Laufzeit    ", "  Tempo Attivo  "},


    {"Alterar lingua ", "Change language ", "Changer l'langue", "Sprache andern ", "Cambiare lingua"},


    {"Limite Sup.:", "Upper Lim.:", "Limite Sup.:", "Obergrenze :", "Limite sup.:"},


    {"Limite Inf.:", "Lower Lim.:", "Limite Inf.:", "Untergrenze:", "Limite inf.:"},


    {"Tempo: ", "Time: ", "Heure : ", "Zeit: ", "Ora: "},

    // Português
    {"Portugues      ", "Portuguese      ", "Portugais       ", "Portugiesisch  ", "Portoghese     "},

    // Inglês
    {"Ingles         ", "English         ", "Anglais         ", "Englisch       ", "Inglese        "},

    // Francês
    {"Frances        ", "French          ", "Francais        ", "Franzosisch    ", "Francese       "},

    // Alemão
    {"Alemao         ", "German          ", "Allemand        ", "Deutsch        ", "Tedesco        "},

    // Italiano
    {"Italiano       ", "Italian         ", "Italien         ", "Italienisch    ", "Italiano       "},

	{"    Atencao!    ", "   Attention!   ", "   Attention!   ", "    Achtung!    ", "  Attenzione!   "},

	{"Alarme Acionado!", "Alarm Activated!", "Alarme Activee! ", "Alarm Aktiviert!", "Allarme Attivo! "}

};

static char* left_Arrow = "   <-   ";
static char* right_Arrow = "   ->   ";

void outputInit(){
	lcdInit();
	timerInit();
	systemIOInit();

	pinMode(PIO1, PINO_LED1, OUTPUT);
	pinMode(PIO1, PINO_LED2, OUTPUT);


}


void outputPrint(int32_t screenNum, int32_t language){

	if (__ALARM_TRIGGERED_FLAG__ != 0){
		lcdSetCursor(0, 0);
		lcdString(msgs[STATE - 2][language]);
		lcdSetCursor(1, 0);
		lcdString(msgs[STATE - 1][language]);

		digitalWrite(PIO1, PINO_LED1, HIGH);
		digitalWrite(PIO1, PINO_LED2, LOW);

		delay(100);


		digitalWrite(PIO1, PINO_LED1, LOW);
		digitalWrite(PIO1, PINO_LED2, HIGH);

		delay(100);

	}

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
		if (screenNum == SUB_STATE_ALARM){
			lcdSetCursor(0,0);
			lcdString(msgs[screenNum][language]);
			lcdChar(((getUpperLimit() / 100)) + 48);
			lcdChar(((getUpperLimit() / 10) % 10) + 48);
			lcdChar(((getUpperLimit() / 1) % 10) + 48);
			if (__CHANGER_FLAG__ && __UPPER_LIMIT_FLAG__){
				lcdString("*");
			}
			else{
				lcdString("  ");
			}
			lcdSetCursor(1, 0);
			lcdString(msgs[screenNum + 1][language]);
			lcdChar(((getLowerLimit() / 100)) + 48);
			lcdChar(((getLowerLimit() / 10) % 10) + 48);
			lcdChar(((getLowerLimit() / 1) % 10) + 48);
			if (__CHANGER_FLAG__ && __LOWER_LIMIT_FLAG__){
				lcdString("*");
			}else{
				lcdString("  ");
			}
		}
		if (screenNum == SUB_STATE_TIME){
			lcdSetCursor(0,0);
			lcdString(msgs[screenNum + 1][language]);
			lcdChar(((getHr() / 10)) + 48);
			lcdChar(((getHr() / 1) % 10) + 48);
			lcdChar(':');
			lcdChar(((getMin() / 10)) + 48);
			lcdChar(((getMin() / 1) % 10) + 48);
			lcdChar(':');
			lcdChar(((getSeg() / 10)) + 48);
			lcdChar(((getSeg() / 1) % 10) + 48);
			lcdChar(' ');
			lcdSetCursor(1, 0);
			lcdString("                ");


		}
		if (screenNum == SUB_STATE_LANGUAGE_1){
			lcdSetCursor(0,0);
			lcdString(msgs[screenNum + 1][language]);
			lcdSetCursor(1, 0);
			lcdString(left_Arrow);
			lcdString(right_Arrow);

		}
		if (screenNum == SUB_STATE_LANGUAGE_2){
			lcdSetCursor(0,0);
			lcdString(msgs[screenNum + 1][language]);
			lcdSetCursor(1, 0);
			lcdString(left_Arrow);
			lcdString(right_Arrow);

		}
		if (screenNum == SUB_STATE_LANGUAGE_3){
			lcdSetCursor(0,0);
			lcdString(msgs[screenNum + 1][language]);
			lcdSetCursor(1, 0);
			lcdString(left_Arrow);
			lcdString(right_Arrow);

		}
		if (screenNum == SUB_STATE_LANGUAGE_4){
			lcdSetCursor(0,0);
			lcdString(msgs[screenNum + 1][language]);
			lcdSetCursor(1, 0);
			lcdString(left_Arrow);
			lcdString(right_Arrow);

		}
		if (screenNum == SUB_STATE_LANGUAGE_5){
			lcdSetCursor(0,0);
			lcdString(msgs[screenNum + 1][language]);
			lcdSetCursor(1, 0);
			lcdString(left_Arrow);
			lcdString(right_Arrow);

		}




}
