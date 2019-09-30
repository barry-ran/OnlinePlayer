# OnlinePlayer
online video player

# 编译
## QtAV 编译
[参考文档](https://github.com/wang-bin/QtAV/wiki/Build-QtAV)

QtAV我已经编译好了放在third_party\QtAV（Qt5.12.4 + vs2017），不过QtAV是和Qt强依赖的，所以如果你的开发环境和我不统一，建议使用自己版本的Qt环境编译一份QtAV替换third_party\QtAV中的相关文件。QtAV开发过程中编译一次即可。

1. 同步QtAV源码

```
git submodule update
```

2. 在QtAV目录下新建ffmpeg目录，将depends/ffmpeg*win32-dev.zip中的include和lib目录解压到third_party/ffmpeg/win32目录中

3. 编辑QtAV/.qmake.conf，添加如下两行：

```
INCLUDEPATH += $$PWD/../third_party/ffmpeg/win32/include
LIBS += -L$$PWD/../third_party/ffmpeg/win32/lib
```

4. 编译QtAV(也可以直接QtCreator打开QtAV/QtAV.pro来编译（使用shadow build）)（debug/release都需要编译）：

注意使用命令行编译的话不要在QtAV根目录下编译

```
mkdir your_build_dir
cd your_build_dir
qmake QtAV_source_dir/QtAV.pro
make -j4
```

5. 将编译输出目录中的相关库文件复制到third_party\QtAV中，主要有以下文件：
    - lib: QtAVd1.lib, QtAVWidgetsd1.lib
    - bin: QtAVd1.dll, QtAVWidgetsd1.dll

# mark
[图标](https://www.iconfont.cn/collections/detail?spm=a313x.7781069.0.da5a778a4&cid=567)
