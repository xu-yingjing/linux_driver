#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>

#define DEVICE_NAME "chrdev_dynamic"

static dev_t device_num;

static int __init chrdev_dynamic_init(void)
{
    int ret;
    int major_num, minor_num;

    printk("module init\n");

    ret = alloc_chrdev_region(&device_num, 0, 1, DEVICE_NAME);
    if (ret < 0)
    {
        printk("alloc_chrdev_region failed\n");

        return -1;
    }
    printk("alloc_chrdev_region success\n");

    major_num = MAJOR(device_num);
    minor_num = MINOR(device_num);

    printk("major_num: %d\n", major_num);
    printk("minor_num: %d\n", minor_num);

    return 0;
}

static void __exit chrdev_dynamic_exit(void)
{
    unregister_chrdev_region(device_num, 1);

    printk("module exit\n");
}

module_init(chrdev_dynamic_init);
module_exit(chrdev_dynamic_exit);

MODULE_LICENSE("GPL");
