
//File Name   : lcd_driver.c
//Description : I2C LCD Driver


#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>

/* device number */
static dev_t devno;
/* device class ptr */
static struct class *lcdclass;
/* cdev declaration */
struct cdev lcd_cdev;

/* open function */
static int lcd_open(struct inode *pinode, struct file *pfile)
{
	pr_info("%s : lcd_open() is called\n", THIS_MODULE->name);
	return 0;
}

/* release function */
static int lcd_release(struct inode *pinode, struct file *pfile)
{
	pr_info("%s : lcd_release() is called\n", THIS_MODULE->name);
	return 0;
}

/* file operations */
static struct file_operations lcd_fops = {
	.owner   = THIS_MODULE,
	.open    = lcd_open,
	.release = lcd_release,
};

/* init function */
static int __init desd_driver_init(void)
{
	alloc_chrdev_region(&devno, 0, 1, "lcd_dev");
	cdev_init(&lcd_cdev, &lcd_fops);
	cdev_add(&lcd_cdev, devno, 1);

	lcdclass = class_create(THIS_MODULE, "lcd_class");
	device_create(lcdclass, NULL, devno, NULL, "lcd");

	pr_info("%s : character driver registered\n", THIS_MODULE->name);
	return 0;
}

/* exit function */
static void __exit desd_driver_exit(void)
{
	device_destroy(lcdclass, devno);
	class_destroy(lcdclass);
	cdev_del(&lcd_cdev);
	unregister_chrdev_region(devno, 1);

	pr_info("%s : character driver unregistered\n", THIS_MODULE->name);
}

module_init(desd_driver_init);
module_exit(desd_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aishwarya Chavan");
MODULE_DESCRIPTION("Day 2 Character LCD Driver");

