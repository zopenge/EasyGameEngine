REM call %~dp0..\..\SetEnv.bat

%EGE_DIR%\Tools\Bin\FileConverter.exe ShaderFileToCStringVar -source="./Shaders/DefaultEGE.shader" -target="./Shaders/OpenGL/Shaders.h" -shader_type="GLSL" /IsConvertToCFile