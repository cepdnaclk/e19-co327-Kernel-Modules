#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/jiffies.h>
#include <asm/unaccess.h>

MODULE_LICENCE("GPL");
MODULE_AUTHOR("Wishula Jayathunga");

static struct proc_dir_entry *seconds_entry;
static unsigned long start_jiffies;

// Read operation for /proc/seconds
static ssize_t seconds_read(struct file *file, char __user *buf, size_t count, loff_t *offset) {
		
	char seconds_str[20];
	unsigned long elapsed_seconds = (jiffies - start_jiffies) / HZ;
	snprintf(seconds_str, sizeof(seconds_str), "%lu\n", elapsed_seconds);
	return simple_read_from_buffer(buf, count, offset, seconds_str, strlen(seconds_str));

}

static const struct file_operation seconds_fops = {

	.owner = THIS_MODULE,
	.read = seconds_read,
	
};

static int __init seconds_module_init(void) {
	
	start_jiffies = jiffies;
	seconds_entry = proc_create("seconds", 0444, NULL, &seconds_fops);
	
	if
