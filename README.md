##说明
```
本fork增加了文字水印功能
```
![github](./demo_images/demo_.jpg "裁剪后水印图")
![github](./demo_images/demo.jpg "原始图")

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

高级功能
$watermark_text = array(
   'text'  => 'xingqiba_arr',
   'font'  => 7,   //0-7
   'x'     => $width - 200,
   'y'     => $height - 20,
   'red'   => 100,
   'green' => 50,
   'blue'  => 255,
   'scale' => 0.8,
   'thickness' => 2,
);

$ret = tclip($source_file, $dest_file, $width, $height, $watermark_text);
```

#####font设置范围为0-7，具体请参考
```
#define CV_FONT_HERSHEY_SIMPLEX         0
#define CV_FONT_HERSHEY_PLAIN           1
#define CV_FONT_HERSHEY_DUPLEX          2
#define CV_FONT_HERSHEY_COMPLEX         3
#define CV_FONT_HERSHEY_TRIPLEX         4
#define CV_FONT_HERSHEY_COMPLEX_SMALL   5
#define CV_FONT_HERSHEY_SCRIPT_SIMPLEX  6
#define CV_FONT_HERSHEY_SCRIPT_COMPLEX  7
```


####cli
```
Usage: tclip [options] [-s] <source_file> [--] [args...]
-s<path>	the path of source file
-d<path>	the path of destination file
-w<int>		the width of destination file. default value is 300
-h<int>		the height of destination file. default value is 180
-c<path>	the path of config file.
		default path is /usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml
-t<string>	the watermark text.
-m		open debug model
```

###contact
如果你对扩展水印有更多疑问请+qq群 233415606 or [website http://xingqiba.sinaapp.com](http://xingqiba.sinaapp.com)

