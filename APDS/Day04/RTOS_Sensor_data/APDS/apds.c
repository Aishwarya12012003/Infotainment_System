#include "apds.h"

/* Helper function: Write 1 byte to APDS register */
static HAL_StatusTypeDef APDS_Write(uint8_t reg, uint8_t val)
{
    return HAL_I2C_Mem_Write(&hi2c1, APDS_ADDR, reg,
                             I2C_MEMADD_SIZE_8BIT, &val, 1, HAL_MAX_DELAY);
}

/* Helper function: Read 1 byte from APDS register */
static HAL_StatusTypeDef APDS_Read(uint8_t reg, uint8_t *val)
{
    return HAL_I2C_Mem_Read(&hi2c1, APDS_ADDR, reg,
                            I2C_MEMADD_SIZE_8BIT, val, 1, HAL_MAX_DELAY);
}

/* Public API: Read chip ID */
uint8_t APDS_ReadID(void)
{
    uint8_t id = 0;
    APDS_Read(ID_REG, &id);
    return id;
}

/* Initialize APDS-9900 sensor */
HAL_StatusTypeDef APDS_Init(void)
{
    if(APDS_ReadID() != 0x30) return HAL_ERROR; // Wrong chip ID

    APDS_Write(ENABLE_REG, 0x05);   // Disable before config
   // APDS_Write(ATIME_REG, 0xDB);
    APDS_Write(ATIME_REG, 0xFF);
    APDS_Write(PTIME_REG, 0xFF);
    APDS_Write(WTIME_REG, 0xFF);
    //APDS_Write(CONTROL_REG, 0x2F); // 100mA LED, 1x Prox gain
    APDS_Write(CONTROL_REG, 0x23); // 100mA LED, 1x Prox gain

    //APDS_Write(ENABLE_REG, 0x05);  // PON + PEN only

    HAL_Delay(50); // Allow sensor to settle
    APDS_Write(ENABLE_REG, 0x07);

    return 0;
}

/*
//Read proximity value (0–255)
HAL_StatusTypeDef APDS_ReadProximity(uint16_t *value)
{
    uint8_t val = 0;
    if(APDS_Read(PDATA_REG, &val) != HAL_OK) return HAL_ERROR;
    *value = val;
    return HAL_OK;
}
*/

HAL_StatusTypeDef APDS_ReadProximity(uint8_t *value)
{
    return APDS_Read(PDATA_REG, value);
}

/* Read ambient light sensor (16-bit value) */
HAL_StatusTypeDef APDS_ReadALS(uint16_t *value)
{
    uint8_t buf[2];
    if(HAL_I2C_Mem_Read(&hi2c1, APDS_ADDR, CDATA_REG,
                        I2C_MEMADD_SIZE_8BIT, buf, 2, HAL_MAX_DELAY) != HAL_OK)
        return HAL_ERROR;

    *value = ((uint16_t)buf[1] << 8) | buf[0];
    return HAL_OK;
}
