set DIR=%~dp0
echo %DIR%
set NET_VER=v4.2.1
call %DIR%GenTLBFile.bat %1
call %DIR%UnregCSharpDLL.bat %1
call %DIR%RegCSharpDLL.bat %1