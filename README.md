mysql-fifo-plugin
=================

MySQL Pipes (FIFOs) Plugin

Build
-----
	cd /usr/local/src/
	git clone https://github.com/netkiller/mysql-fifo-plugin.git
	cd mysql-fifo-plugin/
	
	cmake .
	make
	make install

	or
	
	gcc -O3  -g  -I/usr/include/mysql -I/usr/include  -fPIC -lm -lz -shared -o libfifo.so fifo.c
	sudo mv libfifo.so /usr/lib/mysql/plugin/
	
Plugin Install and Uninstall
--------------

### Install

	create function fifo_create returns string soname 'libfifo.so';
	create function fifo_remove returns string soname 'libfifo.so';
	create function fifo_read returns string soname 'libfifo.so';
	create function fifo_write returns string soname 'libfifo.so';

### Uninstall

	drop function fifo_create;
	drop function fifo_remove;
	drop function fifo_read;
	drop function fifo_write;

Testing
-------
### 创建管道	
	mysql> create function fifo_create returns string soname 'libfifo.so';
	Query OK, 0 rows affected (0.02 sec)

	mysql> select fifo_create('/tmp/myfifo');
	+----------------------------+
	| fifo_create('/tmp/myfifo') |
	+----------------------------+
	| ture                       |
	+----------------------------+
	1 row in set (0.00 sec)
	
	查看管道是否创建
	
	$ ls /tmp/myfifo 
	/tmp/myfifo
	
	覆盖测试，正确应该返回false
	
	mysql> select fifo_create('/tmp/myfifo');
	+----------------------------+
	| fifo_create('/tmp/myfifo') |
	+----------------------------+
	| false                      |
	+----------------------------+
	1 row in set (0.00 sec)

### 删除管道	
	mysql> select fifo_remove('/tmp/myfifo');
	+----------------------------+
	| fifo_remove('/tmp/myfifo') |
	+----------------------------+
	| true                       |
	+----------------------------+
	1 row in set (0.00 sec)
	
	mysql> select fifo_remove('/tmp/my');
	+------------------------+
	| fifo_remove('/tmp/my') |
	+------------------------+
	| false                  |
	+------------------------+
	1 row in set (0.00 sec)

	删除不存在的管道会提示 false

### 读管道

	在一个终端窗口中运行
	mysql> select fifo_read('/tmp/myfifo');
	+--------------------------+
	| fifo_read('/tmp/myfifo') |
	+--------------------------+
	| Hello world              |
	+--------------------------+
	1 row in set (7.85 sec)

	在另一个终端窗口中运行
	mysql> select fifo_write('/tmp/myfifo','Hello world !!!');
	+---------------------------------------------+
	| fifo_write('/tmp/myfifo','Hello world !!!') |
	+---------------------------------------------+
	| true                                        |
	+---------------------------------------------+
	1 row in set (0.00 sec)	
	
	或者
	
	在命令行运行
	$ echo "Hello world" > /tmp/myfifo
	
	在SQL客户端中运行
	mysql> select fifo_read('/tmp/myfifo');
	+--------------------------+
	| fifo_read('/tmp/myfifo') |
	+--------------------------+
	| Hello world
				 |
	+--------------------------+
	1 row in set (0.00 sec)
	注意上面echo会自动增加换行符，-n参数可以避免
	$ echo -n "Hello world" > /tmp/myfifo
	
	mysql> select fifo_read('/tmp/myfifo');
	+--------------------------+
	| fifo_read('/tmp/myfifo') |
	+--------------------------+
	| Hello world              |
	+--------------------------+
	1 row in set (0.01 sec)
	
### 写管道
	mysql> select fifo_write('/tmp/myfifo','Hello world !!!');
	+---------------------------------------------+
	| fifo_write('/tmp/myfifo','Hello world !!!') |
	+---------------------------------------------+
	| true                                        |
	+---------------------------------------------+
	1 row in set (0.00 sec)
	
	$ cat /tmp/myfifo
	Hello world !!!
	
	管道 /tmp/nofifo 不存在会返回false
	mysql> select fifo_write('/tmp/nofifo',concat(mobile,'\r\n')) from demo;
	+-------------------------------------------------+
	| fifo_write('/tmp/nofifo',concat(mobile,'\r\n')) |
	+-------------------------------------------------+
	| false                                           |
	| false                                           |
	| false                                           |
	| false                                           |
	| false                                           |
	+-------------------------------------------------+
	5 rows in set (0.01 sec)	

# Donations

We accept PayPal through:

https://www.paypal.me/netkiller

Wechat (微信) / Alipay (支付宝) 打赏:

http://www.netkiller.cn/home/donations.html

[![Bitdeli Badge](https://d2weczhvl823v0.cloudfront.net/netkiller/mysql-fifo-plugin/trend.png)](https://bitdeli.com/free "Bitdeli Badge")

