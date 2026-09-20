# linux 内核无 initrd 从 minixfs 启动

主要探索 linux 在没有 initrd 时候的启动机制, 也就是直接从磁盘启动

这里使用 **minix v3 fs** 来作为 `rootfs` 的文件系统, 而不是其他常见的比如 **ext4**

## 前置

首先安装软件包, 我用 nixos 就是这些包, 其他 linux 可以安装对应的包:

```shell
nix-shell -p glibc.static ncurses flex bison bc elfutils pkg-config openssl perl
```

其他还有的包比较常见, 这里不赘述

## 配置

需要自己编译 kernel **来支持 minixfs**, 对于常见的 文件系统, 你当然可以偷个懒, 可以网络上下载, 或者直接使用本系统的 kernel ۹(ÒہÓ)۶

吃个默认配置先 (σ´-ω-`)σ

```shell
make ARCH=x86_64 defconfig
```

依旧是 tui 配置!

```shell
make menuconfig
```

在这个路径下把 minixfs 给启用:

```
 Symbol: MINIX_FS [=y]
   Type  : tristate
   Defined at fs/minix/Kconfig:2
     Prompt: Minix file system support
     Depends on: MISC_FILESYSTEMS [=y] && BLOCK [=y]
     Location:
       -> File systems
         -> Miscellaneous filesystems (MISC_FILESYSTEMS [=y])
   (1)     -> Minix file system support (MINIX_FS [=y])
   Selects: BUFFER_HEAD [=y]
```

接着直接编译

```shell
make -j$(nproc)
```

它最后会告知 kernel 的路径

`x86_64` 的 `bzImage` 位于 `arch/x86_64/boot/bzImage -> ../../x86/boot/bzImage`

## init

> 不用 正经的 init 也可以 (；￣ー￣A

init 也可以是一个普通的 `hello world` (我就不写了)

这里为了不拷贝动态链接库 就直接静态编译了

```shell
gcc init.c -o init -static
```

## 镜像

给个大的, 64M 磁盘:

```shell
dd if=/dev/zero of=linux.img bs=4M count=16
```

分个区先:

```shell
echo ",,81" | sfdisk linux.img
```

??? tip sfdisk 用法
    sfdisk 作为 fdisk 的姊妹工具, 它提供了一个程序友好的方式来操作磁盘, fdisk 是给人类用的
    sfdisk 这里 从 `stdin` 读取操作, `<start>,<size>,<type>,<bootable>` 按照这样的规则来操作
    如果保持 **空** 的话, 就表示默认, `81` 是 `Minix / Old Linux` 文件系统类型的 hex

losetup 将这个文件作为一个设备:

```shell
$ sudo losetup -f linux.img --show --partscan
/dev/loop0
```

??? tip losetup 用法
    `-f` 表示寻找一个可用的 loop 文件, 看看 `/dev` 就可能有很多 `loopX` 文件, 这一些可能是已经被吃上的
    `--show` 告诉你这个文件对应的 loop dev
    `--partscan` 顾名思义, 扫描分区. 如果不加, 可能就看不到分区设备像 `loopXpY`
    `-d` / `--detach` 就是取消这个 loop dev

挂载, 拷贝文件:

```shell
sudo mount /dev/loop0p1 /mnt
sudo mkdir -p /sbin
sudo cp ./init /mnt/sbin
sudo umount /mnt
sudo losetup -d /dev/loop0
```

## 启动

使用 QEMU `-kernel` 可以去除掉 **bootloader**, 所以作为两个章节讨论

### `-kernel`

我是用 **grub2 (2.14)**

```shell
qemu-system-x86_64 -kernel arch/x86/boot/bzImage \
  -append "root=/dev/sda1" -hda linux.img
```

### `bootloader`

```shell
sudo grub-install --boot-directory=/mnt/boot --target=i386-pc /dev/loop0
```

```shell
cat << EOF | sudo tee /mnt/boot/grub/grub.cfg     
menuentry "Linux" {
    insmod minix
    insmod minix3
    linux /bzImage root=/dev/sda1
}
EOF
```

## 参考

- <https://www.gnu.org/software/grub/manual/grub/grub.html>
