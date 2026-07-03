#include "stateMachine.h"
#include "variables.h"
#include <stdlib.h>

static char language;
static int time;
static int alarmLevel;


state_List_Node *head_State_List = NULL;
state_List_Node *tail_State_List = NULL;
state_List_Node *current_State_Node = NULL;

void addNewStateNode(unsigned char state){
	state_List_Node *new;

	new = (state_List_Node*) malloc(sizeof(state_List_Node));

	state_List_Node *current = head_State_List;
	state_List_Node *previous = NULL;



	if (head_State_List == NULL){
		head_State_List = new;
		tail_State_List = new;
		new->state = state;
		new->next = new;
		new->prev = new;

	}else{
		while(state > current->state){
			previous = current;
			current = current->next;

			if (current == head_State_List) break;
		}


		if (previous == NULL){
			head_State_List = new;


		}
		else{
			tail_State_List = new;
			previous->next = new;
		}

		tail_State_List->next = head_State_List;
		head_State_List->prev = tail_State_List;
		new->state = state;
		new->next = current;
		new->prev = previous;

		if (current == head_State_List) tail_State_List = new;
	}
}



void inicializeStateList(void){
	for (unsigned char i = 0; i < NUM_STATES; i++){
		addNewStateNode(i);
	}
}

//state_List_Node* featchNode(unsigned char state){
//
//	state_List_Node *current = head_State_List;
//	int i = 0;
//
//	while(current->state != state || i > NUM_STATES){
//		current = current->next;
//	}
//
//	return current;
//
//}

void varInit(void){

	inicializeStateList();
	current_State_Node = head_State_List;
	time = 1000;
	alarmLevel = 512;
}

char getState(void){
	return current_State_Node->state;
}

void setState(state_List_Node *state){
	current_State_Node = state;
}

state_List_Node* getNode(void){
	return current_State_Node;
}

