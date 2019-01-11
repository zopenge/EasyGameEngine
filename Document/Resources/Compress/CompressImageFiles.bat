@echo off
call %~dp0..\..\..\SetEnv.bat

SET WORKING_DIR=%CD%

setlocal

for /f "tokens=* delims=" %%i in ('dir %WORKING_DIR%\*.png /a:-d/s/b') do (
%EGE_DIR%EasyGameEngine\Source\External\libwebp\bin\cwebp.exe "%%i" -o "%%i"
)