#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include "lcd_fops.h"

static int lcd_open(struct inode *pinode, struct file *pfile)
{
	pr_info("%s : lcd_open() is called\n", THIS_MODULE->name);
    return 0;
}

static int lcd_close(struct inode *pinode, struct file *pfile)
{
	pr_info("%s : lcd_close() is called\n", THIS_MODULE->name);
    return 0;
}

static ssize_t lcd_read(struct file *pfile, char __user *ubuf,size_t ubufsize, loff_t *offset)
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
    .owner   = THIS_MODULE,
    .open    = lcd_open,
    .release = lcd_close,
    .read    = lcd_read,
    .write   = lcd_write,
};
