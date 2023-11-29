# vimixOS
i386 mimarili minimal işletim sistemi. (gerçi işletim sistemi denilebilirse)
<br>[for english version](https://github.com/19atlas/vimixos/blob/main/README_EN.md)
## Derlemek için,
### küçük not: Fedora, Gentoo, Debian tabanlı ve Arch tabanlı sistemlerde denenmiştir.
- `make setup` komutuyla derleyici kurulacaktır.
- kurulduğunda `make clean build` komutunu çalıştırın.

## Sıra çalıştırmada!
- öncelikle gereken paketleri kurmalısınız <br>`nasm`<br>`qemu-full`<br>`qemu-headless-arch-extra`<br> paketleri gibi [daha fazla bilgi için](https://github.com/nanobyte-dev/nanobyte_os#building)
- `make run` komutu ile qemuyu açın.

## Vimixos hedefleri:
- [ ] stabilite (cidden zor)
- [ ] uygun bir shell
- [ ] çok uzun zaman sonra uygulama geliştirme (DEler yazma programları vs.)
- [ ] internet
- [ ] akıllı saatlere portlama (imkansız)

## eklenmesi gerekenler:
- [ ] FAT32 destegi
- [ ] C++ desteği
- [ ] UNIX-like
- [ ] SHELL

## Vimixos dizinleri
- `i386-bin` vimixos derlendikten sonra çıktıyı buraya atar
- `src` vimixos kaynağı
- `src/kernel` viniz kerneli burda bulunur
- `src/bootloader` vimixos bootloader
- `tools/toolchain` çalıştırılabilir dosyası vimixos'a uygun binutils ve derleyiciyi indirir.

BU PROJE GPL LİSANSI İLE LİSANSLANMIŞTIR [daha fazla bilgi için](https://www.gnu.org/licenses/rms-why-gplv3.html)


![GPL kullan](https://www.gnu.org/graphics/gplv3-with-text-136x68.png)
