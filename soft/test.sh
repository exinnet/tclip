#!/bin/sh

if test ! -e "./tclip"; then
  ./tclip.sh
fi

./tclip -s ../demo_images/demo.jpg -d ./demo_.jpg -t "xingqiba" -C "#DD4B54"
