#include "../Inc/SPI_CAN_header.h"

int SPI_TRANSFER_DATA(struct spi_device *spi,struct spi_transfer *t,u8 *tx_buf,u8 *rx_buf,int *len)
{
    struct spi_message m;

    spi_message_init(&m);
    spi_message_add_tail(t, &m);
    
    int ret = spi_sync(spi, &m); // CS line stays low for the whole 3-byte transaction
    if (ret < 0) {
        return ret; // Return the kernel error code
    }
	int i=0;
    while(i<*len)
    {
    	pr_info("%s: OK tx_buf=0x%02X rx_buf=0x%02X\n",THIS_MODULE->name,tx_buf[i],rx_buf[i]);
	    i++;
    }

    // The actual register data is in the third received byte
    return rx_buf[*len-1];  
}

/* Helper function implementation for reading a single register */
int MCP2515_READ(struct spi_device *spi, u8 reg_addr) {
    // tx_buf 3 bytes of data: [READ_CMD, REG_ADDR, DUMMY_BYTE]
    u8 tx_buf[3] = {SPI_READ, reg_addr, NO_DATA};
    u8 rx_buf[3] = {NO_DATA, NO_DATA, NO_DATA};

    struct spi_transfer t = {
        .tx_buf = tx_buf,
        .rx_buf = rx_buf,
        .len = 3, // Transfer all three bytes at once
    };

    return SPI_TRANSFER_DATA(spi,&t,tx_buf,rx_buf,&t.len);

}

void MCP2515_WRITE(struct spi_device *spi, u8 reg_addr,u8 data) {
    u8 tx_buf[3] = {SPI_WRITE, reg_addr, data};
    u8 rx_buf[3] = {NO_DATA, NO_DATA, NO_DATA};

    struct spi_transfer t = {
        .tx_buf = tx_buf,
        .rx_buf = rx_buf,
        .len = 3, // Transfer all three bytes at once
    };

    SPI_TRANSFER_DATA(spi,&t,tx_buf,rx_buf,&t.len);

}

void MCP2515_RESET(struct spi_device *spi)
{
    //  tx only 1 byte of data: [SPI_RESET]
    u8 tx_buf[1] = { RESET };
    u8 rx_buf[1] = { NO_DATA };

    struct spi_transfer t = {
        .tx_buf = tx_buf,
        .rx_buf = rx_buf,
        .len = 1,
    };

    SPI_TRANSFER_DATA(spi,&t,tx_buf,rx_buf,&t.len);
}


// //MSG RX
// void MCP2515_RX_MSG(struct spi_device *spi)
// {
// 	int value = MCP2515_READ_REG(spi,RXBnDLC);
//     pr_info("%s: RXBnDLC: %d",THIS_MODULE->name,value);
// 	value = MCP2515_READ_REG(spi,RXBnDM);
//     pr_info("%s: RXBnDM: %d",THIS_MODULE->name,value);
// 	value = MCP2515_READ_REG(spi,RXBnSIDL);
//     pr_info("%s: RXBnSIDL: %d",THIS_MODULE->name,value);
// 	value = MCP2515_READ_REG(spi,RXBnSIDH);
//     pr_info("%s: RXBnSIDH: %d",THIS_MODULE->name,value);
// 	value = MCP2515_READ_REG(spi,RXB0CTRL);
//     pr_info("%s: RXB0CTRL: %d",THIS_MODULE->name,value);
// }
