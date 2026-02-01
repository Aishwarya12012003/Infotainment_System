#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

char buf[10] = "";

int main()
{
    int ret;
    int fd = open("/dev/my_spi0",O_RDWR);
    if (fd < 0)
    {
        perror("failed to open device");
        _exit(1);
    }
    printf("device file opened.\n");
    
    // write(fd,buf,strlen(buf));
    // while(1)
    // {
    while(1)
    {
    	ret = read(fd,buf,sizeof(buf));
        printf("bytes read from device: %d -- %02x %02x %02x %02x\n", ret, buf[0],buf[1],buf[2],buf[3]);
    	sleep(1);
    }
    // }

    close(fd);
    printf("device file closed.\n");
    return 0;
}
