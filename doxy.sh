#!/bin/sh
rm -rf ./doc
doxygen
cd ./doc/latex
make
cd -
