CC=riscv64-unknown-elf-gcc
AS=riscv64-unknown-elf-as
LD=riscv64-unknown-elf-ld

TARGET=build/a.out
CFLAG= -g -c -std=c99
VIRTLD=-T kernel/my-virt.ld

all: build/boot.o build/mtrap.o build/strap.o build/main.o build/ns16550a.o \
	build/print.o build/string.o
	$(LD) $(VIRTLD) $^ -o $(TARGET)

build/%.o: kernel/%.s
	$(AS) -g $^ -o $@

build/%.o: kernel/%.c
	$(CC) $(CFLAG) $^ -o $@

qemudebug: $(TARGET)
	qemu-system-riscv64 -machine virt -m 128M -nographic -gdb tcp::1235 \
 	-kernel build/a.out  \
 	-bios none -S

qemu: $(TARGET)
	qemu-system-riscv64 -machine virt -m 128M -nographic \
 	-kernel build/a.out  \
    -bios none

clean:
	rm build/*