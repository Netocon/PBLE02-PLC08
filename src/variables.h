#ifndef VARIABLES_H_
#define VARIABLES_H_


typedef struct node{
	unsigned char state;
	struct node *prev;
	struct node *next;

}state_List_Node;


char getState(void);
state_List_Node* getNode(void);
void varInit(void);
void setState(state_List_Node *state);


#endif
