#ifndef _LCD_OPS_H_
#define _LCD_OPS_H_

#include "lcd_common.h"

// LCD operation 
int  LcdWriteByte(uint8_t val);
void LcdWrite(uint8_t rs, uint8_t val);
int  LcdInit(void);
void LcdPuts(uint8_t line, char *str);

#endif
