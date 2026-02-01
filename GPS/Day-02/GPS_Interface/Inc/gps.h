/*
 * gps.h
 *
 *  Created on: 02-Dec-2025
 *      Author: sunbeam
 */

#ifndef GPS_H_
#define GPS_H_

#include <stdint.h>

/* Function Declarations */
void parse_gga(char* sentence, char* lat_str, char* lon_str, char* time_str);
void parse_rmc(char* sentence, char* date_str);

#endif /* GPS_H_ */
