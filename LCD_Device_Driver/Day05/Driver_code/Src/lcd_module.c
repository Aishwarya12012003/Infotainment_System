#include <linux/module.h>
#include "lcd_module.h"

//create i2c board info structure
static struct i2c_board_info lcd_i2c_board_info = {
	I2C_BOARD_INFO(SLAVE_DEVICE_NAME, LCD_SLAVE_ADDR)
};

int __init desd_driver_init(void)
{
    int ret = 0;

    desd_i2c_adapter = i2c_get_adapter(I2C_BUS_AVAILABLE);
    if (!desd_i2c_adapter)
        return -ENODEV;

    desd_i2c_client_lcd =
        i2c_new_client_device(desd_i2c_adapter, &lcd_i2c_board_info);

    if (!desd_i2c_client_lcd) {
        ret = -ENODEV;
    } else {
        i2c_add_driver(&desd_lcd_driver);
    }

    i2c_put_adapter(desd_i2c_adapter);
    return ret;
}

void __exit desd_driver_exit(void)
{
    if (desd_i2c_client_lcd) {
        i2c_unregister_device(desd_i2c_client_lcd);
        i2c_del_driver(&desd_lcd_driver);
    }
}

module_init(desd_driver_init);
module_exit(desd_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aishwarya Chavan");
MODULE_DESCRIPTION("Modular I2C LCD Driver");
