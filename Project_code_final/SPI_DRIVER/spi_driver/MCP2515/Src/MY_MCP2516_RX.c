/*
 * MY_MCP2515.c
 *
 *  Created on: Nov 3, 2025
 *      Author: raghav
 */



#include "../Inc/SPI_CAN_header.h"
//#include <stdio.h>

//MSG RX
int MCP2515_RX_MSG(struct spi_device *spi,uint8_t *data)
{
	MCP2515_READ(spi,RXBnDLC);
	MCP2515_READ(spi,RXBnDM);
	MCP2515_READ(spi,RXBnSIDL);
	MCP2515_READ(spi,RXBnSIDH);
	MCP2515_READ(spi,RXB0CTRL);

	 if ((MCP2515_READ(spi,CANINTF) & CANINTF_RX0IF))
	    {
	        // 1. Read ID
	        uint8_t sidh = MCP2515_READ(spi,RXBnSIDH);
	        uint8_t sidl = MCP2515_READ(spi,RXBnSIDL);
	        uint16_t id = (uint16_t)(sidh << 3) | (sidl >> 5);

	        // 2. Read DLC
	        uint8_t dlc = MCP2515_READ(spi,RXBnDLC) & 0x0F; // Mask off RBR specific bit

		uint8_t i;

	        // 3. Read Data Bytes
	        for ( i = 0; i < dlc; i++)
	        {
	            data[i] = MCP2515_READ(spi,RXBnDM + i);
	        }

	        // 4. Clear the RX Interrupt Flag
	        MCP2515_WRITE(spi,CANINTF, 0x00); // Clear all flags, including RX0IF

	        return 0; // Message read successfully
	    }
	    return 1; // No message waiting

}

