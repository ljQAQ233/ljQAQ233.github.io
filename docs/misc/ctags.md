# ctags 提取函数名称

# Pack!

将函数打包带走!

```shell
ctags -x ${src_file} \
    | grep function  \
    | tr -s ' '      \
    | cut -d' ' -f5- \
    | awk '{print $0";"}'
```

NOTE: 可能只能提取到定义的首行, 使用 `clang-format` 配合?

---

参考:

[Tools / 获取c文件函数名的几种方法](https://zhuanlan.zhihu.com/p/165451452)

