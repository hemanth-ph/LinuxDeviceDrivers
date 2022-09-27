#include <linux/module.h>


static int __init hello_world_init(void)
{
	pr_info("Hello world LKM Init Function\n");
	return 0;
}


static void  __exit hello_world_exit(void)
{
	pr_info("Hello WOrld LKM Exit Function\n");

}	

module_init(hello_world_init);
module_exit(hello_world_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hemanth");
MODULE_DESCRIPTION("My First Module");
