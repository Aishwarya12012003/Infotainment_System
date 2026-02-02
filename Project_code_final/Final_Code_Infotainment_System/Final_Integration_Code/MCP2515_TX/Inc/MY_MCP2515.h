/*
 * MY_MCP2515.h
 *
 *  Created on: Nov 3, 2025
 *      Author: raghav
 */

#ifndef MY_MCP2515_H_
#define MY_MCP2515_H_

//SPI ADDRESS
#define NO_DATA 0x00
#define SPI_RESET 0xC0
#define WRITE 0x02
#define READ 0x03
#define SPI_RTS_0 0x81
#define SPI_READ_STATUS 0xA0

//CAN ADDRESS

//CAN MODE CONTROL
#define CANCTRL 0x0F
#define CANCTRL_ABAT (1<<4)

#define CANSTAT 0x0E
#define CONFIGURATION 0x80
#define LOOPBACK 0x40
#define NORMAL 0x00


//CAN BIT TIMING
#define CNF1 0x2A
#define CNF2 0x29
#define CNF3 0x28


//CAN MSG TX
//CONTROL REGISTER
#define TXBnCTRL 0x30
#define TXBnCTRL_TXREQ (1<<3)
#define TXBnCTRL_ABTF (1<<6)
#define TXBnCTRL_MLOA (1<<5)
#define TXBnCTRL_TXERR (1<<4)
#define TXBnCTRL_TXP1 (1<<1)
#define TXBnCTRL_TXP0 (1<<0)

//PIN CONTROL AND STATUS REGISTER
#define TXRTSCTRL 0x0D


//STANDARD IDENTIFIER High
#define TXBnSIDH 0x31
//STANDARD IDENTIFIER Low
#define TXBnSIDL 0x32

//DATA LENGTH CODE
#define TXBnDLC  0x35
//DATA BYTE
#define TXBnDm 	0x36

//CANINTF
#define CANINTE 0x2B
#define CANINTE_RX0IE 1<<0
#define CANINTF 0x2C
#define CANINTF_TX0IF (1<<2)
#define CANINTF_RX0IF (1<<0)



//CAN MSG RX
#define RXBnDLC 0x65
#define RXBnDM 0x66
#define RXBnSIDL 0x62
#define RXBnSIDH 0x61
#define RXB0CTRL 0x60
#define BFPCTRL 0x0C

#define RXF0SIDH 0x00
#define RXF0SIDL 0x01
#define RXM0SIDH 0x20
#define RXM0SIDL 0x21


uint8_t MCP2515_INIT();
//void MCP2515_SET_MODE(uint16_t id);
int MCP2515_TX_MSG(uint16_t id,uint8_t dlc,uint8_t *data);
int MCP2515_RX_MSG(uint8_t *data);
void MCP2515_RESET();
void MCP2515_WRITE(uint8_t addr, uint8_t data);
void MCP2515_RTS(uint8_t addr);
uint8_t MCP2515_READ(uint8_t addr);
void MCP2515_SET_BAUD_RATE_500KBPS(void);
//void MCP2515_TX();


#endif /* MY_MCP2515_H_ */
