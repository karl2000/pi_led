
// IO映射有问题，待解决



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
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <linux/module.h>
#include <linux/errno.h>
#include <linux/interrupt.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/time.h>
#include <linux/timex.h>
#include <linux/timekeeping.h>
#include <linux/string.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/irq.h>
#include <linux/spinlock.h>
#include <media/lirc.h>
#include <media/lirc_dev.h>
#include <linux/gpio.h>
#include <linux/of_platform.h>
#include <linux/platform_data/bcm2708.h>



#include <linux/device.h>//device_create();device_unregister();
#include <linux/cdev.h>  
#include <linux/fs.h>  //register_chrdev()
#include <asm/io.h>    //ioremap()
#include <mach/platform.h>      
static struct class *leddrv_class;
static struct cdev	*leddrv_class_dev;//用cdev

// struct gpio_chip *gpiochip; 

// static int gpio_2=2;  //gpio 2 
// #define GPFSEL0 (*(volatile unsigned long*)0xF2200000)
// #define GPSET0  (*(volatile unsigned long*)0xF220001C)



volatile unsigned long *gpfsel0 = NULL;
volatile unsigned long *gpset0  = NULL;

// static int is_right_chip(struct gpio_chip *chip, void *data)  
// {  
  
    // if (strcmp(data, chip->label) == 0)  
        // return 1;  
    // return 0;  
// }  
static int led_drv_open(struct inode *inode, struct file *file)
{
	printk("led_drv_open\n");
	
	//将gpio_2设置为输出 
	// *gpfsel0 &= ~((0x1<<8) | (0x1<<7));//第7、8位清零
	// *gpfsel0 |= (0x1<<6);//第6位置1，gpfsel0[8:6]=001，为输出
	return 0;
}

static ssize_t led_drv_write(struct file *file, const char __user *buf, size_t count, loff_t * ppos)
{
	int val;

	printk("led_drv_write\n");

	copy_from_user(&val, buf, count); //用户空间到内核	copy_to_user();内核到用户

	if (val == 1)
	{
		// 点灯
		printk("val=%d\n",val);
		// *gpset0 |= (1<<2);//高电平点灯
		// gpiochip->set(gpiochip, gpio_2, 1);  
		// bcm2835_gpio_set(gpio_2,1);
	}
	else
	{
		// 灭灯
		printk("val=%d\n",val);
		// *gpset0 &= ~(1<<2) ;//低电平灭灯
		// gpiochip->set(gpiochip, gpio_2, 0);  
		// bcm2835_gpio_set(gpio_2,0);
	}
	
	return 0;
}

static struct file_operations led_drv_fops = {
    .owner  =   THIS_MODULE,    /* 这是一个宏，推向编译模块时自动创建的__this_module变量 */
    .open   =   led_drv_open,     
	.write	=	led_drv_write,	   
};



int major;
static int led_drv_init(void)
{
	major = register_chrdev(0, "led_drv", &led_drv_fops); // 注册, 告诉内核

	
	leddrv_class = class_create(THIS_MODULE, "leddrv");

	leddrv_class_dev = device_create(leddrv_class, NULL, MKDEV(major, 0), NULL, "xyz"); /* /dev/xyz */

	// gpiochip = gpiochip_find("bcm2708_gpio", is_right_chip);  //
	// bcm2835_gpio_chip->direction_output(bcm2835_gpio_chip, gpio_2, 1);
	// bcm2835_gpio_chip->set(bcm2835_gpio_chip, gpio_2, 0);  
	// gpiochip = gpiochip_find("bcm2708_gpio", is_right_chip);  //
	// gpiochip->direction_output(gpiochip, gpio_2, 1);  
	// gpiochip->set(gpiochip, gpio_2, 0);  

	// bcm2835_gpio_fsel(gpio_2,1);//设置为输出
	// bcm2835_gpio_set(gpio_2,0);//输出0
	
	
	gpfsel0 = (volatile unsigned long *)ioremap(0x20200000, 16);
	// gpset0  = gpfsel0+7;
	printk("init ok\n");
	
	return 0;
}

static void led_drv_exit(void)
{
	// gpiochip->set(gpiochip, gpio_2, 0);
	// gpio_free(gpio_2); 
	unregister_chrdev(major, "led_drv"); // 卸载

	device_unregister(leddrv_class_dev);
	device_destroy(leddrv_class,MKDEV(major, 0));//增加，与device_create配对
	class_destroy(leddrv_class);
	// iounmap(gpfsel0);
	// iounmap(gpset0);
	
}

module_init(led_drv_init);
module_exit(led_drv_exit);


MODULE_LICENSE("GPL");

