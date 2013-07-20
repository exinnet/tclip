#!/bin/bash
g++ `pkg-config opencv --libs --cflags opencv` tclip.cpp -o tclip