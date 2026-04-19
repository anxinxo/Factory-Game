# build.ps1

$ErrorActionPreference = "Stop"

# ===== Paths (relative to project) =====
$ROOT        = $PSScriptRoot
$BIN_DIR     = "$ROOT/bin"
$SFML_INC    = "$ROOT/libs/SFML/include"
$SFML_LIB    = "$ROOT/libs/SFML/lib"
$SFML_BIN    = "$ROOT/libs/SFML/bin"

# ===== Create bin if not exists =====
if (!(Test-Path $BIN_DIR)) {
    New-Item -ItemType Directory -Path $BIN_DIR | Out-Null
}

# ===== Collect all .cpp files =====
$src = Get-ChildItem -Recurse -Filter *.cpp | ForEach-Object { $_.FullName }

Write-Host "Compiling sources..."
g++ -std=gnu++17 $src `
    -I"$ROOT" `
    -I"$SFML_INC" `
    -L"$SFML_LIB" `
    -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio `
    -o "$BIN_DIR/main.exe"

if ($LASTEXITCODE -ne 0) {
    Write-Host "Build failed!" -ForegroundColor Red
    exit 1
}

Write-Host "Copying SFML DLLs..."
Copy-Item "$SFML_BIN/*.dll" -Destination $BIN_DIR -Force

Write-Host "Build successful!" -ForegroundColor Green