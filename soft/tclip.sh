#!/bin/bash


[ -e tclip ] && rm -rf tclip
export PKG_CONFIG_PATH=/usr/lib/pkgconfig/:/usr/local/lib/pkgconfig:$PKG_CONFIG_PATH 
g++  tclip.cpp `pkg-config opencv --libs --cflags opencv` -o tclip
