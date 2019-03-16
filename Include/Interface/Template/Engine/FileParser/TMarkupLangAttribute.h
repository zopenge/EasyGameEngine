//! @file     TMarkupLangAttribute.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TMarkupLangAttribute
//----------------------------------------------------------------------------

template< typename Type >
class TMarkupLangAttribute : public Type
{
protected:
	//!	Set the content of attribute.
	virtual _ubool OnSetContentU( UStringPtr content ) PURE;
	virtual _ubool OnSetContentW( WStringPtr content ) PURE;
	//!	Get the content of attribute ( only need the ANSI mode ).
	virtual UStringPtr OnGetContentU( ) const PURE;

	//!	Get the value of attribute.
	virtual _ubool OnGetValue( _ubool& value ) const PURE;
	virtual _ubool OnGetValue( _int& value ) const PURE;
	virtual _ubool OnGetValue( _dword& value ) const PURE;
	virtual _ubool OnGetValue( _large& value ) const PURE;
	virtual _ubool OnGetValue( _qword& value ) const PURE;
	virtual _ubool OnGetValue( _float& value ) const PURE;
	virtual _ubool OnGetValue( _double& value ) const PURE;

protected:
	TMarkupLangAttribute( );
	virtual ~TMarkupLangAttribute( );

// IMarkupLangAttribute Interface
public:
	virtual _ubool		SetBool( _ubool value ) override;
	virtual _ubool 		SetLong( _int value ) override;
	virtual _ubool 		SetDword( _dword value ) override;
	virtual _ubool 		SetLarge( _large value ) override;
	virtual _ubool 		SetQword( _qword value ) override;
	virtual _ubool 		SetDouble( _double value ) override;
	virtual _ubool		SetOword( const MD5Code& value ) override;
	virtual _ubool 		SetString( WStringPtr string ) override;
	virtual _ubool		SetColor( const Color& color ) override;
	virtual _ubool		SetVersion( const Version& version ) override;

	virtual _ubool		GetBool( ) const override;
	virtual _int		GetLong( ) const override;
	virtual _dword		GetDword( ) const override;
	virtual _large		GetLarge( ) const override;
	virtual _qword		GetQword( ) const override;
	virtual _float		GetFloat( ) const override;
	virtual _double		GetDouble( ) const override;
	virtual UStringR	GetStringU( ) const override;
	virtual WStringR	GetStringW( ) const override;
	virtual MD5Code		GetMD5Code( ) const override;
	virtual Color		GetColor( ) const override;
	virtual Version		GetVersion( ) const override;
};

//----------------------------------------------------------------------------
// TMarkupLangAttribute Implementation
//----------------------------------------------------------------------------

template< typename Type >
TMarkupLangAttribute< Type >::TMarkupLangAttribute( )
{
}

template< typename Type >
TMarkupLangAttribute< Type >::~TMarkupLangAttribute( )
{

}

template< typename Type >
_ubool TMarkupLangAttribute< Type >::SetBool( _ubool value )
{
	return OnSetContentU( value ? "true" : "false" );
}

template< typename Type >
_ubool TMarkupLangAttribute< Type >::SetLong( _int value )
{
	_chara value_string[1024];
	Platform::ConvertLongToString( value, 10, value_string, 1024 );

	return OnSetContentU( value_string );
}

template< typename Type >
_ubool TMarkupLangAttribute< Type >::SetDword( _dword value )
{
	_chara value_string[1024];
	Platform::ConvertDwordToString( value, 10, value_string, 1024 );

	return OnSetContentU( value_string );
}

template< typename Type >
_ubool TMarkupLangAttribute< Type >::SetLarge( _large value )
{
	_chara value_string[1024];
	Platform::ConvertLargeToString( value, 10, value_string, 1024 );

	return OnSetContentU( value_string );
}

template< typename Type >
_ubool TMarkupLangAttribute< Type >::SetQword( _qword value )
{
	_chara value_string[1024];
	Platform::ConvertQwordToString( value, 10, value_string, 1024 );

	return OnSetContentU( value_string );
}

template< typename Type >
_ubool TMarkupLangAttribute< Type >::SetDouble( _double value )
{
	_chara value_string[1024];
	Platform::ConvertDoubleToString( value, value_string, 1024 );

	return OnSetContentU( value_string );
}

template< typename Type >
_ubool TMarkupLangAttribute< Type >::SetOword( const MD5Code& value )
{
	_charw value_string[1024];
	value.ToWString( value_string, 1024, _true );

	_charw valuestring_unicode[1024];
	Platform::FormatStringBuffer( valuestring_unicode, 1024, L"%s", value_string );

	_chara valuestring_ansi[1024];
	Platform::Utf16ToUtf8( valuestring_ansi, 1024, valuestring_unicode );
	Platform::UppercaseString( valuestring_ansi );

	return OnSetContentU( valuestring_ansi );
}

template< typename Type >
_ubool TMarkupLangAttribute< Type >::SetString( WStringPtr string )
{
	UString string_utf8;
	string_utf8.FromString( string );

	return OnSetContentU( string_utf8 );
}

template< typename Type >
_ubool TMarkupLangAttribute< Type >::SetColor( const Color& color )
{
	_chara color_string[1024];
	Platform::FormatStringBuffer( color_string, 1024, "%.8x", (_dword) color );
	Platform::UppercaseString( color_string );

	return OnSetContentU( color_string );
}

template< typename Type >
_ubool TMarkupLangAttribute< Type >::SetVersion( const Version& version )
{
	return OnSetContentU( version.ToUString( ) );
}

template< typename Type >
_ubool TMarkupLangAttribute< Type >::GetBool( ) const
{
	_ubool value = _false;
	if ( OnGetValue( value ) == _false )
	{
		// Get value string
		UStringPtr content = OnGetContentU( );
		if ( content.IsEmpty( ) == _false )
		{
			if ( content.IsEqual( "true", _true ) || content == "1" )
				value = _true;
		}
	}

	return value;
}

template< typename Type >
_int TMarkupLangAttribute< Type >::GetLong( ) const
{
	_int value = 0;

	// Get the value string if get value directly failed
	if ( OnGetValue( value ) == _false )
	{
		// Get value string
		UStringPtr content = OnGetContentU( );
		if ( ! content.IsEmpty( ) )
			value = content.ToLong( 10 );
	}

	return value;
}

template< typename Type >
_dword TMarkupLangAttribute< Type >::GetDword( ) const
{
	_dword value = 0;

	// Get the value string if get value directly failed
	if ( OnGetValue( value ) == _false )
	{
		// Get value string
		UStringPtr content = OnGetContentU( );
		if ( ! content.IsEmpty( ) )
			value = content.ToDword( 10 );
	}

	return value;
}

template< typename Type >
_large TMarkupLangAttribute< Type >::GetLarge( ) const
{
	_large value = 0;

	// Get the value string if get value directly failed
	if ( OnGetValue( value ) == _false )
	{
		// Get value string
		UStringPtr content = OnGetContentU( );
		if ( ! content.IsEmpty( ) )
			value = content.ToLarge( 10 );
	}

	return value;
}

template< typename Type >
_qword TMarkupLangAttribute< Type >::GetQword( ) const
{
	_qword value = 0;

	// Get the value string if get value directly failed
	if ( OnGetValue( value ) == _false )
	{
		// Get value string
		UStringPtr content = OnGetContentU( );
		if ( ! content.IsEmpty( ) )
			value = content.ToQword( 10 );
	}

	return value;
}

template< typename Type >
_float TMarkupLangAttribute< Type >::GetFloat( ) const
{
	_float value = 0;

	// Get the value string if get value directly failed
	if ( OnGetValue( value ) == _false )
	{
		// Get value string
		UStringPtr content = OnGetContentU( );
		if ( ! content.IsEmpty( ) )
			value = content.ToFloat( );
	}

	return value;
}

template< typename Type >
_double TMarkupLangAttribute< Type >::GetDouble( ) const
{
	_double value = 0;

	// Get the value string if get value directly failed
	if ( OnGetValue( value ) == _false )
	{
		// Get value string
		UStringPtr content = OnGetContentU( );
		if ( ! content.IsEmpty( ) )
			value = content.ToDouble( );
	}

	return value;
}

template< typename Type >
UStringR TMarkupLangAttribute< Type >::GetStringU( ) const
{
	return OnGetContentU( );
}

template< typename Type >
WStringR TMarkupLangAttribute< Type >::GetStringW( ) const
{
	// Get value string
	UStringPtr content = OnGetContentU( );
	if ( content.IsEmpty( ) )
		return WString( L"" );

	// Convert string to UNICODE
	return WString( ).FromString( content );
}

template< typename Type >
MD5Code TMarkupLangAttribute< Type >::GetMD5Code( ) const
{
	// Get value string
	UStringPtr content = OnGetContentU( );
	if ( content.IsEmpty( ) )
		return MD5Code::cNull;

	MD5Code md5_code;
	if ( md5_code.ParseFromString( content ) == _false )
		return MD5Code::cNull;

	return md5_code;
}

template< typename Type >
Color TMarkupLangAttribute< Type >::GetColor( ) const
{
	// Get value string
	UStringPtr content = OnGetContentU( );
	if ( content.IsEmpty( ) )
		return Color::cNull;

	// Convert string to color by 32 bits unsigned value
	return content.ToDword( 16 );
}

template< typename Type >
Version TMarkupLangAttribute< Type >::GetVersion( ) const
{
	// Get value string
	UStringPtr content = OnGetContentU( );
	if ( content.IsEmpty( ) )
		return Version::cZero;

	return Version( content );
}

}