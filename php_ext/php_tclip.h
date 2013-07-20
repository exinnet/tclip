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

#ifndef PHP_TCLIP_H
#define PHP_TCLIP_H

extern zend_module_entry tclip_module_entry;
#define phpext_tclip_ptr &tclip_module_entry

#ifdef PHP_WIN32
#	define PHP_TCLIP_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_TCLIP_API __attribute__ ((visibility("default")))
#else
#	define PHP_TCLIP_API
#endif

extern "C" {
#ifdef ZTS
#include "TSRM.h"
#endif
}

PHP_MINIT_FUNCTION(tclip);
PHP_MSHUTDOWN_FUNCTION(tclip);
PHP_RINIT_FUNCTION(tclip);
PHP_RSHUTDOWN_FUNCTION(tclip);
PHP_MINFO_FUNCTION(tclip);

PHP_FUNCTION(tclip);	/* For testing, remove later. */

/* 
  	Declare any global variables you may need between the BEGIN
	and END macros here:     */

ZEND_BEGIN_MODULE_GLOBALS(tclip)
	//long  global_value;
	void *face_cascade;
	char *face_config_path;
ZEND_END_MODULE_GLOBALS(tclip)


/* In every utility function you add that needs to use variables 
   in php_tclip_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as TCLIP_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define TCLIP_G(v) TSRMG(tclip_globals_id, zend_tclip_globals *, v)
#else
#define TCLIP_G(v) (tclip_globals.v)
#endif

#endif	/* PHP_TCLIP_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
