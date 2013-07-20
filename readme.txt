***概要***
用于图片裁剪。有以下特点： 
1.能进行人脸识别。图片中有人脸，将自动视为人脸区域为重要区域，将不会被裁剪掉。 
2.自动识别其它重要区域。如果图片中未识别出人脸，则会根据特征分布计算出重区域。 
总而言之，自动识别图片中的重要区域，并且在图片裁剪时保留重要区域。 
目前，已经正式在淘宝一淘玩客中使用。wanke.etao.com

效果演示：
http://demo.bo56.com/tclip


***安装步骤***

源码下载:
opencv2 下载地址  http://www.opencv.org.cn/index.php/Download

安装opencv2:
此扩展依赖于opencv2.0 之上版本。因此安装前先安装opencv。opencv的安装步骤如下
1.yum install gtk+ gtk+-devel pkgconfig libpng zlib libjpeg libtiff cmake
2.下载 opencv2 安装包
3.解压安装包
4.cd 进入安装包文件夹内。
5.cmake CMakeLists.txt
6.make && make install
7.vim /etc/profile
在 unset i 前增加
export PKG_CONFIG_PATH=/usr/lib/pkgconfig/:/usr/local/lib/pkgconfig:$PKG_CONFIG_PATH
保持退出后，执行如下命令
8. source /etc/profile
9. echo "/usr/local/lib/" > /etc/ld.so.conf.d/opencv.conf
10. ldconfig

安装tclip扩展:
1. cd 到源代码目录中的php_ext文件夹
2. phpize
3. ./configure
4. make
5. cp modules/tclip.so 到 extension 目录
6. 修改php.ini。加入 extension=tclip.so
7. 重启fpm

安装命令行:
如果想使用命令行方式，可以进行如下安装
1. cd 进入安装包soft文件夹内
2. chmod +x ./tclip.sh
3. ./tclip.sh


***使用方法说明***
第一种：在php中使用格式：
tclip(文件原路径，裁剪后的图片保存路径，裁剪后的图片宽度，裁剪后的图片高度) 
示例：
$source_file = "/tmp/a.jpg"; 
$dest_file = "/www/a_dest.jpg"; 
$width = 400; 
$height = 200; 
tclip($source_file, $dest_file, $width, $height); 
第二种：命令行 
参数说明： 
-s 原图路径 
-d 裁剪后的图片保存路径 
-w 裁剪后的图片宽度 
-h 裁剪后的图片高度 
./tclip -s a.jpg -d a_dest.jpg -w 400 -h 200 