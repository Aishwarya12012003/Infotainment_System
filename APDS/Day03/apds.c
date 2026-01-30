/*
 * apds.c
 *
 *  Created on: Dec 2, 2025
 *      Author: sunbeam
 */

#include "apds.h"
#include "i2c.h"

// Simple delay for slow UART printing
void APDS_DelayMs(int ms)
{
    for(int i=0; i<(ms*16000); i++);
}

// Low-level write
void APDS_Write(uint8_t reg, uint8_t value)
{
    I2CStart();
    I2CSendSlaveAddr(APDS_ADDR);
    I2CSendData(reg);
    I2CSendData(value);
    I2CStop();
}

// Low-level read
uint8_t APDS_Read(uint8_t reg)
{
    uint8_t value;
    I2CStart();
    I2CSendSlaveAddr(APDS_ADDR);
    I2CSendData(reg);
    I2CStop();

    I2CStart();
    I2CSendSlaveAddr(APDS_ADDR | 1);
    value = I2CRecvDataNAck();
    I2CStop();
    return value;
}

// Read 16-bit proximity
uint16_t APDS_ReadProximity(void)
{
    uint16_t p = APDS_Read(PDATA_L);
    p |= ((uint16_t)APDS_Read(PDATA_H)) << 8;
    return p;
}

// Read 16-bit ALS value
uint16_t APDS_ReadALS(void)
{
    uint16_t als = APDS_Read(CDATA_L);
    als |= ((uint16_t)APDS_Read(CDATA_H)) << 8;
    return als;
}

