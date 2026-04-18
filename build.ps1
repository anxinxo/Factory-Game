# build.ps1

$src = Get-ChildItem -Recurse -Filter *.cpp | ForEach-Object { $_.FullName }

g++ -std=gnu++17 $src `
    -I"$PSScriptRoot" `
    -ID:/TINHOC/C++_PROJECT/Today_vsCode/LIBS/SFML-2.6.1/include `
    -L"D:/TINHOC/C++_PROJECT/Today_vsCode/LIBS/SFML-2.6.1/lib" `
    -lsfml-graphics -lsfml-window -lsfml-system `
    -o "$PSScriptRoot/bin/main.exe"