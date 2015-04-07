#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
	int fd;
	char buf[2];
	fd = open("/dev/mem_dev",O_RDWR);

	if(fd<0)
	{
		printf("ope error\n");
		return 0;
	}

	read(fd,buf,1);
	printf("read num is %d",buf);
	return 0;
}
