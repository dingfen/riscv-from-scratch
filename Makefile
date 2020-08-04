CC=riscv64-unknown-elf-gcc
TARGET=build/a.out
CFLAG= -g -ffreestanding -O0 -Wl,--gc-sections -nostartfiles -nostdlib -nodefaultlibs
VIRTLD=-Wl,-T,kernel/riscv64-virt.ld

all: kernel/boot.s kernel/ns16550a.c kernel/main.c kernel/trap.s
	$(CC) $(CFLAG) $(VIRTLD) $^ -o $(TARGET)

qemudebug: $(TARGET)
	qemu-system-riscv64 -machine virt -m 128M -nographic -gdb tcp::1234 \
 	-kernel build/a.out  \
 	-bios none -S

qemu: $(TARGET)
	qemu-system-riscv64 -machine virt -m 128M -nographic \
 	-kernel build/a.out  \
    -bios none
