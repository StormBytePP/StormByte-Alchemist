@echo OFF

rmdir /s /q build
rmdir /s /q dist
mkdir build
mkdir dist

cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_GENERATOR=Ninja -DCMAKE_INSTALL_PREFIX=dist -DWITH_SYSTEM_JSONCPP=OFF -DWITH_SYSTEM_SQLITE=OFF -Bbuild -H.