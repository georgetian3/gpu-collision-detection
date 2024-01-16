clear
git commit -am "$(Get-Date -Format "yyyy-MM-dd HH:mm:ss")"
cmake -B build
cmake --build build
if ($LastExitCode -eq 0) {
    .\build\Debug\gpu-collision-detection.exe
}