///*
// * MY_MCP2515.c
// *
// *  Created on: Nov 3, 2025
// *      Author: raghav
// */
//
//
//#include "MY_SPI.h"
//#include "MY_PIN.h"
//#include "MY_MCP2515.h"
//#include <stdio.h>
//
////MSG RX
//int MCP2515_RX_MSG(uint8_t *data)
//{
//	MCP2515_READ(RXBnDLC);
//	MCP2515_READ(RXBnDM);
//	MCP2515_READ(RXBnSIDL);
//	MCP2515_READ(RXBnSIDH);
//	MCP2515_READ(RXB0CTRL);
//
//	 if ((MCP2515_READ(CANINTF) & CANINTF_RX0IF))
//	    {
//	        // 1. Read ID
//	        uint8_t sidh = MCP2515_READ(RXBnSIDH);
//	        uint8_t sidl = MCP2515_READ(RXBnSIDL);
//	        uint16_t id = (uint16_t)(sidh << 3) | (sidl >> 5);
//
//	        // 2. Read DLC
//	        uint8_t dlc = MCP2515_READ(RXBnDLC) & 0x0F; // Mask off RBR specific bits
//
//	        // 3. Read Data Bytes
//	        for (uint8_t i = 0; i < dlc; i++)
//	        {
//	            data[i] = MCP2515_READ(RXBnDM + i);
//	        }
//
//	        // 4. Clear the RX Interrupt Flag
//	        MCP2515_WRITE(CANINTF, 0x00); // Clear all flags, including RX0IF
//
//	        return 0; // Message read successfully
//	    }
//	    return 1; // No message waiting
//
//}
//
