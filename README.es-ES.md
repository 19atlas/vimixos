# vimixOS
Sistema operativo minimal de arquitectura i386. (si es que se le puede llamar sistema operativo)
<br>[for english version](https://github.com/19atlas/vimixos/blob/main/README_EN.md)
## Para compilar,
### nota corta: Probado en sistemas basados en Fedora, Gentoo, Debian y Arch.
- Se instalará el compilador con el comando `make setup`.
- Una vez instalado, ejecute el comando `make clean build`.

## ¡Ahora a ejecutarlo!
- Primero debe instalar los paquetes necesarios <br>`nasm`<br>`qemu-full`<br>`qemu-headless-arch-extra`<br> [para más información](https://github.com/nanobyte-dev/nanobyte_os#building)
- Abra qemu con el comando `make run`.

## Objetivos de Vimixos:
- [ ] estabilidad (realmente difícil)
- [ ] un shell adecuado
- [ ] desarrollo de aplicaciones después de mucho tiempo (entornos de escritorio, programas de escritura, etc.)
- [ ] internet
- [ ] portabilidad a relojes inteligentes (imposible)

## Cosas que deben agregarse:
- [ ] soporte FAT32
- [ ] soporte C++
- [ ] UNIX-like
- [ ] SHELL

## Directorios de Vimixos
- `i386-bin` coloca la salida aquí después de compilar vimixos
- `src` fuente de vimixos
- `src/kernel` aquí se encuentra el núcleo de viniz
- `src/bootloader` bootloader de vimixos
- `tools/toolchain` el archivo ejecutable descarga binutils y el compilador adecuado para vimixos.

ESTE PROYECTO ESTÁ LICENCIADO BAJO LA LICENCIA GPL [para más información](https://www.gnu.org/licenses/rms-why-gplv3.html)


![GPL kullan](https://www.gnu.org/graphics/gplv3-with-text-136x68.png)
