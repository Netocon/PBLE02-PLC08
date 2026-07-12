#include "stateMachine.h"
#include "variables.h"
#include "libraries/eeprom.h"
#include "libraries/LPC11Uxx.h"
#include "libraries/bit.h"
#include <stdlib.h>
#include <stdint.h>

static char language;
static int time;
static unsigned char seg;
static unsigned char min;
static int milseg;
static unsigned char hr;
static int upper_limit_alarmlevel;
static int lower_limit_alarmlevel;

static unsigned char lastSeg_alarmTriggered;
static unsigned char lastMin_alarmTriggered;
static unsigned char lastHr_alarmTriggered;

state_List_Node *head_State_List = NULL;
state_List_Node *tail_State_List = NULL;

state_List_Node* sub_Head_List[NUM_STATES] = {NULL, NULL, NULL};
state_List_Node* sub_Tail_List[NUM_STATES] = {NULL, NULL, NULL};

state_List_Node *current_State_Node = NULL;




void addNewStateNode(unsigned char state) {
	state_List_Node *new;

	new = (state_List_Node*) malloc(sizeof(state_List_Node));

	state_List_Node *current = head_State_List;
	state_List_Node *previous = NULL;

	if (head_State_List == NULL) {
		head_State_List = new;
		tail_State_List = new;
		new->state = state;
		new->next = new;
		new->prev = new;

	} else {
		while (state > current->state) {
			previous = current;
			current = current->next;

			if (current == head_State_List)
				break;
		}

		if (previous == NULL) {
			head_State_List = new;

		} else {
			previous->next = new;
		}

		if (current == head_State_List)tail_State_List = new;

		tail_State_List->next = head_State_List;
		head_State_List->prev = tail_State_List;
		new->state = state;
		new->next = current;
		new->prev = previous;

	}
}

state_List_Node* featchNode(unsigned char state) {

	state_List_Node *current = head_State_List;
	int i = 0;

	while (current->state != state || i > NUM_STATES) {
		current = current->next;
	}

	return current;

}

void addSubNodes(unsigned char main_State, unsigned char new_state) {

	state_List_Node *new;
	state_List_Node *main = featchNode(main_State);

	new = (state_List_Node*) malloc(sizeof(state_List_Node));

	state_List_Node *current;
	state_List_Node *previous = NULL;

	current = sub_Head_List[main_State];

	if (sub_Head_List[main_State] == NULL) {
		main->subList = new;
		sub_Head_List[main_State] = new;
		sub_Tail_List[main_State] = new;
		new->state = new_state;
		new->next = new;
		new->prev = new;
		new->main = main;

	} else {
		while (new_state > current->state) {
			previous = current;
			current = current->next;

			if (current == sub_Head_List[main_State])
				break;
		}

		if (previous == NULL) {
			main->subList = new;
			sub_Head_List[main_State] = new;
		}
		else{
			previous->next = new;
		}

		if (current == sub_Head_List[main_State])sub_Tail_List[main_State] = new;

		sub_Tail_List[main_State]->next = sub_Head_List[main_State];
		sub_Head_List[main_State]->prev = sub_Tail_List[main_State];

		new->state = new_state;
		new->next = current;
		new->prev = previous;
		new->main = main;
		new->main = main;

	}

}





void inicializeStateList(void) {
	unsigned char base1 = NUM_STATES;
	unsigned char base2 = base1 + NUM_SUB_STATES_ALARM;
	unsigned char base3 = base2 + NUM_SUB_STATES_TIME;
	unsigned char base4 = base3 +  NUM_SUB_STATES_LANGUAGES;
	for (unsigned char i = 0; i < NUM_STATES; i++) {
		addNewStateNode(i);
		switch (i) {
		case STATE_ALARM:
			for (int j = base1; j < base2; j++){
				addSubNodes(i, j);
			}
			break;
		case STATE_TIME:
			for (int j = base2; j < base3; j++){
				addSubNodes(i, j);
			}
			break;
		case STATE_LANGUAGE:
			for (int j = base3; j < base4 + 1; j++){
				addSubNodes(i, j);
			}
			break;
		}

	}
}

void varInit(void) {
	uint8_t *ptr1;
	uint8_t *ptr2;
	inicializeStateList();
	current_State_Node = head_State_List;
	if ((EEPROM_ReadByte(SIGNATURE_ADDR) != 0x66 && EEPROM_ReadByte(SIGNATURE_ADDR + (SIGNATURE_OFFSET - 1)) != 0x99)
			|| ((!BitTst(LPC_SYSCON->SYSRSTSTAT, 0)) && (!BitTst(LPC_SYSCON->SYSRSTSTAT, 3)))){
		seg = 0;
		min = 0;
		hr = 0;
		upper_limit_alarmlevel = 950;
		lower_limit_alarmlevel = 200;
		language = ENGLISH;

		EEPROM_WriteByte(SIGNATURE_ADDR, 0x66);
		EEPROM_WriteByte(SIGNATURE_ADDR + (SIGNATURE_OFFSET - 1), 0x99);
		EEPROM_WriteByte(LANGUAGE_ADDR, language);
		EEPROM_WriteByte(TIME_ADDR, seg);
		EEPROM_WriteByte(TIME_ADDR + 1, min);
		EEPROM_WriteByte(TIME_ADDR + 2, hr);

		ptr1 = (uint8_t*)&upper_limit_alarmlevel;
		ptr2 = (uint8_t*)&lower_limit_alarmlevel;

		for (int i = 0; i < sizeof(upper_limit_alarmlevel); i++){
			EEPROM_WriteByte(UPPER_LIMIT_ADDR + i, ptr1[i]);
			EEPROM_WriteByte(LOWER_LIMIT_ADDR + i, ptr2[i]);
		}

		BitClr(LPC_SYSCON->SYSRSTSTAT, 1);
		BitClr(LPC_SYSCON->SYSRSTSTAT, 3);
	}
	else{
		language = EEPROM_ReadByte(LANGUAGE_ADDR);
		seg = EEPROM_ReadByte(TIME_ADDR);
		min = EEPROM_ReadByte(TIME_ADDR + 1);
		hr = EEPROM_ReadByte(TIME_ADDR + 2);

		ptr1 = (uint8_t*)&upper_limit_alarmlevel;
		ptr2 = (uint8_t*)&lower_limit_alarmlevel;

		for (int i = 0; i < sizeof(upper_limit_alarmlevel); i++){
			ptr1[i] = EEPROM_ReadByte(UPPER_LIMIT_ADDR + i);
			ptr2[i] = EEPROM_ReadByte(LOWER_LIMIT_ADDR + i);
		}

		upper_limit_alarmlevel = *(uint32_t *)ptr1;
		lower_limit_alarmlevel = *(uint32_t *)ptr2;

		BitClr(LPC_SYSCON->SYSRSTSTAT, 1);
		BitClr(LPC_SYSCON->SYSRSTSTAT, 3);
	}

}

char getState(void) {
	return current_State_Node->state;
}

void setState(state_List_Node *state) {
	current_State_Node = state;
}

state_List_Node* getNode(void) {
	return current_State_Node;
}
void setLanguage(unsigned char opt){
	language = opt;
	EEPROM_WriteByte(LANGUAGE_ADDR, language);
}

unsigned char getLanguage(void){
	return language;
}

void setTime(int t){
	time = t;
}

int getTime(void){
	return time;
}

void addSeg(void){
	seg++;
	EEPROM_WriteByte(TIME_ADDR, seg);
}
void addMin(void){
	min++;
	EEPROM_WriteByte(TIME_ADDR + 1, min);
}

void addMilSeg(void){
	milseg++;
}

void addHr(void){
	hr++;
	EEPROM_WriteByte(TIME_ADDR + 2, hr);

}

unsigned char getSeg(void){
	return seg;
}

unsigned char getMin(void){
	return min;
}

int getMilSeg(void){
	return milseg;
}

unsigned char getHr(void){
	return hr;
}

void resetMilSeg(void){
	milseg = 0;
}
void resetSeg(void){
	seg = 0;
	EEPROM_WriteByte(TIME_ADDR, seg);
}

void resetMin(void){
	min = 0;
	EEPROM_WriteByte(TIME_ADDR + 1, min);
}

void resetHr(void){
	hr = 0;
	EEPROM_WriteByte(TIME_ADDR + 2, hr);
}

void addUpperLimit(void){
	upper_limit_alarmlevel++;
	if (upper_limit_alarmlevel >= 1000){
		upper_limit_alarmlevel = 0;
	}
	uint8_t *ptr = (uint8_t*)&upper_limit_alarmlevel;
	for (int i = 0; i < sizeof(upper_limit_alarmlevel); i++){
		EEPROM_WriteByte(UPPER_LIMIT_ADDR + i, ptr[i]);
	}

}

void addLowerLimit(void){
	lower_limit_alarmlevel++;
	if (lower_limit_alarmlevel >= 1000){
		lower_limit_alarmlevel = 0;
	}
	uint8_t *ptr = (uint8_t*)&lower_limit_alarmlevel;
	for (int i = 0; i < sizeof(lower_limit_alarmlevel); i++){
		EEPROM_WriteByte(LOWER_LIMIT_ADDR + i, ptr[i]);
	}
}

void subtractUpperLimit(void){
	upper_limit_alarmlevel--;
	if (upper_limit_alarmlevel < 0 ){
		upper_limit_alarmlevel = 999;
	}
	uint8_t *ptr = (uint8_t*)&upper_limit_alarmlevel;
	for (int i = 0; i < sizeof(upper_limit_alarmlevel); i++){
		EEPROM_WriteByte(UPPER_LIMIT_ADDR + i, ptr[i]);
	}
}

void subtractLowerLimit(void){
	lower_limit_alarmlevel--;
	if (lower_limit_alarmlevel < 0){
		lower_limit_alarmlevel = 999;
	}
	uint8_t *ptr = (uint8_t*)&lower_limit_alarmlevel;
	for (int i = 0; i < sizeof(lower_limit_alarmlevel); i++){
		EEPROM_WriteByte(LOWER_LIMIT_ADDR + i, ptr[i]);
	}
}

int getUpperLimit(void){
	return upper_limit_alarmlevel;
}

int getLowerLimit(void){
	return lower_limit_alarmlevel;
}

void setUpperLimit(int limit){
	upper_limit_alarmlevel = limit;
	uint8_t *ptr = (uint8_t*)&upper_limit_alarmlevel;
	for (int i = 0; i < sizeof(upper_limit_alarmlevel); i++){
		EEPROM_WriteByte(UPPER_LIMIT_ADDR + i, ptr[i]);
	}
}

void setLowerLimit(int limit){
	lower_limit_alarmlevel = limit;
	uint8_t *ptr = (uint8_t*)&lower_limit_alarmlevel;
	for (int i = 0; i < sizeof(lower_limit_alarmlevel); i++){
		EEPROM_WriteByte(LOWER_LIMIT_ADDR + i, ptr[i]);
	}

}

void setLastSegAlarmTriggered(int seg){
	lastSeg_alarmTriggered = seg;
	EEPROM_WriteByte(LAST_ALARM_TRIGGERED_ADDR, seg);
}

void setLastMinAlarmTriggered(int min){
	lastMin_alarmTriggered = min;
	EEPROM_WriteByte(LAST_ALARM_TRIGGERED_ADDR + 1, min);
}

void setLastHrAlarmTriggered(int hr){
	lastHr_alarmTriggered = hr;
	EEPROM_WriteByte(LAST_ALARM_TRIGGERED_ADDR + 2, hr);
}


unsigned char getLastSegAlarmTriggered(void){
	return EEPROM_ReadByte(LAST_ALARM_TRIGGERED_ADDR);
}

unsigned char getLastMinAlarmTriggered(void){
	return EEPROM_ReadByte(LAST_ALARM_TRIGGERED_ADDR + 1);
}

unsigned char getLastHrAlarmTriggered(void){
	return EEPROM_ReadByte(LAST_ALARM_TRIGGERED_ADDR + 2);
}

