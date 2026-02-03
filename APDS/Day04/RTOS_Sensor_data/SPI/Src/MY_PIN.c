/*
 * MY_PIN.c
 *
 *  Created on: Oct 30, 2025
 *      Author: raghav
 */

#include "MY_PIN.h"

void GPIO_SPI_1_INIT(uint8_t pin)
{
	//Enable the GPIO Port Clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	//Set the mode as alternate function
	A->MODER |= BV(pin*2+1);
	A->MODER &= ~BV(pin*2);

	//set no pull up and pull down
	A->PUPDR &= ~( BV(pin*2+1) | BV(pin*2) );

	//set the Alternate function as AF5
	A->AFR[0] |= 5 << ( pin*4 );
}

void GPIO_SPI_1_CS(uint8_t pin)
{
	//Enable the GPIO Port Clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

	//set the mode as output
	B->MODER |= BV(pin*2);
	B->MODER &= ~BV(pin*2+1);

	//set the output type as push pull
	B->OTYPER &= ~BV(pin);

	//set the speed as low
	B->OSPEEDR &= ~( BV(pin*2) | BV(pin*2+1) );

	//set no pull up and pull down
	B->PUPDR &= ~( BV(pin*2) | BV(pin*2+1) );
}

void GPIO_SPI_1_CS_ON(uint8_t pin)
{
	B->ODR |= BV(pin);
}

void GPIO_SPI_1_CS_OFF(uint8_t pin)
{
	B->ODR &= ~BV(pin);
}



//GPIO
void GPIO_OUTPUT(uint8_t pin)
{
	//Enable the GPIO Port Clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN   ;

	//set the mode as output
	C->MODER |= BV(pin*2);
	C->MODER &= ~BV(pin*2+1);

	//set the output type as push pull
	C->OTYPER &= ~BV(pin);

	//set the speed as low
	C->OSPEEDR &= ~( BV(pin*2) | BV(pin*2+1) );

	//set no pull up and pull down
	C->PUPDR &= ~( BV(pin*2) | BV(pin*2+1) );
}

void GPIO_OUTPUT_ON(uint8_t pin)
{
	C->ODR |= BV(pin);
}

void GPIO_OUTPUT_OFF(uint8_t pin)
{
	C->ODR &= ~(BV(pin));
}
