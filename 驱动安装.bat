@echo off
%1 mshta vbscript:CreateObject("Shell.Application").ShellExecute("cmd.exe","/c %~s0 ::","","runas",1)(window.close) && exit
chcp 65001
cd /d %~dp0
echo %cd%
echo 安装驱动完成，即将重启系统......
start install-interception.exe /install
timeout /t 5 && shutdown -r -t 0