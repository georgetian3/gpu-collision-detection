cmake -B build
if [ $? -eq 0 ]; then
    cmake --build build
    if [ $? -eq 0 ]; then
        cd build/realistic-scene
        ./realistic-scene
        cd ../..
    fi
fi