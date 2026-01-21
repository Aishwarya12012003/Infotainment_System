//Write I2C based device driver for LCD

#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>

/* init function */
static int __init lcd_driver_init(void)
{
	pr_info("%s : lcd_driver_init() called\n", THIS_MODULE->name);
	return 0;
}

/* exit function */
static void __exit lcd_driver_exit(void)
{
	pr_info("%s : lcd_driver_exit() called\n", THIS_MODULE->name);
}

module_init(lcd_driver_init);
module_exit(lcd_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aishwarya Chavan");
MODULE_DESCRIPTION("Day 1 LCD Driver Skeleton");

