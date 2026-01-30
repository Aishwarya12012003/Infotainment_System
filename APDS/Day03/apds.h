/*
 * apds.h
 *
 *  Created on: Dec 2, 2025
 *      Author: sunbeam
 */

#ifndef APDS_H_
#define APDS_H_

#include <stdint.h>

// I2C 7-bit address of APDS-9900
#define APDS_ADDR   (0x39 << 1)   // 7-bit 0x39 -> write=0x72

// APDS register constants
#define ATIME_REG   0x81
#define PTIME_REG   0x82
#define WTIME_REG   0x83
#define CONTROL_REG 0x8F
#define ENABLE_REG  0x80
#define ID_REG      0x92
#define PDATA_L     0x98
#define PDATA_H     0x99
#define CDATA_L     0x94
#define CDATA_H     0x95

// APDS driver functions
void APDS_Write(uint8_t reg, uint8_t value);
uint8_t APDS_Read(uint8_t reg);
uint16_t APDS_ReadProximity(void);
uint16_t APDS_ReadALS(void);

// Optional: delay for slow output
void APDS_DelayMs(int ms);

#endif /* APDS_H_ */
