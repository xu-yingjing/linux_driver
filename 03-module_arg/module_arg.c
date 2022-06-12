#include <linux/init.h>
#include <linux/module.h>

static int arg;
static int array[5];
static int size;

module_param(arg, int, S_IRUSR);
module_param_array(array, int, &size, S_IRUSR);

static int __init module_arg_init(void)
{
    int i;

    printk("arg: %d\n", arg);

    for (i=0; i<size; i++)
    {
        printk("array[%d]: %d\n", i, array[i]);
    }

    return 0;
}

static void __exit module_arg_exit(void)
{
    printk("module exit\n");
}

module_init(module_arg_init);
module_exit(module_arg_exit);

MODULE_LICENSE("GPL");
