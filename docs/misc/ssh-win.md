# 用 ssh 连接 windows

打开 powershell

---

安装 OpenSSH Server:

```shell
Add-WindowsCapability -Online -Name OpenSSH.Server~~~~0.0.1.0
```

---

设为开机自启并启动

```shell
Set-Service -Name sshd -StartupType Automatic
Start-Service sshd
```

## 连接

随便找个 `ssh`, 连接就好了 ｏ(≧▼≦○〃

```shell
ssh <username>@<ip>
```

## (可选) 设置登录后的默认 shell

```shell
New-ItemProperty -Path 'HKLM:\SOFTWARE\OpenSSH' -Name DefaultShell `
  -Value 'C:\Program Files\PowerShell\7\pwsh.exe' -PropertyType String -Force
```

---

如果要切换回来就改成 `explorer.exe`

当然, 如果已经重启了, 而且不是管理员 powershell 就只能尝试 UAC 提权:

```shell
Start-Process -FilePath "$env:SystemRoot\System32\WindowsPowerShell\v1.0\powershell.exe" -Verb RunAs
```

再次修改注册表就好了.

