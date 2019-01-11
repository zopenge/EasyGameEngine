"..\..\..\..\Tools\Output\CodeBuilder.exe" ConfigFile="GenZeroFlareScript.xml" OutputPath=".\GenZeroFlare" DisableSerialization EnableScriptCode GO QUIT 
xcopy .\GenZeroFlare\*.h "..\..\..\..\Framework\Source\ZeroFlare\AppScript\" /Y
xcopy .\GenZeroFlare\*.cpp "..\..\..\..\Framework\Source\ZeroFlare\AppScript\" /Y
