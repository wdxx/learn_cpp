#### GDB位置

```
C:\Users\Administrator\AppData\Local\Android\Sdk\ndk\20.0.5594570\prebuilt\windows-x86_64\bin
```

#### 使用方法

```
https://wrlus.com/android-security/android-gdb-native-debug/
https://www.twblogs.net/a/5d2041a4bd9eee1ede064057/?lang=zh-cn
注意： 需要 setenforce 0
```

#### gdb命令

```
file 'E:/AndroidSourceCode/system/bin/app_process64'
set sysroot 'E:/AndroidCode/Symbol'
set dir 'Z:/AndroidSourceCode'

b E:/AndroidSourceCode/art/runtime/art_method.cc:314
```
