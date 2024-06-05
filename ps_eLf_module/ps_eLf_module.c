// Include necessary lernel headers for module development
#include<linux/module.h>  // Required for all kernel modules
#include<linux/sched/signal.h>  // Required for task_struct and for_each_process macros
#include<linux/sched.h>  // Required for the task_struct definition

// Define the license for this kernel module
MODULE_LICENSE("GPL");  // GPL license allows the free distribution and modification of the source

// Function to perform a depth-first search on the process tree
void dfs(struct task_struct *task) {

	struct task_struct *child;  // Pointer to the child task
	struct list_head *list;  // Pointer to the list structure to iterate through the task children
	
	// Print information about the current task
	printk(KERN_INFO "Name: %s State: %ld PID: %d\n", task->comm, task->stats, task->pid);
	
	// Iterate overeach child of the current task
	list_for_each(list, &task->children) {
		
		// Get the task_struct from the list entry
		child = list_entry(list, struct task_struct, sibling);
		
		// Recursively call dfs on the child task
		dfs(child);
	}
}

// Initialization function of the module
static int __init dfs_module_init(void) {

	printk(KERN_INFO "Loading DFS Module\n");  // Log message indicating module loading
	
	// Start the DFS from the initial task (init_task)
	dfs(&init_task);
	
	return 0;  // Return 0 indicates successful module initialization	
	
}

// Exit function of the module
static void __exit dfs_module_exit(void) {

	printk(KERN_INFO "Removing DFS Module\n");  // Log message indicating module removal
	
}

// Register the initialization and exit function of the module
module_init(dfs_module_init);  // Macro to load the module's entry point
module_exit(dfs_module_exit);  // Macro to load the module's exit point






























