
//File Name   : lcd_driver.c
//Description : I2C LCD Driver


#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/i2c.h>

/* I2C bus available */
#define I2C_BUS_AVAILABLE	2
#define SLAVE_DEVICE_NAME	"HD44780"
#define LCD_SLAVE_ADDR		(0x4E >> 1)		//Slave addr

static struct i2c_client *lcd_client;

/* probe function */
static int lcd_i2c_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	pr_info("%s : lcd_i2c_probe() is called\n", THIS_MODULE->name);
	lcd_client = client;
	return 0;
}

/* remove function */
static int lcd_i2c_remove(struct i2c_client *client)
{
	pr_info("%s : lcd_i2c_remove() is called\n", THIS_MODULE->name);
	return 0;
}

/* i2c device id */
static const struct i2c_device_id lcd_id[] = {
	{ SLAVE_DEVICE_NAME, 0 },
	{ }
};
MODULE_DEVICE_TABLE(i2c, lcd_id);

/* i2c driver structure */
static struct i2c_driver lcd_i2c_driver = {
	.driver = {
		.name = SLAVE_DEVICE_NAME,
	},
	.probe    = lcd_i2c_probe,
	.remove   = lcd_i2c_remove,
	.id_table = lcd_id,
};

module_i2c_driver(lcd_i2c_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aishwarya Chavan");
MODULE_DESCRIPTION("Day 3 I2C LCD Driver");

