/*
 * uart.h
 *
 *  Created on: Mar 28, 2025
 *      Author: admin
 */

#ifndef UART_H_
#define UART_H_

#include "stm32f4xx.h"

/*
USART2
PA2 -- TX
PA3 -- RX
*/

void UartInit(uint32_t baud);
void UartPutch(int ch);
int UartGetch(void);
void UartPuts(char *str);
void UartGets(char *str);
float nmea_to_decimal(float nmea, char dir);
void format_decimal(float val, char *buf, int precision);
void convert_utc_to_ist(const char* utc_time, char* ist_time);
void parse_gga(char* sentence, char* lat_str, char* lon_str, char* time_str);
void parse_rmc(char* sentence, char* date_str);

#endif /* UART_H_ */

