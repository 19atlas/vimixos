# vimixos
i386 mimarili minimal OS
## Derlemek için tools klasörüne girin,
### küçük not: Fedora, Gentoo, Debian tabanlı veya arch tabanlı sistemlerde denenmiştir.
- ardından toolchain dosyasını çalıştırın derleyiciyi kuracaktır.
- dosyalar indiğinde ana klasorumuze gelip "make clean build" komutunu çalıştırın.

## Sıra çalıştırmada!
- öncelikle gereken paketleri kurmalısınız `qemu-full` `qemu-headless-arch-extra` paketi gibi [daha fazla bilgi için](https://github.com/nanobyte-dev/nanobyte_os#building)
- [X] ana dizinde "make run" komutunu çalıştırın.

## Vimixos hedefleri:
- [ ] stabilite
- [ ] uygun bir shell
- [ ] çok uzun zaman sonra uygulama geliştirme (DEler yazma programları vs.)
- [ ] internet
- [ ] akıllı saatlerde çalıştırma (imkansız)

## eklenmesi gerekenler:
- [ ] C++ desteği
- [ ] UNIX-like

## Vimixos dizinleri
- `i386-bin` vimixos derlendikten sonra çıktıyı buraya atar
- `src/i386` vimixos kaynağı
- `src/i386/kernel` viniz kerneli burda bulunur
- `src/i386/bootloader` vimixos bootloader
- `tools` klasorundeki `toolchain` dosyası vimixos'a uygun binutils indirir
