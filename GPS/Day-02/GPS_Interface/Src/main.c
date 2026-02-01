/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : STM32 Bare-metal GPS Parsing (GGA + RMC) – Interrupt based
 ******************************************************************************
 */

#include <stdint.h>
#include <string.h>
#include "uart.h"
#include "gps.h"

/* GPS output buffers (used by parser) */
char lat_str[32]  = "";
char lon_str[32]  = "";
char time_str[16] = "";
char date_str[16] = "";

int main(void)
{
    char buffer[128];   // Line buffer (local, safe)

    UartInit(9600);
    UartPuts("GPS Interrupt Mode Started...\r\n");

    while (1)
    {
        /* Check if ISR has received a full line */
        if (UartLineAvailable())
        {
            UartReadLine(buffer);

            if (!strncmp(buffer, "$GNGGA", 6) || !strncmp(buffer, "$GPGGA", 6))
            {
                parse_gga(buffer, lat_str, lon_str, time_str);

                UartPuts("Time: "); UartPuts(time_str); UartPuts("\r\n");
                UartPuts("Lat : "); UartPuts(lat_str);  UartPuts("\r\n");
                UartPuts("Lon : "); UartPuts(lon_str);  UartPuts("\r\n");
            }
            else if (!strncmp(buffer, "$GNRMC", 6) || !strncmp(buffer, "$GPRMC", 6))
            {
                parse_rmc(buffer, date_str);

                UartPuts("Date: "); UartPuts(date_str);
                UartPuts("\r\n\r\n");
            }
        }
    }
}
