@echo OFF

rmdir /s /q build
rmdir /s /q dist
rmdir /s /q thirdparty\libconfig++\dist

mkdir build
mkdir build\libconfig++
mkdir dist
mkdir thirdparty\libconfig++\dist

git submodule update --init --recursive
git submodule update --recursive --remote

cmake -Bbuild\libconfig++ -Hthirdparty\libconfig++\src -DCMAKE_BUILD_TYPE=Release -DCMAKE_GENERATOR=Ninja -DCMAKE_INSTALL_PREFIX=thirdparty\libconfig++\dist -DBUILD_EXAMPLES=OFF -DBUILD_SHARED_LIBS=OFF -DBUILD_TESTS=OFF
cd build\libconfig++
ninja install

cd ..
cmake -B. -H.. -DCMAKE_BUILD_TYPE=Release -DCMAKE_GENERATOR=Ninja -DCMAKE_INSTALL_PREFIX=../dist -DWITH_SYSTEM_JSONCPP=OFF -DWITH_SYSTEM_SQLITE=OFF
ninja install
cd ..