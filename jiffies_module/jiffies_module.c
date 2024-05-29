#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Wishula Jayathunga");

static struct proc_dir_entry *jiffies_entry;

// Read operation for /proc/jiffies
static ssize_t jiffies_read(struct file *file, char __user *buf, size_t count, loff_t *offset)
{
    char jiffies_str[20];
    ssize_t len;
    int ret;

    snprintf(jiffies_str, sizeof(jiffies_str), "%lu\n", jiffies);
    len = strlen(jiffies_str);

    ret = simple_read_from_buffer(buf, count, offset, jiffies_str, len);

    if (ret < 0)
        pr_err("Failed to read jiffies\n");

    return ret;
}

static const struct proc_ops jiffies_fops = {
    .proc_read = jiffies_read
};

static int __init jiffies_module_init(void)
{
    jiffies_entry = proc_create("jiffies", 0444, NULL, &jiffies_fops);

    if (!jiffies_entry) {
        pr_err("Failed to create /proc/jiffies entry\n");
        return -ENOMEM;
    }

    pr_info("/proc/jiffies entry created\n");
    return 0;
}

static void __exit jiffies_module_exit(void)
{
    proc_remove(jiffies_entry);
    pr_info("/proc/jiffies entry removed\n");
}

module_init(jiffies_module_init);
module_exit(jiffies_module_exit);

