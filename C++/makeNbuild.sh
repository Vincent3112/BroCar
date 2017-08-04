#!/bin/bash
echo
echo Running CMAKE to build the makefile
echo 
cd build/
cmake ..
make
mv main ../main
