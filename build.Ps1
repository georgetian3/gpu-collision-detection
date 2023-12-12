git commit -am "$(Get-Date -Format "yyyy-MM-dd HH:mm:ss")"
cmake -B build
cmake --build build