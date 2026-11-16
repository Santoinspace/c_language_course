@echo off
setlocal
cd /d "%~dp0.."
if not exist "build\CMakeCache.txt" (
  echo [ERROR] First run tools\configure.cmd
  exit /b 1
)
echo [Course] Building with mingw32-make via CMake...
cmake --build build --parallel 4
exit /b %errorlevel%
