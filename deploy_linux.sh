#! /bin/bash

rm -Rf build dist
mkdir build dist

cmake -Bbuild -H. -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_INSTALL_PREFIX=dist -DWITH_SYSTEM_JSONCPP=ON -DWITH_SYSTEM_STORMBYTE=ON
cd build
make install
