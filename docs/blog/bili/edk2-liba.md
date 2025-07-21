# EDKII 使用 .a 文件

在 `.inf` 文件 `[BuildOptions]` 中加入:

```ini
GCC:*_*_*_DLINK_FLAGS = -L$(PATH_TO_DIR) -l$(LIB_NAME)
```

就是直接在编译命令里面追加

