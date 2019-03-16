//! @file     IPlatform.h
//! @author   LiCode
//! @version  1.0.0.547
//! @date     2011/01/07
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IPlatform
//----------------------------------------------------------------------------

class IPlatform : public IObject
{
public:
	//!	Initialize.
	//!	@param		none.
	//!	@return		none.
	virtual _ubool Initialize( ) PURE;
	//!	Finalize.
	//!	@param		none.
	//!	@return		none.
	virtual _void Finalize( ) PURE;

	//!	Get the working directory.
	//!	@param		none.
	//!	@return		The working directory.
	virtual WStringPtr GetWorkingDirectory( ) const PURE;
	//!	Set the working directory.
	//!	@param		working_dir		The working directory.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool SetWorkingDirectory( WStringPtr working_dir ) PURE;

	//!	Add the patch directory.
	//!	@param		patch_dir	The patch directory.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool AddPatchDirectory( WStringPtr patch_dir ) PURE;
	//!	Remove the patch directory.
	//!	@param		patch_dir	The patch directory.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool RemovePatchDirectory( WStringPtr patch_dir ) PURE;

	//!	Get the working archive.
	//!	@param		none.
	//!	@return		The working archive.
	virtual IArchive* GetWorkingArchive( ) PURE;

	//!	Get the device info.
	//!	@param		none.
	//! @return		The device info.
	virtual const PlatformDeviceInfo& GetDeviceInfo( ) PURE;

	//!	Get the (IMSI£ºInternational Mobile Subscriber Identification Number) info.
	//!	@param		none.
	//!	@return		The IMSI string.
	virtual WStringR GetIMSI( ) const PURE;

	//!	Get the current process memory size.
	//!	@param		none.
	//!	@return		The current process memory size.
	virtual _qword GetCurProcessMemSize( ) const PURE;
	//!	Get the total memory size.
	//!	@param		none.
	//!	@return		The total memory size.
	virtual _qword GetTotalMemSize( ) const PURE;

	//!	Clean the temporary directory.
	//!	@remark		All files and directories in the temporary directory will be deleted when application exit or enter.
	//!	@param		none.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool CleanTempDirectory( ) PURE;
	//!	Get the temporary directory.
	//!	@param		none.
	//!	@return		The temporary directory.
	virtual WStringR GetTempDirectory( ) const PURE;
	//!	Create temporary file in temporary directory.
	//!	@param		relative_path	The relative path of temporary directory.
	//!	@param		extension_name	The extension name of unique file.
	//!	@param		buffer			The file buffer data.
	//!	@param		size			The file buffer size.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool CreateTempFileInTempDirectory( WStringPtr relative_path, WStringPtr extension_name, const _byte* buffer, _dword size, WString& filename ) PURE;

	//!	Set the absolute directory.
	//!	@param		path	The directory.
	//!	@return		The absolute directory.
	virtual WStringR GetAbsoluteDirectory( WStringPtr path ) PURE;

	//!	Set the current directory.
	//!	@param		path	The current directory.
	//!	@return		none.
	virtual _void SetCurrentDirectory( WStringPtr path ) PURE;
	//!	Get the current directory.
	//!	@param		none.
	//!	@return		The current directory.
	virtual WStringR GetCurrentDirectory( ) const PURE;
	//!	Set the document directory.
	//!	@param		path	The document directory.
	//!	@return		none.
	virtual _void SetDocumentDirectory( WStringPtr path ) PURE;
	//!	Get the document directory.
	//!	@param		none.
	//!	@return		The document directory.
	virtual WStringR GetDocumentDirectory( ) const PURE;
	//!	Set the internal directory.
	//!	@param		path	The internal directory.
	//!	@return		none.
	virtual _void SetInternalDirectory( WStringPtr path ) PURE;
	//!	Get the internal directory.
	//!	@param		none.
	//!	@return		The internal directory.
	virtual WStringR GetInternalDirectory( ) const PURE;
	//!	Set the external directory.
	//!	@param		path	The external directory.
	//!	@return		none.
	virtual _void SetExternalDirectory( WStringPtr path ) PURE;
	//!	Get the external directory.
	//!	@param		none.
	//!	@return		The external directory.
	virtual WStringR GetExternalDirectory( ) const PURE;

	//!	Check whether it's same file.
	//!	@param		filename_1			The first file name.
	//!	@param		filename_2			The second file name.
	//!	@return		True indicates it's same file otherwise indicates it's different file.
	virtual _ubool IsSameFile( WStringPtr filename_1, WStringPtr filename_2 ) const PURE;

	//!	Get the main screen size.
	//!	@param		none.
	//! @return		The main screen size in pixel.
	virtual PointU GetMainScreenSize( ) const PURE;
	//!	Check whether screen is on or off.
	//!	@param		none.
	//!	@return		True indicates screen is on.
	virtual _ubool IsScreenOn( ) const PURE;

	//!	Open URL.
	//!	@param		url		The URL address.
	//!	@return		none.
	virtual _void OpenURL( WStringPtr url ) PURE;

	//!	Run the process.
	//!	@param		modulename		The module name of launching.
	//!	@param		cmdline			The command line of launching.
	//!	@param		creationflags	The creation flags, @see _PROCESS_CREATION.
	//!	@param		workdir			The working directory.
	//!	@param		nodebugheap		True indicates set the environment '_NO_DEBUG_HEAP' variable to not use the debug heap routines.
	//!	@param		fastmode		True indicates we will run the process without any information collection.
	//!	@param		exit_code		The exit code of process.
	//! @return		True indicates success otherwise indicates failure.
	virtual _ubool RunProcess( WStringPtr modulename, WStringPtr cmdline, _dword creationflags, WStringPtr workdir, _ubool nodebugheap = _true, _ubool fastmode = _false, _dword* exit_code = _null ) PURE;

	//!	Get the language UTF-16 code ranges.
	//!	@param		language		The language type.
	//!	@return		The UTF-16 code ranges.
	virtual Array< DwordRange > GetLanguageUTF16CodeRange( _LANG language ) const PURE;

	//!	Load the system font stream.
	//!	@param		name	The font name.
	//!	@return		The stream reader interface.
	virtual IStreamReaderPassRef LoadSystemFont( WStringPtr name ) PURE;
	//!	Get the system font names list.
	//!	@param		files	The font files.
	//! @return		True indicates success otherwise indicates failure.
	virtual _ubool GetSystemFontFiles( FileInfoArray& files ) PURE;
	//!	Get the system font names list.
	//!	@param		files				The font files.
	//!	@param		utf16_code_range	The UTF-16 code range.
	//!	@param		max_number			The max number of feedback files, -1 indicates unlimited.
	//! @return		True indicates success otherwise indicates failure.
	virtual _ubool GetSystemFontFiles( FileInfoArray& files, const DwordRange& utf16_code_range, _dword max_number = -1 ) PURE;
	//!	Get the system font names list.
	//!	@param		files				The font files.
	//!	@param		utf16_code_ranges	The UTF-16 code ranges.
	//!	@param		max_number			The max number of feedback files, -1 indicates unlimited.
	//! @return		True indicates success otherwise indicates failure.
	virtual _ubool GetSystemFontFiles( FileInfoArray& files, const Array< DwordRange >& utf16_code_ranges, _dword max_number = -1 ) PURE;

	//!	Create web view.
	//!	@param		pos		The view position.
	//!	@param		size	The view size.
	//!	@return		The web view interface.
	virtual IWebViewPassRef CreateWebView( const PointI& pos, const PointI& size ) PURE;
	//!	Create edit box.
	//!	@param		none.
	//!	@return		The edit box interface.
	virtual IEditBoxPassRef CreateEditBox( ) PURE;
	//!	Create message box.
	//!	@param		notifier		The notifier.
	//!	@return		The message box interface.
	virtual IMessageBoxPassRef CreateMessageBox( IMessageBoxNotifier* notifier ) const PURE;

	//!	Create keychain.
	//!	@param		identifier		The identifier.
	//!	@param		access_group	The access group, can be empty.
	//!	@return		The keychain interface.
	virtual IKeychainPassRef CreateKeychain( WStringPtr identifier, WStringPtr access_group ) PURE;

	//!	Vibrate the device.
	//!	@param		duration	The vibrate time in milliseconds.
	//!	@return		none.
	virtual _void Vibrate( _dword duration ) PURE;
	//!	Cancel vibrate the device.
	//!	@param		none.
	//!	@return		none.
	virtual _void CancelVibrate( ) PURE;

	//!	Register/Rename export function.
	//!	@param		path			The class path.
	//!	@param		func_name		The function name.
	//!	@param		func_decl		The function declaration.
	//!	@param		func_pointer	The function pointer.
	//! @return		True indicates success otherwise indicates failure.
	virtual _ubool RegisterExportFunction( AStringPtr path, AStringPtr func_name, AStringPtr func_decl, _void* func_pointer ) PURE;
	
	//!	Run process.
	//!	@param		cmdline			The command line of launching.
	//! @return		True indicates success otherwise indicates failure.
	virtual _ubool RunProcess( WStringPtr cmdline ) PURE;
};

}
