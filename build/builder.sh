mkdir -p build_temp
cd build_temp
cmake -DCMAKE_BUILD_TYPE=Release ../.. && cmake --build .
