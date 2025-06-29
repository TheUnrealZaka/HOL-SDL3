@echo off
echo Building Visual Studio 2022 project files...

cd build

echo Running Premake5...
premake5.exe vs2022

if %errorlevel% neq 0 (
    echo Error running Premake5!
    pause
    exit /b %errorlevel%
)

echo Project files generated successfully!
echo Opening solution...

cd ..

for %%f in (*.sln) do (
    echo Found solution file: %%f
    echo Waiting 3 seconds before opening solution...
    timeout /t 3 /nobreak >nul
    echo Opening solution file...
    start %%f
    goto :found
)

echo Solution file not found!
pause

:found