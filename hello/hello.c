#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");

static int __init hello_init(void)
{
	printk(KERN_EMERG"hello world\n");
	return 0;
}

static void __exit hello_exit(void)
{
	printk(KERN_EMERG"goodbye\n");
}

module_init(hello_init);
module_exit(hello_exit);
