#include <stdint.h>
#include <stdio.h>
#include "uart.h"
#include "i2c.h"

#define APDS_ADDR   (0x39 << 1)   // 7-bit = 0x39 → write=0x72, read=0x73

int main(void)
{
    UartInit(9600);
    I2CInit();

    UartPuts("APDS Sensor Detect Test...\r\n");

    // -------------------------------
    // STEP 1 → WRITE PHASE
    // -------------------------------
    UartPuts("Sending Write Address (0x72)...\r\n");

    I2CStart();
    I2CSendSlaveAddr(APDS_ADDR);   // write mode
    UartPuts("Write Address ACK OK\r\n");

    UartPuts("Sending Register 0x92...\r\n");
    I2CSendData(0x92);
    UartPuts("Register 0x92 Sent\r\n");

    I2CStop();
    UartPuts("Write Phase Complete\r\n");


    // -------------------------------
    // STEP 2 → READ PHASE
    // -------------------------------
    UartPuts("Sending Read Address (0x73)...\r\n");

    I2CStart();
    I2CSendSlaveAddr(APDS_ADDR | 1);   // read mode
    UartPuts("Read Address ACK OK\r\n");

    uint8_t id = I2CRecvDataNAck();

    I2CStop();
    UartPuts("Read Phase Complete\r\n");


    // -------------------------------
    // PRINT ID
    // -------------------------------
    char msg[50];
    sprintf(msg, "APDS ID Read = 0x%02X\r\n", id);
    UartPuts(msg);

    // Sensor detection
    if(id == 0xAB)
        UartPuts("Detected: APDS-9960 (Gesture)\r\n");
    else if(id == 0x39)
        UartPuts("Detected: APDS-9930 (ALS + PROX)\r\n");
    else if(id == 0x30)
        UartPuts("Detected: APDS-9900 (ALS Only)\r\n");
    else
        UartPuts("Unknown / No Sensor / Wrong Address\r\n");


    // Endless loop
    while(1);
}
