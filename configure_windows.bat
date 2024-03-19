@echo off
rmdir /S /Q build 2>null
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_GENERATOR=Ninja -DWITH_SYSTEM_JSONCPP=OFF -DWITH_SYSTEM_SQLITE=OFF -DCMAKE_INSTALL_PREFIX=..\dist\packages\com.StormByte.Alchemist\data\ ..

