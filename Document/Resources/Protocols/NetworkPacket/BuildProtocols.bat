SET PROTOC=..\..\..\..\EasyGameEngine\Source\External\google-protobuf\bin\protoc.exe

mkdir CPP
for %%i in (*.proto) do %PROTOC% --cpp_out=./CPP %%i
