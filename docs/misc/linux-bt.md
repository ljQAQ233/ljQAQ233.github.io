# linux 下使用蓝牙

安装一些工具:

```bash
sudo pacman -S bluez bluez-utils
```

启动蓝牙服务:
```bash
sudo systemctl enable bluetooth.service
```

配置蓝牙:

```bash
bluetoothctl
```

进入交互:

```log
Waiting to connect to bluetoothd...[bluetooth]# hci0 new_settings: bondable ssp br/edr le secure-conn wide-band-speech
[bluetooth]# Agent registered
[bluetooth]# [CHG] Controller EC:63:D7:2E:C8:67 Pairable: yes
[bluetooth]#
```

---

打开电源:

```bash
power on
```

启用配对:

```bash
pairable on
```

启动搜索:

```bash
scan on
```

可以看到输出:

```log
[bluetooth]# [NEW] Device 10:21:AC:92:D6:06 BT5.2 Keyboard
[bluetooth]# [NEW] Device 11:21:AC:11:02:3B BT3.0 Keyboard
```

如果要连接低一个设备, 就是用下面的指令:

```bash
pair 10:21:AC:92:D6:06 
```

等待配对成功即可

