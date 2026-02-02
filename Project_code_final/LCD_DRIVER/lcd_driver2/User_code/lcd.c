#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int fd;
    char *msg;

    if (argc < 2) {
        printf("Usage: %s <message>\n", argv[0]);
        return -1;
    }

    msg = argv[1];

    // Open the device file
    fd = open("/dev/lcd0", O_WRONLY);
    if (fd < 0) {
        perror("Cannot open /dev/lcd");
        return -1;
    }

    // Write message to LCD
    write(fd, msg, strlen(msg));

    printf("Message sent to LCD: %s\n", msg);
    // Close device
    close(fd);

    return 0;
}
