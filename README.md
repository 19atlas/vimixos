# vimixOS
i386 mimarili minimal işletim sistemi. (gerçi işletim sistemi denilebilirse)
## Derlemek için,
### küçük not: Fedora, Gentoo, Debian tabanlı ve Arch tabanlı sistemlerde denenmiştir.
- `make setup` komutuyla derleyici kurulacaktır.
- kurulduğunda `make clean build` komutunu çalıştırın.

## Sıra çalıştırmada!
- öncelikle gereken paketleri kurmalısınız `qemu-full` `qemu-headless-arch-extra` paketi gibi [daha fazla bilgi için](https://github.com/nanobyte-dev/nanobyte_os#building)
- [X] ana dizinde "make run" komutunu çalıştırın.

## Vimixos hedefleri:
- [ ] stabilite (cidden)
- [ ] uygun bir shell
- [ ] çok uzun zaman sonra uygulama geliştirme (DEler yazma programları vs.)
- [ ] internet
- [ ] akıllı saatlerde çalıştırma (imkansız)

## eklenmesi gerekenler:
- [ ] FAT32 destegi
- [ ] C++ desteği
- [ ] UNIX-like
- [ ] SHELL

## Vimixos dizinleri
- `i386-bin` vimixos derlendikten sonra çıktıyı buraya atar
- `src/i386` vimixos kaynağı
- `src/i386/kernel` viniz kerneli burda bulunur
- `src/i386/bootloader` vimixos bootloader
- `tools` klasorundeki `toolchain` dosyası vimixos'a uygun binutils indirmesinde görevlidir.

this project under the GPL LICENSE [see](https://www.gnu.org/licenses/rms-why-gplv3.html)


![btw GPL bro](https://www.gnu.org/graphics/gplv3-with-text-136x68.png)