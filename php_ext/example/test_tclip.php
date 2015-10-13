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
   'text' => 'xingqiba_arr',
   'font' => 7,   //0-7
   'x' => $width - 200,
   'y' => $height - 20,
   'red' => 100,
   'green' => 50,
   'blue' => 255,
   'thickness' => 2,
   'scale' => 0.8
);
$ret = tclip($source_file, "./a1_dest_arr.jpg", $width, $height, $watermark_cfg); 
var_dump($ret);