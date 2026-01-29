/*
 * PIN_CONFIG.h
 *
 *  Created on: Jan 28, 2026
 *      Author: raghav
 */

#ifndef INC_PIN_CONFIG_H_
#define INC_PIN_CONFIG_H_

#include "stm32f4xx.h"
#include "stm32f407xx.h"

//UART Configuration
//PA2->USART2_TX			PA3->USART2_RX
#define PA GPIOA
#define TX_2 2
#define RX_2 3

void UART_PIN_INIT(uint8_t pin);

#endif /* INC_PIN_CONFIG_H_ */
