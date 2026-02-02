#ifndef _LCD_MODULE_H_
#define _LCD_MODULE_H_

#include <linux/init.h>
#include "lcd_driver.h"

int __init desd_driver_init(void);
void __exit desd_driver_exit(void);

#endif
