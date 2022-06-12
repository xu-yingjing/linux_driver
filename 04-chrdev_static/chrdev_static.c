#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>

#define DEVICE_NAME "chrdev_static"

static int major_num, minor_num;

module_param(major_num, int, S_IRUSR);
module_param(minor_num, int, S_IRUSR);

static int chrdev_static_open(struct inode *inode, struct file *file)
{
    printk("This is open\n");

    return 0;
}

static int chrdev_static_release(struct inode *inode, struct file *file)
{
    printk("This is release\n");

    return 0;
}

static struct file_operations chrdev_static_ops = {
    .owner = THIS_MODULE,
    .open = chrdev_static_open,
    .release = chrdev_static_release,
};

static struct cdev cdev = {
    .owner = THIS_MODULE,
};

static int __init chrdev_static_init(void)
{
    dev_t device_num;
    int ret;

    printk("module init\n");

    if (major_num == 0)
    {
        printk("major_num invalid\n");
        return -1;
    }

    printk("major_num: %d\n", major_num);
    printk("minor_num: %d\n", minor_num);

    device_num = MKDEV(major_num, minor_num);
    ret = register_chrdev_region(device_num, 1, DEVICE_NAME);
    if (ret < 0)
    {
        printk("register_chrdev_region failed\n");
        return -1;
    }
    printk("register_chrdev_region success\n");

    cdev_init(&cdev, &chrdev_static_ops);
    cdev_add(&cdev, device_num, 1);

    return 0;
}

static void __exit chrdev_static_exit(void)
{
    dev_t device_num;

    device_num = MKDEV(major_num, minor_num);

    unregister_chrdev_region(device_num, 1);
    cdev_del(&cdev);

    printk("module exit\n");
}

module_init(chrdev_static_init);
module_exit(chrdev_static_exit);

MODULE_LICENSE("GPL");
