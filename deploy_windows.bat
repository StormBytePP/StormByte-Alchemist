@echo OFF

rmdir /s /q build
rmdir /s /q dist
rmdir /s /q deps
mkdir build
mkdir dist
mkdir deps

cd deps
mkdir src
cd src
git clone https://github.com/hyperrealm/libconfig.git
cd ..
mkdir build
mkdir bin
cd build

cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_GENERATOR=Ninja -DCMAKE_INSTALL_PREFIX=..\bin -DBUILD_EXAMPLES=OFF -DBUILD_SHARED_LIBS=OFF -DBUILD_TESTS=OFF ..\src\libconfig
ninja install

cd ..\..\build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_GENERATOR=Ninja -DCMAKE_INSTALL_PREFIX=../dist -DWITH_SYSTEM_JSONCPP=OFF -DWITH_SYSTEM_SQLITE=OFF ..
ninja install
cd ..