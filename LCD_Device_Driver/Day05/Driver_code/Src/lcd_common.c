#include "lcd_common.h"

// ---- Global Variable Definitions ----
struct i2c_adapter *desd_i2c_adapter = NULL;
struct i2c_client  *desd_i2c_client_lcd = NULL;
struct class *lcdclass = NULL;
dev_t devno = 0;
struct cdev lcd_cdev;
