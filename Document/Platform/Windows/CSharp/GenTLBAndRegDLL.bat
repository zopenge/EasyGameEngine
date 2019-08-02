set DIR=%~dp0
echo %DIR%
set NET_VER=v4.0.30319
call %DIR%GenTLBFile.bat %1
call %DIR%UnregCSharpDLL.bat %1
call %DIR%RegCSharpDLL.bat %1