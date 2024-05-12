#include <linux/module.h>  // for documentation and macros
#include <linux/kernel.h>  // for kernel macros and functions, kernel data types, kernel version info
#include <linux/proc_fs.h>  // for proc file system (procfs) interface, creating procs entries, reading and writing to procfs
#include <asm/param.h>  // for HZ (jiffies frequency>

MODULE_LICENSE("GPL ");
MODULE_AUTHOR("Wishula Jayathunga");

static struct proc_dir_entry *jiffies_entry;

// Read operation for /proc/jiffies
static ssize_t jiffies_read(struct file *file, char __user *buf, size_t count, loff_t *offset){
  
    char jiffies_str[20];
    snprintf(jiffies_str, sizeof(jiffies_str), "%lu\n", jiffies);
    return simple_read_from_buffer(buf, count, offset, jiffies_str, strlen(jiffies_str));
  
}
  
static const struct file_operations jiffies_fops = {
 
 .owner = THIS_MODULE,
 .read = jiffies_read,
   
}

static int __init jiffies_module_init(void) {

  jiffies_entry = proc_create("jiffies", 0444, NULL, &jiffies_fops);
  
  if (!jiffies_entry)
    return -ENOMEM;
    
  return 0;
  
}

static void __exit jiffies_module_exit(void)
{
  proc_remove(jiffies_entry);
}

module_init(jiffies_module_init);
module_exit(jiffies_module_exit);