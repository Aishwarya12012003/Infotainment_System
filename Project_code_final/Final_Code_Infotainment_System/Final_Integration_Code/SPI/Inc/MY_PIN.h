/*
 * MY_PIN.h
 *
 *  Created on: Oct 30, 2025
 *      Author: raghav
 */

#ifndef MY_PIN_H_
#define MY_PIN_H_

#include "stm32f4xx.h"
#include "stm32f407xx.h"


//GPIO PORTS
#define A GPIOA
#define B GPIOB
#define C GPIOC


//SPI_1
//PA6(MISO) PA7(MOSI) PA5(SCK) PB2(CS)
#define MISO 6 	//PA6   //PB4(optional)
#define MOSI 7	//PA7
#define SCK  5	//PA5
#define CS	 2	//PB2

void GPIO_SPI_1_INIT(uint8_t pin);
void GPIO_SPI_1_CS(uint8_t pin);
void GPIO_SPI_1_CS_ON(uint8_t pin);
void GPIO_SPI_1_CS_OFF(uint8_t pin);



#define LED 13

void GPIO_OUTPUT(uint8_t pin);
void GPIO_OUTPUT_ON(uint8_t pin);
void GPIO_OUTPUT_OFF(uint8_t pin);

#endif /* MY_PIN_H_ */
