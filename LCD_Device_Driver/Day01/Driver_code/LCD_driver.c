//Write I2C based device driver for LCD

#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>

// device
#define MAX 32
static char buffer[MAX];
static dev_t devno;
// device class
static struct class *lcdclass;
// device cdev
struct cdev lcd_cdev;
// device operations

static int lcd_open(struct inode *pinode, struct file *pfile);
static int lcd_close(struct inode *pinode, struct file *pfile);
static ssize_t lcd_write(struct file *pfile, const char *ubuf, size_t ubufsize, loff_t *poffset);
static ssize_t lcd_read(struct file *pfile, char *ubuf, size_t ubufsize, loff_t *poffset);

static struct file_operations lcd_fops = {
    .open = lcd_open,
    .release = lcd_close,
    .write = lcd_write,
    .read = lcd_read,
};

// driver init
static int __init I2C_driver_init(void)
{
    int ret;
    struct device *lcddevice;
    pr_info("%s: I2C_driver_init() called.\n", THIS_MODULE->name);
    // allocate device number
    ret = alloc_chrdev_region(&devno, 0, 1, "lcd");
    pr_info("%s: alloc_chrdev_region() allocated devno: %d/%d\n",
            THIS_MODULE->name, MAJOR(devno), MINOR(devno));
    // create device class
    lcdclass = class_create("lcd_class");
    pr_info("%s: class_create() created device class.\n", THIS_MODULE->name);
    // create device file
    lcddevice = device_create(lcdclass, NULL, devno, NULL, "lcd%d", 0);
    pr_info("%s: device_create() created device file.\n", THIS_MODULE->name);
    // init cdev
    cdev_init(&lcd_cdev, &lcd_fops);
    // add cdev in kernel
    ret = cdev_add(&lcd_cdev, devno, 1);
    pr_info("%s: cdev_add() added device in kernel.\n", THIS_MODULE->name);
    return 0;
}

// driver exit
static void __exit I2C_driver_exit(void)
{
    pr_info("%s: I2C_driver_exit() called.\n", THIS_MODULE->name);
    // delete cdev from kernel
    cdev_del(&lcd_cdev);
    pr_info("%s: cdev_del() delete device from kernel.\n", THIS_MODULE->name);
    // destroy device file
    device_destroy(lcdclass, devno);
    pr_info("%s: device_destroy() destroyed device file.\n", THIS_MODULE->name);
    // destroy device class
    class_destroy(lcdclass);
    pr_info("%s: class_destroy() destroyed device class.\n", THIS_MODULE->name);
    // release device number
    unregister_chrdev_region(devno, 1);
    pr_info("%s: unregister_chrdev_region() released device number.\n", THIS_MODULE->name);
}

// file operations
static int lcd_open(struct inode *pinode, struct file *pfile)
{
    pr_info("%s: lcd_open() called.\n", THIS_MODULE->name);
    return 0;
}

static int lcd_close(struct inode *pinode, struct file *pfile)
{
    pr_info("%s: lcd_close() called.\n", THIS_MODULE->name);
    return 0;
}

static ssize_t lcd_write(struct file *pfile, const char __user *ubuf, size_t ubufsize, loff_t *poffset)
{
    pr_info("%s: lcd_write() called.\n", THIS_MODULE->name);

    return ubufsize;
}

static ssize_t lcd_read(struct file *pfile, char __user *ubuf, size_t ubufsize, loff_t *poffset)
{
    int ret;
    pr_info("%s: lcd_read() called.\n", THIS_MODULE->name);
    // copy device buffer into user buffer
    ret = copy_to_user(ubuf, buffer, ubufsize);
    return ubufsize;
}

module_init(I2C_driver_init);
module_exit(I2C_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Aishwarya Chavan @ sunbeam");
MODULE_DESCRIPTION("Simple Char Device Driver");
