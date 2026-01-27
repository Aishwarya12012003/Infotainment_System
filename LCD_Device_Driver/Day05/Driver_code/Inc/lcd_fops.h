#ifndef _LCD_FOPS_H_
#define _LCD_FOPS_H_

#include <linux/fs.h>
#include "lcd_common.h"
#include "lcd_ops.h"

//  file_operations structure 
extern struct file_operations lcd_fops;

#endif
