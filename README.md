# vimixos
### The 32 bit os || 32 bit sistemler için
## Derlemek için toolchain klasörüne girin,
### küçük not: Fedora, Debian tabanlı veya arch tabanlı sistemlerde denenmiştir.
- ardından toolchain dosyasını çalıştırın ilk olarak gereken dosyaları indirilir, bu dosyalar olmazsa **DERLEYEMEZSİNİZ!**
- dosyalar indiğinde ana klasorumuze gelip "derle.sh" dosyasını çalıştırın.
- eğer hata çıkmadıysa,
- [X] artık vimixOS'u **derlediniz**!!!
## Sıra çalıştırmada!
- öncelikle gereken paketleri kurmalısınız `qemu` paketi gibi [daha fazla bilgi için](https://github.com/nanobyte-dev/nanobyte_os#building)
- [X] ana dizindeki "basla.sh" ı çalıştırın.

## Vimixos hedefleri:
- [ ] stabilite
- [ ] uygun bir shell
- [ ] çok uzun zaman sonra uygulama geliştirme (DEler yazma programları vs.)
- [ ] internet
- [ ] saatlerde çalıştırma (imkansız)

## Vimixos dizinleri
- `i386-bin` vimixos derlendikten sonra çıktıyı buraya atar
- `src/i386` vimixos kaynağı
- `src/i386/kernel` viniz kerneli burda bulunur
- `src/i386/bootloader` vimixos bootloader
- `toolchain` klasorundeki `toolchain` dosyası vimixosa uygun binutilsi indirir
