# Virtual Memory in OS #

Sources:
- <https://www.enterprisestorageforum.com/hardware/virtual-memory/>

- <https://www.youtube.com/watch?v=pJ6qrCB8pDw>

Contents:
- [Virtual Memory in OS](#virtual-memory-in-os)
  - [What is a virtual memory?](#what-is-a-virtual-memory)
  - [Why do we need a virtual memory?](#why-do-we-need-a-virtual-memory)
  - [How does VM works?](#how-does-vm-works)
    - [VM comes at a cost](#vm-comes-at-a-cost)
      - [Thrashing](#thrashing)
  - [Managing VMs](#managing-vms)
    - [VM Paging](#vm-paging)
      - [The Paging process](#the-paging-process)
      - [Paging Fault Issues](#paging-fault-issues)
    - [VM Segmentation](#vm-segmentation)
      - [The Segmentation Process](#the-segmentation-process)
      - [Fragmantation Issues](#fragmantation-issues)

<br/>

This is a tutorial to explain the concept of virtual memory in modern operating systems.

Unless you are programming an embedded systems, your C programs are protected by the OS. Your programs are always guaranteed to have their own **virtual** memory space. We need to stress on the word "virtual" here. It means you are bounded by the actual physical memory available, but it also means, you are not entitled to any.

## What is a virtual memory? ##

Virtual memory is an area of a computer system’s secondary memory storage space (such as a hard disk or solid state drive) which acts as if it were a part of the system’s RAM or primary memory.

Normally, the data and instructions of any running app is stored in RAM, where they can be accessed quickly by the CPU. But when we run large applications (or multiple applications at once), the system's RAM becomes full.

To get around this problem, some data stored in RAM that is not actively being used can be temporarily moved to virtual memory (which is physically located on a hard drive or other storage device). This frees up space in RAM, which can then be used to accommodate data which the system needs to access imminently.

By swapping data between RAM and virtual memory when it is not needed and back  from virtual memory to RAM when it is needed, a system can continue to work smoothly with far less physical RAM than it would otherwise require.

The area in the hard drive where virtual memory is stored is called **Swap area**, some operating systems like Ubuntu gives you the freedom to set your own swap area size, however, it is recommended to keep 1.5 the size of the actual RAM and don't set it to a very large amount, for reasons that will be discussed later in this tutorial. See [Thrashing](#thrashing)

<br/>

## Why do we need a virtual memory? ##

RAM is more expensive that storage media (Like SSDs and HDDs). For that reason it is much less costly to use a combination of physical RAM and virtual memory than to equip a computer system with more RAM.

Another key driver for the use of virtual memory is that all computer systems have a limit (dictated by hardware and software) on the amount of physical RAM that can be installed. Using virtual memory allows the system to continue to operate beyond those physical RAM limits.

<br/>

## How does VM works? ##

> From now on, we are going to refer to virtual memory as **VM**.

When an application (including the operating system) is running, it stores the location of program threads and other data at a virtual address, while the data is actually stored at a physical address in RAM. If later that RAM space is needed more urgently by another process, then the data may be swapped out of RAM and into virtual memory.

The memory manager of a computer keep track of the mapping between virtual memory address and the actual physical memory. The memory manager maintains a table that records this mapping.

### VM comes at a cost ###

As we said earlier, the CPU can only process data stored in RAM and not in hard drive, and it takes a non-neglible amount of time to swap data needed intro RAM. Consequently, it follows that using VM involves a performance hit!

In other words, a system with 4 GB RAM will generally offer higher performance than a system with 2 GB RAM and 2 GB virtual memory because of the performance hit caused by swapping, and for that reason it is said that virtual memory is slower than RAM.

#### Thrashing ####

One potential problem with virtual memory is that if the amount of RAM present is too small compared to the amount of virtual memory then a system can end up spending a large proportion of its CPU resources swapping data back and forth. Meanwhile, performance of useful work grinds to a near halt – a process known as thrashing.

To prevent thrashing it is usually necessary to reduce the number of applications being run simultaneously, or simply to increase the amount of RAM in the system.

To minimize the performance hit caused by swapping between physical and virtual memory, it is best use the fastest storage device connected to the system to host the virtual memory, and to locate the virtual memory storage area on its own partition.

![Virtual memory can act in concert with a computer’s main memory to enable faster, more fluid operations.](https://www.enterprisestorageforum.com/wp-content/uploads/2021/02/virtual-memory_6019c62e91446.png "Virtual memory can act in concert with a computer’s main memory to enable faster, more fluid operations.")

> Virtual memory can act in concert with a computer’s main memory to enable faster, more fluid operations.

<br/>

## Managing VMs ##

Virtual memory can be managed in a number of different ways by a system’s operating system, and the two most common approaches are **paging** and **segmentation**.

### VM Paging ###

In a system which uses paging, RAM is divided into a number of blocks – usually `4k` in size – called pages.

Processes are then allocated just enough pages to meet their memory requirements. That means that there will always be a small amount of memory wasted, except in the unusual case where a process requires exactly  a whole number of pages.

During the normal course of operations, pages (i.e. memory blocks of 4K in size) are swapped between RAM and a page file, which represents the virtual memory.

Before we jump into further details. Let's summarize the terms we have learned so far:

- **Page**: is a fixed size of contigious memory block of virtual memory residing on disk.

- **Frame**: is a fixed size of contigious memory block located in RAM. The size of a RAM frame is equivalent to the size of VM page.

- **Physical memory**: The computer’s random access memory (RAM), typically contained in DIMM cards attached to the computer’s motherboard.

- **Virtual memory**: Virtual memory is a portion of an HDD or SSD that is reserved to emulate RAM. The MMU serves up virtual memory from disk to the CPU to reduce the workload on physical memory.

- **Virtual address**: is an address generated by the CPU for each active process. The MMU (Memory Management Unit) maps the virtual address to a physical location in RAM and passes the address to the bus. A virtual address space is the range of virtual addresses under CPU control.

- **Physical address**: The physical address is a location in RAM. The physical address space is the set of all physical addresses corresponding to the CPU’s virtual addresses. A physical address space is the range of physical addresses under MMU control.

    ![By assigning an address to a piece of data using a “page table” between the CPU and the computer’s physical memory, a computer’s MMU enables the system to retrieve that data whenever needed.](https://www.enterprisestorageforum.com/wp-content/uploads/2021/02/paging-and-segmentation_6019c4f207ec5.png "By assigning an address to a piece of data using a “page table” between the CPU and the computer’s physical memory, a computer’s MMU enables the system to retrieve that data whenever needed.")

#### The Paging process ####

A page table stores the definition of each page. When an active process requests data, the MMU retrieves corresponding pages into frames located in physical memory for faster processing. The process is called paging.

The MMU uses page tables to translate virtual addresses to physical ones. Each table entry indicates where a page is located: in RAM or on disk as virtual memory. Tables may have a single or multi-level page table such as different tables for applications and segments.

However, constant table lookups can slow down the MMU. A memory cache called the Translation Lookaside Buffer (TLB) stores recent translations of virtual to physical addresses for rapid retrieval. Many systems have multiple TLBs, which may reside at different locations, including between the CPU and RAM, or between multiple page table levels.

Different frame sizes are available for data sets with larger or smaller pages and matching-sized frames. 4KB to 2MB are common sizes, and GB-sized frames are available in high-performance servers.

An issue called hidden fragmentation used to be a problem in older Windows deployments (95, 98, and Me). The problem was internal (or hidden) fragmentation. Unlike the serious external fragmentation of segmenting, internal fragmentation occurred if every frame is not the exact size of the page size. However, this is not an issue in modern Windows OS.

#### Paging Fault Issues ####

A **page fault** is an interruption that occurs when a software program attempts to access a memory block not currently stored in the system's RAM. This exception tells the operating system to find the block in virtual memory so it can be sent from a device's storage (SSD or HD) to RAM.

While most page faults are normal background processes in Windows, macOS, and Ubuntu, some are invalid and can cause issues. **An invalid page fault (IPF)** is when a program tries to access a memory address that doesn't exist. If the program cannot find a new address, the operating system may terminate that program, resulting in a crash.

Invalid page faults can occur in any operating system that utilizes virtual memory, including Windows, macOS, and Ubuntu. IPFs are usually caused by software bugs, but can also occur at the hardware level due to changes like overclocking a computer's CPU.

### VM Segmentation ###

#### The Segmentation Process ####

The process known as segmentation is a virtual process that creates address spaces of various sizes in a computer system, called segments. Each segment is a different virtual address space that directly corresponds to process objects.

When a process executes, segmentation assigns related data into segments for faster processing. The segmentation function maintains a segment table that includes physical addresses of the segment, size, and other data.

![Segmentation speeds up a computer’s information retrieval by assigning related data into a “segment table” between the CPU and the physical memory.](https://www.enterprisestorageforum.com/wp-content/uploads/2021/02/paging-and-segmentation_6019c4f2d369c.png "Segmentation speeds up a computer’s information retrieval by assigning related data into a “segment table” between the CPU and the physical memory.")

> Segmentation speeds up a computer’s information retrieval by assigning related data into a “segment table” between the CPU and the physical memory.

Each segment stores the processes primary function, data structures, and utilities. The CPU keeps a segment map table for every process and memory blocks, along with segment identification and memory locations.

The CPU generates virtual addresses for running processes. Segmentation translates the CPU-generated virtual addresses into physical addresses that refer to a unique physical memory location. The translation is not strictly one-to-one: different virtual addresses can map to the same physical address.

#### Fragmantation Issues ####

External fragmentation occurs when unusable memory is located outside of allocated memory blocks. The issue is that the system may have enough memory to satisfy process request, but the available memory is not in a contiguous location. In time, the fragmentation worsens and significantly slows the segmentation process.
