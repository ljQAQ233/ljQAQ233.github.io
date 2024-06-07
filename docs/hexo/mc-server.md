---
title: 一个Minecratf服务器自动配置脚本
date: 2022-02-17 10:38:29
tags: 
- Minecraft
- Linux
- 脚本
- Bilibili
- 工具
---

Welcome To my Pages!

# 一个Minecratf服务器自动配置脚本

- 2022/02/17 10:38:29

# 下载并执行

## 使用Git

安装git:

```bash
sudo apt update
sudo apt install git -y
```
一般来说Ubuntu预装Git工具……
克隆仓库：

```bash
git clone https://gitee.com/canyan233/install_minecraft_server.git
```
取出脚本:

```bash
mv install_minecraft_server/install-McServer-finally.sh .
```

```bash
sudo bash ./install-McServer-finally.sh
```

**一定不能用sh执行啊>_<**

## 使用curl

还可以用更简单的方法的.

安装curl:

```bash
sudo apt update
sudo apt install curl -y
```
下载直接执行!

```bash
sudo su -c "bash <(curl -s -S -L https://gitee.com/canyan233/raw/raw/master/install-McServer-finally.sh)"
```

## 使用Wget

这个也很硬核哈，等同于上文使用curl

```bash
sudo apt install wget -y
```

```bash
sudo su -c "bash <(wget -qO- https://gitee.com/canyan233/raw/raw/master/install-McServer-finally.sh)"
```

# 使用脚本进行配置

执行过命令后，脚本会自动更新软件列表

```bash
#运行实录
命中:1 https://mirrors.tuna.tsinghua.edu.cn/ubuntu bionic InRelease
获取:2 https://mirrors.tuna.tsinghua.edu.cn/ubuntu bionic-updates InRelease [88.7 kB]
获取:3 https://mirrors.tuna.tsinghua.edu.cn/ubuntu bionic-backports InRelease [74.6 kB]
获取:4 https://mirrors.tuna.tsinghua.edu.cn/ubuntu bionic-security InRelease [88.7 kB]
已下载 252 kB，耗时 3秒 (74.4 kB/s)              
正在读取软件包列表... 完成
正在分析软件包的依赖关系树       
正在读取状态信息... 完成
```

并安装**Java**与**iptables**(默认是default-jdk，由于信息太大，将输出重定向到/dev/null以**舍去**哈).
将会在**家**创建一个目录**tmp-mcserver**存放临时文件.
**没有意外的话就下一步啦，但我们考虑到了意外QwQ……那就是安装的服务器目录下有另外一个叫"server.jar"的文件，也对此作出了解决.**
#运行实录

```bash
It is detected that there is already a "server.jar" file, please install it in another directory
delete(d);exit(e);Continue to install this Jar(c)|
```

如下解释：
输入d => 删除server.jar文件
输入e => 退出，你解不解决吧？
输入c => 直接安装这个.我走啦哈.
不会吧，不会吧，这个应该没有人看不懂吧?
<br>
如果没有那个server.jar文件就可以选择了（或者有已经删除）,Okayyyy.选择时间！这里我选 1.7.10[服务端版本号].
接下来是没有以外的情况.这个好诶.JPG

```bash
#运行实录
--------------------------------
--------------------------------
1.17.1  1.17    1.16.5
1.16.4  1.16.3  1.16.2
1.16.1  1.15.2  1.15.1
1.15    1.14.4  1.14.3
1.14.2  1.14.1  1.14
1.13.2  1.13.1  1.13
1.12.2  1.12.1  1.12
1.11.2  1.11.1  1.10.2
1.10    1.9.4   1.9.2
1.9     1.8.8   1.8.7
1.8.6   1.8.5   1.8.4
1.8.3   1.8     1.7.10
1.7.9   1.7.8   1.7.5
1.7.2   1.6.4   1.6.2
1.5.2   1.5.1   1.4.7
1.4.6
 Choose my Jar of Server(r)
--------------------------------
Enter the version you want to install:
```

之后是自动配置时间!将会安装screen工具以创建一个命令行终端在后台配置及运行Minecraft服务器.

```bash
#运行实录
Installing screeen...done
Configuring server...................done
```

需要同意一下这个协议（eula.txt内容），我想没有人选Ctrl-C吧……

```bash
#运行实录
--------------------------------
By changing the setting below to TRUE you are indicating your agreement to our EULA (https://account.mojang.com/documents/minecraft_eula).
2022-02-08 16:30:17
--------------------------------
Just so you know, by downloading any of the software on this page, you agree to theMinecraft End User License AgreementandPrivacy Policy.
--------------------------------
Angree(yes)|yes
```
```bash
This is 1.7.10+
```

接下来是一系列的配置
输入您希望的Minecraft服务器端口号.默认25565.必须要输入,不然我不给你过.

```bash
#运行实录
Please enter the Server port number|
```
输入您希望的启动脚本所在位置(生成位置).
```bash
#运行实录
Please enter the generated startup script directory|For example: /root/ |
```
```bash
#运行实录
Create startup script...done
The startup script has been created in *$%@ #是个变量，我总不可能用我的路径来迷惑你们吧？
```

回车之后请稍等，最终花费时间将取决于计算机性能…… <strike> 像我计算机这么差的性能都可以28s过……</strike>

最后，看到如下信息就成功了哈

```bash
#运行实录
=============Ok=============
```

# Q&A

## 1.1 为什么不可以用`curl (wget -pO-) URL|bash`命令执行？

**A：不保存为文件，read命令直接被跳过，功能不能实现，无互动的功能.**

## 1.2 E: 无法定位软件包 default-jdk并找不到java命令

**A: 手动安装java,这里只说一下OpenJDK安装**

```bash
sudo apt update
sudo apt-cache search openjdk
```

**将会在输出中找到一下几行**

```bash
#差不多的运行结果
openjdk-11-jdk - OpenJDK Development Kit (JDK)
openjdk-11-jdk-headless - OpenJDK Development Kit (JDK) (headless)
openjdk-11-jre - OpenJDK Java runtime, using Hotspot JIT
openjdk-11-jre-headless - OpenJDK Java runtime, using Hotspot JIT (headless)
```

**你也可以在其中找到”openjdk-?-jdk”与”openjdk-?-jre”，并安装它**

`sudo apt install openjdk-11-jre openjdk-11-jdk -y`

**再运行脚本.**

# 视频演示

<iframe src="//player.bilibili.com/player.html?aid=759870508&bvid=BV1h64y1q7cH&cid=388857105&page=1" scrolling="no" border="0" frameborder="no" framespacing="0" allowfullscreen="true"> </iframe>

# Git仓库

## 项目仓库[Proj]

**Https => https://gitee.com/canyan233/install_minecraft_server**

## 2.原始代码仓库[Raw]

**Https => https://gitee.com/canyan233/raw/raw/master/install-McServer-finally.sh**

