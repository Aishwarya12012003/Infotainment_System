/*
 * UART_CONFIG.h
 *
 *  Created on: Jan 28, 2026
 *      Author: raghav
 */

#ifndef INC_UART_CONFIG_H_
#define INC_UART_CONFIG_H_

#include "PIN_CONFIG.h"
#include "string.h"


void UART2_INIT();
void UART2_SEND(char *data);
//void UART2_RECEIVE(char *buff);
//void GPS_Update(void);
void Get_GNGGA_Data(char *buff, int maxLen);


#define SIZE 100
//extern char buff[SIZE];
//extern volatile int i;


#endif /* INC_UART_CONFIG_H_ */
