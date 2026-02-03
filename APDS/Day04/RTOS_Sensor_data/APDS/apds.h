/*
 * apds.h
 *
 *  Created on: Jan 22, 2026
 *      Author: sunbeam
 */

#ifndef INC_APDS_H_
#define INC_APDS_H_

#include "stm32f4xx_hal.h"
#include <stdint.h>

/* I2C handle (defined in main.c or CubeMX) */
extern I2C_HandleTypeDef hi2c1;

/* APDS-9900 I2C address and registers */
#define APDS_ADDR       (0x39 << 1) // 7-bit address shifted for HAL
#define ID_REG          0x92
#define ATIME_REG       0x81
#define PTIME_REG       0x82
#define WTIME_REG       0x83
#define CONTROL_REG     0x8F
#define ENABLE_REG      0x80
#define PDATA_REG       0x9C
#define CDATA_REG       0x94

/* Structure to hold sensor data */
typedef struct
{
    uint8_t  prox;   // ✅ proximity is 8-bit
    uint16_t als;
} APDS_Data_t;

/* Public APIs */
HAL_StatusTypeDef APDS_Init(void);
uint8_t APDS_ReadID(void);
//HAL_StatusTypeDef APDS_ReadProximity(uint16_t *value);
HAL_StatusTypeDef APDS_ReadProximity(uint8_t *value);
HAL_StatusTypeDef APDS_ReadALS(uint16_t *value);

#endif /* INC_APDS_H_ */
