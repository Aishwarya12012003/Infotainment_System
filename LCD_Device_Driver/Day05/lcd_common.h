#ifndef _LCD_COMMON_H_
#define _LCD_COMMON_H_

#include <linux/i2c.h>
#include <linux/cdev.h>

// ---- Shared Macros ----
#define I2C_BUS_AVAILABLE      2
#define SLAVE_DEVICE_NAME      "HD44780"
#define LCD_SLAVE_ADDR         (0x4E >> 1)

#define LCD_CLEAR              0x01
#define LCD_FN_SET_8BIT        0x30
#define LCD_FN_SET_4BIT        0x20
#define LCD_FN_SET_4BIT_2LINES 0x28
#define LCD_DISP_CTRL          0x08
#define LCD_DISP_ON            0x0C
#define LCD_ENTRY_MODE         0x06
#define LCD_LINE1              0x80
#define LCD_LINE2              0xC0

#define LCD_RS 0
#define LCD_RW 1
#define LCD_EN 2
#define LCD_BL 3

#define LCD_CMD  0
#define LCD_DATA 1

#define BV(n) (1 << (n))

typedef unsigned char uint8_t;

// GLOBAL extern variables 
extern struct i2c_adapter *desd_i2c_adapter;
extern struct i2c_client  *desd_i2c_client_lcd;
extern struct class *lcdclass;
extern dev_t devno;
extern struct cdev lcd_cdev;

#endif
