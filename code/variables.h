#ifndef VARIABLES_H_
#define VARIABLES_H_

#define SIGNATURE 0x6699
#define SIGNATURE_ADDR 0x0000
#define SIGNATURE_OFFSET 2

#define LANGUAGE_ADDR 0x0002
#define LANGUAGE_OFFSET 1

#define TIME_ADDR (LANGUAGE_ADDR + LANGUAGE_OFFSET)
#define TIME_OFFSET 3

#define UPPER_LIMIT_ADDR (TIME_ADDR + TIME_OFFSET)
#define UPPER_LIMIT_OFFSET 4

#define LOWER_LIMIT_ADDR (UPPER_LIMIT_ADDR + UPPER_LIMIT_OFFSET)
#define LOWER_LIMIT_OFFSET 4

#define LAST_ALARM_TRIGGERED_ADDR (LOWER_LIMIT_ADDR + LOWER_LIMIT_OFFSET)
#define LAST_ALARM_TRIGGERED_OFFSET 3

#define PINO_LED1 22
#define PINO_LED2 14




typedef struct node{
	unsigned char state;
	struct node *prev;
	struct node *next;
	struct node *subList;
	struct node *main;

}state_List_Node;


enum{
	PORTUGUESE,
	ENGLISH,
	FRENCH,
	GERMAN,
	ITALIAN
};

void varInit(void);

char getState(void);
state_List_Node* getNode(void);
void setState(state_List_Node *state);

void setLanguage(unsigned char opt);
unsigned char getLanguage(void);

int getTime(void);
void setTime(int t);

void addSeg(void);
void addMin(void);
void addMilSeg(void);
void addHr(void);

int getMilSeg(void);
unsigned char getSeg(void);
unsigned char getMin(void);
unsigned char getHr(void);

void resetMilSeg(void);
void resetSeg(void);
void resetMin(void);
void resetHr(void);


void subtractLowerLimit(void);
void subtractUpperLimit(void);
void addLowerLimit(void);
void addUpperLimit(void);

int getUpperLimit(void);
int getLowerLimit(void);

void setLowerLimit(int limit);
void setUpperLimit(int limit);

void setLastSegAlarmTriggered(int seg);
void setLastMinAlarmTriggered(int min);
void setLastHrAlarmTriggered(int hr);

unsigned char getLastSegAlarmTriggered(void);
unsigned char getLastMinAlarmTriggered(void);
unsigned char getLastHrAlarmTriggered(void);


#endif
