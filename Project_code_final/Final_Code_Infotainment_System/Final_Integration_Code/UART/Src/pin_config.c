/*
 * pin_config.c
 *
 *  Created on: Jan 28, 2026
 *      Author: raghav
 */


#include "PIN_CONFIG.h"

void UART_PIN_INIT(uint8_t pin)
{
	//Enable the GPIOA Clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	//Configure GPIOA as Alternate function
	PA->MODER |= BV(pin*2+1);
	PA->MODER &= ~BV(pin*2);

	//Configure pins as push pull
	PA->OTYPER &= ~BV(pin);

	//Configure the speed as low
	PA->OSPEEDR &= ~(BV(pin*2)|BV(pin*2+1));

	//Configure the pins as no pull up and pull down
	PA->PUPDR &= ~(BV(pin*2)|BV(pin*2+1));

	//Configure the alternate function to tx and rx
	PA->AFR[0] |= 7<<(pin*4);
}



