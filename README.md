virt QEMU 虚拟机的内存布局

```c
/****************************
0x02000000 --
            | clint (core local interrupt)
0x02010000-- 

0x0c000000 --
    |       |  interrupt-controller
0x10000000 --
            |  uart
0x10000100 --
    |
    |
    |
0x10001000 --
    |       |
0x10002000 --
    |       |
0x10003000 --
    |       |
0x10004000 --
    |       |   virtio,mmio
0x10005000 --
    |       |
0x10006000 --
    |       |
0x10007000 --
    |       |
0x10008000 --

0x20000000 --
    |       |
    |       |  flash
    |       |
0x24000000 --
    |
    |
    |
0x30000000 --
    |       |
    |       |  PCI
    |       |
0x40000000 --
    |
    |
    |
    |
    |
0x80000000 -----RAM
                text code
                |--- boot
                     main
                     ns16550a
                initialized data
                bss
                heap
                |
                |
                |
                |
                |
                stack
                env cli args

0x88000000 -----
****************************/
```