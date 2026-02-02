#ifndef __MY_SPI_DRIVER_HEADER_H
#define __MY_SPI_DRIVER_HEADER_H

#include<linux/module.h>
#include<linux/spi/spi.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/slab.h>
#include<linux/of_device.h>
#include<linux/delay.h>
#include<linux/fs.h>
#include<linux/device.h>
#include<linux/cdev.h>
#include<linux/kfifo.h>


//SPI driver
extern struct spi_driver SPI_LCD_DRIVER;

int SPI_LCD_PROBE(struct spi_device *spi);
int SPI_LCD_REMOVE(struct spi_device *spi);


//SPI device
extern struct spi_device *my_spi_device;

//device number
extern dev_t devNo;

//device class
extern struct class *pClass;

//cdev object
extern struct cdev myDeviceCdev;
extern struct file_operations my_spi_ops;

int my_spi_open(struct inode *, struct file *);
int my_spi_close(struct inode *, struct file *);
ssize_t my_spi_read(struct file *, char *, size_t, loff_t *);
ssize_t my_spi_write(struct file *, const char *, size_t, loff_t *);

//My device  kernel buffer
extern struct kfifo KERNEL_BUFFER;
#define SIZE 32

#endif
