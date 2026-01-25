#include <linux/delay.h>
#include <linux/kernel.h>
#include "lcd_ops.h"

int LcdWriteByte(uint8_t val)
{
    int ret = i2c_master_send(desd_i2c_client_lcd, &val, 1);
    return (ret < 0) ? ret : 0;
}

void LcdWrite(uint8_t rs, uint8_t val)
{
    uint8_t high = val & 0xF0;
    uint8_t low  = (val << 4) & 0xF0;

    uint8_t rs_bit = (rs == LCD_CMD) ? 0 : BV(LCD_RS);

    LcdWriteByte(high | rs_bit | BV(LCD_EN) | BV(LCD_BL));
    mdelay(1);
    LcdWriteByte(high | rs_bit | BV(LCD_BL));

    LcdWriteByte(low | rs_bit | BV(LCD_EN) | BV(LCD_BL));
    mdelay(1);
    LcdWriteByte(low | rs_bit | BV(LCD_BL));
}

int LcdInit(void)
{
    mdelay(20);

    LcdWriteByte(LCD_FN_SET_8BIT | BV(LCD_EN));
    LcdWriteByte(LCD_FN_SET_8BIT);
    mdelay(5);

    LcdWriteByte(LCD_FN_SET_8BIT | BV(LCD_EN));
    LcdWriteByte(LCD_FN_SET_8BIT);
    mdelay(1);

    LcdWriteByte(LCD_FN_SET_8BIT | BV(LCD_EN));
    LcdWriteByte(LCD_FN_SET_8BIT);
    mdelay(3);

    LcdWriteByte(LCD_FN_SET_4BIT | BV(LCD_EN));
    LcdWriteByte(LCD_FN_SET_4BIT);
    mdelay(3);

    LcdWriteByte(LCD_FN_SET_4BIT_2LINES);
    LcdWrite(LCD_CMD, LCD_DISP_CTRL);
    LcdWrite(LCD_CMD, LCD_CLEAR);
    LcdWrite(LCD_CMD, LCD_ENTRY_MODE);
    LcdWrite(LCD_CMD, LCD_DISP_ON);

    return 0;
}

void LcdPuts(uint8_t line, char *str)
{
    int i;
    LcdWrite(LCD_CMD, line);
    for (i = 0; str[i] != '\0'; i++)
        LcdWrite(LCD_DATA, str[i]);
}
