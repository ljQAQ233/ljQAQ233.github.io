# osdev 离线预览

# Using

可以使用重命名的方法即 将文件添加 `.html` 的后缀

---

使用 httpd 可以简单方便地使用:

安装 busybox:

```
yes | pacman -S busybox
```

```
apt-get install busybox -y
```

到 osdev 解压后的目录:

```
busybox -h . -p 8080
```

然后访问 `http://localhost:8080/Main_Page` 启动!

