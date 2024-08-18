# clang format

## 忽略目录

在目录下创建一个 `.clang-format` 文件[^so_ans]:

[^so_ans]: [How to ignore files or directories with clang-format 3.9](https://stackoverflow.com/questions/50647960/how-to-ignore-files-or-directories-with-clang-format-3-9)

```ini
DisableFormat: true,
SortIncludes: Never # with clang-format version < 13 use `false` here.
```

