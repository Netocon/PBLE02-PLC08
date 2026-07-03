
#ifndef LCD_H_
#define LCD_H_

void lcdInit(void);
void lcdChar(char c);
void lcdString(char *s);
void lcdCommand(char command);
void lcdSetCursor(unsigned char row, unsigned char col);



#endif
