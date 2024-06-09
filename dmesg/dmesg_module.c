#include <linux/module.h>       // Needed by all modules
#include <linux/kernel.h>       // Needed for KERN_INFO
#include <linux/slab.h>         // Needed for kmalloc and kfree
#include <linux/list.h>         // Needed for linked list functions

MODULE_LICENSE("GPL");

struct my_list {
    struct list_head list; // Kernel's list structure
    int data;
};

static LIST_HEAD(my_linked_list);

static int __init linked_list_init(void) {
    struct my_list *new_element, *cursor;
    int i;

    printk(KERN_INFO "Loading linked list module\n");

    // Create and add new elements to the linked list
    for (i = 0; i < 5; i++) {
        new_element = kmalloc(sizeof(*new_element), GFP_KERNEL);
        if (!new_element)
            return -ENOMEM;

        new_element->data = i;
        INIT_LIST_HEAD(&new_element->list);
        list_add_tail(&new_element->list, &my_linked_list);
    }

    // Traverse the linked list and output its contents to the kernel log buffer
    list_for_each_entry(cursor, &my_linked_list, list) {
        printk(KERN_INFO "Element data: %d\n", cursor->data);
    }

    return 0;
}

static void __exit linked_list_exit(void) {
    struct my_list *cursor, *tmp;

    printk(KERN_INFO "Removing linked list module\n");

    // Delete the elements from the linked list and return the free memory back to the kernel
    list_for_each_entry_safe(cursor, tmp, &my_linked_list, list) {
        list_del(&cursor->list);
        kfree(cursor);
    }
}

module_init(linked_list_init);
module_exit(linked_list_exit);
