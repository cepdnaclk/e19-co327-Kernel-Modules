// Include necessary header files
#include <linux/module.h>  // Needed by all modules
#include <linux/kernel.h>  // Needed for KERN_INFO
#include <linux/proc_fs.h>  // Needed for proc file system functions
#include <linux/jiffies.h>  // Needed for jiffies
#include <asm/unaccess.h>  // Needed for user space copy function

// Module metadata
MODULE_LICENCE("GPL");  // The license type -- this affects runtime behaviour (GNU Public License)
MODULE_AUTHOR("Wishula Jayathunga");  // The author -- visible when we use modinfo

// Declare variables
static struct proc_dir_entry *seconds_entry;  // Pointer to the proc file entry
static unsigned long start_jiffies;  // Variable to hold start time in jiffies

// Read operation for /proc/seconds
static ssize_t seconds_read(struct file *file, char __user *buf, size_t count, loff_t *offset) {
		
	char seconds_str[20];  // Buffer to hold string representation of elapsed seconds
	unsigned long elapsed_seconds = (jiffies - start_jiffies) / HZ;  // Calculate elapsed seconds
	snprintf(seconds_str, sizeof(seconds_str), "%lu\n", elapsed_seconds);  // Format elapsed seconds as string
	return simple_read_from_buffer(buf, count, offset, seconds_str, strlen(seconds_str));  // Return elapsed seconds to user

}

// File operations structure
static const struct file_operation seconds_fops = {

	.owner = THIS_MODULE,  // Owner is this module
	.read = seconds_read,  // Read operation is handled by seconds_read function
};

// Module initialization function
static int __init seconds_module_init(void) {
	
	start_jiffies = jiffies;  // Save the current time in jiffies
	seconds_entry = proc_create("seconds", 0444, NULL, &seconds_fops);  // Create the /proc/seconds file
	
	if (!seconds_entry) {
		return -ENOMEM  // Return error if proc file creation failed
	} else {
		printk(KERN_INFO "Successfully created /proc/seconds\n");  // Log success message
