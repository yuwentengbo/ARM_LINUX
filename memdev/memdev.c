#include <linux/module.h>
#include <linux/types.h>
#include <linux/cdev.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>      /*copy to user,copy from user*/
#include <linux/miscdevice.h>
#include <linux/pci.h>
#include <mach/map.h>
#include <mach/regs-gpio.h>
#include <mach/gpio-bank-m.h>
#include <plat/gpio-cfg.h>
#include <linux/slab.h>

#define MEM_MAJOR 240
char wbuf[100];

int  mem_open(struct inode *inode,struct file *filp)
{
	return 0;
}

int mem_release(struct inode *inode,struct file *filp)
{
	return 0;
}

static size_t mem_read(struct file *filp,char __user *buf,size_t size,loff_t *ppos)
{
	int ret=0;
	unsigned int count = size;
	
	ret = copy_to_user(buf,wbuf,count);
	if(ret != 0)	return -EFAULT;
	return (size_t)ret; 
}

static size_t mem_write(struct file *filp,char __user *buf,size_t size,loff_t *ppos)
{
	int ret=0;
	unsigned int count = size;

	if(copy_from_user(wbuf,buf,count))
	{
		ret = -EFAULT;
	}

	return (size_t)ret;
}


static const struct file_operations mem_fops={
.owner = THIS_MODULE,
.open = mem_open,
.read = mem_read,
.write = mem_write,
.release = mem_release,
};

static int memdev_init(void)
{
	int result,i;

	result = register_chrdev(MEM_MAJOR,"memdev",&mem_fops);

	if(result < 0)
		return result;
	printk(KERN_INFO"memdev init\n");
	return 0;
}

static void memdev_exit(void)
{
	unregister_chrdev(MEM_MAJOR,"memdev");
	printk(KERN_INFO"memdev exit\n");
	return;
}

MODULE_LICENSE("GPL");

module_init(memdev_init);
module_exit(memdev_exit);
