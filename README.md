# Linux Kernel Modules (LKM) Project

Welcome to the **Linux Kernel Modules (LKM)** project repository! This project is based on assignments from the **Operating System Concepts, 10th Edition** textbook, specifically focusing on Linux kernel modules, task listing, kernel data structures, and system building.

## Project Overview

In this project, you will develop kernel modules for a Linux system to perform a variety of tasks. The assignments are organized into three main parts:

### Part I - Introduction to Linux Kernel Modules (LKM) - Chapter 2

- **Assignment: Introduction to LKM**  
  This part will help you get started with Linux Kernel Modules (LKM), covering the basics of module development and compilation.

- **Learning Resources**:  
  - Chapter 2 of *Operating System Concepts, 10th Edition*  
  - Section 2.9 on building and booting a Linux system

- **Key Topics**:
  - Understanding the structure and building blocks of LKM
  - Compiling and loading modules into the Linux kernel

---

### Part II - Linux Kernel Module for Listing Tasks - Chapter 3

- **Assignment: ps-el**  
  Develop a kernel module to list processes running on the system, similar to the `ps -el` command.

- **Assignment: ps-eLf**  
  Extend the `ps-el` module to display more detailed information, resembling `ps -eLf`.

- **Learning Resources**:  
  - Chapter 3 of *Operating System Concepts, 10th Edition*  
  - Pages 201–205 for detailed instructions

- **Key Topics**:
  - Listing tasks in the kernel using kernel data structures
  - Implementing process listing functionality in kernel space

---

### Part III - Kernel Data Structures - Chapter 3

- **Assignment: dmesg**  
  Implement a kernel module to interact with the `dmesg` command and display kernel messages.

- **Assignment: collatz**  
  Create a kernel module to compute the Collatz sequence and output the results.

- **Learning Resources**:  
  - Chapter 3 of *Operating System Concepts, 10th Edition*  
  - Pages 205–208 for detailed instructions

- **Key Topics**:
  - Understanding and utilizing kernel data structures
  - Implementing the `dmesg` functionality and algorithmic tasks in kernel space

---

## Setup and Installation

### Requirements
- A Linux virtual machine (VM) is recommended to avoid crashes or errors on the host system.
  - Use VMware Player, VirtualBox, Microsoft Hyper-V, or any similar tool.
- A basic understanding of Linux kernel module programming and C language.

### Steps to Build the Kernel Modules

1. Clone the repository:
   ```bash
   git clone <repository-url>
   cd <repository-directory>

2. Build the kernel module:

  ```bash
  make
```

3. Load the kernel module:

  ```bash
  sudo insmod <module-name>.ko
```

4. Check the output of the module (depending on the assignment):

  * Use dmesg to view kernel log messages.
  * For process listing assignments, use the appropriate ps commands.

5. Unload the kernel module:

  ```bash
  sudo rmmod <module-name>
```

## Additional Notes
* Caution: Working with the Linux kernel can cause system instability if errors occur. It is strongly recommended to complete these exercises on a virtual machine.
* Refer to the relevant chapters in the textbook for step-by-step instructions



