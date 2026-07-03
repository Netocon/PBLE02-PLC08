#include "libraries/keys.h"
#include "variables.h"
#include "output.h"
#include "event.h"
#include <stdlib.h>

void smInit(void){
	keysInit();
}

void smLoop(void){
	unsigned char event;

	event = eventRead();
	state_List_Node *state_Node = getNode();

	if (event == EV_RIGHT){
		state_Node = state_Node->next;
		setState(state_Node);
	}
	if (event == EV_LEFT){
		state_Node = state_Node->prev;
		setState(state_Node);
	}


	outputPrint(getState(), 1);

}
