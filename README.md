# tclip

## 名字说明

* `T`开头，代表是头像识别。
* `clip`，读[klip]，译为裁剪。
* `Tclip`，意为自动头像识别的图片裁剪项目。


## 概要

用于图片裁剪，有以下特点： 

1. **能进行人脸识别**。图片中有人脸，将自动视为人脸区域为重要区域，将不会被裁剪掉。
2. **自动识别其它重要区域**。如果图片中未识别出人脸，则会根据特征分布计算出重区域。
总而言之，自动识别图片中的重要区域，并且在图片裁剪时保留重要区域。
3. **可以加水印**。


## 效果演示

### 人物效果演示

* 原图

    ![github](https://raw.github.com/exinnet/tclip/master/demo_images/a1.jpg "github")

* 按照从中间截取为 `400 X 225` 大小大图片。效果如下：

    ![github](https://raw.github.com/exinnet/tclip/master/demo_images/a2.jpg "github")

* 使用`tclip`裁剪图片效果如下：

    ![github](https://raw.github.com/exinnet/tclip/master/demo_images/a3.jpg "github")


### 景物效果演示

* 原图

    ![github](https://raw.github.com/exinnet/tclip/master/demo_images/b1.jpg "github")

* 按照从中间截取。效果如下：

    ![github](https://raw.github.com/exinnet/tclip/master/demo_images/b2.jpg "github")

* 使用`tclip`裁剪图片效果如下：

    ![github](https://raw.github.com/exinnet/tclip/master/demo_images/b3.jpg "github")


### 水印效果

* 加水印效果

    ![github](https://raw.github.com/exinnet/tclip/master/demo_images/a1_dest_watermark.jpg "github")


### 在线演示

演示地址：[http://demo.bo56.com/tclip](http://demo.bo56.com/tclip)


## 安装步骤：

### 源码下载

* opencv下载(建议opencv2.4.4版本) ：
    * http://www.bo56.com/download/opencv2.tar.bz2
    * https://github.com/opencv/opencv/archive/2.4.9.tar.gz
* tclip下载：
    * [http://www.bo56.com/tclip人脸识别图片裁剪/#download](http://www.bo56.com/tclip%E4%BA%BA%E8%84%B8%E8%AF%86%E5%88%AB%E5%9B%BE%E7%89%87%E8%A3%81%E5%89%AA/#download)
    * https://github.com/exinnet/tclip/archive/1.0.0.tar.gz

### 安装`opencv2`

此扩展依赖于`opencv2.0`之上版本。因此安装前先安装`opencv`。

> 步骤如下：

* **安装依赖**

    ```bash
    yum -y install gtk+ gtk+-devel pkgconfig libpng zlib libjpeg libtiff cmake
    ```

* **下载安装 opencv2**

    ```bash
    # 下载
    wget https://github.com/opencv/opencv/archive/2.4.9.tar.gz
    
    # 解压安装包
    tar xvf 2.4.9.tar.gz
    
    # 进入opencv目录
    cd opencv-2.4.9/
    
    # 编译安装
    cmake CMakeLists.txt
    make -j $(cat /proc/cpuinfo|grep processor|wc -l)
    make install
    ```
    
* **设置环境变量**

    ```bash
    cp -p /etc/profile{,.$(date +%F_%T)}
    
    # 在/etc/profile unset i前增加PKG_CONFIG_PATH
    grep '^PKG_CONFIG_PATH' /etc/profile||sed -i '/^unset i/iexport PKG_CONFIG_PATH=/usr/lib/pkgconfig/:/usr/local/lib/pkgconfig:$PKG_CONFIG_PATH' /etc/profile
    source /etc/profile
    
    [[ -f /etc/ld.so.conf.d/opencv.conf ]] && cp -p /etc/ld.so.conf.d/opencv.conf{,.$(date +%F)}
    echo "/usr/local/lib/" > /etc/ld.so.conf.d/opencv.conf
    ldconfig
    ```

### 安装`php-tclip`扩展

```bash
# 下载tclip
wget https://github.com/exinnet/tclip/archive/1.0.0.tar.gz

# 解压
tar xvf 1.0.0.tar.gz

# 进入php_ext
cd tclip-1.0.0/php_ext/

# 编译安装php-tclip
phpize
./configure --with-php-config=/usr/bin/php-config
make
make install

# 拷贝到php扩展目录
cp modules/tclip.so /path/to/extension/

# 修改php.ini 加入tclip
php -m|grep tclip.so||echo 'extension = tclip.so' >> /etc/php.ini

# 重启php-fpm
/etc/init.d/php-fpm restart
```

### 安装命令行

想使用命令行方式，可以进行如下安装

```bash
cd cd tclip-1.0.0/
chmod +x ./tclip.sh 
./tclip.sh
```

## 使用方法说明

### 一、在php中使用格式

> `tclip(文件原路径，裁剪后的图片保存路径，裁剪后的图片宽度，裁剪后的图片高度)`

* 示例：

    ```php
    <?php
    $source_file = "/tmp/a.jpg";
    $dest_file = "/www/a_dest.jpg";
    $width = 400; 
    $height = 200;
    $watermark_text = ""; // 可选
    $ret = tclip($source_file, $dest_file, $width, $height, $watermark_text);
    
    // 裁剪成功 $ret 为 true
    // 裁剪失败 $ret 为 false
    ```
    

### 二、命令行

```bash
参数说明：
    -s 原图路径
    -d 裁剪后的图片保存路径
    -w 裁剪后的图片宽度
    -h 裁剪后的图片高度
    -c 配置文件路径。
       默认配置路径：/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml
    -t 水印文本
    -m 打开debug模式

./tclip -s a.jpg -d a_dest.jpg -w 400 -h 200
```

## 贡献者

* jonnywang [https://github.com/jonnywang](https://github.com/jonnywang)


