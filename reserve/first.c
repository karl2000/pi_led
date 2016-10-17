#include <linux/miscdevice.h>  
#include <linux/delay.h>  
#include <asm/irq.h>  
#include <linux/kernel.h>  
#include <linux/module.h>  
#include <linux/init.h>  
#include <linux/mm.h>  
#include <linux/fs.h>  
#include <linux/types.h>  
#include <linux/delay.h>  
#include <linux/moduleparam.h>  
#include <linux/slab.h>  
#include <linux/errno.h>  
#include <linux/ioctl.h>  
#include <linux/cdev.h>  
#include <linux/string.h>  
#include <linux/list.h>  
#include <linux/pci.h>  
#include <asm/uaccess.h>  
#include <asm/atomic.h>  
#include <asm/unistd.h>  
#include <asm/io.h>  
#include <asm/uaccess.h>  
#include <linux/ioport.h>  
   
static struct class *firstdrv_class;
static struct class_device	*firstdrv_class_dev;

static int first_drv_open(struct inode *inode, struct file *file)
{
	printk(KERN_ALERT "first_drv_open\n");
	return 0;
}
static ssize_t first_drv_write(struct file *file, const char __user *buf, size_t count, loff_t * ppos)
{
	printk(KERN_ALERT "first_drv_write\n");
	return 0;
}
static struct file_operations first_drv_fops = {
    .owner  =   THIS_MODULE,    /* 这是一个宏，推向编译模块时自动创建的__this_module变量 */
    .open   =   first_drv_open,     
	.write	=	first_drv_write,	   
};


int major;
static int first_drv_init(void)
{
	register_chrdev(111, "first_drv", &first_drv_fops); // 注册, 告诉内核

	return 0;
}

static void first_drv_exit(void)
{
	unregister_chrdev(111, "first_drv"); // 卸载

}

module_init(first_drv_init);
module_exit(first_drv_exit);


MODULE_LICENSE("GPL");

