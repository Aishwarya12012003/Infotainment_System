/*
 * MY_SPI.h
 *
 *  Created on: Oct 30, 2025
 *      Author: raghav
 */

#ifndef MY_SPI_H_
#define MY_SPI_H_

#include "stm32f4xx.h"

#define SPI_CAN SPI1

void SPI_INIT() ;
void SPI_CHIP_ENABLE();
void SPI_CHIP_DISABLE();
uint8_t SPI_TRANSFER(uint8_t data);

#endif /* MY_SPI_H_ */
