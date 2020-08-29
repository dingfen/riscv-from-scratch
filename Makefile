CC=riscv64-unknown-elf-gcc
AS=riscv64-unknown-elf-as
LD=riscv64-unknown-elf-ld

TARGET=build/a.out
CFLAG= -c -g -ffreestanding
VIRTLD=-T kernel/my-virt.ld

all: build/boot.o build/main.o build/mm.o build/ns16550a.o \
	build/print.o build/string.o build/mtrap.o build/strap.o
	$(LD) $(VIRTLD) $^ -o $(TARGET)

build/%.o: kernel/%.s
	$(AS) -g $^ -o $@

build/%.o: kernel/%.c
	$(CC) $(CFLAG) $^ -o $@

qemudebug: $(TARGET)
	qemu-system-riscv64 -machine virt -m 128M -nographic -gdb tcp::1234 \
 	-kernel build/a.out  \
 	-bios none -S

qemu: $(TARGET)
	qemu-system-riscv64 -machine virt -m 128M -nographic \
 	-kernel build/a.out  \
    -bios none

clean:
	rm build/*