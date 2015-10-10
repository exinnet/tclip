##说明
```
本fork增加了文字水印功能
```

###效果演示请参考原作者
https://github.com/exinnet/tclip

###安装说明
```
opencv-2.4.4 or opencv-2.4.11 见libs文件夹
```
* 请首先安装opencv-2.4.4,如果mac上安装失败，请尝试opencv-2.4.11

###安装步骤
```
yum install gtk+ gtk+-devel pkgconfig libpng zlib libjpeg libtiff cmake
cd opencv-2.4.x
cmake CMakeLists.txt
make
make install

export PKG_CONFIG_PATH=/usr/lib/pkgconfig/:/usr/local/lib/pkgconfig:$PKG_CONFIG_PATH

echo "/usr/local/lib/" > /etc/ld.so.conf.d/opencv.conf 
ldconfig
```
* mac用户请先安装 brew install cmake autoconf libpng pkgconfig 等

###php扩展
```
cd php_ext
phpize
./configure
make
make install
```

###cli
```
cd soft
chmod +x ./tclip.sh
./tclip.sh
```

###使用方法说明

####php
```
$source_file = "/tmp/a.jpg";
$dest_file = "/www/a_dest.jpg";
$width = 400;
$height = 200;
$watermark_text = ""; //可选
$ret = tclip($source_file, $dest_file, $width, $height, $watermark_text);
裁剪成功 $ret 为 true，裁剪失败 $ret 为false
```

####cli
```
Usage: exclip [options] [-s] <source_file> [--] [args...]
-s<path>	the path of source file
-d<path>	the path of destination file
-w<int>		the width of destination file. default value is 300
-h<int>		the height of destination file. default value is 180
-c<path>	the path of config file.
-t<string>	the watermark text.
		default path is /usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml
-m		open debug model
```

###contact
如果你对扩展水印有更多疑问请+qq群 233415606 or [website http://xingqiba.sinaapp.com](http://xingqiba.sinaapp.com)

