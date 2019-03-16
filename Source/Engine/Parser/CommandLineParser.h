//! @file     CommandLineParser.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// CommandLineArgument
//----------------------------------------------------------------------------

class CommandLineArgument
{
private:
	//!	The argument data
	ICommandLineParser::ArgData	mArgData;

private:
	//!	Check whether starts with key.
	static _ubool StartsWithKey( const _charw* string );

private:
	//!	Build the argument with key name.
	//!	@param		string		The string.
	//!	@return		The next command line string address.
	const _charw* BuildArgumentWithKeyName( const _charw* string );
	//!	Build the argument.
	//!	@param		string		The string.
	//!	@return		The next command line string address.
	const _charw* BuildArgument( const _charw* string );

public:
	CommandLineArgument( );
	~CommandLineArgument( );

public:
	//!	Get the argument data.
	EGE_GET_ACCESSOR_CONST( const ICommandLineParser::ArgData&, ArgData )

public:
	//!	Build the configure data.
	//!	@param		string		The command line string.
	//!	@return		The next command line string address.
	const _charw* Build( const _charw* string );
};

//----------------------------------------------------------------------------
// CommandLineParser
//----------------------------------------------------------------------------

class CommandLineParser : public INTERFACE_OBJECT_IMPL( ICommandLineParser )
{
private:
	typedef Array< CommandLineArgument > ArgumentArray;

private:
	//!	The current index of arguments
	_dword			mCurrentArgumentIndex;
	//!	The arguments
	ArgumentArray	mArguments;

public:
	CommandLineParser( AStringPtr cmdline );
	CommandLineParser( WStringPtr cmdline );
	CommandLineParser( _dword argc, const _chara* argv[] );
	CommandLineParser( _dword argc, const _charw* argv[] );
	CommandLineParser( _dword argc, const _chara* argn[], const _chara* argv[] );
	CommandLineParser( _dword argc, const _charw* argn[], const _charw* argv[] );
	virtual ~CommandLineParser( );

	template< typename Type >
	_ubool					OnReadDwordValue( WStringPtr name, Type& value ) const;
	template< typename Type >
	_ubool					OnReadIntValue( WStringPtr name, Type& value ) const;
	template< typename Type >
	_ubool					OnReadQwordValue( WStringPtr name, Type& value ) const;
	template< typename StringType, typename Type >
	_ubool					OnReadStringValue( WStringPtr name, Type& value ) const;
	template< typename Type >
	_ubool					OnReadFloatValue( WStringPtr name, Type& value ) const;
	template< typename Type >
	_ubool					OnReadDoubleValue( WStringPtr name, Type& value ) const;
	template< typename Type >
	_ubool					OnReadBoolValue( WStringPtr name, Type& value ) const;
	template< typename Type >
	_ubool					OnReadValue( WStringPtr name, Type& value ) const;
// ICommandLineParser Interface
public:
	virtual _void 			Initialize( AStringPtr cmdline ) override;
	virtual _void 			Initialize( WStringPtr cmdline ) override;
	virtual _void 			Initialize( _dword argc, const _chara* argv[] ) override;
	virtual _void 			Initialize( _dword argc, const _charw* argv[] ) override;
	virtual _void			Initialize( _dword argc, const _chara* argn[], const _chara* argv[] ) override;
	virtual _void			Initialize( _dword argc, const _charw* argn[], const _charw* argv[] ) override;

	virtual WStringR		GetString( _dword startindex = 0 ) const override;

	virtual _ubool			HasArgument( WStringPtr name, _ubool ignorecase = _true ) const override;

	virtual _dword			GetArgumentsNumber( ) const override;
	virtual const ArgData*	GetArgumentByIndex( _dword index ) const override;
	virtual const ArgData*	GetArgumentByKeyName( WStringPtr keyname, _ubool ignorecase = _true ) const override;
	virtual _int			GetArgumentValueByKeyName( WStringPtr keyname, _dword radix, _ubool ignorecase = _true ) const override;
	virtual WStringR		GetArgumentStringByKeyName( WStringPtr keyname, _ubool ignorecase = _true ) const override;

	virtual _ubool			BeginGettingArguments( _dword startindex ) override;
	virtual const ArgData*	GetArgument( ) override;
	virtual _void			EndGettingArguments( ) override;

	virtual _ubool			Read( WStringPtr name, _byte& value ) const override;
	virtual _ubool			Read( WStringPtr name, _word& value ) const override;
	virtual _ubool			Read( WStringPtr name, _int& value ) const override;
	virtual _ubool			Read( WStringPtr name, _dword& value ) const override;
	virtual _ubool			Read( WStringPtr name, _qword& value ) const override;
	virtual _ubool			Read( WStringPtr name, _ubool& value ) const override;
	virtual _ubool			Read( WStringPtr name, _float& value ) const override;
	virtual _ubool			Read( WStringPtr name, _double& value ) const override;
	virtual _ubool			Read( WStringPtr name, _time_t& value ) const override;
	virtual _ubool			Read( WStringPtr name, AString& value ) const override;
	virtual _ubool			Read( WStringPtr name, UString& value ) const override;
	virtual _ubool			Read( WStringPtr name, WString& value ) const override;
	virtual _ubool			Read( WStringPtr name, AStringObj& value ) const override;
	virtual _ubool			Read( WStringPtr name, UStringObj& value ) const override;
	virtual _ubool			Read( WStringPtr name, WStringObj& value ) const override;
	virtual _ubool			Read( WStringPtr name, Time& value ) const override;
	virtual _ubool			Read( WStringPtr name, MD5Code& value ) const override;
	virtual _ubool			Read( WStringPtr name, Version& value ) const override;
	virtual _ubool			Read( WStringPtr name, Color& value ) const override;
	virtual _ubool			Read( WStringPtr name, SafeInt& value ) const override;
	virtual _ubool			Read( WStringPtr name, SafeDword& value ) const override;
	virtual _ubool			Read( WStringPtr name, SafeFloat& value ) const override;
	virtual _ubool			Read( WStringPtr name, SafeBool& value ) const override;
	virtual _ubool			Read( WStringPtr name, SafeDouble& value ) const override;
	virtual _ubool			Read( WStringPtr name, SafeLarge& value ) const override;
	virtual _ubool			Read( WStringPtr name, SafeQword& value ) const override;
	virtual _ubool			Read( WStringPtr x_name, WStringPtr y_name, Vector2& vector ) const override;
	virtual _ubool			Read( WStringPtr x_name, WStringPtr y_name, WStringPtr z_name, Vector3& vector ) const override;
	virtual _ubool			Read( WStringPtr x_name, WStringPtr y_name, WStringPtr z_name, WStringPtr w_name, Vector4& vec4 ) const override;
	virtual _ubool			Read( WStringPtr x_name, WStringPtr y_name, WStringPtr z_name, WStringPtr w_name, Quaternion& quaternion ) const override;
	virtual _ubool			Read( WStringPtr px_name, WStringPtr py_name, WStringPtr sx_name, WStringPtr sy_name, WStringPtr rotation_name, Transform2D& transform ) const override;
	virtual _ubool			Read( WStringPtr min_name, WStringPtr max_name, DwordRange& bounds ) const override;
	virtual _ubool			Read( WStringPtr min_name, WStringPtr max_name, FloatRange& bounds ) const override;
	virtual _ubool			Read( WStringPtr r, WStringPtr g, WStringPtr b, WStringPtr a, Color& color ) const override;
};

}