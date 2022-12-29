#include<linux/module.h>
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

// Structure to hold class of c_dev
struct class* my_cd_class;

// Structure to hold Device info
struct device* my_cd_device;

loff_t my_cd_seek (struct file *fl, loff_t offset, int whence)
{
	loff_t temp;

	pr_info("lseek requested \n");
	pr_info("Current value of the file position = %lld\n",fl->f_pos);

	if(whence == SEEK_SET)
	{
		if((offset>DEV_BUFFER_SIZE) || (offset<0))
		{
			return -EINVAL;
		}
		fl->f_pos = offset;
	}
	else if(whence == SEEK_CUR)
	{
		temp = fl->f_pos+offset;
		if((temp>DEV_BUFFER_SIZE) || (temp<0))
		{
			return -EINVAL;
		}
		fl->f_pos = temp;
	}
	else if(whence == SEEK_END)
	{
		temp = DEV_BUFFER_SIZE+offset;
		if((temp>DEV_BUFFER_SIZE) || (temp<0))
		{
			return -EINVAL;
		}
		fl->f_pos = temp;
	}
	else 
	{
		return -EINVAL;
	}
	pr_info("New value of the file position = %lld\n",fl->f_pos);
	return fl->f_pos;
}

ssize_t my_cd_read (struct file *fl, char __user *buff, size_t size, loff_t *offset)
{
	// adjust the count
	/*
		If last byte of requested memory > maximum memory allocated to device(DEV_MEM_SIZE)
		then adjust size such that (*offset+count) don't exceed max limit
	*/
	pr_info("Read requested for %zu bytes \n",size);
	pr_info("Current file position = %lld\n",*offset);
	if( (*offset+size) > DEV_BUFFER_SIZE)
	{
		size = DEV_BUFFER_SIZE-*offset;
	}

	/* copy to user */
	if( copy_to_user(buff, (void *)(buffer+*offset), size) )
	{
		return EFAULT;
	}

	/* update file position */
	*offset += size;

	pr_info("Number of bytes successfully read = %zu\n", size);
	pr_info("Updated file position = %lld\n",*offset);


	return size;
}

ssize_t my_cd_write(struct file *fl, const char __user *buff, size_t size, loff_t *offset)
{
	pr_info("Write requested for %zu bytes \n",size);
	pr_info("Current file position = %lld\n",*offset);
	
	// adjust the count
	/*
		If last byte of requested memory > maximum memory allocated to device(DEV_MEM_SIZE)
		then adjust size such that (*offset+count) don't exceed max limit
	*/
	if( (*offset+size) > DEV_BUFFER_SIZE)
	{
		size = DEV_BUFFER_SIZE-*offset;
	}
	
	if(size==0)
	{
		// return -ENOMEM;
	}
	/* copy to user */
	if( copy_from_user((void *)(buffer+*offset), buff, size) )
	{
		return EFAULT;
	}

	/* update file position */
	*offset += size; 

	pr_info("Number of bytes successfully written = %zu\n",size);
	pr_info("Updated file position = %lld\n",*offset);

	return size;
}

int my_cd_open (struct inode *ind, struct file *fl)
{
	pr_info("open was successful\n");
	return 0;
}

int my_cd_release (struct inode *ind, struct file *fl)
{
	pr_info("release was successful\n");
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
	// 1. Dynamically Allocate Device Number
	alloc_chrdev_region(&device_number, 0, 1, DEV_NAME);

	pr_info("Device number <major>:<minor> = %d:%d\n",MAJOR(device_number),MINOR(device_number));

	// 2. Initialize cdev structure with fops 
	cdev_init(&my_cd_cdev, &my_cd_fops);
	my_cd_cdev.owner = THIS_MODULE; // we are doing it because in above step that structure will be set to 0
	
	// 3. Register our cdev with VFS
	cdev_add(&my_cd_cdev, device_number, 1); 

	// 4. Create and register a class with sysfs
	my_cd_class = class_create(THIS_MODULE, "my_cd_class");

	// 5. Populates the sysfs class that was created in step 4 with device numbers and device names
	my_cd_device = device_create(my_cd_class, NULL, device_number, NULL, "my_cd");

	pr_info("Module init was successful\n");

	return 0;
}

static void  __exit my_cd_exit(void)
{
	// Unregister and delete create entities.
	device_destroy(my_cd_class, device_number);
	class_destroy(my_cd_class);
	cdev_del(&my_cd_cdev);
	unregister_chrdev_region(device_number, 1);
	pr_info("module unloaded\n");
}

module_init(my_cd_init);
module_exit(my_cd_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("HEMANTH");
MODULE_DESCRIPTION("My First Char Device");
