#include<linux/module.h>
#include<linux/fs.h>
#include<linux/cdev.h>

#define DEV_BUFFER_SIZE 512
#define DEV_NAME  "My First Char Device"

// Size of Character buffer size
char buffer[DEV_BUFFER_SIZE];

dev_t device_number;

static int __init my_cd_init(void)

{
	printk(KERN_ALERT "Init Function of my character device program");
	
	// Dynamically Allocate Device Number
	alloc_chrdev_region(&device_number, 0, 1, DEV_NAME);
	return 0;
}

static void  __exit my_cd_exit(void)
{
	printk(KERN_ALERT "Init Function of my charactern");
}

module_init(my_cd_init);
module_exit(my_cd_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("HEMANTH");
MODULE_DESCRIPTION("My First Char Device");
