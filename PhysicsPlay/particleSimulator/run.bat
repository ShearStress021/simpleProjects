@echo off
cmake -B build
if %errorlevel% neq 0 exit /b %errorlevel%
cmake --build build
if %errorlevel% neq 0 exit /b %errorlevel%
build\Debug\particleSimulator.exe
