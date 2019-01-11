"..\..\..\..\Tools\Output\CodeBuilder.exe" ConfigFile="GenPlatformSerialization.xml" OutputPath=".\GenEGEPlatform" EnableSerialization DisableScriptCode GO QUIT 
xcopy .\GenEGEPlatform\*.h "..\..\..\..\EasyGameEngine\Include\Platform\" /Y
xcopy .\GenEGEPlatform\*.cpp "..\..\..\..\EasyGameEngine\Source\Platform\" /Y

"..\..\..\..\Tools\Output\CodeBuilder.exe" ConfigFile="GenEngineSerialization.xml" OutputPath=".\GenEGEEngine" EnableSerialization DisableScriptCode GO QUIT 
xcopy .\GenEGEEngine\*.h "..\..\..\..\EasyGameEngine\Include\Interface\Engine\" /Y
xcopy .\GenEGEEngine\*.cpp "..\..\..\..\EasyGameEngine\Source\Engine\" /Y

"..\..\..\..\Tools\Output\CodeBuilder.exe" ConfigFile="GenGraphicSerialization.xml" OutputPath=".\GenEGEGraphic" EnableSerialization DisableScriptCode GO QUIT 
xcopy .\GenEGEGraphic\*.h "..\..\..\..\EasyGameEngine\Include\Interface\Module\Graphic\" /Y
xcopy .\GenEGEGraphic\*.cpp "..\..\..\..\EasyGameEngine\Source\Module\Graphic\" /Y

"..\..\..\..\Tools\Output\CodeBuilder.exe" ConfigFile="GenScriptSerialization.xml" OutputPath=".\GenEGEScript" EnableSerialization DisableScriptCode GO QUIT 
xcopy .\GenEGEScript\*.h "..\..\..\..\EasyGameEngine\Include\Interface\Module\Script\" /Y
xcopy .\GenEGEScript\*.cpp "..\..\..\..\EasyGameEngine\Source\Module\Script\" /Y

"..\..\..\..\Tools\Output\CodeBuilder.exe" ConfigFile="GenScriptDebuggerCode.xml" OutputPath=".\GenEGEScript" DisableSerialization EnableScriptCode GO QUIT 
xcopy .\GenEGEScript\*.h "..\..\..\..\EasyGameEngine\Source\Module\Script\script\lua\" /Y
xcopy .\GenEGEScript\*.cpp "..\..\..\..\EasyGameEngine\Source\Module\Script\script\lua\" /Y

"..\..\..\..\Tools\Output\CodeBuilder.exe" ConfigFile="GenFrameworkSerialization.xml" OutputPath=".\GenEGEFramework" EnableSerialization DisableScriptCode GO QUIT 
xcopy .\GenEGEFramework\*.h "..\..\..\..\Framework\Include\Interface\EGEFramework\" /Y
xcopy .\GenEGEFramework\*.cpp "..\..\..\..\Framework\Source\EGEFramework\" /Y

"..\..\..\..\Tools\Output\CodeBuilder.exe" ConfigFile="GenSDKFrameworkRC.xml" OutputPath=".\GenSDKFramework" DisableSerialization DisableScriptCode GO QUIT 
xcopy .\GenSDKFramework\*.h "..\..\..\..\Framework\Source\SDKFramework\" /Y
xcopy .\GenSDKFramework\*.cpp "..\..\..\..\Framework\Source\SDKFramework\" /Y
