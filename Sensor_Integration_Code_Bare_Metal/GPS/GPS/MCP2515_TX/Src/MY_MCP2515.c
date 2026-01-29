/*
 * MY_MCP2515.c
 *
 *  Created on: Nov 3, 2025
 *      Author: raghav
 */


#include "MY_SPI.h"
#include "MY_PIN.h"
#include "MY_MCP2515.h"
#include <stdio.h>

//RESET THE DEVICE
void MCP2515_RESET()
{

	SPI_CHIP_ENABLE();
	SPI_TRANSFER(RESET);
	SPI_CHIP_DISABLE();
	DelayMs(10);
}


void MCP2515_WRITE(uint8_t addr, uint8_t data)
{
	SPI_CHIP_ENABLE();
	SPI_TRANSFER(WRITE);
//	DelayMs(1);
	SPI_TRANSFER(addr);
//	DelayMs(1);
	SPI_TRANSFER(data);
//	DelayMs(1);
	SPI_CHIP_DISABLE();
}

void MCP2515_RTS(uint8_t addr)
{
	SPI_CHIP_ENABLE();
	SPI_TRANSFER(addr);
//	DelayMs(1);
	SPI_CHIP_DISABLE();

}

uint8_t MCP2515_READ(uint8_t addr)
{
	uint8_t data;
	SPI_CHIP_ENABLE();
	SPI_TRANSFER(READ);
//	DelayMs(1);
	SPI_TRANSFER(addr);
//	DelayMs(1);
	data = SPI_TRANSFER(0x00);
//	DelayMs(1);
	SPI_CHIP_DISABLE();
	return data;
}

//
//// Example Baud Rate Setting for 500Kbps with an 8MHz Crystal
//void MCP2515_Set_BaudRate_500Kbps(void) {
//    // Must be in CONFIGURATION mode to set these registers.
//    // CNF1: SJW=0, BRP=0 (Prescaler value)
//    MCP2515_WRITE(REG_CNF1, 0x00);
//    // CNF2: BTLMODE=1, PHSEG1=6, PRSEG=1
//    MCP2515_WRITE(REG_CNF2, 0x90);
//    // CNF3: SOF=0, WAKFIL=0, PHSEG2=2
//    MCP2515_WRITE(REG_CNF3, 0x02);
//    // Note: These values might need tuning based on actual performance. Refer to the Microchip datasheet for precise calculations.
//}

void MCP2515_SET_BAUD_RATE_500KBPS(void)
{
	MCP2515_WRITE(CNF1, 0x00);
	MCP2515_WRITE(CNF2, 0x90);
	MCP2515_WRITE(CNF3, 0x82);
}


uint8_t MCP2515_INIT()
{
	MCP2515_RESET();
	MCP2515_READ(CANCTRL);
	MCP2515_READ(CANSTAT);

	MCP2515_WRITE(CANCTRL,((MCP2515_READ(CANCTRL)|0XF0)&(CONFIGURATION|0x0F))); //0x07
	MCP2515_READ(CANCTRL);
	MCP2515_READ(CANSTAT);


	if((MCP2515_READ(CANSTAT)&0xE0)!=CONFIGURATION)
	{
		return 1;
	}

	MCP2515_SET_BAUD_RATE_500KBPS();

	MCP2515_WRITE(RXB0CTRL,0x60);
	// Set masks to accept all messages (RXB0)
	MCP2515_WRITE(RXM0SIDH, 0x00);
	MCP2515_WRITE(RXM0SIDL, 0x00);
	MCP2515_WRITE(RXF0SIDH, 0x00);
	MCP2515_WRITE(RXF0SIDL, 0x00);


	MCP2515_WRITE(CANINTF,0x00);
	MCP2515_WRITE(CANINTE,CANINTE_RX0IE);


//	(MCP2515_READ(CANSTAT)&(NORMAL|0x0F))
	MCP2515_WRITE(CANCTRL,((MCP2515_READ(CANCTRL)|0XF0)&(NORMAL|0x0F))); //0x07
	MCP2515_READ(CANCTRL);
	MCP2515_READ(CANSTAT);
	if((MCP2515_READ(CANSTAT)&0xE0)!=NORMAL)
	{
		return 2;
	}
	return 0;
}


//
//////SET THE MODE
////void MCP2515_SET_MODE(uint16_t id)
////{
////
////	MCP2515_READ(CANSTAT);
////
////	if(MCP2515_READ(CANSTAT)==CONFIGURATION)
////		{
////			printf("Hello");
////		}
////	else
////	{
////		printf("World");
////	}
////
////
////
//////	MCP2515_WRITE(RXFnSIDH,(uint8_t)(id>>3));
//////	MCP2515_READ(RXFnSIDH);
//////
//////	MCP2515_WRITE(RXFnSIDL,(uint8_t)(id<<5));
//////	MCP2515_READ(RXFnSIDL);
////
////}
//
//


