CC=riscv64-unknown-elf-gcc
TARGET=build/a.out
CFLAG= -g -ffreestanding -O0 -Wl,--gc-sections -nostartfiles -nostdlib -nodefaultlibs
VIRTLD=-Wl,-T,kernel/riscv64-virt.ld

all: kernel/boot.s kernel/ns16550a.c kernel/main.c kernel/trap.s 
	$(CC) $(CFLAG) $(VIRTLD) $^ -o $(TARGET)

qemudebug: $(TARGET)
	cd ~ && \
	qemu-system-riscv64 -machine virt -m 128M -nographic -gdb tcp::1234 \
 	-kernel riscv-from-scratch/build/a.out  \
 	-drive file=busybear-linux/busybear.bin,format=raw,id=hd0  \
 	-device virtio-blk-device,drive=hd0,bus=virtio-mmio-bus.0 -bios none -S

qemu: $(TARGET)
	cd && \
	qemu-system-riscv64 -machine virt -m 128M -nographic \
 	-kernel riscv-from-scratch/build/a.out  \
 	-drive file=busybear-linux/busybear.bin,format=raw,id=hd0  \
 	-device virtio-blk-device,drive=hd0,bus=virtio-mmio-bus.0 -bios none
