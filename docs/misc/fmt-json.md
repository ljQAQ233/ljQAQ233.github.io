# 格式化 json

直接输出结果:

```shell
jq < file.json
```

## vim

```vim
:%!jq
```

## confrom.nvim

```lua
-- 保存时格式化
vim.api.nvim_create_autocmd('BufWritePre', {
  pattern = '*',
  callback = function(args)
    require('conform').format({ bufnr = args.buf })
  end,
})

-- 配置 jq
require('conform').setup({
  formatters_by_ft = {
    ['json'] = { 'jq' },
  },
})
```

# 参考

- <https://ganquan.org/posts/neovim/using-jq-format-JSON-in-neovim>

