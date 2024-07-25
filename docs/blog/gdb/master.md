# gdb 的进阶玩法

## 变量

- gdb 内部
- 可执行程序

## 寄存器

查看所有寄存器:

```gdb
info registers
```

---

打印寄存器的值:

```gdb
p $rsp
```

## 栈

查看调用栈:

- `bt` / `backtrace`

---

查看栈的内容:

```gdb
x /32x $rsp
```

## 虚伪のUI

gdb 有一个 ui 界面, {--也许可以让你感受到熟悉--}

- 命令
  - `tui enable` - 开启
  - `tui disable` - 关闭
- 快捷键
  - `ctrl-x` + `a` - 打开 / 关闭 (toggle)

当然还有另一种方式 -> `tui layout` 可以简写成 -> `layout`

- `layout`
   - `src` - 源码
   - `asm` - 汇编
   - `regs` - 寄存器 与 `src` / `asm`
   - `next` - [next](#np) layout
   - `prev` - [prev](#np) layout

进入之后你会发现, 你的 **方向键** 只能控制 **聚焦的窗口**, 我想使用上一条命令不就要再打一遍? QwQ

将窗口聚焦过去不久好了吗, 不愧是我 :)

- `ctrl-x` + `o` - 切换聚焦窗口

但是, 有更加好的方法

- `ctrl-p` - 上一条指令 - prev
- `ctrl-n` - 下一条指令 - next
- `ctrl-b` - 向行首移动 - backwards
- `ctrl-f` - 向行位移动 - forwards

### next / prev

<span id="np"></span>

**排列组合** 的知识绕一圈, 你就会知道有多少种布局...

### 注意事项

* 刷新窗口是非常必要的
  - 在 tui 下非常容易出现输出的界面会覆盖到命令行的情况, 刷新可以解决这个问题
    - `ctrl-l`
* Registers Values Unavailable
  - 下一步即可

## 参考

- [linux 命令行快捷键](https://www.cnblogs.com/coder-gui/p/6070657.html)

