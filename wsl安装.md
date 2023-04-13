## wsl 自定义安装 Ubuntu
1. 参考 https://zhuanlan.zhihu.com/p/263089007 先将Ubuntu wsl版本给下载下来。
下载地址：https://link.zhihu.com/?target=https%3A//docs.microsoft.com/zh-cn/windows/wsl/install-manual
下载完后将对应的Ubuntu-xxx.appx 修改成  Ubuntu-xxx.zip   如：Ubuntu_2204.1.7.0_x64.zip
然后解压zip
2.  参考： https://blog.csdn.net/icandoit_2014/article/details/120473339
打开PowerShell 执行如下命令，启动 "适用于 Linux 的 Windows 子系统" 的可选功能
dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart

启用虚拟机功能：
dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart
进行这里后一定要重启计算机

3. 下载：https://wslstorestorage.blob.core.windows.net/wslblob/wsl_update_x64.msi 然后安装
4.  将 WSL 2 设置为默认版本
wsl --set-default-version 2
有些版本运行上面的命令回报错，那是系统不支持，用wsl1就行。
5. 双击 第1步中解压后的zip中的ubuntu.exe就可以启动Ubuntu了

### 运行adb
参考： https://blog.csdn.net/qq295109601/article/details/113754144
其实就是将 Windows下的adb alias 到 Linux
```
# Android Debug Bridge
# 下面添加Linux 下adb所在目录
export PATH=$PATH:/mnt/c/tool/android-develpe-SDK/platform-tools/
# 下面是 Windows下adb位置
alias adb='/mnt/c/tool/android-develpe-SDK/platform-tools/adb.exe'
```

### 启用ssh
```
# 1. 卸载并重新安装 ssh
sudo apt-get purge openssh-server  # purge 是卸载并删除配置文件
sudo apt-get install openssh-server

#2. 修改配置
sudo vi /etc/ssh/sshd_config 
#Port 22   # 如果端口冲突，就需要修改这个
ListenAddress localhost  # 只接受本地请求
PasswordAuthentication yes  # 允许密码登录

#3 重启服务
sudo service ssh restart
```

PS: 用xshell4连接时可能会报"找不到匹配的host key算法" 按照如下操作执行：
```
echo "KexAlgorithms +diffie-hellman-group14-sha1" >>/etc/ssh/sshd_config
sudo vim /etc/ssh/sshd_config
# 添加如下：
HostKeyAlgorithms +ssh-rsa
PubkeyAcceptedKeyTypes +ssh-rsa
```
然后使用 ssh localhost 进行连接
