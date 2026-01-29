/*
 * uart_config.c
 *
 *  Created on: Jan 28, 2026
 *      Author: raghav
 */

#include "UART_CONFIG.h"

//char ch;

void UART2_INIT() {
	//Enable the UART2 Clock
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

	//Initializing the pin
	UART_PIN_INIT(TX_2);
	UART_PIN_INIT(RX_2);

	//Configure UART
	USART2->CR1 |=
			USART_CR1_UE | USART_CR1_TE | USART_CR1_RE ;
//	| USART_CR1_RXNEIE;
	USART2->CR1 &= ~USART_CR1_M;

	USART2->CR2 &= ~(USART_CR2_STOP_0 | USART_CR2_STOP_1);

	USART2->BRR = 0x683;

//	NVIC_EnableIRQ(USART2_IRQn);

}

void UART2_TX(char data) {
	USART2->DR = data;
	while (!(USART2->SR & USART_SR_TXE))
		;
}

void UART2_SEND(char *data) {
	for (int i = 0; data[i] != '\0'; i++)
		UART2_TX(data[i]);
}

char UART2_RX()
{
	while(!(USART2->SR & USART_SR_RXNE));
	return USART2->DR;
}

//void UART2_RECEIVE(char *buff)
//{
//	volatile int i=0,count=0;
//	char ch;
//	do
//	{
//		ch = UART2_RX();
//		buff[i++] = ch;
//		if(ch=='$')
//			count++;
//	}while(count!=9);
////(ch != '\r') &&
////	&& (i<(656-1))
//	buff[i++] = '\n';
//	buff[i++] = '\r';
//	buff[i] =  '\0';
//}


//void GPS_Update(void) {
////    char buff[100];
//    int i = 0;
//
//    // 1. CLEAR OVERRUN: If we delayed 2s, the ORE (Overrun Error) flag is likely set.
//    // Reading SR followed by DR clears most error flags on STM32F4.
//    uint32_t temp = USART2->SR;
//    temp = USART2->DR;
//    (void)temp;
//
//    // 2. FLUSH: Skip old/stale bytes until we find the start of a fresh sentence
//    while (UART2_RX() != '$');
//
//    // 3. CAPTURE: Store the fresh sentence
//    buff[i++] = '$';
//    while (i < 99) {
//        char c = UART2_RX();
//        buff[i++] = c;
//        if (c == '\n') break;
//    }
//    buff[i] = '\0';
//
//    // Process your NMEA sentence here (e.g., print to another UART or parse)
//
//}



void Get_GNGGA_Data(char *buff, int maxLen) {
    // 1. Clear Overrun/Error Flags (Crucial for STM32 polling after a delay)
    uint32_t temp = USART2->SR;
    temp = USART2->DR;
    (void)temp;

    // 2. Search specifically for "$GNGGA"
    int matchIndex = 0;
    const char target[] = "$GNGGA";

    while (matchIndex < 6) {
        char c = UART2_RX();
        if (c == target[matchIndex]) {
            matchIndex++;
        } else {
            matchIndex = (c == '$') ? 1 : 0; // Reset if we miss a character
        }
    }

    // 3. Header found, now capture the rest of the line
    buff[0] = '$'; buff[1] = 'G'; buff[2] = 'N';
    buff[3] = 'G'; buff[4] = 'G'; buff[5] = 'A';

    int i = 6;
    while (i < maxLen - 1) {
        char c = UART2_RX();
        buff[i++] = c;
        if (c == '\n') break;
    }
    buff[i] = '\0';
}


//void USART2_IRQHandler(void) {
//	if (USART2->SR & USART_SR_RXNE)
//	{
//		char ch = USART2->DR;
//		if (i < SIZE - 1)
//		{
//			buff[i++] = ch;
//			if (ch == '\n') {
//				buff[i] = '\0';
//				i = 0;
//			}
//		}
//	}
//}
//
//
////		if((ch!='\n'))
////			buff[i++] = ch;
////		else
////		{
////			buff[i++] = '\r';
////			buff[i++] = '\n';
////			buff[i] =  '\0';
////			i=0;
//////			UART2_SEND(buff);
//////			memset(buff,0,sizeof(buff));
////		}
