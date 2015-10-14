<?php

$source_file = "../../demo_images/demo.jpg";
$width = 400;
$height = 200;
$watermark_text = "xingqiba";

$ret = tclip($source_file, "./a1_dest_watermark.jpg", $width, $height, $watermark_text); 
var_dump($ret);

$ret = tclip($source_file, "./a1_dest_default.jpg", $width, $height); 
var_dump($ret);

$watermark_cfg = array(
   'text' => 'xingqiba',
   //以下参数均可选   
   'font' => 7,   //0-7 默认0
   //左上角坐标0 0
   'x' => $width - 200,  //默认10
   'y' => $height - 20,  //默认高度 - 20
   'color' => '#cc00ff', //默认#ffffff 指定时长度7
   //也可以选用red,green,blue方式分别指定
   'red' => 204,
   'green' => 0,
   'blue' => 255,
   //厚度
   'thickness' => 2,  //默认1
   'scale' => 0.8     //默认0.8
);
$ret = tclip($source_file, "./a1_dest_arr.jpg", $width, $height, $watermark_cfg); 
var_dump($ret);