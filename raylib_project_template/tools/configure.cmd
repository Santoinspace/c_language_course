@echo off
REM Generate build/ in the project root; the first run downloads raylib 6.0.
REM This script lives in tools/, so %~dp0.. is the project root.
setlocal
cd /d "%~dp0.."
echo [Course] Configuring with CMake MinGW Makefiles...
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_C_COMPILER=gcc -DCMAKE_BUILD_TYPE=Debug
if errorlevel 1 (
  echo [ERROR] Configuration failed. See docs/QA.md
  exit /b 1
)
echo [OK] Configuration completed.
exit /b 0
