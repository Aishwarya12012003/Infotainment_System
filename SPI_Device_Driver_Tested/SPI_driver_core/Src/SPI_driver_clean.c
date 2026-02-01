#include "../../SPI_driver_core/Inc/SPI_driver_header.h"

//Cleanup
static void __exit SPI_DRIVER_EXIT(void)
{
    pr_info("%s: SPI_DRIVER_EXIT() is called\n",THIS_MODULE->name);

    spi_unregister_driver(&SPI_LCD_DRIVER);

    pr_info("%s: SPI_DRIVER_EXIT() is completed\n",THIS_MODULE->name);
}
module_exit(SPI_DRIVER_EXIT);