del "Digit Viewer.sdf"
rd /s /q "ipch\"
rd /s /q "x64\"
rd /s /q "Digit Viewer\x64\"
rd /s /q "Debug\"
rd /s /q "Digit Viewer\Debug\"
rd /s /q "Release\"
rd /s /q "Digit Viewer\Release\"
rd /s /q "x86 SSE2\"
rd /s /q "Digit Viewer\x86 SSE2\"
rd /s /q "x86 SSE4.1\"
rd /s /q "Digit Viewer\x86 SSE4.1\"
rd /s /q "Binaries\"
rd /s /q "Output Files\"
del "Digit Viewer.exe"

cd Launcher
del "Launcher.sdf"
rd /s /q "Debug\"
rd /s /q "Launcher\Debug\"
rd /s /q "Release\"
rd /s /q "Launcher\Release\"

cd ..