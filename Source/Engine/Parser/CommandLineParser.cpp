//! @file     CommandLineParser.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// CommandLineArgument Implementation
//----------------------------------------------------------------------------

CommandLineArgument::CommandLineArgument( )
{

}

CommandLineArgument::~CommandLineArgument( )
{

}

_ubool CommandLineArgument::StartsWithKey( const _charw* string )
{
	EGE_ASSERT( string != _null );

	// The '-' character indicates it's key
	if ( string[0] == '-' )
		return _true;

	// Jump the unused characters
	while ( *string )
	{
		if ( *string != ' ' && *string != '\t' )
			break;

		string ++;
	}

	// Check the '=' character
	while ( *string )
	{
		if ( *string == ' ' || *string == '\t' )
			break;

		if ( *string == '=' )
			return _true;

		string ++;
	}

	return _false;
}

const _charw* CommandLineArgument::BuildArgumentWithKeyName( const _charw* string )
{
	EGE_ASSERT( string != _null );

	// The check flag of ( " ) character
	_ubool checkflag = _true;

	// The string buffer
	_dword	stringbufferindex = 0;
	_charw	stringbuffer[4096]; 

	// Build arguments string
	while ( _true )
	{
		// Get the character
		_charw character = *string;

		// Build the arguments
		if ( checkflag )
		{
			// Build the key name string
			if ( character == '=' )
			{
				// Build the single argument string
				stringbuffer[ stringbufferindex ] = 0;

				// Set the key name string
				mArgData.mKeyName = stringbuffer;
				mArgData.mKeyName.TrimBoth( L" \t\r\n" );

				// Clean the string buffer
				stringbufferindex	= 0;
				stringbuffer[0]		= 0;

				// Jump to the next character
				string ++;

				continue;
			}
			// Build the value string
			else if ( character == ' ' || character == '\t' || character == 0 )
			{
				// Build the single argument string
				stringbuffer[ stringbufferindex ] = 0;

				// Set the value string
				mArgData.mValue = stringbuffer;
				mArgData.mValue.TrimBoth( L" \t\r\n" );

				break;
			}
		}

		// Exchange the check flag by ( " ) character
		if ( character == '\"' )
		{
			checkflag ^= 1;
		}
		// Update the string buffer
		else
		{
			stringbuffer[ stringbufferindex ++ ] = character;
		}

		// Do we reach the tail of string
		if ( string[0] == 0 )
			break;

		// Jump to the next character
		string ++;
	}

	return string;
}

const _charw* CommandLineArgument::BuildArgument( const _charw* string )
{
	EGE_ASSERT( string != _null );

	// It's optional argument
	if ( *string == '/' )
	{
		string ++;
		mArgData.CombineFlags( ICommandLineParser::ArgData::_FLAG_OPTIONAL );
	}

	// The string buffer
	_dword	stringbufferindex = 0;
	_charw	stringbuffer[4096]; 

	// Build arguments string
	while ( _true )
	{
		// Get the character
		_charw character = *string;

		// Build the arguments
		if ( character == ' ' || character == '\t' || character == 0 )
		{
			// Build the single argument string
			stringbuffer[ stringbufferindex ] = 0;

			// Set the argument name
			mArgData.mValue = stringbuffer;
			mArgData.mValue.TrimBoth( L" \t\r\n" );

			break;
		}
		// Update the string buffer
		else
		{
			stringbuffer[ stringbufferindex ++ ] = character;
		}

		// Jump to the next character
		string ++;
	}

	return string;
}

const _charw* CommandLineArgument::Build( const _charw* string )
{
	// Skip for the delimiter characters
	while ( string[0] == ' ' || string[0] == '\t' )
		string ++;

	// Check the command line string
	if ( string[0] != 0 )
	{
		// It's argument with key name
		if ( StartsWithKey( string ) )
		{
			// Jump '-' character
			if ( string[0] == '-' )
				string ++;

			return BuildArgumentWithKeyName( string ); 
		}
		// It's argument without key name
		else
		{
			return BuildArgument( string );
		}
	}

	// Feedback the next command line string address
	return string;
}

//----------------------------------------------------------------------------
// CommandLineParser Implementation
//----------------------------------------------------------------------------

CommandLineParser::CommandLineParser( AStringPtr cmdline )
{
	mCurrentArgumentIndex = -1;

	// Initialize the parser
	Initialize( cmdline );
}

CommandLineParser::CommandLineParser( WStringPtr cmdline )
{
	mCurrentArgumentIndex = -1;

	// Initialize the parser
	Initialize( cmdline );
}

CommandLineParser::CommandLineParser( _dword argc, const _chara* argv[] )
{
	mCurrentArgumentIndex = -1;

	// Initialize the parser
	Initialize( argc, argv );
}

CommandLineParser::CommandLineParser( _dword argc, const _charw* argv[] )
{
	mCurrentArgumentIndex = -1;

	// Initialize the parser
	Initialize( argc, argv );
}

CommandLineParser::CommandLineParser( _dword argc, const _chara* argn[], const _chara* argv[] )
{
	mCurrentArgumentIndex = -1;

	// Initialize the parser
	Initialize( argc, argn, argv );
}

CommandLineParser::CommandLineParser( _dword argc, const _charw* argn[], const _charw* argv[] )
{
	mCurrentArgumentIndex = -1;

	// Initialize the parser
	Initialize( argc, argn, argv );
}

CommandLineParser::~CommandLineParser( )
{

}

_void CommandLineParser::Initialize( AStringPtr cmdline )
{
	Initialize( WString( ).FromString( cmdline ) );
}

_void CommandLineParser::Initialize( WStringPtr cmdline )
{
	// Clear the previous arguments
	mArguments.Clear( );

	// Build the configure data
	while ( cmdline.IsBlank( ) == _false )
	{
		CommandLineArgument argument;
		cmdline = argument.Build( cmdline.Str( ) );

		// Append it into arguments
		mArguments.Append( argument );
	}
}

_void CommandLineParser::Initialize( _dword argc, const _chara* argv[] )
{
	// Clear the previous arguments
	mArguments.Clear( );

	// Build the whole command line string
	_chara cmdlinestring[2048]; cmdlinestring[0] = 0;
	for ( _dword i = 0; i < argc; i ++ )
	{
		Platform::AppendString( cmdlinestring, argv[i] );
		Platform::AppendString( cmdlinestring, " " );
	}

	// Initialize command line string
	Initialize( cmdlinestring );
}

_void CommandLineParser::Initialize( _dword argc, const _charw* argv[] )
{
	// Clear the previous arguments
	mArguments.Clear( );

	// Build the whole command line string
	_charw cmdlinestring[2048]; cmdlinestring[0] = 0;
	for ( _dword i = 0; i < argc; i ++ )
	{
		Platform::AppendString( cmdlinestring, argv[i] );
		Platform::AppendString( cmdlinestring, L" " );
	}

	// Initialize command line string
	Initialize( cmdlinestring );
}

_void CommandLineParser::Initialize( _dword argc, const _chara* argn[], const _chara* argv[] )
{
	// Clear the previous arguments
	mArguments.Clear( );

	// Build the whole command line string
	_chara cmdlinestring[2048]; cmdlinestring[0] = 0;
	for ( _dword i = 0; i < argc; i ++ )
	{
		Platform::AppendString( cmdlinestring, "-" );
		Platform::AppendString( cmdlinestring, argn[i] );
		Platform::AppendString( cmdlinestring, "=" );
		Platform::AppendString( cmdlinestring, argv[i] );
		Platform::AppendString( cmdlinestring, " " );
	}

	// Initialize command line string
	Initialize( cmdlinestring );
}

_void CommandLineParser::Initialize( _dword argc, const _charw* argn[], const _charw* argv[] )
{
	// Clear the previous arguments
	mArguments.Clear( );

	// Build the whole command line string
	_charw cmdlinestring[2048]; cmdlinestring[0] = 0;
	for ( _dword i = 0; i < argc; i ++ )
	{
		Platform::AppendString( cmdlinestring, L"-" );
		Platform::AppendString( cmdlinestring, argn[i] );
		Platform::AppendString( cmdlinestring, L"=" );
		Platform::AppendString( cmdlinestring, argv[i] );
		Platform::AppendString( cmdlinestring, L" " );
	}

	// Initialize command line string
	Initialize( cmdlinestring );
}

WStringR CommandLineParser::GetString( _dword startindex ) const
{
	_charw string[4096]; string[0] = 0;

	for ( _dword i = startindex; i < mArguments.Number( ); i ++ )
	{
		const ArgData& argdata = mArguments[i].GetArgData( );

		// Argument without key name
		if ( argdata.mKeyName.IsEmpty( ) )
		{
			// Optional argument
			if ( argdata.IsOptional( ) )
				Platform::AppendString( string, L"/" );

			Platform::AppendString( string, argdata.mValue.Str( ) );
		}
		// Argument with key name
		else
		{
			Platform::AppendString( string, L"-" );
			Platform::AppendString( string, argdata.mKeyName.Str( ) );
			Platform::AppendString( string, L"=" );
			Platform::AppendString( string, argdata.mValue.Str( ) );
		}

		// Use space character to separate arguments 
		Platform::AppendString( string, L" " );
	}

	return WString( string );
}

_ubool CommandLineParser::HasArgument( WStringPtr name, _ubool ignorecase ) const
{
	for ( _dword i = 0; i < mArguments.Number( ); i ++ )
	{
		const ArgData& argdata = mArguments[i].GetArgData( );

		// It's optional argument
		if ( argdata.IsOptional( ) )
		{
			// Compare the variable name
			if ( argdata.mValue.IsEqual( name, ignorecase ) )
				return _true;
		}
		// It's argument with value and key name
		else
		{
			// Compare the key name
			if ( argdata.mKeyName.IsEqual( name, ignorecase ) )
				return _true;
		}
	}

	return _false;
}

_dword CommandLineParser::GetArgumentsNumber( ) const
{
	return mArguments.Number( );
}

const ICommandLineParser::ArgData* CommandLineParser::GetArgumentByIndex( _dword index ) const
{
	if ( index >= mArguments.Number( ) )
		return _null;

	const ArgData* arg_data = &mArguments[ index ].GetArgData( );
	return arg_data;
}

const ICommandLineParser::ArgData* CommandLineParser::GetArgumentByKeyName( WStringPtr keyname, _ubool ignorecase ) const
{
	for ( _dword i = 0; i < mArguments.Number( ); i ++ )
	{
		const ArgData& argdata = mArguments[i].GetArgData( );

		// Compare the key name
		if ( argdata.mKeyName.IsEqual( keyname, ignorecase ) == _false )
			continue;

		return &argdata;
	}

	return _null;
}

_int CommandLineParser::GetArgumentValueByKeyName( WStringPtr keyname, _dword radix, _ubool ignorecase ) const
{
	const ArgData* arg_data = GetArgumentByKeyName( keyname, ignorecase );
	if ( arg_data == _null )
		return 0;

	return arg_data->GetValue( radix );
}

WStringR CommandLineParser::GetArgumentStringByKeyName( WStringPtr keyname, _ubool ignorecase ) const
{
	const ArgData* arg_data = GetArgumentByKeyName( keyname, ignorecase );
	if ( arg_data == _null )
		return WString( L"" );

	return arg_data->mValue;
}

_ubool CommandLineParser::BeginGettingArguments( _dword startindex )
{
	if ( mArguments.Number( ) == 0 )
		return _true;

	if ( startindex >= mArguments.Number( ) )
		return _false;

	mCurrentArgumentIndex = startindex;

	return _true;
}

const ICommandLineParser::ArgData* CommandLineParser::GetArgument( )
{
	// Parse completed
	if ( mCurrentArgumentIndex >= mArguments.Number( ) )
		return _null;

	// Get the argument data
	const ArgData* argdata = &mArguments[ mCurrentArgumentIndex ].GetArgData( );

	// Update the current argument index
	mCurrentArgumentIndex ++;

	return argdata;
}

_void CommandLineParser::EndGettingArguments( )
{
	mCurrentArgumentIndex = -1;
}

template< typename Type >
_ubool CommandLineParser::OnReadDwordValue( WStringPtr name, Type& value ) const
{
	const ICommandLineParser::ArgData* channel_arg = GetArgumentByKeyName( name );
	if ( channel_arg == _null )
		return _false;
	value = Type( channel_arg->mValue.ToDword( 10 ) );
	return _true;
}

template< typename Type >
_ubool CommandLineParser::OnReadIntValue( WStringPtr name, Type& value ) const
{
	const ICommandLineParser::ArgData* channel_arg = GetArgumentByKeyName( name );
	if ( channel_arg == _null )
		return _false;
	value = Type( channel_arg->mValue.ToLong( 10 ) );
	return _true;
}

template< typename Type >
_ubool CommandLineParser::OnReadQwordValue( WStringPtr name, Type& value ) const
{
	const ICommandLineParser::ArgData* channel_arg = GetArgumentByKeyName( name );
	if ( channel_arg == _null )
		return _false;
	value = Type( channel_arg->mValue.ToQword( 10 ) );
	return _true;
}

template< typename StringType, typename Type >
_ubool CommandLineParser::OnReadStringValue( WStringPtr name, Type& value ) const
{
	const ICommandLineParser::ArgData* channel_arg = GetArgumentByKeyName( name );
	if ( channel_arg == _null )
		return _false;
	value = StringType( ).FromString( channel_arg->mValue );
	return _true;
}

template< typename Type >
_ubool CommandLineParser::OnReadFloatValue( WStringPtr name, Type& value ) const
{
	const ICommandLineParser::ArgData* channel_arg = GetArgumentByKeyName( name );
	if ( channel_arg == _null )
		return _false;
	value = Type( channel_arg->mValue.ToFloat( ) );
	return _true;
}

template< typename Type >
_ubool CommandLineParser::OnReadDoubleValue( WStringPtr name, Type& value ) const
{
	const ICommandLineParser::ArgData* channel_arg = GetArgumentByKeyName( name );
	if ( channel_arg == _null )
		return _false;
	value = Type( channel_arg->mValue.ToDouble( ) );
	return _true;
}

template< typename Type >
_ubool CommandLineParser::OnReadBoolValue( WStringPtr name, Type& value ) const
{
	const ICommandLineParser::ArgData* channel_arg = GetArgumentByKeyName( name );
	if ( channel_arg == _null )
		return _false;
	value = Type( channel_arg->mValue.ToBool( ) );
	return _true;
}

template< typename Type >
_ubool CommandLineParser::OnReadValue( WStringPtr name, Type& value ) const
{
	const ICommandLineParser::ArgData* channel_arg = GetArgumentByKeyName( name );
	if ( channel_arg == _null )
		return _false;
	value = Type( channel_arg->mValue );
	return _true;
}

_ubool CommandLineParser::Read( WStringPtr name, _byte& value ) const
{
	return OnReadDwordValue( name, value );
}

_ubool CommandLineParser::Read( WStringPtr name, _word& value ) const
{
	return OnReadDwordValue( name, value );
}

_ubool CommandLineParser::Read( WStringPtr name, _int& value ) const
{
	return OnReadIntValue( name, value );
}

_ubool CommandLineParser::Read( WStringPtr name, _dword& value ) const
{
	return OnReadDwordValue( name, value );
}

_ubool CommandLineParser::Read( WStringPtr name, _qword& value ) const
{
	return OnReadQwordValue( name, value );
}

_ubool CommandLineParser::Read( WStringPtr name, _ubool& value ) const
{
	return OnReadBoolValue( name, value );
}

_ubool CommandLineParser::Read( WStringPtr name, _float& value ) const
{
	return OnReadFloatValue( name, value );
}

_ubool CommandLineParser::Read( WStringPtr name, _double& value ) const
{
	return OnReadDoubleValue( name, value );
}

_ubool CommandLineParser::Read( WStringPtr name, _time_t& value ) const
{
	return OnReadQwordValue( name, value );
}

_ubool CommandLineParser::Read( WStringPtr name, AString& value ) const
{
	return OnReadStringValue< AString >( name, value );
}

_ubool CommandLineParser::Read( WStringPtr name, UString& value ) const
{
	return OnReadStringValue< UString >( name, value );
}

_ubool CommandLineParser::Read( WStringPtr name, WString& value ) const
{
	return OnReadStringValue< WString >( name, value );
}

_ubool CommandLineParser::Read( WStringPtr name, AStringObj& value ) const
{
	return OnReadStringValue< AString >( name, value );
}

_ubool CommandLineParser::Read( WStringPtr name, UStringObj& value ) const
{
	return OnReadStringValue< UString >( name, value );
}

_ubool CommandLineParser::Read( WStringPtr name, WStringObj& value ) const
{
	return OnReadStringValue< WString >( name, value );
}

_ubool CommandLineParser::Read( WStringPtr name, Time& value ) const
{
	return OnReadValue( name, value );
}

_ubool CommandLineParser::Read( WStringPtr name, MD5Code& value ) const
{
	UString content;
	if ( Read( name, content ) == _false )
		return _false;

	MD5Code md5_code;
	if ( md5_code.ParseFromString( content ) == _false )
		return _false;

	value = md5_code;

	return _true;
}

_ubool CommandLineParser::Read( WStringPtr name, Version& value ) const
{
	return OnReadValue( name, value );
}

_ubool CommandLineParser::Read( WStringPtr name, Color& value ) const
{
	return OnReadDwordValue( name, value );
}

_ubool CommandLineParser::Read( WStringPtr name, SafeInt& value ) const
{
	return OnReadIntValue( name, value );
}

_ubool CommandLineParser::Read( WStringPtr name, SafeDword& value ) const
{
	return OnReadDwordValue( name, value );
}

_ubool CommandLineParser::Read( WStringPtr name, SafeFloat& value ) const
{
	return OnReadFloatValue( name, value );
}

_ubool CommandLineParser::Read( WStringPtr name, SafeBool& value ) const
{
	return OnReadBoolValue( name, value );
}

_ubool CommandLineParser::Read( WStringPtr name, SafeDouble& value ) const
{
	return OnReadDoubleValue( name, value );
}

_ubool CommandLineParser::Read( WStringPtr name, SafeLarge& value ) const
{
	return OnReadQwordValue( name, value );
}

_ubool CommandLineParser::Read( WStringPtr name, SafeQword& value ) const
{
	return OnReadQwordValue( name, value );
}

_ubool CommandLineParser::Read( WStringPtr x_name, WStringPtr y_name, Vector2& vector ) const
{
	Vector2 value = Vector2::cOrigin;

	if ( Read( x_name, value.x ) == _false )
		return _false;

	if ( Read( y_name, value.y ) == _false )
		return _false;

	vector = value;

	return _true;
}

_ubool CommandLineParser::Read( WStringPtr x_name, WStringPtr y_name, WStringPtr z_name, Vector3& vector ) const
{
	Vector3 value = Vector3::cOrigin;

	if ( Read( x_name, value.x ) == _false )
		return _false;

	if ( Read( y_name, value.y ) == _false )
		return _false;

	if ( Read( z_name, value.z ) == _false )
		return _false;

	vector = value;

	return _true;
}

_ubool CommandLineParser::Read( WStringPtr x_name, WStringPtr y_name, WStringPtr z_name, WStringPtr w_name, Vector4& vec4 ) const
{
	Vector4 value = Vector4::cOrigin;

	if ( Read( x_name, value.x ) == _false )
		return _false;

	if ( Read( y_name, value.y ) == _false )
		return _false;

	if ( Read( z_name, value.z ) == _false )
		return _false;

	if ( Read( w_name, value.w ) == _false )
		return _false;

	vec4 = value;

	return _true;
}

_ubool CommandLineParser::Read( WStringPtr x_name, WStringPtr y_name, WStringPtr z_name, WStringPtr w_name, Quaternion& quaternion ) const
{
	Quaternion value = Quaternion::cIdentity;

	if ( Read( x_name, value.x ) == _false )
		return _false;

	if ( Read( y_name, value.y ) == _false )
		return _false;

	if ( Read( z_name, value.z ) == _false )
		return _false;

	if ( Read( w_name, value.w ) == _false )
		return _false;

	quaternion = value;

	return _true;
}

_ubool CommandLineParser::Read( WStringPtr px_name, WStringPtr py_name, WStringPtr sx_name, WStringPtr sy_name, WStringPtr rotation_name, Transform2D& transform ) const
{
	Transform2D value = Transform2D::cZero;

	if ( Read( px_name, py_name, value.mPosition ) == _false )
		return _false;

	if ( Read( sx_name, sy_name, value.mScale ) == _false )
		return _false;

	if ( Read( rotation_name, value.mRadian ) == _false )
		return _false;

	transform = value;

	return _true;
}

_ubool CommandLineParser::Read( WStringPtr min_name, WStringPtr max_name, DwordRange& bounds ) const
{
	DwordRange value = DwordRange::cNull;

	if ( Read( min_name, value.mMinValue ) == _false )
		return _false;

	if ( Read( max_name, value.mMaxValue ) == _false )
		return _false;

	bounds = value;

	return _true;
}

_ubool CommandLineParser::Read( WStringPtr min_name, WStringPtr max_name, FloatRange& bounds ) const
{
	FloatRange value = FloatRange::cNull;

	if ( Read( min_name, value.mMinValue ) == _false )
		return _false;

	if ( Read( max_name, value.mMaxValue ) == _false )
		return _false;

	bounds = value;

	return _true;
}

_ubool CommandLineParser::Read( WStringPtr r, WStringPtr g, WStringPtr b, WStringPtr a, Color& color ) const
{
	Color value = Color::cNull;

	if ( Read( r, value.r ) == _false )
		return _false;

	if ( Read( g, value.g ) == _false )
		return _false;

	if ( Read( b, value.b ) == _false )
		return _false;

	if ( Read( a, value.a ) == _false )
		return _false;

	color = value;

	return _true;
}
