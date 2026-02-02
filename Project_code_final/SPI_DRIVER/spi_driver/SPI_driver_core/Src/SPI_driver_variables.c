//#include "SPI_driver_header.h"
#include "../../SPI_driver_core/Inc/SPI_driver_header.h"

//Device ids
static const struct spi_device_id my_device_ids[] = {
    {"SPI_LCD",0},
    {}
};

//Adding device id into kernel
MODULE_DEVICE_TABLE(spi,my_device_ids);

//device tree id
static const struct of_device_id spi_device_tree_ids[] = {
    { .compatible = "SPI_LCD"},
    {}
};

//SPI device
struct spi_device *my_spi_device;


MODULE_DEVICE_TABLE(of,spi_device_tree_ids);


//SPI driver
struct spi_driver SPI_LCD_DRIVER = {
    .driver = {
        .name = "SPI_LCD",
        .owner = THIS_MODULE,
        .of_match_table = spi_device_tree_ids,
    },
    .id_table = my_device_ids,
    .probe = SPI_LCD_PROBE,
    .remove = SPI_LCD_REMOVE,
};

//device number
dev_t devNo;

//device class
struct class *pClass;

//cdev object
struct cdev myDeviceCdev;
struct file_operations my_spi_ops = {
    .open = my_spi_open,
    .release = my_spi_close,
    .read = my_spi_read,
    .write = my_spi_write,
};

//My device kernel buffer
struct kfifo KERNEL_BUFFER;