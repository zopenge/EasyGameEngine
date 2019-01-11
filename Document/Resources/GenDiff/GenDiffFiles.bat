@echo off
SET FTP_URL=%1 REM ftp://%USERNAME%:%PASSWORD%@%SITE%:%PORT%
SET FTP_RESOURCE_PATH=%2 REM Remote FTP path
SET LATEST_RESOURCE_PATH=%3 REM Local latest resource path
SET MANIFEST_FILENAME=%4 REM Manifest file name
SET CDN_WEBSITE=%5 REM CDN prefix website name
SET TOOL_FILE_CONVERTER_FILE_PATH=%6 REM FTP file converter file path
SET TOOL_FILE_FTP_FILE_PATH=%7 REM FTP upload file path
SET ENCRYPTION_TYPE=%8 REM Encryption type
SET ENCRYPTION_KEY=%9 REM Encryption key

REM Update all resources to latest
set CUR_DIR=%CD%
cd %LATEST_RESOURCE_PATH%
svn revert * -R
svn update
cd %CUR_DIR%

set TEMP_DIR=%CD%\Temp
if NOT exist "%TEMP_DIR%" ( 
md %TEMP_DIR%
)

rem Download the remote manifest file to compare
del %TEMP_DIR%\%MANIFEST_FILENAME% /Q
%TOOL_FILE_FTP_FILE_PATH% -download %FTP_URL% -localpath="%TEMP_DIR%\%MANIFEST_FILENAME%" -remotepath="%FTP_RESOURCE_PATH%/%MANIFEST_FILENAME%" -logfile="%TEMP_DIR%/upload_diff.log" -c2

rem If the remote manifest file is not existing then we need to create empty none
if exist "%TEMP_DIR%\%MANIFEST_FILENAME%" ( 
rem Decrypt the remote manifest file
%TOOL_FILE_CONVERTER_FILE_PATH% Crypto -source="%TEMP_DIR%\%MANIFEST_FILENAME%" -target="%TEMP_DIR%\%MANIFEST_FILENAME%" -type="%ENCRYPTION_TYPE%" -key="%ENCRYPTION_KEY%" /SkipForTextFile
) else ( 
rem Create the temporary manifest file
echo ^<?xml version="1.0" encoding="utf-8"?^> > %TEMP_DIR%\%MANIFEST_FILENAME%
echo ^<Manifest version="0.0.0.0" name=""^> >> %TEMP_DIR%\%MANIFEST_FILENAME%
echo ^</Manifest^> >> %TEMP_DIR%\%MANIFEST_FILENAME%
) 

rem Generate diff folder and diff.txt
rd %TEMP_DIR%\diff /s /q
md %TEMP_DIR%\diff
del %TEMP_DIR%\diff.txt /q
%TOOL_FILE_CONVERTER_FILE_PATH% GenerateDiffManifstFile -manifest_name="%MANIFEST_FILENAME%" -cur_manifest_filepath="%TEMP_DIR%\%MANIFEST_FILENAME%" -prefix_name="%CDN_WEBSITE%" -output_diff_filename="%TEMP_DIR%\diff.txt" -output_diff_dirname="%TEMP_DIR%\diff" -res_dirname="%LATEST_RESOURCE_PATH%" -encryption_type="%ENCRYPTION_TYPE%" -encryption_key="%ENCRYPTION_KEY%"

rem Copy the lastest manifest file to diff folder
copy %LATEST_RESOURCE_PATH%\%MANIFEST_FILENAME% %TEMP_DIR%\diff\%MANIFEST_FILENAME% /Y
echo %CDN_WEBSITE%%MANIFEST_FILENAME% >> "%TEMP_DIR%\diff.txt"
rem Upload diff folder resources
%TOOL_FILE_FTP_FILE_PATH% -upload %FTP_URL% -localpath="%TEMP_DIR%\diff\" -remotepath="%FTP_RESOURCE_PATH%" -logfile="%TEMP_DIR%/upload_diff.log" -c2

rem Check whether need to update.json file
if NOT exist "%TEMP_DIR%\diff\update.json" ( 
goto SHOW_DIFF_TXT
)

rem Upload update.json file
echo %CDN_WEBSITE%update.json >> "%CD%\diff.txt"
%TOOL_FILE_FTP_FILE_PATH% -upload %FTP_URL% -localpath="%TEMP_DIR%\diff\update.json" -remotepath="../%FTP_RESOURCE_PATH%/update.json" -logfile="%TEMP_DIR%/upload_diff.log" -c2

rem Show the diff.txt to copy to CDN website
:SHOW_DIFF_TXT
start "C:\Program Files (x86)\Notepad++\notepad++.exe" "C:\Program Files (x86)\Notepad++\notepad++.exe" "%TEMP_DIR%\diff.txt"