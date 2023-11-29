# vimixOS
Minimal operating system with i386 architecture. (if it can even be called an operating system)
## For compiling
### footnote: tested in: Fedora, Gentoo, Debian and Arch based distros
- `make setup` The toolchains will be compiled with the command
- when finished run `make clean build`!

## Emulation (QEMU)
- You should install required packages, such as <br>`qemu-full`<br>`qemu-headless-arch-extra` packages [for more information](https://github.com/nanobyte-dev/nanobyte_os#building)
- run `make run` for qemu

## Vimixos goals:
- [ ] stability (serius)
- [ ] shell (but minimal for some reasons)
- [ ] UI (ex. GUI)
- [ ] internet
- [ ] porting to smartwatch (impossible)

## Features to be added
- [ ] FAT32 support
- [ ] file system (from scratch)
- [ ] C++ and compiler support
- [ ] UNIX-like
- [ ] SHELL

## Vimixos file locations
- `i386-bin` vimixos after compiled files
- `src/kernel` viniz kernel
- `src/bootloader` vimixos bootloader
- `tools/toolchain` file for vimixos'a suitable binutils and cross-compiler.

this project under the GPL LICENSE [see](https://www.gnu.org/licenses/rms-why-gplv3.html)


![USE GPL bro](https://www.gnu.org/graphics/gplv3-with-text-136x68.png)