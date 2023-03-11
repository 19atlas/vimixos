elfgcc=tools/i386-elf/bin/i386-elf-gcc
elfld=tools/i386-elf/bin/i386-elf-ld
BUILD_DIR=i386-bin

.PHONY: help
help:
	@printf "clean: derlenmişi temizler\nbuild: derler\nrun: qemu da açar\n"

.PHONY: build
build: $(clean)
	export PATH=$PATH:/usr/local/i386elfgcc/bin
	mkdir -pv $(BUILD_DIR)
	@printf "\n\e[0;32m==> $(BUILD_DIR) e derleniyor..."
	@nasm "src/i386/bootloader/stage1/stage1.asm" -f bin -o "$(BUILD_DIR)/stage1.bin"
	@nasm "src/i386/bootloader/stage2/stage2.asm" -f elf -o "$(BUILD_DIR)/stage2.o"
	@nasm "src/i386/kernel/kernel.asm" -f elf -o "$(BUILD_DIR)/kernel_asm.o"
	@nasm "i386-app/main.asm" -f elf -o "$(BUILD_DIR)/main_asm.o"
	$(elfgcc) -ffreestanding -m32 -g -c -Wno-write-strings "src/i386/bootloader/stage2/bootloader.cpp" -o "$(BUILD_DIR)/bootloader.o"
	$(elfgcc) -ffreestanding -m32 -g -c -Wno-write-strings "src/i386/kernel/kernel.cpp" -o "$(BUILD_DIR)/kernel_c.o"
	$(elfgcc) -ffreestanding -m32 -g -c -Wno-write-strings "i386-app/main.cpp" -o "$(BUILD_DIR)/main_c.o"
	$(elfld) -o "$(BUILD_DIR)/bootloader.bin" -T i386-bootloader.ld "$(BUILD_DIR)/stage2.o" "$(BUILD_DIR)/bootloader.o" --oformat binary
	$(elfld) -o "$(BUILD_DIR)/kernel.bin" -T i386-kernel.ld "$(BUILD_DIR)/kernel_asm.o" "$(BUILD_DIR)/kernel_c.o" --oformat binary
	$(elfld) -o "$(BUILD_DIR)/main.bin" -T i386-app.ld "$(BUILD_DIR)/main_asm.o" "$(BUILD_DIR)/main_c.o" --oformat binary
	cat "$(BUILD_DIR)/stage1.bin" "$(BUILD_DIR)/bootloader.bin" > "$(BUILD_DIR)/boot.bin"
	dd if=/dev/zero of=$(BUILD_DIR)/disk.bin bs=512 count=2880
	mkfs.fat -v -F 12 -n "DISK" $(BUILD_DIR)/disk.bin
	dd if=$(BUILD_DIR)/boot.bin of=$(BUILD_DIR)/disk.bin conv=notrunc
	mcopy -v -i $(BUILD_DIR)/disk.bin $(BUILD_DIR)/kernel.bin "::kernel.bin"
	mcopy -v -i $(BUILD_DIR)/disk.bin $(BUILD_DIR)/main.bin "::main.bin"

.PHONY: clean
clean:
	rm -rvf $(BUILD_DIR)/*

.PHONY: run
run:
	qemu-system-i386 -m 256M -device VGA,vgamem_mb=128 $(BUILD_DIR)/disk.bin