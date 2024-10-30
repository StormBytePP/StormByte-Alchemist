#! /bin/bash

rm -Rf build dist
mkdir build dist

cmake -Bbuild -H. -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_INSTALL_PREFIX=dist -DWITH_SYSTEM_JSONCPP=OFF -DWITH_SYSTEM_SQLITE=OFF -DCMAKE_VERBOSE_MAKEFILE=1
cd build
make install
