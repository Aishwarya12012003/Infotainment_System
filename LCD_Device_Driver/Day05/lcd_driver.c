#include <linux/device.h>
#include <linux/module.h>
#include <linux/init.h>
#include "lcd_driver.h"

static const struct i2c_device_id desd_lcd_id[] = {
    { SLAVE_DEVICE_NAME, 0 },
    {}
};
MODULE_DEVICE_TABLE(i2c, desd_lcd_id);

int desd_lcd_probe(struct i2c_client *client,const struct i2c_device_id *id)
{
    int ret;
    struct device *lcddevice;
    pr_info("%s : lcd Probed!!!\n", THIS_MODULE->name);

    ret = LcdInit();
    if (ret < 0)
        return ret;
    pr_info("%s : LCD is initialized.\n",THIS_MODULE->name);

    // allocate device number
    ret = alloc_chrdev_region(&devno, 0, 1, SLAVE_DEVICE_NAME);
    if(ret < 0)
	{
		pr_err("%s : alloc_chrdev_region() is failed.\n", THIS_MODULE->name);
		goto alloc_chrdev_region_failed;
	}
	pr_info("%s : alloc_chrdev_region() allocated device number %d/%d.\n", THIS_MODULE->name, MAJOR(devno), MINOR(devno));


    // create device class and device file
    lcdclass = class_create(THIS_MODULE, "lcd_class");
    //lcdclass = class_create("lcd_class");

    if(IS_ERR(lcdclass))
	{
		pr_err("%s : class_create() is failed.\n", THIS_MODULE->name);
		ret = -1;
		goto class_create_failed;
	}
	pr_info("%s : class_create() created device class.\n", THIS_MODULE->name);


    lcddevice = device_create(lcdclass, NULL, devno, NULL, "lcd0");
    if(IS_ERR(lcdclass))
	{
		pr_err("%s : device_create() is failed.\n", THIS_MODULE->name);
		ret = -1;
		goto device_create_failed;
	}
	pr_info("%s : device_create() created device file.\n", THIS_MODULE->name);

    // init cdev (with fops)
    cdev_init(&lcd_cdev, &lcd_fops);

    //add cdev in kernel
    ret = cdev_add(&lcd_cdev, devno, 1);
    if(ret < 0)
	{
		pr_info("%s : cdev_add() is failed.\n", THIS_MODULE->name);
		goto cdev_add_failed;
	}
	pr_info("%s : cdev_add() device added into kernel.\n", THIS_MODULE->name);

    return ret;


cdev_add_failed:
	device_destroy(lcdclass, devno);
device_create_failed:
	class_destroy(lcdclass);
class_create_failed:
	unregister_chrdev_region(devno,1);
alloc_chrdev_region_failed:
	return ret;

}

int desd_lcd_remove(struct i2c_client *client) 
//static void desd_lcd_remove(struct i2c_client *client) 
{
    // delete cdev from kernel
	cdev_del(&lcd_cdev);
	pr_info("%s : cdev_del() deleted cdev from kernel.\n", THIS_MODULE->name);

    // destroy device file and device class
	device_destroy(lcdclass, devno);
	pr_info("%s : device_destroy() destroyed device file.\n", THIS_MODULE->name);

    // destroy device class
	class_destroy(lcdclass);
	pr_info("%s : class_destroy() destroyed device class.\n", THIS_MODULE->name);

    // release device number
	unregister_chrdev_region(devno,1);
	pr_info("%s : unregister_chrdev_region() deallocated the device number.\n", THIS_MODULE->name);

	pr_info("%s : lcd Removed!!!\n", THIS_MODULE->name);

    return 0;
}

struct i2c_driver desd_lcd_driver = {
    .driver = {
        .name = SLAVE_DEVICE_NAME,
        .owner = THIS_MODULE,
    },
    .probe    = desd_lcd_probe,
    .remove   = desd_lcd_remove,
    .id_table = desd_lcd_id,
};
