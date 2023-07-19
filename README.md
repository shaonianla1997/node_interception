node-interception
============

[基于https://github.com/oblitum/Interception][latest-release]
关键字：nodejs 键盘鼠标驱动级模拟、拦截；驱动级键鼠模拟；虚拟鼠标、虚拟键盘。

用途
--------

windows默认的键盘、鼠标模式为 <kbd>raw input</kbd> ,部分游戏或者软件为了提升性能和防作弊，会通过 <kbd>direct input</kbd> 模式检索键鼠数据
因此你通过系统API的方式发送的键盘鼠标模拟事件就无法在游戏或软件中响应。该示例展示了如何通过nodejs的n-api调用[Interception][latest-release]
实现驱动级键盘鼠标的事件拦截、模拟。

安装使用
--------

. 双击“驱动安装.bat”进行驱动安装，安装后会自动重启；
. <kbd>node index.js</kbd> 执行测试方法

[latest-release]: https://github.com/oblitum/interception/releases/latest