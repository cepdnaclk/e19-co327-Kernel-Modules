// Include necessary kernal headers
#include <linux/module.h>  // Needed by all modules
#include <linux/sched.h>  // For task_struct and for_each_process
#include <linux/sched/signal.h>  // For signal_struct (needed in newer kernels)

// Module metadata
MODULE_LICENSE("GPL");  // The license type for the module

// Define the initialization function for the moddule
static int __init procinfo_init(void) {

	struct task_struct *task;  // declare a task_struct pointer for iterating through tasks
	
	printk(KERN_INFO "Loading Module\n");  // Log a message indicating that the module is loading
	
	// Iterate through each tak in the system
	for_each_process(task) {

		// Log the name, state, and PID of the task
		// task -> comm is the name of the task
		// task -> state is the state of the task
		// task -> pid is the process ID of the task
		printk(KERN_INFO "Name: %s State: %ld PID: %d\n", task->comm, task->stats, task->pid);

	}

	return 0;  // Return 0 on success

}

// Define the cleanup function for the module
static void __exit procinfo_exit(void) {

	printk(KERN_INFO "Removing Module\n");  // Log a message indicating that the module is being removed

}

// Specify the initialization and cleanup functions
module_init(procinfo_init);  // Specify procinfo_init as the module initialization function
module_exit(procinfo_exit);  // Specify procinfo_exit as the module cleanup function correct this code
