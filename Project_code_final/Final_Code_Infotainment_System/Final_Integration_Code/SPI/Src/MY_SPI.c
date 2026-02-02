/*
 * MY_SPI.c
 *
 *  Created on: Oct 30, 2025
 *      Author: raghav
 */

#include "MY_SPI.h"
#include "MY_PIN.h"

void SPI_INIT() {
	GPIO_SPI_1_INIT(MISO);
	GPIO_SPI_1_INIT(MOSI);
	GPIO_SPI_1_INIT(SCK);
	GPIO_SPI_1_CS(CS);

	//Enable the clock for the SPI1
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

	//Set the baud rate
	SPI_CAN->CR1 |= SPI_CR1_BR_1;
	SPI_CAN->CR1 &= ~SPI_CR1_BR_0;
	SPI_CAN->CR1 &= ~SPI_CR1_BR_2;

	//Set the CPOL and CPHA
	SPI_CAN->CR1 &= ~SPI_CR1_CPHA;
	SPI_CAN->CR1 &= ~SPI_CR1_CPOL;

//	//Set the data frame format as 8 bit
//	SPI_CAN->CR1 &= ~SPI_CR1_DFF;
//
//	//Set the lsbfirst
//	SPI_CAN->CR1 |= SPI_CR1_LSBFIRST;

	//Set the SSM and SSI bit
	SPI_CAN->CR1 |= SPI_CR1_SSM;
	SPI_CAN->CR1 |= SPI_CR1_SSI;

	//Set the CR2 equal to 0
	SPI_CAN->CR2 = 0;

	//Set the master pin and enable the spi
	SPI_CAN->CR1 |= SPI_CR1_MSTR;
	SPI_CAN->CR1 |= SPI_CR1_SPE;

}

void SPI_CHIP_ENABLE() {
	GPIO_SPI_1_CS_OFF(CS);
}

void SPI_CHIP_DISABLE() {
	GPIO_SPI_1_CS_ON(CS);
}


uint8_t SPI_TRANSFER(uint8_t data)
{
	while(!(SPI_CAN->SR & SPI_SR_TXE));
	SPI_CAN->DR = data;

	while(!(SPI_CAN->SR & SPI_SR_RXNE));
	return SPI_CAN->DR;
}
