# Visual Studio

## Cross Platform Install

### config setup (CentOS): 
1. vi /etc/sysconfig/network-scripts/ifcfg-eth0 change ONBOOT=no to yes
	press i -> press esc -> press shift+: -> wq
2. service network restart
3. yum install gcc-c++ 
4. ip addr 
	check IP address