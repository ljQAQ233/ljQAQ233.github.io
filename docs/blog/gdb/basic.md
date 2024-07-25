# gdb 的基本使用

一般装了 `gcc` 的 linux 都会配备 gdb, 如果没有...

## get started!

调试一个文件, 首先确保它要存在调试信息

> gcc 在生成命令之后添加 `-g`, 那么生成的文件就会附带调试信息

于是开始调试:

```shell
gdb <file>
```

- `start` - 开始执行

- `n` / `next` - 下一步
- `s` / `step` - 进入函数
- `c` / `continue` - 继续执行
- `l` / `list` - 查看源代码
- `finish` - 跳出函数

---

- `p` / `print` - 打印符号信息(变量等)

`print` 是一个重头戏, 它后面可以接各种选项

> (gdb) help x
>
> FMT is a repeat count followed by a format letter and a size letter.
>  Format letters are o(octal), x(hex), d(decimal), u(unsigned decimal),
>  t(binary), f(float), a(address), i(instruction), c(char), s(string)
>  and z(hex, zero padded on the left).

e.g.
 - `print x` - 打印 x
 - `p /x x` - 十六进制
 - `p /t x` - 二进制
 - `p /o x` - 八进制

---

- `b` / `break` - 添加断点

- `b `

---

- `display` - 在每一次操作后打印符号的值

---



