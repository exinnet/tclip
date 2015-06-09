#!/bin/bash
g++  tclip.cpp `pkg-config opencv --libs --cflags opencv` -o tclip
