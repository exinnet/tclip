<?php

$source_file = "../../demo_images/a1.jpg";
$dest_file = "./a1_dest.jpg";
$width = 400;
$height = 200;
$watermark_text = "xingqiba";
$ret = tclip($source_file, $dest_file, $width, $height, $watermark_text); 
var_dump($ret);
