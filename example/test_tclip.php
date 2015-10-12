<?php
$source_file = "../demo_images/a1.jpg";
$width = 400;
$height = 200;
$watermark_text = "tclip";

$ret = tclip($source_file, "./a1_dest_watermark.jpg", $width, $height, $watermark_text); 
var_dump($ret);

$ret = tclip($source_file, "./a1_dest.jpg", $width, $height); 
var_dump($ret);
