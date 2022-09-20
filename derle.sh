export PATH=$PATH:/usr/local/i386elfgcc/bin

DIR="$PWD/i386-bin"
if [ -d "$DIR" ]; then
  echo "${DIR} Dizinine derleniyor..."
  nasm "src/i386/bootloader/stage1/stage1.asm" -f bin -o "i386-bin/stage1.bin"
  nasm "src/i386/bootloader/stage2/stage2.asm" -f elf -o "i386-bin/stage2.o"
  nasm "src/i386/kernel/kernel.asm" -f elf -o "i386-bin/kernel_asm.o"
  nasm "i386-app/main.asm" -f elf -o "i386-bin/main_asm.o"

  ./toolchain/i386-elf/bin/i386-elf-gcc -ffreestanding -m32 -g -c -Wno-write-strings "src/i386/bootloader/stage2/bootloader.cpp" -o "i386-bin/bootloader.o"
  ./toolchain/i386-elf/bin/i386-elf-gcc -ffreestanding -m32 -g -c -Wno-write-strings "src/i386/kernel/kernel.cpp" -o "i386-bin/kernel_c.o"
  ./toolchain/i386-elf/bin/i386-elf-gcc -ffreestanding -m32 -g -c -Wno-write-strings "i386-app/main.cpp" -o "i386-bin/main_c.o"

  ./toolchain/i386-elf/bin/i386-elf-ld -o "i386-bin/bootloader.bin" -T i386-bootloader.ld "i386-bin/stage2.o" "i386-bin/bootloader.o" --oformat binary
  ./toolchain/i386-elf/bin/i386-elf-ld -o "i386-bin/kernel.bin" -T i386-kernel.ld "i386-bin/kernel_asm.o" "i386-bin/kernel_c.o" --oformat binary
  ./toolchain/i386-elf/bin/i386-elf-ld -o "i386-bin/main.bin" -T i386-app.ld "i386-bin/main_asm.o" "i386-bin/main_c.o" --oformat binary
  cat "i386-bin/stage1.bin" "i386-bin/bootloader.bin" > "i386-bin/boot.bin"

  dd if=/dev/zero of=i386-bin/disk.bin bs=512 count=2880
  mkfs.fat -F 12 -n "DISK" i386-bin/disk.bin
  dd if=i386-bin/boot.bin of=i386-bin/disk.bin conv=notrunc
  mcopy -i i386-bin/disk.bin i386-bin/kernel.bin "::kernel.bin"
  mcopy -i i386-bin/disk.bin i386-bin/main.bin "::main.bin"
  echo "derlenme basarili"
else
  echo "HATA: ${DIR} yok"
  exit 1
fi
