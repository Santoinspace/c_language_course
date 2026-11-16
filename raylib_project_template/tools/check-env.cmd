@echo off
REM Check that gcc, mingw32-make, cmake and git are available in PATH.
setlocal
set ERR=0
echo === Course Toolchain Check (Windows CMD / VS Code Terminal) ===
for %%T in (gcc mingw32-make cmake git) do (
    where %%T >nul 2>nul
    if errorlevel 1 (
        echo [MISSING] %%T
        set ERR=1
    ) else (
        echo [OK] %%T
        where %%T
    )
)
echo.
echo === Versions ===
where gcc >nul 2>nul && gcc --version
where mingw32-make >nul 2>nul && mingw32-make --version
where cmake >nul 2>nul && cmake --version
where git >nul 2>nul && git --version
echo.
echo === Optional tools ===
where gdb >nul 2>nul && (echo [OK] gdb debugger) || (echo [OPTIONAL] gdb not detected; F5 debug will not work)
where code >nul 2>nul && (echo [OK] VS Code CLI) || (echo [OPTIONAL] VS Code CLI not on PATH)
if "%ERR%"=="1" (
    echo [ERROR] Required tools are missing from PATH.
    exit /b 1
)
echo [OK] Ready to configure.
exit /b 0
