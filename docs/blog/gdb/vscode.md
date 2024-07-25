# gdb 在 vscode

vscode 中除了可视化地调试, 还会提供一个控制台, 它可以让我们与 gdb 交互

---

首先, vscode 使用的不是一般的 gdb, 而是 `mi-interrupter`

当然平时也可以启动!

```shell
gdb --interpreter=mi
```

然后你就会发现这东西不是个人看的...

## 变量

直接输入变量名就好了

- `x` - 查看 x

可以加上 **逗号**, 表示输出格式

- `x, x` - 十六进制
- `x, X` - 依然是小写...
- `x, `

## 命令

对于一个 **普通人** 最实用的命令实际是 -> `-exec`, 也就是直接运行一个 gdb 命令...

e.g. 调试汇编时非常有用的一条命令:

```gdb
-exec x/32x $rsp
```

然而, 掌握这么多好像没什么用, 因为 vscode 不认...

### 程序控制

- `-exec-run`
- `-exec-continue` - 继续
- `-exec-finish`
- `-exec-interrupt`
- `-exec-step`
- `-exec-return` - 强制返回

