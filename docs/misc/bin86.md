# bin86 安装

bin86 包含 as86, ld86, nm86, objdump86, size86 可以用于编译老一点的 linux, 或者其他操作系统.

一些解析 linux 源码的书籍, 可能会介绍如何安装 as86.

## ArchLinux

```
yay -S bin86
```

---

其他的发行版我不知道, 但是可以用 [AUR](https://aur.archlinux.org/packages/bin86) 下载的 [`PKGBUILD`](https://aur.archlinux.org/cgit/aur.git/tree/PKGBUILD?h=bin86) 来编译

```bash
# Maintainer: Andreas Radke <andyrtr@archlinux.org>
# Contributor: judd <jvinet@zeroflux.org>

pkgname=bin86
pkgver=0.16.21
pkgrel=6
pkgdesc='A complete 8086 assembler and loader'
arch=('x86_64')
license=('GPL')
url='https://v3.sk/~lkundrak/dev86/'
depends=('glibc')
source=("https://sources.archlinux.org/other/packages/dev86/${pkgname}-${pkgver}.tar.gz"
        'bin86-0.16.17-x86_64-1.patch')
sha1sums=('35a1222350adce5b6d62dd56f3477d9416c59174'
          '2c967c062fbee4e40ca1bf55feec2033e132e0a9')
sha256sums=('021e37cde3a20632c4c9000993cb4aa9f58cb82b1d3c26b9aeb62d6566925738'
            'f5174f7f703bb21486196c7d9ce027ba8d501c51f6099f02c6c13ee48fc861db')

prepare() {
  cd "${pkgname}-${pkgver}"

  patch -Np1 < ../bin86-0.16.17-x86_64-1.patch
}

build() {
  cd "${pkgname}-${pkgver}"

  make \
    CFLAGS="${CFLAGS} -Wno-implicit-int -Wno-implicit-function-declaration" \
    PREFIX=/usr
}

package() {
  cd "${pkgname}-${pkgver}"

  install -d "${pkgdir}"/usr/{bin,share/man/man1}
  make PREFIX="${pkgdir}"/usr MANDIR="${pkgdir}"/usr/share/man/man1 install
}
```

这时就简单了, 按照上面的敲命令就可以了, 需要注意的是原版好像不支持 x86_64, 所以需要打[patch](https://aur.archlinux.org/cgit/aur.git/tree/bin86-0.16.17-x86_64-1.patch?h=bin86):

