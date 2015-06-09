dnl $Id$
dnl config.m4 for extension tclip

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

PHP_ARG_WITH(tclip, for tclip support,
Make sure that the comment is aligned:
[  --with-tclip             Include tclip support])

dnl Otherwise use enable:

if test "$PHP_TCLIP" != "no"; then

  dnl # --with-tclip -> check with-path
  SEARCH_PATH="/usr/lib/pkgconfig /usr/local/lib/pkgconfig"     # you might want to change this
  SEARCH_FOR="opencv.pc"  # you most likely want to change this
  if test -r $PHP_TCLIP/$SEARCH_FOR; then # path given as parameter
     TCLIP_DIR=$PHP_TCLIP
  else # search default path list
     AC_MSG_CHECKING([for opencv.pc file in default path])
     for i in $SEARCH_PATH ; do
       if test -r $i/$SEARCH_FOR; then
         TCLIP_DIR=$i
         AC_MSG_RESULT(found in $i)
       fi
     done
  fi
  dnl
  if test -z "$TCLIP_DIR"; then
     AC_MSG_RESULT([not found])
     AC_MSG_ERROR([does not find opencv.pc])
  fi

  OPENCV_FLAGS="`pkg-config opencv --libs --cflags opencv`"
  opencv_lib_path=""
  for i in $OPENCV_FLAGS;do
        if test ${i:0:2} = "-I" ;then
                PHP_ADD_INCLUDE(${i:2})
        elif test ${i:0:2} = "-L" ;then
                opencv_lib_path=${i:2}
        elif test ${i:${#i}-3} = ".so" ;then
                dir_name=`dirname $i`
                file_name=${i/$dir_name/}
                file_name=${file_name/\/lib/}
                file_name=${file_name/.so/}
		        PHP_ADD_LIBRARY_WITH_PATH($file_name,$dir_name,TCLIP_SHARED_LIBADD)
        elif test ${i:${#i}-6} = ".dylib" ;then
                dir_name=`dirname $i`
                file_name=${i/$dir_name/}
                file_name=${file_name/\/lib/}
                file_name=${file_name/.dylib/}
		        PHP_ADD_LIBRARY_WITH_PATH($file_name,$dir_name,TCLIP_SHARED_LIBADD)
        elif test ${i:0:2} = "-l" ;then 
                file_name=${i:2}
                PHP_ADD_LIBRARY_WITH_PATH($file_name,$opencv_lib_path,TCLIP_SHARED_LIBADD)
	    else
		        AC_MSG_ERROR([no result from pkg-config opencv --libs --cflags opencv])
        fi
  done

  PHP_ADD_LIBRARY(stdc++,"",TCLIP_SHARED_LIBADD)
  PHP_SUBST(TCLIP_SHARED_LIBADD)
  PHP_REQUIRE_CXX()

  PHP_NEW_EXTENSION(tclip, tclip.cpp, $ext_shared)
fi
