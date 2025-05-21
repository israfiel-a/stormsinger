#!/bin/bash
if [ -z "$2" ]; then
    cmake -B build -DCMAKE_BUILD_TYPE=$1
else
    cmake -B build -DCMAKE_BUILD_TYPE=$1 -DSTORMSINGER_DISABLE_ASAN:BOOL=$2
fi
cd build && cmake --build . --parallel 9 --config $1
cd Stormsinger && ./Stormsinger