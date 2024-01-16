clear
git commit -am "$(Get-Date -Format "yyyy-MM-dd HH:mm:ss")"
cmake -B build
$Result = cmake --build build

if ($Result.ExitCode -eq 0) {
    .\build\Debug\gpu-collision-detection.exe
}