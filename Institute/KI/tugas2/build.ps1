param([switch]$Test)
$ErrorActionPreference = 'Stop'
Push-Location $PSScriptRoot
try {
    New-Item -ItemType Directory -Force -Path build | Out-Null
    $compiler = (Get-Command g++ -ErrorAction Stop).Source
    $flags = @('-std=c++17', '-Wall', '-Wextra', '-Wpedantic', '-Werror', '-O2', '-pthread', '-Iinclude')
    $libraries = @('-static', '-lws2_32', '-lbcrypt')
    & $compiler @flags src/aes.cpp src/protocol.cpp src/network.cpp src/main.cpp -o build/ki_chat.exe @libraries
    if ($LASTEXITCODE -ne 0) { throw 'Application build failed' }
    if ($Test) {
        & $compiler @flags src/aes.cpp src/protocol.cpp tests/unit.cpp -o build/unit_tests.exe @libraries
        if ($LASTEXITCODE -ne 0) { throw 'Test build failed' }
        & ./build/unit_tests.exe
        if ($LASTEXITCODE -ne 0) { throw 'Unit tests failed' }
        python tests/integration.py --binary build/ki_chat.exe
        if ($LASTEXITCODE -ne 0) { throw 'Integration tests failed' }
    }
} finally { Pop-Location }
