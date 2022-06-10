#include <linux/init.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>

static struct file_operations misc_fops = {
    .owner = THIS_MODULE,
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
