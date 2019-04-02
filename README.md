# JavaScript

## WINSCP上传方法
windows环境下载winscp<br>
用户名：密码为datatmp:ui12331<br>
地址为：47.93.212.144<br>
目录： /home/datatmp/static/  注意是**static** 目录

## 目录关联设置方法
mklink /D "./dist" "f:/thing3d/dist"

## 转换成浏览器支持版本方法
browserify index.js -s TinyQueue > tinyqueue.js

## 检测 min 版本编译错误方法
uglifyjs thing.js -o thing-min.js

## 添加随机种子始终加载最新文件方法
<script>document.write('<script src="../dist/thing.js?t=' + new Date().getTime() + '"><\/script>')</script>

## spector.js 调试 WebGL 方法
<script type="text/javascript" src="https://spectorcdn.babylonjs.com/spector.bundle.js"></script>
var spector = new SPECTOR.Spector();
spector.displayUI();

## 使用 vorlon 远程调试 log 方法
npm i -g vorlon 
vorlon
http://localhost:1337
<script src="http://localhost:1337/vorlon.js"></script>

## 上传 API 文档
gulp jsdoc-upload

## DTS 文件报错后的错误查找
index.js: writeDeclaration(d) 函数中 default: 段加入
var keys = Object.keys(d);
for(var i = 0; i < keys.length; i++) {
	console.log('key: ' + keys[i] + ', value: ' + d[keys[i]]);
}

# EGE API

# Linux Visual Studio Cross Platform Install

## config setup (CentOS): 
1. vi /etc/sysconfig/network-scripts/ifcfg-eth0 change ONBOOT=no to yes
	press i -> press esc -> press shift+: -> wq
2. service network restart
3. yum install gcc-c++ 
4. ip addr 
	check IP address
 
-- 待续 --