使用 `qemu` 加载自己的内核

```shell
 qemu-system-riscv64 -machine virt -m 128M -nographic -gdb tcp::1234
 -kernel riscv-from-scratch/build/a.out  
 -drive file=busybear-linux/busybear.bin,format=raw,id=hd0
 -device virtio-blk-device,drive=hd0,bus=virtio-mmio-bus.0 -bios none -S
```

编译语句

```shell
riscv64-unknown-elf-gcc -g -ffreestanding -O0 -Wl,--gc-sections -nostartfiles -nostdlib -nodefaultlibs -Wl,-T,riscv64-virt.ld boot.s ns16550a.c main.c trap.s -o ../build/a.out