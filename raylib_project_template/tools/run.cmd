@echo off
setlocal
cd /d "%~dp0.."
if not exist "build\c_final_project.exe" (
  echo [ERROR] First run tools\configure.cmd and tools\build.cmd
  exit /b 1
)
"build\c_final_project.exe"
exit /b %errorlevel%
