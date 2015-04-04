#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
	int fd;
	char buf[2]={0,1};
	fd=open("/dev/my_led",O_RDWR);
	if(fd<0)
	{
		printf("open /dev/my_led error\n");
		return -1;
	}
	while(1)
	{
		write(fd,&buf[0],1);
		sleep(1);
		write(fd,&buf[1],1);
		sleep(1);
	}
	close(fd);
	return 0;
}
