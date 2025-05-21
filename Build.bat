if [%2]==[] goto normal
cmake -B build -DCMAKE_BUILD_TYPE=%1 -DSTORMSINGER_DISABLE_ASAN:BOOL=%2
goto rest
:normal
cmake -B build -DCMAKE_BUILD_TYPE=%1
:rest
cd build && cmake --build . --parallel 9 --config %1
cd Stormsinger\Debug && .\Stormsinger.exe