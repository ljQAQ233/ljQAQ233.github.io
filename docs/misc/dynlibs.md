# 动态链接库缺失

# yay

```
$ yay
yay: error while loading shared libraries: libalpm.so.13: cannot open shared object file: No such file or directory

```

看到 github 的一个回答瞬间绷不住了[^yay0]:

```shell
sudo cp /usr/lib/libalpm.so.14 /usr/lib/libalpm.so.13
```

估计只是暂时可用

[^yay0]: https://github.com/Morganamilo/paru/issues/1155

