# 网站

从前我是用的博客是使用 `hexo` 进行搭建的, 但是我觉得它的组织方式有点不适合我了, 而且 `node_modules` 的特性众所周知. 总之, 为了更加的方便文档展示, 我决定将 `hexo` 换成 `mkdocs`
这是 2024.06.01 的事情, 开始迁移至 `mkdocs`.

使用 `mkdocs` 以及 `material`, 我是受到了许多 up主 的启发.

# Github Pages

白嫖太好了...

## Github Actions

{--yaml 就是很奇怪--}

- `.github/workflows/deploy.yml`

```yml
name: deploy

on: push

jobs:
  deploy:
    name: deploy
    runs-on: ubuntu-latest

    steps:
    - name: checkout
      uses: actions/checkout@v4
    
    - name: prepare python
      uses: actions/setup-python@v4

    - name: prepare dependencies
      run: pip install mkdocs-material 

    - name: build docs
      run: mkdocs build

    - name: push to repo
      uses: JamesIves/github-pages-deploy-action@v4
      with:
        branch: gh-pages
        folder: site

```

# 参考

- [Material Theme](https://squidfunk.github.io/mkdocs-material/getting-started/)
- [Mkdocs Material使用记录](https://shafish.cn/blog/mkdocs/#__tabbed_10_2)

