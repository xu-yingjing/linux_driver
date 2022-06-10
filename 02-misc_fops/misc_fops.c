#include <linux/init.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>

static int misc_open(struct inode *inode, struct file *file)
{
    printk("This is misc open\n");
    return 0;
}

static int misc_release(struct inode *inode, struct file *file)
{
    printk("This is misc release\n");
    return 0;
}

static ssize_t misc_read(struct file *file, char __user *ubuf, size_t size, loff_t *loff)
{
    char kbuf[] = "This is misc read\n";

    if (copy_to_user(ubuf, kbuf, sizeof(kbuf)) != 0)
    {
        printk("copy_to_user failed\n");
        return -1;
    }

    return 0;
}

static ssize_t misc_write(struct file *file, const char __user *ubuf, size_t size, loff_t *loff)
{
    char kbuf[32] = {0};

    if (copy_from_user(kbuf, ubuf, size) != 0)
    {
        printk("copy_from_user failed\n");
        return -1;
    }

    printk("kbuf is %s\n", kbuf);
    
    return 0;
}

static struct file_operations misc_fops = {
    .owner = THIS_MODULE,
    .open = misc_open,
    .release = misc_release,
    .read = misc_read,
    .write = misc_write,
};

static struct miscdevice misc_dev = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "misc_dev",
    .fops = &misc_fops,
};

static int __init misc_init(void)
{
    int ret;

    ret = misc_register(&misc_dev);
    if (ret < 0)
    {
        printk("misc device register failed\n");
        return -1;
    }

    printk("misc device register success\n");

    return 0;
}

static void __exit misc_exit(void)
{
    misc_deregister(&misc_dev);
    printk("misc device deregister success\n");
}

module_init(misc_init);
module_exit(misc_exit);

MODULE_LICENSE("GPL");
