---
title: 'VimSpector 简介及使用'
date: 2023-04-21 06:32:23
tags: 
 - 调试
 - vim
 - neovim
 - Bilibili
 - C语言
---

# VimSpector 简介及使用

- 2023/04/21 06:32:23

---

# Overview

由于电脑实在是太拉了,我用不了vscode,所以我试着使用gdb命令行调试,但并不方便,我想着转向NeoVim,这就来折腾一下,也就有了这篇文章.

# 简介

在座的各位都用过VSCode调试C语言程序吧,那对cpptools一定不陌生.

我们的上古神器Vim上也可以进行类似的可视化调试,使用VimSpector(甚至一模一样......)

如果是NeoVim,还可以选择使用 **nvim-dap** ,但它的配置较为繁琐,就不再介绍(暂时吧......)

# 安装

## 插件

使用 **vim-plug** 进行安装:

<!--- 这里原来用的是 vim, 但是 mkdocs 无法识别 --->

```vim

call plug#begin("~/.config/nvim/plugged")

 Plug 'puremourning/vimspector'

call plug#end()

```

其他插件管理器执行类似操作.

```vim

:PlugInstall

```

## 调试适配器

切换到我们安装的vimspector插件的目录,我这里是`plugged/vimspector`

可以看到简单的帮助,及一些语言

```sh
./install_gadget.py --help
```

我们安装C语言的调试适配器,C++的也可.

```bash
./install_gadget.py --enable-c --verbose
```

`--verbose`输出安装详细步骤.

在这里,大多数人都会遇见下载速度过慢的问题:

```log
Installing vscode-cpptools@1.14.5...
Downloading https://github.com/Microsoft/vscode-cpptools/releases/download/v1.14.5/cpptools-linux.vsix to /home/maouai233/.config/nvim/plugged/vimspector/gadgets/linux/download/vscode-cpptools/1.14.5/cpptools-linux.vsix
```

当然你可以**挂代理**,我这里使用一个成本极低的方法.

使用 **axel** 进行下载!
我们先将 **install_gadget.py** 停下来先

将文件下载至它应该在的位置,完成**install_gadget.py**的部分使命......

```
axel -n 256 https://github.com/Microsoft/vscode-cpptools/releases/download/v1.14.5/cpptools-linux.vsix -o /home/maouai233/.config/nvim/plugged/vimspector/gadgets/linux/download/vscode-cpptools/1.14.5/cpptools-linux.vsix
```

- `-n` 最大连接数
- `-o` 输出文件至

几次如此之后,我们的调试适配器就安装好了!

# 使用

## 配置文件

就如同 vscode 调试一样,调试需要 **launch.json **, vimspector 也不例外.

### 白嫖

我们可以通过一个偷懒而又简单的方式获取一个配置文件.

```vim
:h vimspector
```

其实就是直接翻 vimspector 的** README.md** ...... (同Github)

或者看 **vimspector/docs/configuration.md** (同官网)

将需要的复制粘贴到调试的根目录下的 **.vimspector** 中,并稍加修改.

当然你可以自己手动编写,Let's get higher!

### 自己动手,丰衣足食

以C语言为例,一个最简单的配置文件,在这里全部都是必须项!

```json

{
  "configurations": {
    "Launch": {
      "adapter": "vscode-cpptools",
      "configuration": {
        "request": "launch",
        "program": "<path to binary>", // 要调试的可执行文件路径
      }
    }
  }
}

```

如你所见,它是和vscode一样,支持在配置文件中的注释的,形同C语言注释.

> The JSON configuration file allows C-style comments:
> 
> - '// comment to end of line ...'
> - '/\* inline comment ... \*/'

---

**configurations** 允许有多个配置

Format :

```json
"configurations": {
  "name": {
    "adapter": "adapter",
    "filetypes": [...]
    ...
    "configuration": {
      ...
    }
  },
  "name": {
    "adapter": "adapter",
    "filetypes": [...]
    ...
    "configuration": {
      ...
    }
  }
}
```

**name** 是该配置条目的名称,如果有多个配置,在启动时供用户选择.
**adapter**指定了调试适配器

---

#### 调试适配器 adapter

除了提供的我们还可以自己自定义,也可以在原有的adapter下建立

#### 文件类型 filetypes

限制了该配置在当前打开文件**为某种类型(后缀)时才可以启动debug**

Example :

```json
"filetypes": [ "cpp", "c" ]
```

#### 配置项 configuration

##### request

可以为`launch`或`attach`

##### program

要调试的可执行程序的路径,注意不必要的空格不允许出现!

##### stopOnEntry / stopAtEntry

这两个是等价的,在程序入口停止.

##### environment

环境变量

Example :

```json
"environment": [
  {"name":" NAME1","value":"TEST1"},
  {"name":" NAME2","value":"TEST2"}
]
```

##### args

启动参数

Example :

```json
args: ["arg1","arg2"]
```

##### externalConsole

外部终端.
~~貌似没有什么用~~

##### cwd

工作目录

> `${cwd}` - the current working directory of the active window on launch

##### setupCommands 

Format :
```json
{
  "description": "描述",
  "text": "命令",
  "ignoreFailures": true // 执行错误是否可以忽略
}
```

##### customLaunchSetupCommands

如果此选项设置了,它将会替代默认的启动命令
但是,若直接这样可能会报错,因为我们并未指定架构,详见 **targetArchitecture**.

Format : 同 setupCommands

Example :

```json
"customLaunchSetupCommands": [
  {
    "description": "Connect to qemu",
    "text": "-target-select remote :1234",
    "ignoreFailures": true
  }
]
```

##### launchCompleteCommand

在调试器启动好后执行的命令,有限定:

- `exec-run` (default)
- `exec-continue`
- `None`

##### targetArchitecture

- `x64`
- `x86`
- `amd64`
- `arm`
- `arm64`
- ...

此选项可以**占位**使用,保证调试器的启动,在**启动时使用命令设置成目标架构即可**.

##### MIMode

调试器

`lldb`或者`gdb`

##### miDebuggerPath

相应调试器的可执行程序路径,如果没有设置,则在环境变量中搜索.

##### miDebuggerArgs

调试器的附加启动参数

> "是退出时的冒泡罢了 QwQ"
> 
> `"/usr/bin/gdb" --interpreter=mi ${在这里} --tty=${DbgTerm} 0<"/tmp/Microsoft-MIEngine-In-2aisxnef.g3f"` 

##### miDebuggerServerAddress

远程 remote 的地址,在这个选项设置后,调试器会尝试连接
就和我们平时调试时用的`target remote`一样

它给调试带来了一些可能.

#### 日志 logging

控制输出至 **Debug Console**

```json
"logging": {
  ...
}
```

- `engingLogging` 引擎日志 def-> false
- `exceptions` 异常 def-> true
- `moduleLoad` 模块加载 def-> true
- `programOutput` 被调试程序输出 def-> true
- `trace` def-> false
- `traceResponse` def-> false

#### 变量 variables

##### 预设变量

* `${dollar}` -> `$`
* `$$` -> `$`
* `${workspaceRoot}` `.vimspector.json`所在位置
* `${workspaceFolder}` `.vimspector.json`所在的位置
* `${gadgetDir}` 调试适配器的路径 (`gadgets/<OS>`)
* `${file}` 当前打开的文件
* `${relativeFile}` 当前打开的文件相对于`${workspaceFolder}`的路径
* `${relativeFileDirname}` 当前打开的文件所在目录相对于`${workspaceFolder}`的路径
* `${fileBasenameNoExtension}` 当前打开的文件的名称,不带后缀
* `${fileDirname}` 当前打开的文件所在目录,绝对路径
* `${fileExtname}` 当前打开的文件的后缀名
* `${cwd}` 工作目录
* `${unusedLocalPort}` 一个没有使用的本地TCP端口号

##### 自定义变量

于作用的配置的`name->variables`中定义,作用于作用的配置.

```json
"varibales": {
  "Common": "Value",
  "Shell": {
    "shell": [...],
    "env": {
      "name": "value"
    }
  }
}
```

Common 展示了如何定义一个普通变量.
Shell  展示了如何在调用shell进行变量值的获取,env可以设置环境变量.

##### 默认值

```json
  { "key": "${value:default {\\} stuff}" }
```

当value已被定义,使用value的值.

在这里的花括号中,要避免出现另一个花括号,否则将视其为结束,要对它进行转义,使用`\\`

Example :

```json
  {
    "configuration": {
      "program": "${program:${file\\}.out}"
    }
  }
```

##### 未定义的变量

未定义的变量在`.vimspector.json`某个地方使用,会要求用户手动输入

##### 类型转换

想象一下,你如果要询问用户,是否在入口处暂停,如果你是这样写的:

```json
  {
    "configuration": {
      "program": "${script:${file\\}}"
    }
  }
```

那它并不会生效,WHY?
因为输入的是一个string,那么这个变量就"理所应当"地成了一个string...

所以我们这样解决:

```json
  "stopOnEntry#json": "${stopOnEntry}"
```

加个默认值压压筋...

```json
  "stopOnEntry#json": "${stopOnEntry:true}"
```

同时还有一个鸡肋的问题,就是有人在变量后带`#json`,它就叫这个,非常的不友好,怎么办呢?

在它后面添加`#s`就行了!告诉vimspector不是要进行类型转换,它本身就长这个样...

##### 展开为数组

使用`*`(splat operator)将string展开为数组

```json
   "args": [ "*${CommandLineArgs}" ]
```

就是这样: `arg1 arg2 "This is a string"` -> `["arg1","arg2","This is a string"]`

#### 断点 breakpoints

##### Exceptions

除`stopAtEntry / stopOnEntry`外,可以:

```json
{
  "configurations": {
    "name": {
      "breakpoints": {
        "exception": {
          "cpp_throw": "Y",   // 抛出异常
          "cpp_catch": "Y"    // 捕获异常
        },
      },
      ...
    }
  }
}
```

如果将键值设为`""`(`"cpp_catch": ""`),跟随默认

如果不设置,那它大概会在启动时给你抛出这个小可爱:


```
cpp_throw: Break on C++: on throw (Y/N/default: Y)?
cpp_catch: Break on C++: on catch (Y/N/default: N)?
```

这个大概与我们的C语言没有太大关系

# Demo

抛个`.vimspector.json`,是我用来调试**操作系统内核**和**Uefi**的

这个操作系统的仓库在我将当前进度的代码全部整理好后才开放,当然你可以看到一点影子.

```json
{
  "configurations": {
    "TextOS - Kernel debug": {
      "adapter": "vscode-cpptools",
      "filetypes": [ "cpp", "c" ],
      "configuration": {
        "request": "launch",
        "program": "${workspaceRoot}/Build/Kernel/Kernel.elf.symbol",
        "cwd": "${workspaceRoot}",
        "MIMode": "gdb",
        "miDebuggerServerAddress": "localhost:1234",
        "setupCommands": [
          {
            "description": "Enable pretty-printing for gdb",
            "text": "-enable-pretty-printing",
            "ignoreFailures": true
          },
          {
            "description": "Set disassembly style for gdb",
            "text": "-gdb-set disassembly-flavor intel",
            "ignoreFailures": true
          }
        ]
      }
    },
    "TextOS - Boot debug": {
      "adapter": {
        "extends": "vscode-cpptools",
        "delay": "50000m"
      },
      "configuration": {
        "request": "launch",
        "program": "${workspaceRoot}/Build/Boot/DEBUG_GCC5/X64/SigmaBootPkg.debug",
        "cwd": "${workspaceRoot}",
        "MIMode": "gdb",
        "miDebuggerPath": "/usr/bin/gdb",
        "externalConsole": false,
        "targetArchitecture": "x64",
        "customLaunchSetupCommands": [
          {
            "description": "Connect to qemu",
            "text": "-target-select remote :1234",
            "ignoreFailures": true
          },
          {
            "description": "Load script for uefi debugging",
            "text": "source ${workspaceRoot}/Src/Base/setup.gdb",
            "ignoreFailures": true
          },
          {
            "description": "Enable pretty-printing for gdb",
            "text": "-enable-pretty-printing",
            "ignoreFailures": true
          },
          {
            "description": "Set disassembly style for gdb",
            "text": "-gdb-set disassembly-flavor intel",
            "ignoreFailures": true
          }
        ],
        "launchCompleteCommand": "exec-continue",
        "logging": {
          "engineLogging": true
        }
      }
    }
  }
}
```

# 补充

## 配置文件迁移 (vscode -> vimspector)

在vimspector的插件目录下的`support`下有个pyhthon脚本:`import_vscode_config`,但它不能直接对`launch.json`进行转换.
她针对笼统的配置，将`launch.json`等合并到一个文件,且不能转换带注释的config,于是我便自己写了个.

[import_vscode_config.py | download](https://gitee.com/canyan233/raw/raw/master/import_vscode_config.py)

```shell
./import_vscode_config launch.json
```

## 快捷键

### Visual Studio / VSCode

```vim
let g:vimspector_enable_mappings = 'VISUAL_STUDIO'
```

| Key             | Mapping                                    | Function
| ---             | ---                                        | ---
| `F5`            | `<Plug>VimspectorContinue`                 | When debugging, continue. Otherwise start debugging.
| `Shift F5`      | `<Plug>VimspectorStop`                     | Stop debugging.
| `Ctrl Shift F5` | `<Plug>VimspectorRestart`                  | Restart debugging with the same configuration.
| `F6`            | `<Plug>VimspectorPause`                    | Pause debuggee.
| `F8`            | `<Plug>VimspectorJumpToNextBreakpoint`     | Jump to next breakpoint in the current file.
| `Shift F8`      | `<Plug>VimspectorJumpToPreviousBreakpoint` | Jump to previous breakpoint in the current file.
| `F9`            | `<Plug>VimspectorToggleBreakpoint`         | Toggle line breakpoint on the current line.
| `Shift F9`      | `<Plug>VimspectorAddFunctionBreakpoint`    | Add a function breakpoint for the expression under cursor
| `F10`           | `<Plug>VimspectorStepOver`                 | Step Over
| `F11`           | `<Plug>VimspectorStepInto`                 | Step Into
| `Shift F11`     | `<Plug>VimspectorStepOut`                  | Step out of current function scope
| `Alt 8`         | `<Plug>VimspectorDisassemble`              | Show disassembly

### Human Mode

```vim
let g:vimspector_enable_mappings = 'HUMAN'
```

| Key          | Mapping                                       | Function
| ---          | ---                                           | ---
| `F5`         | `<Plug>VimspectorContinue`                    | When debugging, continue. Otherwise start debugging.
| `F3`         | `<Plug>VimspectorStop`                        | Stop debugging.
| `F4`         | `<Plug>VimspectorRestart`                     | Restart debugging with the same configuration.
| `F6`         | `<Plug>VimspectorPause`                       | Pause debuggee.
| `F9`         | `<Plug>VimspectorToggleBreakpoint`            | Toggle line breakpoint on the current line.
| `<leader>F9` | `<Plug>VimspectorToggleConditionalBreakpoint` | Toggle conditional line breakpoint or logpoint on the current line.
| `F8`         | `<Plug>VimspectorAddFunctionBreakpoint`       | Add a function breakpoint for the expression under cursor
| `<leader>F8` | `<Plug>VimspectorRunToCursor`                 | Run to Cursor
| `F10`        | `<Plug>VimspectorStepOver`                    | Step Over
| `F11`        | `<Plug>VimspectorStepInto`                    | Step Into
| `F12`        | `<Plug>VimspectorStepOut`                     | Step out of current function scope

### 映射

个人喜好...

```vim
nnoremap <C-S> <Plug>VimspectorBalloonEval " 浮动窗口显示变量值
nnoremap <C-B> <Plug>VimspectorBreakpoints " 断点监测
```

# Links

- [Vimspector | Github](https://github.com/puremourning/vimspector)
- [Setting up Vimspector | Vimspector](https://puremourning.github.io/vimspector-web/demo-setup.html)
- [Configure launch.json for C/C++ debugging in Visual Studio Code](https://code.visualstudio.com/docs/cpp/launch-json-reference)
- [Vim最强调试插件: vimspector](https://www.cnblogs.com/kongj/p/12831690.html)
