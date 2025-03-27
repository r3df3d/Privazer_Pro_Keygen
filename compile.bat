@echo off
windres resources.rc -O coff -o resources.res
g++ privazer_keygen.cpp resources.res -o privazer_keygen.exe -mwindows -lcomctl32 -luser32 -lgdi32
echo Compilation complete.
pause
