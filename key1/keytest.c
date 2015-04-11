#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main(void)
{
	int fd;
	int key_val[4]={1,1,1,1};
	fd = open("/dev/keydrv",O_RDWR);
	if(fd<0)
	{
		printf("open error\n");
		return -1;
	}
	while(1)
	{
		read(fd,key_val,sizeof(key_val));
		if(!key_val[0] || !key_val[1] || !key_val[2] || !key_val[3])
			printf("%d %d %d %d\n",key_val[0],key_val[1],key_val[2],key_val[3]);
	}
	return 0;
}
