/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2013 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */
extern "C"{
	#ifdef HAVE_CONFIG_H
	#include "config.h"
	#endif

	#include "php.h"
	#include "php_ini.h"
	#include "ext/standard/info.h"
}

#include "cv.h"  
#include "opencv2/core/core.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/nonfree.hpp"

#include "php_tclip.h"

#include <iostream>
#include <map>
#include <math.h>

using namespace cv;
using namespace std;

/* If you declare any globals in php_tclip.h uncomment this:*/
ZEND_DECLARE_MODULE_GLOBALS(tclip)


/* True global resources - no need for thread safety here */
static int le_tclip;
static CascadeClassifier face_cascade;


/* {{{ tclip_functions[]
 *
 * Every user visible function must have an entry in tclip_functions[].
 */
zend_function_entry tclip_functions[] = {
	PHP_FE(tclip,	NULL)		/* For testing, remove later. */
	{NULL,NULL,NULL}	/* Must be the last line in tclip_functions[] */
};
/* }}} */

/* {{{ tclip_module_entry
 */
zend_module_entry tclip_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"tclip",
	tclip_functions,
	PHP_MINIT(tclip),
	PHP_MSHUTDOWN(tclip),
	PHP_RINIT(tclip),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(tclip),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(tclip),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1", /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_TCLIP
BEGIN_EXTERN_C()
ZEND_GET_MODULE(tclip)
END_EXTERN_C()
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini*/
PHP_INI_BEGIN()
    //STD_PHP_INI_ENTRY("tclip.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_tclip_globals, tclip_globals)
    STD_PHP_INI_ENTRY("tclip.face_config_path", "", PHP_INI_ALL, OnUpdateString, face_config_path, zend_tclip_globals, tclip_globals)
PHP_INI_END()

/* }}} */

/* {{{ php_tclip_init_globals
 */
/* Uncomment this function if you have INI entries*/
static void php_tclip_init_globals(zend_tclip_globals *tclip_globals)
{
	tclip_globals->face_cascade = &face_cascade;
	tclip_globals->face_config_path = NULL;
}

/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(tclip)
{
	/* If you have INI entries, uncomment these lines */
	REGISTER_INI_ENTRIES();
	
	string face_config_path = (TCLIP_G(face_config_path) == "" || TCLIP_G(face_config_path) == NULL)? "/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml" :TCLIP_G(face_config_path);
	if( !face_cascade.load( face_config_path ) ){ 
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "can not load classifier file！%s", face_config_path.c_str());
        return FAILURE; 
    }
	TCLIP_G(face_cascade) = &face_cascade;
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(tclip)
{
	/* uncomment this line if you have INI entries	*/
	UNREGISTER_INI_ENTRIES();

	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(tclip)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(tclip)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(tclip)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "tclip support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini	*/
	DISPLAY_INI_ENTRIES();

}
/* }}} */


int detectFace( Mat &img TSRMLS_DC){
	std::vector<Rect> faces;
    Mat img_gray;
	int face_size;
	int Y;

    cvtColor( img, img_gray, CV_BGR2GRAY );
    equalizeHist( img_gray, img_gray );

	//TSRMLS_FETCH();
	((CascadeClassifier *)TCLIP_G(face_cascade))->detectMultiScale( img_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

	face_size = faces.size();
		
	if ( face_size > 0)
	{
		Y = faces[face_size -1].y - faces[face_size -1].height / 2;
		if ( Y > img.size().height / 2 ) //fix
		{
			return -1;
		} else {
			return Y < 0 ? 0 : Y;
		}
	} else {
		return -1;
	}
}

int detectCharacter( Mat &img TSRMLS_DC){
	int start_x = 0; //特征点X坐标开始位置 
	int end_x = 0; //特征点X坐标结束位置
	int section_index = 0; //Y坐标段数字索引
	map<int,int> section_num; //每个Y坐标段中特征点的数量
	int total = 0; //总共特征点数量
	int avg = 0; //每个Y坐标段的平均特征点数量
	int con_num = 4; //需要连续的阀值 
	int flag = 0;
	int counter = 0;
	int Y = 0;

	vector<KeyPoint> keypoints;

	cv::initModule_nonfree();//使用SIFT/SURF create之前，必须先initModule_<modulename>(); 

	Ptr<FeatureDetector> detector = FeatureDetector::create( "SURF" );

	if( detector.empty())
	{
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Can not create detector or descriptor exstractor or descriptor matcher of given types！");
		return -1;
	}

	start_x = 0;
	end_x = img.size().width;

	detector->detect( img, keypoints );
	for (vector<KeyPoint>::iterator i = keypoints.begin(); i != keypoints.end(); i++)
	{
		if (i->pt.x > start_x && i->pt.x < end_x)
		{
			section_index = (int)ceil(i->pt.y / 10);
			section_num[section_index] = section_num[section_index] + 1;
			total = total + 1;
		}
	}
	avg = total / section_num.size();

	//检测特征点分布是否均匀
	int slice_total = 10 ; 
	int slice_num = section_num.size() / slice_total;
	int slice_counter = 0;
	for (int m = 0; m < slice_total; m++)
	{
		for (int n = m * slice_num; n < (m+1) * slice_num; n++)
		{
			if ( section_num[n] >= avg )
			{
				slice_counter++;
				break;
			}
		}
	}
	if (slice_counter >= slice_total)
	{
		return -1;
	}

	//检测特征点主要分布区域[找最开始连续大于avg的Y]
	for (map<int,int>::iterator i = section_num.begin(); i != section_num.end(); i++)
	{
		if (i->second >= avg && flag == 0)
		{
			counter++;
		} else {
			counter = 0;
		}
		if (counter >= con_num && flag == 0)
		{
			Y = i->first;
			flag = 1;
		}
	}
	if (Y > con_num && Y  < img.size().height / 4)
	{
		return (Y - con_num - 11) * slice_total < 0 ? 0 : (Y - con_num - 11) * slice_total ;//fix
	} else if (Y > con_num){
		return (Y - con_num) * slice_total;
	}
	return Y * slice_total;
}

/* Remove the following function when you have succesfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string tclip(string source_path, string dst_path, int width, int height)
   Return a true/false to confirm that the module is compiled in */
PHP_FUNCTION(tclip)
{
	char *source_path = NULL;
	char *dest_path = NULL;
	int source_len, dest_len;
	int dest_height, dest_width;
	int result = 0;
	Mat image;
	Mat dest_image;
	Size tmp_size;
	float ratio_width = 0;
	float ratio_height = 0;
	float ratio = 0;
	int clip_top = 0;
	int clip_bottom = 0;
	int clip_left = 0;
	int clip_right = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ssll", &source_path, &source_len, &dest_path, &dest_len, &dest_width, &dest_height) == FAILURE) {
		return;
	}

	image = imread( source_path );
    if( !image.data ){
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "fail to load image from %s", source_path);
        RETURN_FALSE;
    }

	if (image.size().width * 3 <= image.size().height)
	{
		ratio = (float)dest_width / image.size().width;
		tmp_size = Size((int)(image.size().width * ratio), (int)(image.size().height * ratio));
		dest_image = Mat(tmp_size, CV_32S);
		resize(image, dest_image, tmp_size);
		clip_top = 0;
		clip_bottom = dest_height - dest_image.size().height;
		clip_left = 0;
		clip_right = 0;
		dest_image.adjustROI(clip_top, clip_bottom, clip_left, clip_right); //Mat& Mat::adjustROI(int dtop, int dbottom, int dleft, int dright)
		imwrite(dest_path, dest_image);
		RETURN_TRUE;
	}

	ratio = (float)300.0 / image.size().width;
	tmp_size = Size((int)(image.size().width * ratio), (int)(image.size().height * ratio));
	dest_image = Mat(tmp_size, CV_32S);
	resize(image, dest_image, tmp_size);

	result = detectFace( dest_image TSRMLS_CC);

	if (result == -1)
	{
    	result = detectCharacter( dest_image TSRMLS_CC);
	}

	result = result == -1 ? -1 : (int)((float)result / ratio);

	ratio_width = (float)dest_width / image.size().width;
	ratio_height = (float)dest_height / image.size().height;
	if (ratio_width > ratio_height)
	{
		ratio = ratio_width;
	}
	else
	{
		ratio = ratio_height;
	}

	result = result == -1 ? -1 : (int)((float)result * ratio);

	tmp_size = Size((int)(image.size().width * ratio), (int)(image.size().height * ratio));
	dest_image = Mat(tmp_size, CV_32S);
	resize(image, dest_image, tmp_size);

	if (ratio_width > ratio_height) //原图片 宽度小于高度
	{
		if (result == -1)
		{
			clip_top = -((dest_image.size().height - dest_height) / 2);
			clip_bottom = clip_top;
		}else {
			if (dest_image.size().height - result >= dest_height)
			{
				clip_top = -result;
				clip_bottom = -(dest_image.size().height - result - dest_height);
			} else {
				clip_top = -(dest_image.size().height - dest_height);
			}
		}
	} else {
		clip_left = -((dest_image.size().width - dest_width) / 2);
		clip_right = clip_left;
	}

	dest_image.adjustROI(clip_top, clip_bottom, clip_left, clip_right); //Mat& Mat::adjustROI(int dtop, int dbottom, int dleft, int dright)

	imwrite(dest_path, dest_image);
	
	RETURN_TRUE;
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
