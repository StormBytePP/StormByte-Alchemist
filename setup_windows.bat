rmdir /s /q build
mkdir build
cd build
cmake -G Ninja -DWITH_SYSTEM_JSONCPP=OFF -DWITH_SYSTEM_SQLITE=OFF ..