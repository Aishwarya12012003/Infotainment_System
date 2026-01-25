#ifndef _LCD_DRIVER_H_
#define _LCD_DRIVER_H_

#include <linux/i2c.h>
#include "lcd_common.h"
#include "lcd_fops.h"
#include "lcd_ops.h"

int desd_lcd_probe(struct i2c_client *client,const struct i2c_device_id *id);

int desd_lcd_remove(struct i2c_client *client);

extern struct i2c_driver desd_lcd_driver;

#endif
                                    