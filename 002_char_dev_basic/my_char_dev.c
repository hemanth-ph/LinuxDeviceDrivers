#include<linux/module.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include<linux/kdev_t.h>
#include<linux/uaccess.h>


#define DEV_BUFFER_SIZE 512
#define DEV_NAME  "My First Char Device"

// Size of Character buffer size
char buffer[DEV_BUFFER_SIZE];

// Structure to hold dev number.
dev_t device_number;

// Structure to hold c_dev
struct cdev my_cd_cdev;

loff_t my_cd_seek (struct file *fl, loff_t offset, int whence)
{
	return 0;
}

ssize_t my_cd_read (struct file *fl, char __user *buff, size_t size, loff_t *offset)
{
	return 0;
}

ssize_t my_cd_write(struct file *fl, const char __user *buff, size_t count, loff_t *f_pos)
{
	return 0;
}

int my_cd_open (struct inode *ind, struct file *fl)
{
	return 0;
}

int my_cd_release (struct inode *ind, struct file *fl)
{
	return 0;
}

// Structure to hold file operations
struct file_operations my_cd_fops=
						{
							.open = my_cd_open,
							.release = my_cd_release,
							.read = my_cd_read,
							.write = my_cd_write,
							.llseek = my_cd_seek,
							.owner = THIS_MODULE
						};

static int __init my_cd_init(void)

{
	printk(KERN_ALERT "Init Function of my character device program");
	
	// 1. Dynamically Allocate Device Number
	alloc_chrdev_region(&device_number, 0, 1, DEV_NAME);

	// 2. Initialize cdev structure with fops 
	cdev_init(&my_cd_cdev, &my_cd_fops);
	my_cd_cdev.owner = THIS_MODULE; // we are doing it because in above step that structure will be set to 0
	
	// 3. Register our cdev with VFS
	cdev_add(&my_cd_cdev, device_number, 1); 

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
