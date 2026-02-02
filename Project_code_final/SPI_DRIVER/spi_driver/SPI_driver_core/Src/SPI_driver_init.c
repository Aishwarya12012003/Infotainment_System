#include "../../SPI_driver_core/Inc/SPI_driver_header.h"


//Initialization
static int __init SPI_DRIVER_INIT(void)
{
    pr_info("%s: SPI_DRIVER_INIT() is called\n",THIS_MODULE->name);

    int ret = spi_register_driver(&SPI_LCD_DRIVER);
    if(ret<0)
    {
        spi_unregister_device(my_spi_device);
        pr_err("%s: spi_register_driver() is failed\n",THIS_MODULE->name);
        return ret;
    }

    pr_info("%s: SPI_DRIVER_INIT() is completed\n",THIS_MODULE->name);
    return 0;
}
module_init(SPI_DRIVER_INIT);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Raghav Goel");
MODULE_DESCRIPTION("SPI-MCP2515 Driver Code");