#!/bin/bash
echo
echo Running CMAKE to build the makefile
echo 
cd build/
cmake ..
echo
echo Running MAKE to compile and link
echo
make
mv main ../main
doxygen Doxyfile
