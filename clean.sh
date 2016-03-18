#! /bin/bash
find ./ -name "CMakeF*" -exec rm -rf {} ';'
find ./ -name "CMakeC*" -exec rm -rf {} ';'
find ./ -name "cmake_install*" -exec rm -rf {} ';'
find ./ -name ".DS_Store" -exec rm -rf {} ';'
find ./ -name "Makefile" -exec rm -rf {} ';'
find ./ -name "moc_*.cpp" -exec rm -rf {} ';'
find ./ -name "*_automoc*" -exec rm -rf {} ';'
find ./ -name "bin" -exec rm -rf {} ';'
rm -rf bin
# Makefile
