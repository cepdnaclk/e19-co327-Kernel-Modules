#include <linux/module.h>       // Needed by all modules
#include <linux/kernel.h>       // Needed for KERN_INFO
#include <linux/slab.h>         // Needed for kmalloc and kfree
#include <linux/list.h>         // Needed for linked list functions
#include <linux/init.h>         // Needed for the macros

MODULE_LICENSE("GPL");           // The license type -- this affects available functionality
MODULE_AUTHOR("Your Name");      // The author -- visible when you use modinfo
MODULE_DESCRIPTION("A simple Linux kernel module for the Collatz conjecture");
MODULE_VERSION("0.1");           // The module version number

static int start_value = 6;      // Default start value if no parameter is provided
module_param(start_value, int, S_IRUGO); // Module parameter for start value

struct collatz_list {
    struct list_head list;       // Kernel's list structure
    unsigned long value;
};

static LIST_HEAD(collatz_head);  // Define the head of the linked list

// Function to generate the Collatz sequence and add it to the linked list
void generate_collatz_sequence(unsigned long value) {
    struct collatz_list *node;

    while (value != 1) {
        node = kmalloc(sizeof(*node), GFP_KERNEL);
        if (!node) {
            printk(KERN_ERR "Unable to allocate memory for the Collatz sequence\n");
            return;
        }

        node->value = value;
        list_add_tail(&node->list, &collatz_head);

        // Collatz conjecture: n -> n/2 (if n is even) or 3n+1 (if n is odd)
        if (value % 2 == 0)
            value /= 2;
        else
            value = 3 * value + 1;
    }
}

// Module entry point
static int __init collatz_init(void) {
    struct collatz_list *node;

    printk(KERN_INFO "Starting Collatz module with start value: %d\n", start_value);
    generate_collatz_sequence(start_value);

    // Traverse the list and output its contents to the kernel log buffer
    list_for_each_entry(node, &collatz_head, list) {
        printk(KERN_INFO "%lu ", node->value);
    }
    printk(KERN_INFO "\n");

    return 0;
}

// Module exit point
static void __exit collatz_exit(void) {
    struct collatz_list *node, *tmp;

    printk(KERN_INFO "Removing Collatz module\n");

    // Delete the elements from the linked list and return the free memory back to the kernel
    list_for_each_entry_safe(node, tmp, &collatz_head, list) {
        list_del(&node->list);
        kfree(node);
    }
}

// Register module entry/exit points
module_init(collatz_init);
module_exit(collatz_exit);
