ifneq ($(KERNELRELEASE),)
obj-m:=hello.o

else
KDIR:=/home/forlinux/linux-3.0.1

all:
	make -C $(KDIR) M=$(PWD) modules ARCH=arm CROSS_COMPILE=arm-linux-
clean:
	rm -f *.ko *.o *.mod.o *.mod.c *.symvers

endif

