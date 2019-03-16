//! @file     ChromePlatform.h
//! @author   LiCode
//! @version  1.1.0.556
//! @date     2011/01/08
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// Extern Helpful Functions Declarations
//----------------------------------------------------------------------------

//!	Release PP-Var.
EGE_EXTERNAL _void ReleasePPVar( PP_Var* var );
//!	Release PP-Resource.
EGE_EXTERNAL _void ReleasePPResource( PP_Resource* res );

//----------------------------------------------------------------------------
// PP_VarPassRef
//----------------------------------------------------------------------------

class PP_VarPassRef
{
private:
	PP_Var mVar;

public:
	operator PP_Var( ) const
	{
		return mVar;
	}

	bool IsNull( ) const
	{
		return mVar.type == PP_VARTYPE_UNDEFINED;
	}
	bool IsValid( ) const
	{
		return mVar.type != PP_VARTYPE_UNDEFINED;
	}

	const PP_Var* operator -> ( )  const
	{
		return &mVar;
	}
	PP_Var* operator -> ( )
	{
		return &mVar;
	}

public:
	PP_VarPassRef( const PP_Var& var )
	{
		mVar = var;
	}
	~PP_VarPassRef( )
	{
		ReleasePPVar( &mVar );
	}
};

//----------------------------------------------------------------------------
// PP_ResourcePassRef
//----------------------------------------------------------------------------

class PP_ResourcePassRef
{
private:
	PP_Resource	mResource;

public:
	operator PP_Resource( ) const
	{
		return mResource;
	}

	bool IsNull( ) const
	{
		return mResource == 0;
	}
	bool IsValid( ) const
	{
		return mResource != 0;
	}

public:
	PP_ResourcePassRef( PP_Resource res )
	{
		mResource = res;
	}
	~PP_ResourcePassRef( )
	{
		if ( mResource != _null )
			ReleasePPResource( &mResource );
	}
};

//----------------------------------------------------------------------------
// IPP_ResourceModuleNotifier
//----------------------------------------------------------------------------

class IPP_ResourceModuleNotifier
{
public:
	//!	Called before the plugin module is unloaded.
	//!	@param		none.
	//!	@return		none.
	virtual _void OnShutdownModule( ) PURE;

	//! Entry points for the module.
	//!	@param		module_id		The module ID.
	//!	@param		get_browser		The pointer to PPB_GetInterface.
	//!	@return		PP_OK on success, any other value on failure.
	virtual _int OnInitializeModule( PP_Module module_id, PPB_GetInterface get_browser ) PURE;

	//!	Returns an interface pointer for the interface of the given name, or NULL if the interface is not supported.
	//!	@param		interface_name	The name of the interface.
	//!	@return		The pointer to the interface.
	virtual const _void* OnGetInterface( const _chara* interface_name ) PURE;
};

//----------------------------------------------------------------------------
// IPP_ResourceModuleAccess
//----------------------------------------------------------------------------

class IPP_ResourceModuleAccess : public IPP_ResourceModuleNotifier
{
public:
	//!	Get the module.
	//!	@param		none.
	//!	@return		The module.
	virtual PP_Module GetPPModule( ) PURE;
	//!	Get the interface query function pointer.
	//!	@param		none.
	//!	@return		The interface query function pointer.
	virtual PPB_GetInterface GetPPGetInterfaceFunc( ) PURE;
	//!	Get the instance.
	//!	@param		none.
	//!	@return		The instance.
	virtual PP_Instance GetPPInstance( ) PURE;
	//!	Get the file system resource.
	//!	@param		none.
	//!	@return		The resource.
	virtual PP_Resource	GetPPFileSystemRes( ) PURE;
	//!	Get the file IO resource.
	//!	@param		none.
	//!	@return		The resource.
	virtual PP_Resource	GetPPFileIORes( ) PURE;
	//!	Get the message loop resource.
	//!	@param		none.
	//!	@return		The resource.
	virtual PP_Resource	GetPPMessageLoopRes( ) PURE;

	//!	Get the var dictionary interface.
	//!	@param		none.
	//!	@return		The interface.
	virtual const PPB_VarDictionary* GetPPBVarDictionary( ) PURE;
	//!	Get the var array buffer interface.
	//!	@param		none.
	//!	@return		The interface.
	virtual const PPB_VarArrayBuffer* GetPPBVarArrayBuffer( ) PURE;
	//!	Get the input event interface.
	//!	@param		none.
	//!	@return		The interface.
	virtual const PPB_InputEvent* GetPPBInputEvent( ) PURE;
	//!	Get the keyboard input interface.
	//!	@param		none.
	//!	@return		The interface.
	virtual const PPB_KeyboardInputEvent* GetPPBKeyboardInputEvent( ) PURE;
	//!	Get the console interface.
	//!	@param		none.
	//!	@return		The interface.
	virtual const PPB_Console* GetPPBConsole( ) PURE;
	//!	Get the core interface.
	//!	@param		none.
	//!	@return		The interface.
	virtual const PPB_Core* GetPPBCore( ) PURE;
	//!	Get the var interface.
	//!	@param		none.
	//!	@return		The interface.
	virtual const PPB_Var* GetPPBVar( ) PURE;
	//!	Get the graphic 3D interface.
	//!	@param		none.
	//!	@return		The interface.
	virtual const PPB_Graphics3D* GetPPBGraphics3D( ) PURE;
	//!	Get the instance interface.
	//!	@param		none.
	//!	@return		The interface.
	virtual const PPB_Instance*	GetPPBInstance( ) PURE;
	//!	Get the message loop interface.
	//!	@param		none.
	//!	@return		The interface.
	virtual const PPB_MessageLoop* GetPPBMessageLoop( ) PURE;
	//!	Get the messaging interface.
	//!	@param		none.
	//!	@return		The interface.
	virtual const PPB_Messaging* GetPPBMessaging( ) PURE;
	//!	Get the file system interface.
	//!	@param		none.
	//!	@return		The interface.
	virtual const PPB_FileSystem* GetPPBFileSystem( ) PURE;
	//!	Get the file interface.
	//!	@param		none.
	//!	@return		The interface.
	virtual const PPB_FileRef* GetPPBFileRef( ) PURE;
	//!	Get the file IO interface.
	//!	@param		none.
	//!	@return		The interface.
	virtual const PPB_FileIO* GetPPBFileIO( ) PURE;
	//!	Get the URL response info interface.
	//!	@param		none.
	//!	@return		The interface.
	virtual const PPB_URLResponseInfo* GetPPBURLResponseInfo( ) PURE;
	//!	Get the URL request info interface.
	//!	@param		none.
	//!	@return		The interface.
	virtual const PPB_URLRequestInfo* GetPPBURLRequestInfo( ) PURE;
	//!	Get the URL loader interface.
	//!	@param		none.
	//!	@return		The interface.
	virtual const PPB_URLLoader* GetPPBURLLoader( ) PURE;
	//!	Get the image data interface.
	//!	@param		none.
	//!	@return		The interface.
	virtual const PPB_ImageData* GetPPBImageData( ) PURE;
	//!	Get the view interface.
	//!	@param		none.
	//!	@return		The interface.
	virtual const PPB_View* GetPPBView( ) PURE;
	//!	Get the web socket interface.
	//!	@param		none.
	//!	@return		The interface.
	virtual const PPB_WebSocket* GetPPBWebSocket( ) PURE;
};

//----------------------------------------------------------------------------
// IPP_ResourceModule
//----------------------------------------------------------------------------

class IPP_ResourceModule : public IPP_ResourceModuleAccess
{
public:
	//!	Release.
	//!	@param		none.
	//!	@return		none.
	virtual _void Release( ) PURE;
	//!	Initialize.
	//!	@param		module				The PP-Module.
	//!	@param		get_interface_func	The PPB get interface function.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool Initialize( PP_Module module, PPB_GetInterface get_interface_func ) PURE;

	//!	Attach to current thread.
	//!	@param		none.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool AttachToCurrentThread( ) PURE;

	//!	Add PP-Resource ref.
	//!	@param		res		The PP-Resource.
	//!	@return		none.
	virtual _void AddRefResource( PP_Resource res ) PURE;
	//!	Release PP-Resource.
	//!	@param		res		The PP-Resource.
	//!	@return		none.
	virtual _void ReleaseResource( PP_Resource& res ) PURE;

	//!	Create PP-Var.
	//!	@param		none.
	//!	@return		none.
	virtual PP_Var CreateVar( ) PURE;
	//!	Release PP-Var.
	//!	@param		var		The PP-VAR.
	//!	@return		none.
	virtual _void ReleaseVar( PP_Var& var ) PURE;

	//!	Convert bool to PP-VAR type.
	//!	@param		value	The value.
	//!	@return		The PP-VAR.
	virtual PP_VarPassRef BoolToVar( _ubool value ) PURE;
	//!	Convert ANSI string to PP-VAR type.
	//!	@param		str		The string.
	//!	@return		The PP-VAR.
	virtual PP_VarPassRef AnsiToVar( AStringPtr str ) PURE;
	//!	Convert UTF-8 string to PP-VAR type.
	//!	@param		str		The string.
	//!	@return		The PP-VAR.
	virtual PP_VarPassRef Utf8ToVar( UStringPtr str ) PURE;
	//!	Convert UTF-16 string to PP-VAR type.
	//!	@param		str		The string.
	//!	@return		The PP-VAR.
	virtual PP_VarPassRef Utf16ToVar( WStringPtr str ) PURE;

	//!	Build PP-VAR array.
	//!	@param		size	The buffer size.
	//!	@param		buffer	The buffer data.
	//!	@return		The PP-VAR array.
	virtual PP_VarPassRef BuildPPVarArray( _dword size, const _void* buffer ) PURE;
	//!	Map PP-VAR array's buffer data.
	//!	@param		var		The PP-VAR.
	//!	@param		size	The buffer data size.
	//!	@return		The PP-VAR buffer data.
	virtual _void* MapPPVarArrayData( const PP_Var& var, _dword& size ) PURE;
	//!	Unmap PP-VAR array's buffer data.
	//!	@param		var		The PP-VAR.
	//!	@return		none.
	virtual _void UnmapPPVarArrayData( const PP_Var& var ) PURE;

	//!	Convert PP-VAR to ANSI string type.
	//!	@param		var		The PP-VAR.
	//!	@param		str		The string.
	//!	@return		none.
	virtual _void VarToAnsi( const PP_Var& var, AString& str ) PURE;
	//!	Convert PP-VAR to UTF-8 string type.
	//!	@param		var		The PP-VAR.
	//!	@param		str		The string.
	//!	@return		none.
	virtual _void VarToUtf8( const PP_Var& var, UString& str ) PURE;
	//!	Convert PP-VAR to UTF-16 string type.
	//!	@param		var		The PP-VAR.
	//!	@param		str		The string.
	//!	@return		none.
	virtual _void VarToUtf16( const PP_Var& var, WString& str ) PURE;

	//!	Output log to console.
	//!	@param		string	The string to output.
	//!	@return		none.
	virtual _void OutputLog( AStringPtr string ) PURE;
	//!	Output log to console.
	//!	@param		string	The string to output.
	//!	@return		none.
	virtual _void OutputLog( WStringPtr string ) PURE;
};

//!	Get the PP-Resource module.
EGE_EXTERNAL IPP_ResourceModule* GetPPResourceModule( );

}