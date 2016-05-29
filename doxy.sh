#!/bin/sh
rm -rf ./doc
rm -rf refman.pdf
doxygen
cd ./doc/latex
make
mv refman.pdf ../../
cd -
