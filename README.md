tclip
=====

名字说明
---------------
T开头，代表是头像识别<br/>
clip，读[klip]，译为裁剪。<br/>
Tclip，意为自动头像识别的图片裁剪项目。<br/>
<br/>

概要
---------------
用于图片裁剪。有以下特点： <br/>
1.能进行人脸识别。图片中有人脸，将自动视为人脸区域为重要区域，将不会被裁剪掉。 <br/>
2.自动识别其它重要区域。如果图片中未识别出人脸，则会根据特征分布计算出重区域。 <br/>
总而言之，自动识别图片中的重要区域，并且在图片裁剪时保留重要区域。 <br/>
3.可以加水印。
<br/>

效果演示
-----------------------
### 人物效果演示
原图<br/>
![github](https://raw.github.com/exinnet/tclip/master/demo_images/a1.jpg "github")
<br/><br/>
如果按照从中间截取为 400 * 225 大小大图片。效果如下：<br/>
![github](https://raw.github.com/exinnet/tclip/master/demo_images/a2.jpg "github")
<br/><br/>
使用tclip裁剪图片效果如下：<br/>
![github](https://raw.github.com/exinnet/tclip/master/demo_images/a3.jpg "github")
<br/>
### 景物效果演示
原图<br/>
![github](https://raw.github.com/exinnet/tclip/master/demo_images/b1.jpg "github")
<br/><br/>
如果按照从中间截取。效果如下：<br/>
![github](https://raw.github.com/exinnet/tclip/master/demo_images/b2.jpg "github")
<br/><br/>
使用tclip裁剪图片效果如下：<br/>
![github](https://raw.github.com/exinnet/tclip/master/demo_images/b3.jpg "github")
<br/>
<br/>
### 水印效果
![github](https://raw.github.com/exinnet/tclip/master/demo_images/a1_dest_watermark.jpg "github")
<br/>
<br/>
### 在线演示
演示地址：[http://demo.bo56.com/tclip](http://demo.bo56.com/tclip)
<br/>
<br/>
安装步骤：
--------------
### 源码下载<br/>
opencv2 下载地址  [http://www.bo56.com/tclip人脸识别图片裁剪/#download](http://www.bo56.com/tclip%E4%BA%BA%E8%84%B8%E8%AF%86%E5%88%AB%E5%9B%BE%E7%89%87%E8%A3%81%E5%89%AA/#download) (建议opencv2.4.4版本) 
<br/>
### 安装opencv2 <br/>
此扩展依赖于opencv2.0 之上版本。因此安装前先安装opencv。opencv的安装步骤如下<br/>
yum install gtk+ gtk+-devel pkgconfig libpng zlib libjpeg libtiff cmake <br/>
下载 opencv2 安装包 <br/>
解压安装包 <br/>
cd 进入安装包文件夹内。<br/>
cmake CMakeLists.txt <br/>
make && make install <br/>
vim /etc/profile <br/>
在 unset i 前增加 <br/>
export PKG_CONFIG_PATH=/usr/lib/pkgconfig/:/usr/local/lib/pkgconfig:$PKG_CONFIG_PATH <br/>
保持退出后，执行如下命令 <br/>
source /etc/profile <br/>
echo "/usr/local/lib/" > /etc/ld.so.conf.d/opencv.conf <br/>
ldconfig <br/>
<br/>
### 安装tclip扩展<br/>
cd 到源代码目录中的php_ext文件夹 <br/>
phpize <br/>
./configure <br/>
make <br/>
cp modules/tclip.so 到 extension 目录 <br/>
修改php.ini。加入 extension=tclip.so <br/>
重启fpm <br/>
### 安装命令行<br/>
如果想使用命令行方式，可以进行如下安装<br/>
cd 进入安装包soft文件夹内<br/>
chmod +x ./tclip.sh <br/>
./tclip.sh <br/>
<br/>

使用方法说明
---------------------
第一种：在php中使用格式：<br/>
tclip(文件原路径，裁剪后的图片保存路径，裁剪后的图片宽度，裁剪后的图片高度)  <br/>
示例： <br/>
$source_file = "/tmp/a.jpg";  <br/>
$dest_file = "/www/a_dest.jpg";  <br/>
$width = 400;  <br/>
$height = 200;  <br/>
$watermark_text = ""; //可选<br/>
$ret = tclip($source_file, $dest_file, $width, $height, $watermark_text);  <br/>
裁剪成功 $ret 为 true，裁剪识别 $ret 为false <br/>
第二种：命令行 <br/>
参数说明： <br/>
-s 原图路径 <br/>
-d 裁剪后的图片保存路径 <br/>
-w 裁剪后的图片宽度 <br/>
-h 裁剪后的图片高度 <br/>
-c 配置文件路径。默认 default path is /usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml <br/>
-t 水印文本 <br/>
-m 打开debug模式 <br/>
./tclip -s a.jpg -d a_dest.jpg -w 400 -h 200 <br/>

贡献者
---------------------
jonnywang [https://github.com/jonnywang](https://github.com/jonnywang) <br/>
