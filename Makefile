#elfgcc=tools/i386-elf/bin/i386-elf-gcc # installation from toolchain dir
#elfld=tools/i386-elf/bin/i386-elf-ld

elfgcc=i386-elf-gcc # installation from `yay -S i386-elf-gcc`
elfld=i386-elf-ld

BUILD_DIR=i386-bin

.PHONY: build
build: $(clean)
	export PATH=$PATH:/usr/local/i386elfgcc/bin
	mkdir -pv $(BUILD_DIR)
	@printf "\n\e[0;32m==> $(BUILD_DIR) e derleniyor..."
	@nasm "src/bootloader/stage1/stage1.asm" -f bin -o "$(BUILD_DIR)/stage1.bin"
	@nasm "src/bootloader/stage2/stage2.asm" -f elf -o "$(BUILD_DIR)/stage2.o"
	@nasm "src/kernel/kernel.asm" -f elf -o "$(BUILD_DIR)/kernel_asm.o"
	@nasm "src/kernel/modules.asm" -f elf -o "$(BUILD_DIR)/moduleAsm.o"
	$(elfgcc) -ffreestanding -m32 -g -c -Wno-write-strings "src/bootloader/stage2/bootloader.cpp" -o "$(BUILD_DIR)/bootloader.o"
	$(elfgcc) -ffreestanding -m32 -g -c -Wno-write-strings "src/kernel/kernel.cpp" -o "$(BUILD_DIR)/kernel_c.o"
	$(elfgcc) -ffreestanding -m32 -g -c -Wno-write-strings "src/kernel/modules.cpp" -o "$(BUILD_DIR)/modulesC.o"
	$(elfld) -o "$(BUILD_DIR)/bootloader.bin" -T i386-bootloader.ld "$(BUILD_DIR)/stage2.o" "$(BUILD_DIR)/bootloader.o" --oformat binary
	$(elfld) -o "$(BUILD_DIR)/kernel.bin" -T i386-kernel.ld "$(BUILD_DIR)/kernel_asm.o" "$(BUILD_DIR)/kernel_c.o" --oformat binary
	$(elfld) -o "$(BUILD_DIR)/modules.bin" -T i386-module.ld "$(BUILD_DIR)/moduleAsm.o" "$(BUILD_DIR)/modulesC.o" --oformat binary
	cat "$(BUILD_DIR)/stage1.bin" "$(BUILD_DIR)/bootloader.bin" > "$(BUILD_DIR)/boot.bin"
	dd if=/dev/zero of=$(BUILD_DIR)/disk.bin bs=512 count=2880
	mkfs.fat -v -F 12 -n "DISK" $(BUILD_DIR)/disk.bin #kernel and module outputs are on disk
	dd if=$(BUILD_DIR)/boot.bin of=$(BUILD_DIR)/disk.bin conv=notrunc
	@mcopy -v -i $(BUILD_DIR)/disk.bin $(BUILD_DIR)/kernel.bin "::kernel.bin"
	@mcopy -v -i $(BUILD_DIR)/disk.bin $(BUILD_DIR)/modules.bin "::modules.bin"

.PHONY: help
help:
	@printf "clean: derlenmişi temizler\nbuild: derler\nrun: qemu da açar\noutput: $(BUILD_DIR)"

.PHONY: clean
clean:
	rm -rvf $(BUILD_DIR)/*
.PHONY: setup
setup:
	./tools/toolchain

.PHONY: run
run:
	qemu-system-i386 -m 256M -device VGA,vgamem_mb=128 $(BUILD_DIR)/disk.bin
