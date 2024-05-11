#include <linux/module.h>  // for documentation and macros
#include <linux/kernel.h>  // for kernel macros and functions, kernel data types, kernel version info
#include <linux/proc_fs.h>  // for proc file system (procfs) interface, creating procs entries, reading and writing to procfs
#include <asm/param.h>  // for HZ (jiffies frequency>

MODULE_LICENSE("GPL ");
MODULE_AUTHOR("Wishula Jayathunga");

static struct proc_dir_entry *jiffies_entry;

// Read operation for /proc/jiffies
static ssize_t jiffies_read(struct file *file, char __user *buf, size_t count, loff_t *offset)
  {
    char jiffies_str[20];
    snprintf(jiffies_str, sizeof
  } 