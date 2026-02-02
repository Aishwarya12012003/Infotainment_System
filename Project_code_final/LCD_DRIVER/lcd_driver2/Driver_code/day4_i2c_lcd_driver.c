//Write I2C based device driver for LCD

#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/i2c.h>
#include <linux/delay.h>
#include <linux/kernel.h>

#define I2C_BUS_AVAILABLE 2		//I2C BUS
#define SLAVE_DEVICE_NAME "HD44780"
#define LCD_SLAVE_ADDR (0x4E >> 1)		//Slave addr

#define LCD_CLEAR		0x01
#define LCD_FN_SET_8BIT	0x30
#define LCD_FN_SET_4BIT	0x20
#define LCD_FN_SET_4BIT_2LINES	0x28
#define LCD_DISP_CTRL	0x08
#define LCD_DISP_ON		0x0C
#define LCD_ENTRY_MODE	0x06
#define LCD_LINE1		0x80
#define LCD_LINE2		0xC0

#define LCD_RS	0
#define LCD_RW	1
#define LCD_EN	2
#define LCD_BL	3

#define LCD_CMD		0
#define LCD_DATA	1

#define BV(n)       (1 << (n))
#define __NOP()     asm("nop")		//No operation function
typedef unsigned char uint8_t;

// I2C Adapter Structure 
static struct i2c_adapter *desd_i2c_adapter = 	NULL;
// I2C Cient Structure (In our case it is lcd)
static struct i2c_client * desd_i2c_client_lcd = NULL;

//device number
static dev_t devno;
//device class ptr
static struct class *lcdclass;
//cdev declaration
struct cdev lcd_cdev;

int LcdWriteByte(uint8_t val)
{
    int ret = i2c_master_send(desd_i2c_client_lcd, &val, 1);
    if (ret < 0) {
        pr_err("%s: i2c_master_send failed: %d\n", THIS_MODULE->name, ret);
        return ret;
    }
    return 0; 	// return 0 on success
	
	//return i2c_master_send( desd_i2c_client_lcd, &val, 1);
}

void LcdWrite(uint8_t rs, uint8_t val)
{
	uint8_t high = val & 0xF0;
	uint8_t low = (val << 4) & 0xF0;
	uint8_t bvrs = (rs == LCD_CMD) ? 0 : BV(LCD_RS);	//bit value of rs
	
	LcdWriteByte(high | bvrs | BV(LCD_EN) | BV(LCD_BL));	//send Higher nibble with LCD backlight - ON, EN =1
	mdelay(1);
	LcdWriteByte(high | bvrs |BV(LCD_BL));	
	
	LcdWriteByte(low | bvrs | BV(LCD_EN) | BV(LCD_BL));	//send Higher nibble with LCD backlight - ON, EN =1
	mdelay(1);
	LcdWriteByte(low | bvrs | BV(LCD_BL));	//send Higher nibble with LCD backlight - ON, EN =1
}

int LcdInit(void) 
{
	int ret;
	pr_info("%s : LcdInit!!!\n", THIS_MODULE->name);
    //wait for min 15 ms (for 5V)
	mdelay(20);

	// attention sequence
	ret = LcdWriteByte(LCD_FN_SET_8BIT | BV(LCD_EN));
	// check if lcd is ready
    if(ret < 0)
	{
    	return -1;
	}
	__NOP();
	LcdWriteByte(LCD_FN_SET_8BIT);
	mdelay(5);

	LcdWriteByte(LCD_FN_SET_8BIT | BV(LCD_EN));
	__NOP();
	LcdWriteByte(LCD_FN_SET_8BIT);
	mdelay(1);

	LcdWriteByte(LCD_FN_SET_8BIT | BV(LCD_EN));
	__NOP();
	LcdWriteByte(LCD_FN_SET_8BIT);
	mdelay(3);

	LcdWriteByte(LCD_FN_SET_4BIT | BV(LCD_EN));
	__NOP();
	LcdWriteByte(LCD_FN_SET_4BIT);
	mdelay(3);

	// // lcd initialization
	LcdWriteByte(LCD_FN_SET_4BIT_2LINES);
	mdelay(1);
	LcdWrite(LCD_CMD, LCD_DISP_CTRL);
	mdelay(1);
	LcdWrite(LCD_CMD, LCD_CLEAR);
	mdelay(1);
	LcdWrite(LCD_CMD, LCD_ENTRY_MODE);
	mdelay(1);
	LcdWrite(LCD_CMD, LCD_DISP_ON);
	mdelay(1);
	//return ret;
	return 0;

}

// call this function from device write operation.
static void LcdPuts(u_int8_t line, char str[])
{
	int i;
	LcdWrite(LCD_CMD, line);
	mdelay(1);
	for(i = 0; str[i] != '\0'; i++)
		LcdWrite(LCD_DATA, str[i]);
}

// lcd_open()
static int lcd_open(struct inode *pinode, struct file *pfile)
{
	pr_info("%s : lcd_open() is called\n", THIS_MODULE->name);
	return 0;
}

// lcd_close()
static int lcd_close(struct inode *pinode, struct file *pfile)
{
	pr_info("%s : lcd_close() is called\n", THIS_MODULE->name);
	return 0;
}

// lcd_read() -- do nothing
static ssize_t lcd_read(struct file *pfile, char __user *ubuf, size_t ubufsize, loff_t *offset)
{
	//not required
	return 0;
}

// lcd_write()
static ssize_t lcd_write(struct file *pfile, const char __user *ubuf,size_t ubufsize, loff_t *offset)
{
	char *kbuf;
	pr_info("%s : lcd_write() is called\n", THIS_MODULE->name);

	//Allocate buffer
    kbuf = kmalloc(ubufsize + 1, GFP_KERNEL);   //ubufsize + 1
    if (!kbuf)
    {
        pr_err("%s: kmalloc() failed\n", THIS_MODULE->name);
        return -ENOMEM;
    }
    pr_info("%s : kmalloc allocation successful.\n",THIS_MODULE->name);

	// 1. copy data from user buf to kernel buf
	if(copy_from_user(kbuf, ubuf, ubufsize))
	{
		pr_err("%s: copy_from_user() failed\n", THIS_MODULE->name);
		kfree(kbuf);
        return -EFAULT;
	}

	//Initialize kbuf to 0 to avoid garbage value
	kbuf[ubufsize] = '\0';

    // 2. send data to lcd device from kernel buf -- LcdPuts()
	LcdPuts(LCD_LINE1, kbuf);
	kfree(kbuf);

	return ubufsize;
}

struct file_operations lcd_fops = {
	.owner = THIS_MODULE,
	.open = lcd_open,
	.release = lcd_close,
	.read = lcd_read,
	.write = lcd_write,
};

static int desd_lcd_probe(struct i2c_client *client, const struct i2c_device_id *id) 
//static int desd_lcd_probe(struct i2c_client *client) 
{
    int ret;
	struct device *lcddevice;

    pr_info("%s : lcd Probed!!!\n", THIS_MODULE->name);

	ret = LcdInit();
    if(ret != 0) 
	{
        pr_err("%s : LCD not ready/available.\n",THIS_MODULE->name);
        return ret;
    }
    pr_info("%s : LCD is initialized.\n",THIS_MODULE->name);

    // allocate device number
	ret = alloc_chrdev_region(&devno, 0, 1, "SLAVE_DEVICE_NAME");
    if(ret < 0)
	{
		pr_err("%s : alloc_chrdev_region() is failed.\n", THIS_MODULE->name);
		goto alloc_chrdev_region_failed;
	}
	pr_info("%s : alloc_chrdev_region() allocated device number %d/%d.\n", THIS_MODULE->name, MAJOR(devno), MINOR(devno));

	// create device class and device file
	//lcdclass = class_create(THIS_MODULE,"lcd_class");
	lcdclass = class_create(THIS_MODULE,"lcd_class");
	if(IS_ERR(lcdclass))
	{
		pr_err("%s : class_create() is failed.\n", THIS_MODULE->name);
		ret = -1;
		goto class_create_failed;
	}
	pr_info("%s : class_create() created device class.\n", THIS_MODULE->name);

	lcddevice = device_create(lcdclass, NULL, devno,NULL, "lcd%d", 0);
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

static int desd_lcd_remove(struct i2c_client *client) 
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

//create i2c device id for slave device
static const struct i2c_device_id desd_lcd_id[] = {
	{SLAVE_DEVICE_NAME, 0},
	{}
};

MODULE_DEVICE_TABLE(i2c, desd_lcd_id);

//create i2c_driver circuit
struct i2c_driver desd_lcd_driver = {
	.driver = {
		.name = SLAVE_DEVICE_NAME,
		.owner = THIS_MODULE,
	},
	.probe = desd_lcd_probe,
	.remove = desd_lcd_remove,
	.id_table = desd_lcd_id,
};

//create i2c board info structure
static struct i2c_board_info lcd_i2c_board_info = {
	I2C_BOARD_INFO(SLAVE_DEVICE_NAME, LCD_SLAVE_ADDR)
};

// As per 4-bit initialization sequence mentioned HD44780 datasheet fig 24 (page 46)
static int __init desd_driver_init(void)
{
	int ret;

	desd_i2c_adapter = i2c_get_adapter(I2C_BUS_AVAILABLE);
	if(desd_i2c_adapter != NULL)		//check success
	{
		desd_i2c_client_lcd = i2c_new_client_device(desd_i2c_adapter, &lcd_i2c_board_info);
		if(desd_i2c_client_lcd != NULL)
		{
			i2c_add_driver(&desd_lcd_driver);
			pr_info("%s : desd_lcd_driver is added",THIS_MODULE->name);
			ret = 0;
		}
		else
			pr_info("%s : lcd client not found",THIS_MODULE->name);

		i2c_put_adapter(desd_i2c_adapter);
	}
	else
		pr_info("%s : I2C bus adapter not found",THIS_MODULE->name);
	
	return ret;
}

static void __exit desd_driver_exit(void)
{
	if(desd_i2c_client_lcd != NULL)
	{
		i2c_unregister_device(desd_i2c_client_lcd);
		i2c_del_driver(&desd_lcd_driver);
	}
	pr_info("%s : Driver Removed!!!\n",THIS_MODULE->name);
}

module_init(desd_driver_init);
module_exit(desd_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aishwarya Chavan @ sunbeam");
MODULE_DESCRIPTION("I2C based LCD device driver");








