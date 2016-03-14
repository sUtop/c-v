#! /bin/bash
find ./ -name CMakeFiles* -exec rm -rf {} ';'
find ./ -name cmake_install* -exec rm -rf {} ';'
find ./ -name CMakeCache* -exec rm -rf {} ';'
find ./ -name .DS_Store -exec rm -rf {} ';'
find ./ -name Makefile -exec rm -rf {} ';'

# Makefile
