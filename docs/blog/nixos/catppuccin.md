# catppuccin 主题

> current version : v25.11

# waybar

这个, 需要在 `home` 的配置里面启动 `waybar`:

```nix
programs.waybar.enable = true;
```

要不然不会生效, 你可以试试

??? note ""

    catppuccin/nix : modules/home-manager/waybar.nix
    
    ```
    cfg = config.catppuccin.waybar;
    enable = cfg.enable && config.programs.waybar.enable;
    ```
    
    这里 config 只是 home 的配置, 不是系统配置, 所以必须在 home-manager 模块 的配置里面启用 waybar

