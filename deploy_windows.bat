@echo OFF

rmdir /s /q build
rmdir /s /q dist
rmdir /s /q deps
mkdir build
mkdir dist
mkdir deps

git submodule update --init --recursive
git submodule update --recursive --remote

cd build
mkdir libconfig
cd libconfig

cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_GENERATOR=Ninja -DCMAKE_INSTALL_PREFIX=..\..\deps -DBUILD_EXAMPLES=OFF -DBUILD_SHARED_LIBS=OFF -DBUILD_TESTS=OFF ..\..\thirdparty\libconfig
ninja install

cd ..
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_GENERATOR=Ninja -DCMAKE_INSTALL_PREFIX=../dist -DWITH_SYSTEM_JSONCPP=OFF -DWITH_SYSTEM_SQLITE=OFF ..
ninja install
cd ..