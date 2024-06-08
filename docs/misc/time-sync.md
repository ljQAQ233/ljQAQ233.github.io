# Overiew

Opreating System : Arch Linux

> 时间不准确的问题.

# Solution

安装 ntpdate 用于在线授时

```shell
yes | sudo pacman -S ntp
```

Update our time!

**url** 是授时服务器的地址.

```shell
ntpdate url
```

以下是可用的 url

|         url          |         描述         | 
|        ------        |        ------        |
|    ntp.aliyun.com    |        阿里云        |
|   time.windows.com   | Windows 默认使用的   |


