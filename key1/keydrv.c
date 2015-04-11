#include <linux/module.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <linux/miscdevice.h>
#include <linux/pci.h>
#include <mach/map.h>
#include <mach/regs-gpio.h>
#include <mach/gpio-bank-m.h>
#include <plat/gpio-cfg.h>

#define KEY_MAJOR 240

volatile unsigned long *gpncon = NULL;
volatile unsigned long *gpndat = NULL;
static int key_open(struct inode *inode,struct file *filp)
{
	unsigned long tmp;
	
	tmp = 0xffffff00;
	*gpncon &=tmp ;
	return 0;
}

static int key_read(struct file *file,char __user *user,size_t size,loff_t *ppos)
{
	unsigned int key_val[4];
	unsigned long  tmp;
	
	if(size != sizeof(key_val))
		return -EINVAL;

	tmp = *gpndat;
	
	key_val[0] = (tmp & 1<<0)? 1:0;
	key_val[1] = (tmp & 1<<1)? 1:0;
	key_val[2] = (tmp & 1<<2)? 1:0;
	key_val[3] = (tmp & 1<<3)? 1:0;

	copy_to_user(user,key_val,sizeof(key_val));
	return sizeof(key_val);
}
static const struct file_operations key_fops={
.owner=THIS_MODULE,
.open=key_open,
.read=key_read,
};

static int key_init(void)
{
	int ret = 0;
	ret = register_chrdev(KEY_MAJOR,"key_drv",&key_fops);
	if(ret < 0)
		return ret;
	gpncon = (volatile unsigned long *)ioremap(0x7f008830,16);
	gpndat = gpncon + 1;
	printk(KERN_INFO"key_init\n");
	return 0;
}

static void key_exit(void)
{
	unregister_chrdev(KEY_MAJOR,"key_drv");
	printk(KERN_INFO"key_exit\n");
	return;
}

module_init(key_init);
module_exit(key_exit);

MODULE_LICENSE("GPL"); 
