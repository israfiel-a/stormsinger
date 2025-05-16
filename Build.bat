cmake -B build -DCMAKE_BUILD_TYPE=%1
cd build && cmake --build . --parallel 9 --config %1
cd Stormsinger\Debug && .\Stormsinger.exe