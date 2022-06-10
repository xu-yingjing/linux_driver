#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <filepath>", argv[0]);
    }

    int fd;
    ssize_t ret;
    char write_buf[32] = "This is write\n";
    char read_buf[32] = {0};

    fd = open(argv[1], O_RDWR);
    if (fd < 0)
    {
        printf("Can't open file: %s\n", argv[1]);
        return fd;
    }

    ret = write(fd, write_buf, sizeof(read_buf));
    if (ret < 0)
    {
        printf("Can't write file: %s\n", argv[1]);
        return ret;
    }

    ret = read(fd, read_buf, sizeof(read_buf));
    if (ret < 0)
    {
        printf("Can't read file: %s\n", argv[1]);
        return ret;
    }
    printf("read_buf is %s\n", read_buf);

    close(fd);
}
