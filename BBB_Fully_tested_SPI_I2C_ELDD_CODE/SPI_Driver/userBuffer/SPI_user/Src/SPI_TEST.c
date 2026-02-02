#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>

char buf[10] = "";
char msg[16] = "";

int main()
{
	int ret;
	int fd = open("/dev/my_spi0",O_RDWR);
	if (fd < 0)
	{
		perror("failed to open spi  device");
		_exit(1);
	}
	printf("spi device file opened.\n");

	// Open the lcd device file
	int fd2 = open("/dev/lcd0", O_WRONLY);
	if (fd2 < 0) {
		perror("Cannot open /dev/lcd");
		return -1;
	}
	printf("lcd device file opened.\n");



	// write(fd,buf,strlen(buf));
	// while(1)
	// {
	while(1)
	{
		ret = read(fd,buf,sizeof(buf));
		printf("bytes read from device: %d -- %02x %02x %02x %02x\n", ret, buf[0],buf[1],buf[2],buf[3]);
		sprintf(msg,"Data:%02x %02x %02x %02x",buf[0],buf[1],buf[2],buf[3]);
		// Write message to LCD
		write(fd2, msg, strlen(msg));
		sleep(1);
	}
	// }

	close(fd);
	close(fd2);
	printf("device file closed.\n");
	return 0;
}
