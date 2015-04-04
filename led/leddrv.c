#include <linux/module.h>

#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>	/*copy to user,copy from user*/
#include <linux/miscdevice.h>
#include <linux/pci.h>
#include <mach/map.h>
#include <mach/regs-gpio.h>
#include <mach/gpio-bank-m.h>
#include <plat/gpio-cfg.h>

#define LED_MAJOR 240

MODULE_LICENSE("GPL");

int led_open(struct inode *inode,struct file *filp)
{
	unsigned int tmp;
		tmp = readl(S3C64XX_GPMCON);
	tmp = (tmp & ~(0x7u<<1))|0x1u;
		writel(tmp,S3C64XX_GPMCON);
	return 0;
}

ssize_t led_read(struct file *filp,char __user *buf,size_t count,loff_t *fops)
{
	return count;
}

ssize_t led_write(struct file *filp,const char __user *buf,size_t count,loff_t *fops)
{
	char wbuf[10];
	unsigned int tmp;
	copy_from_user(wbuf,buf,count);
	switch(wbuf[0])
	{
		case 0:	//off
			tmp = readl(S3C64XX_GPMDAT);
			tmp |= (0x1u);
			writel(tmp,S3C64XX_GPMDAT);
			break;
		case 1:	//on
			tmp = readl(S3C64XX_GPMDAT);
			tmp &= ~(0x1u);
			writel(tmp,S3C64XX_GPMDAT);
			break;
		default:
			break;
	}
	return count; 
}

int led_release(struct inode *inode,struct file *filp)
{
	printk(KERN_ALERT"relese\n");
	return 0;
}

struct file_operations led_fops={
	.owner = THIS_MODULE,
	.open = led_open,
	.read = led_read,
	.write = led_write,
	.release = led_release,
};

static int __init led_init(void)
{
	int rc;
	rc=register_chrdev(LED_MAJOR,"led",&led_fops);
	if(rc<0)
	{
		printk(KERN_ALERT"regisetr error\n");
		return -1;
	}
	return 0;
}

static void __exit led_exit(void)
{
	unregister_chrdev(LED_MAJOR,"led");
	printk(KERN_ALERT"module exit \n");
	return ;
}

module_init(led_init);
module_exit(led_exit);
