# Tclip

[TOC]

## 名字说明

**T开头**，代表是头像识别
**clip**，读[klip]，译为裁剪。
**Tclip**，意为自动头像识别的图片裁剪项目。

## 概要

**用于图片裁剪。有以下特点：**

1. **能进行人脸识别**。图片中有人脸，将自动视为人脸区域为重要区域，将不会被裁剪掉。
2. **自动识别其它重要区域**。如果图片中未识别出人脸，则会根据特征分布计算出重区域。总而言之，自动识别图片中的重要区域，并且在图片裁剪时保留重要区域。
3. **可以加水印**。

## 效果演示

### 人物效果演示

**原图：**

![github](https://raw.github.com/exinnet/tclip/master/demo_images/a1.jpg "github")

**按照从中间截取为 400 * 225 大小大图片，效果如下：**

![github](https://raw.github.com/exinnet/tclip/master/demo_images/a2.jpg "github")

**使用tclip裁剪图片效果如下：**

![github](https://raw.github.com/exinnet/tclip/master/demo_images/a3.jpg "github")


### 景物效果演示

**原图：**

![github](https://raw.github.com/exinnet/tclip/master/demo_images/b1.jpg "github")

**如果按照从中间截取。效果如下：**

![github](https://raw.github.com/exinnet/tclip/master/demo_images/b2.jpg "github")

**使用tclip裁剪图片效果如下：**

![github](https://raw.github.com/exinnet/tclip/master/demo_images/b3.jpg "github")

### 水印效果演示

![github](https://raw.github.com/exinnet/tclip/master/demo_images/a1_dest_watermark.jpg "github")

### 在线演示

**演示地址**：[http://demo.bo56.com/tclip](http://demo.bo56.com/tclip)

## 安装步骤：

> **此扩展依赖于`opencv2.0` 之上版本。因此安装前先安装`opencv2.0`。**

**默认约定：**

1. 软件包现在路径为：`/usr/local/src`;
2. 下载的软件包版本：`opencv-2.4.10.4`, `tclip-1.0.0`

### 安装`opencv2`

> `opencv2` 下载地址： [http://www.bo56.com/tclip人脸识别图片裁剪/#download](http://www.bo56.com/tclip%E4%BA%BA%E8%84%B8%E8%AF%86%E5%88%AB%E5%9B%BE%E7%89%87%E8%A3%81%E5%89%AA/#download)  (建议`opencv2.4.4`版本) 

**安装opencv2依赖**

```
yum install gtk+ gtk+-devel pkgconfig libpng zlib libjpeg libtiff cmake
```

**下载 opencv2 安装包**

```
wget -c -t 0 -O /usr/local/src/opencv.tar.gz https://github.com/Itseez/opencv/archive/2.4.10.4.tar.gz
```

**解压，编译**

```
tar -C /usr/local/src/ /usr/local/src/opencv.tar.gz
cd /usr/local/src/opencv
cmake CMakeLists.txt
make && make install
```

**为opencv设置 `PKG_CONFIG_PATH`**

> 需要在 `/etc/profile` 中 `unset i` 前增加以下一行:
> `export PKG_CONFIG_PATH=/usr/lib/pkgconfig/:/usr/local/lib/pkgconfig:$PKG_CONFIG_PATH`

```
sed -i '/unset i/i export PKG_CONFIG_PATH=/usr/lib/pkgconfig/:/usr/local/lib/pkgconfig:$PKG_CONFIG_PATH' /etc/profile
source /etc/profile
```

**创建 `/etc/ld.so.conf.d/opencv.conf`**

```
echo "/usr/local/lib/" > /etc/ld.so.conf.d/opencv.conf
ldconfig
```

### 安装tclip扩展<br/>

**下载tclip**

```
wget -c -t 0 -O /usr/local/src/tclip.tar.gz https://github.com/exinnet/tclip/archive/1.0.0.tar.gz
```

**解压并进入php_ext目录**

```
tar -C /usr/local/src/ /usr/local/src/tclip.tar.gz
cd /usr/local/src/tclip
```

**编译安装**

```
phpize
./configure --with-php-config=$(which php-config) # $(which php-config) 即php-config的绝对路径
make
make install
```

**进入php配置文件目录修改`php.ini`**

```
cd /path/to/php_ini_file
grep tclip.so php.ini||echo 'extension = tclip.so' >> php.ini
```

**重启php-fpm**

```
/etc/init.d/php-fpm restart
```

### 安装命令行

**如果想在命令行中使用tclip，可以进行如下安装：**

```
cd /usr/local/src/tclip/soft
chmod +x ./tclip.sh
./tclip.sh
\cp tclip /usr/bin/
```

**`tclip`命令行使用方法说明**

1. **在php中使用`tclip`:**

    ```php
    <?php
    /**
     * tclip(文件原路径，裁剪后的图片保存路径，裁剪后的图片宽度，裁剪后的图片高度)
     * 裁剪成功 $ret 为 true，裁剪识别 $ret 为false
     */
    
    $source_file = "/tmp/a.jpg";
    $dest_file = "/www/a_dest.jpg";
    $width = 400;
    $height = 200;
    $watermark_text = ""; //可选
    $ret = tclip($source_file, $dest_file, $width, $height, $watermark_text); 
    ```

2. **在命令行中使用`tclip`:**

    ```
    tclip -s a.jpg -d a_dest.jpg -w 400 -h 200
    
    参数说明：
        -s 原图路径
        -d 裁剪后的图片保存路径
        -w 裁剪后的图片宽度
        -h 裁剪后的图片高度
        -c 配置文件路径。默认 default path is /usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml
        -t 水印文本
        -m 打开debug模式
    ```

## 贡献者

jonnywang [https://github.com/jonnywang](https://github.com/jonnywang)


