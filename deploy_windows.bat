@echo OFF

rmdir /s /q build
rmdir /s /q dist

mkdir build
mkdir dist

git submodule update --init --recursive
git submodule update --recursive --remote

cd build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_GENERATOR=Ninja -DCMAKE_INSTALL_PREFIX=../dist -DWITH_SYSTEM_JSONCPP=OFF -DWITH_SYSTEM_SQLITE=OFF -DWITH_SYSTEM_CONFIG++=OFF -DCMAKE_WINDOWS_EXPORT_ALL_SYMBOLS=TRUE ..
ninja install

cd ..