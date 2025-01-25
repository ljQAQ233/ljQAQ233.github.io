# nurses 无法找到

```
 *** Unable to find the ncurses libraries or the
 *** required header files.
 *** 'make menuconfig' requires the ncurses libraries.
 ***
 *** Install ncurses (ncurses-devel) and try again.
 ***
```

---

情景: `busybox-1.37.0`

首先如果 `whereis ncurses.h` 有结果就说明已安装 ncurses

其次, 它告诉我没找到, 就可以扒它的检测代码了, 在 `scripts/kconfig/lxdialog/check-lxdialog.sh` 中

```shell
check() {
    $cc -x c - -o $tmp 2>/dev/null <<'EOF'
#include CURSES_LOC
main() {}
EOF
	if [ $? != 0 ]; then
	    echo " *** Unable to find the ncurses libraries or the"       1>&2
	    echo " *** required header files."                            1>&2
	    echo " *** 'make menuconfig' requires the ncurses libraries." 1>&2
	    echo " *** "                                                  1>&2
	    echo " *** Install ncurses (ncurses-devel) and try again."    1>&2
	    echo " *** "                                                  1>&2
	    exit 1
	fi
}
```

把 `2>/dev/null` 去掉看 gcc 输出发现不是找不到头文件, 而是 `main()` 的返回类型出错. 加上 `int` 就可以了

