# Memory Management Table of Contents
1. [Overview of Memory Types](#overview-of-memory-types)
	1. [Memory Addresses and Hexadecimal Numbers](#memory-addresses-and-hexadecimal-numbers)
	2. [Using the GDB Debugger to Analyze Memory](#Using-the-GDB-Debugger-to-Analyze-Memory)
	3. [Types of Computer Memory](#Types-of-Computer-Memory)
	4. [Cache Memory](#Cache-Memory)
	5. [Virtual Memory](#Virtual-Memory)
2. [Variables and Memory](#Variables-and-Memory)
	1. [The Process Memory Model](#The-Process-Memory-Model)
	2. [Memory Allocation in C++](#Memory-Allocation-in-C++)
	3. [Automatic Memory Allocation The Stack](#Automatic-Memory-Allocation-The-Stack)
	4. [Call By Value vs Call By Reference](#Call-By-Value-vs-Call-By-Reference)
3. [Dynamic Memory Allocation The Heap](#Dynamic-Memory-Allocation-The-Heap)
	1. [Heap Memory](#Heap-Memory)
	2. [Using malloc and free](#Using-malloc-and-free)
	3. [Using new and delete](#Using-new-and-delete)
	4. [Typical Memory Management Problems](#Typical-Memory-Management-Problems)
4. [Resource Copying Policies](#Resource-Copying-Policies)
	1. [Copy Semantics](#Copy-Semantics)
	2. [Lvalues and rvalues](#Lvalues-and-rvalues)
	3. [Move Semantics](#Move-Semantics)
5. [Smart Pointers](#Smart-Pointers)
	1. [Resource Acquisition Is Initialization RAII](#Resource-Acquisition-Is-Initialization-RAII)
	2. [Smart pointers](#Smart-pointers)
	3. [Transferring ownership](#Transferring-ownership)
6. [Project Memory Management Chatbot](#Project-Memory-Management-Chatbot)

# Overview of Memory Types
## Memory Addresses and Hexadecimal Numbers

Inside each computer, all numbers, characters, commands and every imaginable type of information are represented in binary form. Over the years, many coding schemes and techniques were invented to manipulate these 0s and 1s effectively. One of the most widely used schemes is called ASCII (_American Standard Code for Information Interchange_), which lists the binary code for a set of 127 characters. The idea was to represent each letter with a sequence of binary numbers so that storing texts on in computer memory and on hard (or floppy) disks would be possible.

![](images/ascii-table-black.png)

There are several reasons why it is preferable to use hex numbers instead of binary numbers (which computers store at the lowest level), three of which are given below:

1. **Readability**: It is significantly easier for a human to understand hex numbers as they resemble the decimal numbers we are used to. It is simply not intuitive to look at binary numbers and decide how big they are and how they relate to another binary number.
    
2. **Information density**: A hex number with two digits can express any number from 0 to 255 (because 16^2 is 256). To do the same in the binary system, we would require 8 digits. This difference is even more pronounced as numbers get larger and thus harder to deal with.
    
3. **Conversion into bytes**: Bytes are units of information consisting of 8 bits. Almost all computers are byte-addressed, meaning all memory is referenced by byte, instead of by bit. Therefore, using a counting system that can easily convert into bytes is an important requirement. We will shortly see why grouping bits into a byte plays a central role in understanding how computer memory works.

## Using the GDB Debugger to Analyze Memory

See [debugger_analyze_memory.cpp](debugger_analyze_memory.cpp) for an example of how to debug. To build with debugging symbols
```
g++ -g debugger_analyze_memory.cpp
```

To start gdb debugger:
```
gdb a.out
```
When gdb displays the line `Type <RET> for more, q to quit, c to continue without paging`, be sure to press the RETURN key to continue.

See [GDB Cheat Sheet](gdb_cheat_sheet.pdf) for gdb commands.

For this example, to set a breakpoint at line 5, run the program, step to the next line, and display variable value and address of variable, do the following:
```
break 5
run
step
p str1
p &str1
```

Now to print what's at the memory addresses:
```
(gdb) p str1
$3 = "UDACITY"
(gdb) p &str1
$4 = (char (*)[8]) 0x7fffffffdc60
(gdb) x/7tb 0x7fffffffdc60
0x7fffffffdc60: 01010101        01000100        01000001        01000011        01001001        01010100        01011001
(gdb) x/7xb 0x7fffffffdc60
0x7fffffffdc60: 0x55    0x44    0x41    0x43    0x49    0x54    0x59
(gdb) x/7cb 0x7fffffffdc60
0x7fffffffdc60: 85 'U'  68 'D'  65 'A'  67 'C'  73 'I'  84 'T'  89 'Y'
(gdb) x/7db 0x7fffffffdc60
0x7fffffffdc60: 85      68      65      67      73      84      89
```
The 7 says to print 7 units, the t stands for binary, the x stands for hex, the c stands for char (read as int, but use ascii to print char), the d is just as an int. And the b in the 3rd character stands for bytes. See GDB Cheat Sheet (linked above) for more options.

There is also an [online gdb application](https://www.onlinegdb.com) you can use to debug code.

## Types of Computer Memory

Below you will find a small list of some common memory types that you will surely have heard of:
- RAM / ROM
- Cache (L1, L2)
- Registers
- Virtual Memory
- Hard Disks, USB drives

Regrettably though, low latency and large memory are not compatible with each other (at least not at a reasonable price). In practice, the decision for low latency usually results in a reduction of the available storage capacity (and vice versa). This is the reason why a computer has multiple memory types that are arranged hierarchically. The following pyramid illustrates the principle, fast and low storage at top, and slow and more storage at bottom:
![](images/pyramid-memory.png)

Stuff that needs accessed often or soon should be closer to the top of the pyramid while stuff that isn't accessed often should be near the bottom.

## Cache Memory

Cache memory is much faster but also significantly smaller than standard RAM. It holds the data that will (or might) be used by the CPU more often. In the memory hierarchy we have seen in the last section, the cache plays an intermediary role between fast CPU and slow RAM and hard disk. The figure below gives a rough overview of a typical system architecture:
![](images/c14-fig1.png)
The central CPU chip is connected to the outside world by a number of buses. There is a cache bus, which leads to a block denoted as L2 cache, and there is a system bus as well as a memory bus that leads to the computer main memory. The latter holds the comparatively large RAM while the L2 cache as well as the L1 cache are very small with the latter also being a part of the CPU itself.

![](images/c14-fig2.png)
1. **Level 1 cache** is the fastest and smallest memory type in the cache hierarchy. In most systems, the L1 cache is not very large. Mostly it is in the range of 16 to 64 kBytes, where the memory areas for instructions and data are separated from each other (L1i and L1d, where "i" stands for "instruction" and "d" stands for "data". Also see "[Harvard architecture](https://en.wikipedia.org/wiki/Harvard_architecture)" for further reference). The importance of the L1 cache grows with increasing speed of the CPU. In the L1 cache, the most frequently required instructions and data are buffered so that as few accesses as possible to the slow main memory are required. This cache avoids delays in data transmission and helps to make optimum use of the CPU's capacity.
    
2. **Level 2 cache** is located close to the CPU and has a direct connection to it. The information exchange between L2 cache and CPU is managed by the L2 controller on the computer main board. The size of the L2 cache is usually at or below 2 megabytes. On modern multi-core processors, the L2 cache is often located within the CPU itself. The choice between a processor with more clock speed or a larger L2 cache can be answered as follows: With a higher clock speed, individual programs run faster, especially those with high computing requirements. As soon as several programs run simultaneously, a larger cache is advantageous. Usually normal desktop computers with a processor that has a large cache are better served than with a processor that has a high clock rate.
    
3. **Level 3 cache** is shared among all cores of a multicore processor. With the L3 cache, the [cache coherence](https://en.wikipedia.org/wiki/Cache_coherence) protocol of multicore processors can work much faster. This protocol compares the caches of all cores to maintain data consistency so that all processors have access to the same data at the same time. The L3 cache therefore has less the function of a cache, but is intended to simplify and accelerate the cache coherence protocol and the data exchange between the cores.

On Mac, information about the system cache can be obtained by executing the command `sysctl -a hw` in a terminal. On Debian Linux linux, this information can be found with `lscpu | grep cache`.

While L1 access operations are close to the speed of a photon traveling at light speed for a distance of 1 foot, the latency of L2 access is roughly one order of magnitude slower already while access to main memory is two orders of magnitude slower.

In algorithm design, programmers can exploit two principles to increase runtime performance:

1. **Temporal locality** means that address ranges that are accessed are likely to be used again in the near future. In the course of time, the same memory address is accessed relatively frequently (e.g. in a loop). This property can be used at all levels of the memory hierarchy to keep memory areas accessible as quickly as possible.
    
2. **Spatial locality** means that after an access to an address range, the next access to an address in the immediate vicinity is highly probable (e.g. in arrays). In the course of time, memory addresses that are very close to each other are accessed again multiple times. This can be exploited by moving the adjacent address areas upwards into the next hierarchy level during a memory access.
    
Let us consider the following code example:

```cpp
#include <chrono>
#include <iostream>

int main()
{
    // create array 
    const int size = 4000;
    static int x[size][size];

    auto t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            x[j][i] = i + j;
            //std::cout << &x[j][i] << ": i=" << i << ", j=" << j << std::endl;
        }
    }

    // print execution time to console
    auto t2 = std::chrono::high_resolution_clock::now(); // stop time measurement
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "Execution time: " << duration << " microseconds" << std::endl;

    return 0;
}
```

Changing the order of j and i when indexing x x[i][j] instead of x[j][i] is more cache friendly code and runs way more quickly.

## Virtual Memory

The idea of virtual memory stems back from a (not so long ago) time, when the random access memory (RAM) of most computers was severely limited. Programers needed to treat memory as a precious resource and use it most efficiently. Also, they wanted to be able to run programs even if there was not enough RAM available. At the time of writing (August 2019), the amount of RAM is no longer a large concern for most computers and programs usually have enough memory available to them. But in some cases, for example when trying to do video editing or when running multiple large programs at the same time, the RAM memory can be exhausted. In such a case, the computer can slow down drastically.

There are several other memory-related problems, that programmers need to know about:

1. **Holes in address space** : If several programs are started one after the other and then shortly afterwards some of these are terminated again, it must be ensured that the freed-up space in between the remaining programs does not remain unused. If memory becomes too fragmented, it might not be possible to allocate a large block of memory due to a large-enough free contiguous block not being available any more.
    
2. **Programs writing over each other** : If several programs are allowed to access the same memory address, they will overwrite each others' data at this location. In some cases, this might even lead to one program reading sensitive information (e.g. bank account info) that was written by another program. This problem is of particular concern when writing concurrent programs which run several threads at the same time.
    

The basic idea of virtual memory is to separate the addresses a program may use from the addresses in physical computer memory. By using a mapping function, an access to (virtual) program memory can be redirected to a real address which is guaranteed to be protected from other programs.

In the following, you will see, how virtual memory solves the problems mentioned above and you will also learn about the concepts of memory pages, frames and mapping. A sound knowledge on virtual memory will help you understand the C++ memory model, which will be introduced in the next lesson of this course.

With virtual memory, the RAM acts as a cache for the virtual memory space which resides on secondary storage devices. On Windows systems, the file `pagefile.sys` is such a virtual memory container of varying size. To speed up your system, it makes sense to adjust the system settings in a way that this file is stored on an SSD instead of a slow magnetic hard drive, thus reducing the latency. On a Mac, swap files are stored in`/private/var/vm/`.

In a nutshell, virtual memory guarantees us a fixed-size address space which is largely independent of the system configuration. Also, the OS guarantees that the virtual address spaces of different programs do not interfere with each other.

The task of mapping addresses and of providing each program with its own virtual address space is performed entirely by the operating system, so from a programmer’s perspective, we usually don’t have to bother much about memory that is being used by other processes.

Before we take a closer look at an example though, let us define two important terms which are often used in the context of caches and virtual memory:

- A **memory page** is a number of directly successive memory locations in virtual memory defined by the computer architecture and by the operating system. The computer memory is divided into memory pages of equal size. The use of memory pages enables the operating system to perform virtual memory management. The entire working memory is divided into tiles and each address in this computer architecture is interpreted by the Memory Management Unit (MMU) as a logical address and converted into a physical address.
- A **memory frame** is mostly identical to the concept of a memory page with the key difference being its location in the physical main memory instead of the virtual memory.

![](images/c15-fig3.png)

# Variables and Memory
## The Process Memory Model

As we have seen in the previous lesson, each program is assigned its own virtual memory by the operating system. This address space is arranged in a linear fashion with one block of data being stored at each address. It is also divided into several distinct areas as illustrated by the figure below:
![](images/c21-fig1.png)
1. The **stack** is a contiguous memory block with a fixed maximum size. If a program exceeds this size, it will crash. The stack is used for storing automatically allocated variables such as local variables or function parameters. If there are multiple threads in a program, then each thread has its own stack memory. New memory on the stack is allocated when the path of execution enters a scope and freed again once the scope is left. It is important to know that the stack is managed "automatically" by the compiler, which means we do not have to concern ourselves with allocation and deallocation.
2. The **heap** (also called "free store" in C++) is where data with dynamic storage lives. It is shared among multiple threads in a program, which means that memory management for the heap needs to take concurrency into account. This makes memory allocations in the heap more complicated than stack allocations. In general, managing memory on the heap is more (computationally) expensive for the operating system, which makes it slower than stack memory. Contrary to the stack, the heap is not managed automatically by the system, but by the programmer. If memory is allocated on the heap, it is the programmer’s responsibility to free it again when it is no longer needed. If the programmer manages the heap poorly or not at all, there will be trouble.
3. The **BSS** (Block Started by Symbol) segment is used in many compilers and linkers for a segment that contains global and static variables that are initialized with zero values. This memory area is suitable, for example, for arrays that are not initialized with predefined values.
4. The **Data** segment serves the same purpose as the BSS segment with the major difference being that variables in the Data segment have been initialized with a value other than zero. Memory for variables in the Data segment (and in BSS) is allocated once when a program is run and persists throughout its lifetime.

## Memory Allocation in C++

Now that we have an understanding of the available process memory, let us take a look at memory allocation in C++.

Not every variable in a program has a permanently assigned area of memory. The term **allocate** refers to the process of assigning an area of memory to a variable to store its value. A variable is **deallocated** when the system reclaims the memory from the variable, so it no longer has an area to store its value.

Generally, three basic types of memory allocation are supported:

1. **Static memory allocation** is performed for static and global variables, which are stored in the BSS and Data segment. Memory for these types of variables is allocated once when your program is run and persists throughout the life of your program.
2. **Automatic memory allocation** is performed for function parameters as well as local variables, which are stored on the stack. Memory for these types of variables is allocated when the path of execution enters a scope and freed again once the scope is left.
3. **Dynamic memory allocation** is a possibility for programs to request memory from the operating system at runtime when needed. This is the major difference between automatic and static allocation, where the size of the variable must be known at compile time. Dynamic memory allocation is not performed on the limited stack but on the heap and is thus (almost) only limited by the size of the address space.

From a programmer’s perspective, stack and heap are the most important areas of program memory. Hence, in the following lessons, let us look at these two in turn.

## Automatic Memory Allocation The Stack

As mentioned in the last section, the stack is the place in virtual memory where the local variables reside, including arguments to functions. Each time a function is called, the stack grows (from top to bottom) and each time a function returns, the stack contracts. When using multiple threads (as in concurrent programming), it is important to know that each thread has its own stack memory - which can be considered thread-safe.

In the following, a short list of key properties of the stack is listed:

1. The stack is a **contiguous block of memory**. It will not become fragmented (as opposed to the heap) and it has a fixed maximum size.
    
2. When the **maximum size of the stack** memory is exceeded, a program will crash.
    
3. Allocating and deallocating **memory is fast** on the stack. It only involves moving the stack pointer to a new position.

The following diagram shows the stack memory during a function call:
![](images/c22-fig1.png)
In the example, the variable `x` is created on the stack within the scope of main. Then, a stack frame which represents the function `Add` and its variables is pushed to the stack, moving the stack pointer further downwards. It can be seen that this includes the local variables `a` and `b`, as well as the return address, a base pointer and finally the return value `s`.

The following shows how the stack can grow and contract:
```cpp
#include <stdio.h>

void MyFunc()
{
    int k = 3; 
    printf ("3: %p \n",&k);
}

int main()
{
    int i = 1; 
    printf ("1: %p \n",&i);

    int j = 2; 
    printf ("2: %p \n",&j);

    MyFunc();

    int l = 4; 
    printf ("4: %p \n",&l);

    return 0; 
}
```

Within the main function, we see two declarations of local variables `i` and `j` followed by a call to `MyFunc`, where another local variable is allocated. After `MyFunc` returns, another local variable is allocated in `main`. The program generates the following output:

`1: 0x7ffeefbff688`  
`2: 0x7ffeefbff684`
`3: 0x7ffeefbff65c`
`4: 0x7ffeefbff680` 

Between 1 and 2, the stack address is reduced by 4 bytes, which corresponds to the allocation of memory for the int `j`.

Between 2 and 3, the address pointer is moved by 0x28. We can easily see that calling a function causes a significant amount of memory to be allocated. In addition to the local variable of `MyFunc`, the compiler needs to store additional data such as the return address.

Between 3 and 4, `MyFunc` has returned and a third local variable `k` has been allocated on the stack. The stack pointer now has moved back to a location which is 4 bytes relative to position 2. This means that after returning from `MyFunc`, the stack has contracted to the size it had before the function call.

When a thread is created, stack memory is allocated by the operating system as a contiguous block. With each new function call or local variable allocation, the stack pointer is moved until eventually it will reach the bottom of said memory block. Once it exceeds this limit (which is called "stack overflow"), the program will crash. We will try to find out the limit of your computer’s stack memory in the following exercise.

```cpp
#include <iostream>

int calls = 0;

void myFunc(int& y)
{
    calls++;
    int x = 3;
    std::cout << calls << ": stack bottom : " << &y << ", current : " << &x << std::endl;
    myFunc(y);
}

int main()
{
    int y = 10;
    myFunc(y);
    return 0;
}
```

`ulimit -s` prints the stack size `8192` for my linux machine. The program above prints:

```
171157: stack bottom : 0x7f2071c4ee14, current : 0x7f2071479234
171158: stack bottom : 0x7f2071c4ee14, current : 0x7f2071479204
171159: stack bottom : 0x7f2071c4ee14, current : 0x7f20714791d4
Segmentation fault
```

The difference between the current stack position and the stack bottom right before the segmentation fault should match the stack size for the machine indicating a stack overflow.

## Call By Value vs Call By Reference

# Dynamic Memory Allocation The Heap
## Heap Memory
## Using malloc and free
## Using new and delete
## Typical Memory Management Problems

# Resource Copying Policies
## Copy Semantics
## Lvalues and rvalues
## Move Semantics

# Smart Pointers
## Resource Acquisition Is Initialization RAII
## Smart pointers
## Transferring ownership

# Project Memory Management Chatbot
