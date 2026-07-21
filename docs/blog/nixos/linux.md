# "保守派" 编译 linux kernel

安装好 nixos 之后当然需要安装环境啦, 于是我试了一下我的 [textos](https://github.com/ljQAQ233/textos-dev) 项目.

但是死活都通过不了. 于是我想先试一下 linux, 看看能不能过编译, 于是就有了这篇文章.

---

之所以是 "保守派", 是因为 nixos 好像原本就提供了 nix 的方式 (有吗?) 来编译 linux kernel.

但是我这是为了编译我的 textos 才实验的, 所以直接手动拉取源码, 然后直接在 源码目录 里面手动 make.

由于这里只简单测试环境, 所以只讲到 make 跑通为止.

## round 1 - gcc 15 问题

我用的 kernel 源码 是 `linux-6.1`. 当前 (2026.02.19) nixpkgs.gcc 使用的是 **gcc 15.2.0**

这个版本貌似直接使用 c23, 导致部分源码出现 warning / error. 可以手动切换会 **nixpkgs.gcc14**

也可以调 `-std=c11` / ...

## round 2 - gelf.h 在哪?

之前 linux kernel 使用 libelf 即可, 现在需要 elfutils.

所以会出现有的函数是旧的签名, 没有实现.

那么切换之后就可以没事了... 吧?

```txt
<stdin>:1:10: fatal error: libelf.h: No such file or directory
compilation terminated.
gcc   -o /mnt/linux-6.1/tools/objtool/fixdep /mnt/linux-6.1/tools/objtool/fixdep-in.o
rm -f /mnt/linux-6.1/tools/objtool/libsubcmd.a && ar rcs /mnt/linux-6.1/tools/objtool/libsubcmd.a /mnt/linux-6.1/tools/objtool/libsubcmd-in.o
In file included from /mnt/linux-6.1/tools/objtool/include/objtool/objtool.h:13,
                 from /mnt/linux-6.1/tools/objtool/include/objtool/arch.h:11,
                 from /mnt/linux-6.1/tools/objtool/include/objtool/check.h:11,
                 from /mnt/linux-6.1/tools/objtool/include/objtool/special.h:10,
                 from arch/x86/special.c:4:
/mnt/linux-6.1/tools/objtool/include/objtool/elf.h:10:10: fatal error: gelf.h: No such file or directory
   10 | #include <gelf.h>
      |          ^~~~~~~~
```

所以先:

```diff
export PKG_CONFIG_PATH="${pkgs.elfutils.dev}/lib/pkgconfig"
```

## round 3 - FHS 问题

!!! DROP

普通的 distro 使用 FHS, 但是 nixos...

如果 `ls /lib64` 就可以看到十分的简单, 只有一个 `stub-ld`

一般的软件安装会将自己的 头文件 安装到 `/usr/include`, 但是 nixos 不会.

所以 "重建" FHS 也是解决 **round 2** 的一种方法.

利用 `pkgs.buildFHSEnv` 与 `extraOutputsToInstall` 就可以解决了.
