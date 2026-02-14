# nixos 配置 fcitx5 + rime

# fcitx5

普通的中文设置

```nix
  i18n.inputMethod = {
    enable = true;
    type = "fcitx5";
    fcitx5.addons = with pkgs; [
      fcitx5-gtk
      fcitx5-pinyin-zhwiki
      qt6Packages.fcitx5-configtool
      qt6Packages.fcitx5-chinese-addons
    ];
  };
```

# rime

> rime - 中州韻輸入法引擎
>
>  Rime 是一个开源的输入法引擎，支持多种输入方案，包括 朙月拼音。它允许用户自定义输入规则和词库，具有高度的可定制性和隐私保护。

```
  i18n.inputMethod = {
    enable = true;
    type = "fcitx5";
    fcitx5 = {
      waylandFrontend = true;
      addons = with pkgs; [
        (fcitx5-rime.override {
          rimeDataPkgs = [
            rime-ice
          ];
        })
      ];
    };
  };
```

**如果安装了 fcitx5, 建议先删除软件与所有的配置.**

新建 `~/.local/share/fcitx5/rime/default.custom.yaml`

输入:

```yaml
patch:
  __include: rime_ice_suggestion:/

  schema_list:
    - schema: rime_ice
```

如果没有新建, 默认可能会使用 **朙月拼音**.

这里使用流行的 **雾凇拼音** (`rime-ice`)

启动 fcitx5, 打开系统托盘, 启动 `configure`, 搜索 `rime`, 添加到 "左边" 即可

这时候系统托盘会多出一个 "rime", 选择, 并点击 "部署"(deploy)

接下来, `~/.local/share/fcitx5/rime` 里面会多出许多文件, 这时可以试一下

## 英文标点

切换英文标点需要 点击 fcitx / rime-ice 托盘的 `¥ -> $`

当然, 快捷键默认是 **ctrl + `**, 启动一个设置. 或者 **ctrl + shift + 3**

源码中是这么写的:

```yaml
key_binder:
  bindings:
    - {accept: "Control+Shift+3", toggle: ascii_punct, when: always}
    - {accept: "Control+Shift+numbersign", toggle: ascii_punct, when: always}
    - {accept: "Control+Shift+4", toggle: traditionalization, when: always}
    - {accept: "Control+Shift+dollar", toggle: traditionalization, when: always}
```
