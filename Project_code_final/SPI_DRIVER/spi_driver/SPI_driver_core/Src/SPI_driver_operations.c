
#include "../../SPI_driver_core/Inc/SPI_driver_header.h"
#include <linux/delay.h> // Required for udelay()
#include "../../MCP2515/Inc/SPI_CAN_header.h"


int SPI_LCD_PROBE(struct spi_device *spi)
{
    pr_info("%s: SPI_LCD_PROBE() is called\n", THIS_MODULE->name);

    /* 1. Configure the SPI Bus Parameters */
    spi->mode = SPI_MODE_0; // Often works better for generic comms, Mode 3 is also acceptable
    spi->bits_per_word = 8;
    spi->max_speed_hz = 500000; // Safe initial speed

    // MCP2515_RESET(spi);
    // /* 3. Wait for the Oscillator Start-up Timer (OST) */
    // udelay(100); // Wait >128 oscillator cycles (100us is safe for 8MHz crystal)

    // MCP2515_WRITE_REG(spi,CANCTRL,CONFIGURATION);
    // int canstat_value = MCP2515_READ_REG(spi, CANSTAT);
    // if (canstat_value < 0) {
    //     pr_err("%s: Verification read failed, SPI error %d\n", THIS_MODULE->name, canstat_value);
    //     return canstat_value;
    // }
    // pr_info("%s: Read CANSTAT register: 0x%02X\n", THIS_MODULE->name, canstat_value);
    // // Check if the value matches the expected Configuration Mode (0x80 in the top 3 bits)
    // if ((canstat_value & 0xE0) == CONFIGURATION) {
    //     pr_info("%s: MCP2515 communication VERIFIED! Chip is in Configuration Mode.\n", THIS_MODULE->name);
    //     my_spi_device = spi; // Store device pointer only if verification passes
    // } else {
    //     pr_err("%s: MCP2515 verification failed. Unexpected CANSTAT value received.\n", THIS_MODULE->name);
    //     pr_err("%s: Check hardware connections, power supply, and crystal oscillator.\n", THIS_MODULE->name);
    //     return -ENODEV; // No device found or responding incorrectly
    // }

    if(!MCP2515_RX_INIT(spi))
    {
	    my_spi_device = spi;
	    pr_info("%s: my_spi_device is initialized\n",THIS_MODULE->name);
    }

    //allocate device number
    int ret = alloc_chrdev_region(&devNo,0,1,"my_spi");
    if(ret<0)
    {
        pr_err("%s: alloc_chrdev_region() is failed\n",THIS_MODULE->name);
        goto alloc_chrdev_region_failed;
    }
    pr_info("%s: alloc_chrdev_region() is successful\n",THIS_MODULE->name);

    //create device class   
    pClass = class_create(THIS_MODULE,"my_spi_class");
    if(IS_ERR(pClass))
    {
        pr_err("%s: class_create() is failed\n",THIS_MODULE->name);
        ret=-1;
        goto class_create_failed;
    }
    pr_info("%s: class_create() is successful\n",THIS_MODULE->name);

    //create device file
    struct device *pDevice = device_create(pClass,NULL,devNo,NULL,"my_spi%d",0);
    if(IS_ERR(pDevice))
    {
        pr_err("%s: device_create() is failed\n",THIS_MODULE->name);
        ret=-1;
        goto device_create_failed;
    }
    pr_info("%s: device_create() is successful\n",THIS_MODULE->name);
    
    //init cdev object and add it
    cdev_init(&myDeviceCdev,&my_spi_ops);
    ret = cdev_add(&myDeviceCdev,devNo,1);
    if(ret<0)
    {
        pr_err("%s: cdev_add() is failed\n",THIS_MODULE->name);
        goto cdev_add_failed;
    }
    pr_info("%s: cdev_add() is successful\n",THIS_MODULE->name);

   //allocate kfifo
    ret = kfifo_alloc(&KERNEL_BUFFER,SIZE,GFP_KERNEL);
    if(ret != 0)
    {
        pr_err("%s: kfifo_alloc() is failed\n",THIS_MODULE->name);
        goto kfifo_alloc_failed;
    }
    pr_info("%s: kfifo_alloc() is successful\n",THIS_MODULE->name);


    return 0; // Success
    
    kfifo_alloc_failed:
        cdev_del(&myDeviceCdev);
    cdev_add_failed:
        device_destroy(pClass,devNo);
    device_create_failed:
        class_destroy(pClass);
    class_create_failed:
        unregister_chrdev_region(devNo,1);
    alloc_chrdev_region_failed:
        return ret;
    
}


int SPI_LCD_REMOVE(struct spi_device *spi)
{
    // ... (rest of the remove function is fine)
    pr_info("%s: SPI_LCD_REMOVE() is called\n",THIS_MODULE->name);
    
    //free kernel buffer
    kfifo_free(&KERNEL_BUFFER);

    //delete cdev object
    cdev_del(&myDeviceCdev);

    //delete device file
    device_destroy(pClass,devNo);

    //destroy device class
    class_destroy(pClass);

    //release device number
    unregister_chrdev_region(devNo,1);

    if(my_spi_device==spi)
        my_spi_device = NULL;
    return 0;
}


int my_spi_open(struct inode *pInode, struct file *pFile)
{
    pr_info("%s: my_spi_open() is successful\n",THIS_MODULE->name);
    return 0;
}

int my_spi_close(struct inode *pInode, struct file *pFile)
{
    pr_info("%s: my_spi_close() is successful\n",THIS_MODULE->name);
    return 0;
}

ssize_t my_spi_read(struct file *pFile, char __user *UBUF, size_t UBUF_LEN, loff_t *poffset)
{
    pr_info("%s: my_spi_read() is successful\n",THIS_MODULE->name);
    uint8_t data[8];
    MCP2515_RX_MSG(my_spi_device,data);
    //pr_info("%s: data: %s\n",THIS_MODULE->name,data);
    pr_info("%s: data: %02x %02x %02x %02x\n",THIS_MODULE->name,data[0],data[1],data[2],data[3]);
    
    kfifo_in(&KERNEL_BUFFER, data, 8);

    int bytesRead,ret;
    if(kfifo_is_empty(&KERNEL_BUFFER))
    {
        pr_warn("%s: buffer is empty\n",THIS_MODULE->name);
        return 0;
    }
    ret = kfifo_to_user(&KERNEL_BUFFER,UBUF,UBUF_LEN,&bytesRead);
    if(ret!=0)
    {
        pr_info("%s: kfifo_to_user() is failed\n",THIS_MODULE->name);
        return ret;
    }
    pr_info("%s: kfifo_to_user() is successful\n",THIS_MODULE->name);

    return bytesRead;

    return 0;
}

ssize_t my_spi_write(struct file *pFile, const char __user *UBUF, size_t UBUF_LEN, loff_t *poffset)
{
    pr_info("%s: my_spi_write() is successful\n",THIS_MODULE->name);
    // // uint16_t id = 0x123;
    // MCP2515_WRITE_REG(my_spi_device,CNF1,0x00);
    // MCP2515_WRITE_REG(my_spi_device,CNF2,0x90);
    // MCP2515_WRITE_REG(my_spi_device,CNF3,0x02);

    // MCP2515_WRITE_REG(my_spi_device,RXMnSIDH,0x00);
	// MCP2515_WRITE_REG(my_spi_device,RXMnSIDL,0x00);
    // // // MCP2515_WRITE_REG(spi,RXFnSIDH,(uint8_t)(id>>3));
    // // // MCP2515_WRITE_REG(spi,RXFnSIDL,(uint8_t)(id<<5));
    // MCP2515_WRITE_REG(my_spi_device,CANCTRL,NORMAL);
    return 0;
}
