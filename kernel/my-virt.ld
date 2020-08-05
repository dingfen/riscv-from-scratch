ENTRY(_start)
MEMORY
{
   /* qemu-system-riscv64 virt machine */
   RAM (rwx) : ORIGIN = 0x80000000, LENGTH = 128M
}

SECTIONS {
    PROVIDE(__stack_top = 0x88000000);
    PROVIDE(__uart_base_addr = 0x10000000);
    
    . = 0x80000000;
    .init : {
        * (.init);
    }
    .text : {
        * (.text);
    }

    .data : {
        __global_pointer$ = .;
        ram_sdata = .;
        * (.data);
    }
    .rodata : {
        * (.rodata);
    }
    ram_edata = .;
    data_size = ram_edata - ram_sdata;

    __bss_start = .;
    .bss : {
        * (.bss);
    }
    __bss_end = .;
}