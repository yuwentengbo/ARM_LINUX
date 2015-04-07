#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
	int fd=0;
	char buf[2]={1,2};
	fd = open("/dev/mem_dev",O_RDWR);
	if(fd<0)
	{
		printf("open error\n");
		return -1;
	}

	write(fd,buf,1);
	return 0;
}
