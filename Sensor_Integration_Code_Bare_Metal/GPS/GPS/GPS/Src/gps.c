/*
 * gps.c
 *
 *  Created on: Jan 28, 2026
 *      Author: raghav
 */


#include "GPS.h"

float nmea_to_decimal(float nmea, char dir)
{
    int degrees = (int)(nmea / 100);
    float minutes = nmea - (degrees * 100);
    float decimal = degrees + (minutes / 60.0f);
    if (dir == 'S' || dir == 'W') decimal = -decimal;
    return decimal;
}

void format_decimal(float val, char *buf, int precision)
{
    int int_part = (int)val;
    if (int_part < 0) int_part = -int_part;
    int idx = 0;

    if (val < 0) buf[idx++] = '-';

    char temp[12]; int t_idx = 0;
    if(int_part==0) temp[t_idx++]='0';
    while(int_part>0){
        temp[t_idx++] = '0'+(int_part%10);
        int_part/=10;
    }
    for(int i=t_idx-1;i>=0;i--) buf[idx++]=temp[i];

    if(precision>0){
        buf[idx++]='.';
        float frac = val - (int)val;
        if(frac<0) frac=-frac;
        for(int i=0;i<precision;i++){
            frac *=10;
            int digit = (int)frac;
            buf[idx++]='0'+digit;
            frac -= digit;
        }
    }
    buf[idx]='\0';
}

void convert_utc_to_ist(const char* utc_time, char* ist_time)
{
    int hh=0, mm=0, ss=0;
    if(strlen(utc_time)>=6){
        hh=(utc_time[0]-'0')*10 + (utc_time[1]-'0');
        mm=(utc_time[2]-'0')*10 + (utc_time[3]-'0');
        ss=(utc_time[4]-'0')*10 + (utc_time[5]-'0');

        hh += 5; mm +=30;
        if(mm>=60){ mm-=60; hh+=1; }
        if(hh>=24) hh-=24;

        ist_time[0]='0'+hh/10; ist_time[1]='0'+hh%10;
        ist_time[2]=':';
        ist_time[3]='0'+mm/10; ist_time[4]='0'+mm%10;
        ist_time[5]=':';
        ist_time[6]='0'+ss/10; ist_time[7]='0'+ss%10;
        ist_time[8]='\0';
    }
}

/* Parse GGA sentence */
void parse_gga(char* sentence, char* lat_str, char* lon_str, char* time_str)
{
    char temp[128]; strcpy(temp,sentence);
    char *token = strtok(temp,","); // $GNGGA

    token = strtok(NULL,","); // UTC time
    char utc_time[16]="";
    if(token) strncpy(utc_time, token, sizeof(utc_time));

    token = strtok(NULL,","); // latitude
    float raw_lat = token? atof(token):0;

    token = strtok(NULL,","); // N/S
    char lat_dir = token? token[0]:'N';

    token = strtok(NULL,","); // longitude
    float raw_lon = token? atof(token):0;

    token = strtok(NULL,","); // E/W
    char lon_dir = token? token[0]:'E';

    float latitude = nmea_to_decimal(raw_lat,lat_dir);
    float longitude = nmea_to_decimal(raw_lon,lon_dir);

    format_decimal(latitude, lat_str, 6);
    format_decimal(longitude, lon_str, 6);

    convert_utc_to_ist(utc_time, time_str);
}

/* Parse RMC sentence for date */
void parse_rmc(char* sentence, char* date_str)
{
    char temp[128]; strcpy(temp,sentence);
    char *token = strtok(temp,","); // $GNRMC

    token = strtok(NULL,","); // UTC time
    token = strtok(NULL,","); // status
    for(int i=0;i<6;i++) token=strtok(NULL,","); // skip lat,lon,speed,track

    token = strtok(NULL,","); // date DDMMYY
    if(token && strlen(token)==6){
        date_str[0]=token[0]; date_str[1]=token[1]; date_str[2]='-';
        date_str[3]=token[2]; date_str[4]=token[3]; date_str[5]='-';
        date_str[6]='2'; date_str[7]='0'; date_str[8]=token[4]; date_str[9]=token[5]; date_str[10]='\0';
    }
}
