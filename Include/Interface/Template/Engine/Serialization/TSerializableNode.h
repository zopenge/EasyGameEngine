//! @file     TSerializableNode.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TSerializableNode
//----------------------------------------------------------------------------

template< typename Type >
class TSerializableNode : public Type
{
protected:
	//!	Check whether it's hex mode. 
	_ubool IsHex( UStringPtr string ) const;
	_ubool IsHex( WStringPtr string ) const;

	//!	Get the radix of value.
	template< typename StringPtrType >
	_dword GetRadix( StringPtrType string ) const;
	//!	Convert the string to signed integer value.
	template< typename StringPtrType >
	_int String2Long( StringPtrType string ) const;
	//!	Convert the string to unsigned integer value.
	template< typename StringPtrType >
	_dword String2Dword( StringPtrType string ) const;
	//!	Convert the string to 64-bits signed integer value.
	template< typename StringPtrType >
	_large String2Large( StringPtrType string ) const;
	//!	Convert the string to 64-bits unsigned integer value.
	template< typename StringPtrType >
	_qword String2Qword( StringPtrType string ) const;

protected:
	//!	When get the content string of property.
	virtual _ubool	OnGetPropertyValue( WStringPtr name, AString& content ) PURE;
	virtual _ubool	OnGetPropertyValue( WStringPtr name, UString& content ) PURE;
	virtual _ubool	OnGetPropertyValue( WStringPtr name, WString& content ) PURE;
	virtual _ubool	OnGetPropertyValue( WStringPtr name, _ubool& value ) PURE;
	virtual _ubool	OnGetPropertyValue( WStringPtr name, _int& value ) PURE;
	virtual _ubool	OnGetPropertyValue( WStringPtr name, _dword& value ) PURE;
	virtual _ubool	OnGetPropertyValue( WStringPtr name, _large& value ) PURE;
	virtual _ubool	OnGetPropertyValue( WStringPtr name, _qword& value ) PURE;
	virtual _ubool	OnGetPropertyValue( WStringPtr name, _double& value ) PURE;

	//!	When set the content string of property.
	virtual _ubool	OnSetPropertyValue( WStringPtr name, AStringPtr content ) PURE;
	virtual _ubool	OnSetPropertyValue( WStringPtr name, UStringPtr content ) PURE;
	virtual _ubool	OnSetPropertyValue( WStringPtr name, WStringPtr content ) PURE;
	virtual _ubool	OnSetPropertyValue( WStringPtr name, _ubool value ) PURE;
	virtual _ubool	OnSetPropertyValue( WStringPtr name, _int value ) PURE;
	virtual _ubool	OnSetPropertyValue( WStringPtr name, _dword value ) PURE;
	virtual _ubool	OnSetPropertyValue( WStringPtr name, _large value ) PURE;
	virtual _ubool	OnSetPropertyValue( WStringPtr name, _qword value ) PURE;
	virtual _ubool	OnSetPropertyValue( WStringPtr name, _double value ) PURE;

	template< typename SafeValueType >
	_ubool ReadSafeValueType( WStringPtr name, SafeValueType& value );

protected:
	TSerializableNode( );
	virtual ~TSerializableNode( );

// ISerializableNode Interface
public:
	virtual _ubool	Read( WStringPtr name, _byte& value ) override; 
	virtual _ubool	Read( WStringPtr name, _word& value ) override;
	virtual _ubool	Read( WStringPtr name, _int& value ) override;
	virtual _ubool	Read( WStringPtr name, _dword& value ) override;
	virtual _ubool	Read( WStringPtr name, _large& value ) override;
	virtual _ubool	Read( WStringPtr name, _qword& value ) override;
	virtual _ubool	Read( WStringPtr name, _ubool& value ) override;
	virtual _ubool	Read( WStringPtr name, _float& value ) override;
	virtual _ubool	Read( WStringPtr name, _double& value ) override;
	virtual _ubool	Read( WStringPtr name, _charw& value ) override;
	virtual _ubool	Read( WStringPtr name, AString& value ) override;
	virtual _ubool	Read( WStringPtr name, UString& value ) override;
	virtual _ubool	Read( WStringPtr name, WString& value ) override;
	virtual _ubool	Read( WStringPtr name, AStringObj& value ) override;
	virtual _ubool	Read( WStringPtr name, UStringObj& value ) override;
	virtual _ubool	Read( WStringPtr name, WStringObj& value ) override;
	virtual _ubool	Read( WStringPtr name, Time& value ) override;
	virtual _ubool	Read( WStringPtr name, MD5Code& value ) override;
	virtual _ubool	Read( WStringPtr name, Version& value ) override;
	virtual _ubool	Read( WStringPtr name, Color& value ) override;
	virtual _ubool	Read( WStringPtr name, SafeInt& value ) override;
	virtual _ubool	Read( WStringPtr name, SafeDword& value ) override;
	virtual _ubool	Read( WStringPtr name, SafeFloat& value ) override;
	virtual _ubool	Read( WStringPtr name, SafeBool& value ) override;
	virtual _ubool	Read( WStringPtr name, SafeDouble& value ) override;
	virtual _ubool	Read( WStringPtr name, SafeLarge& value ) override;
	virtual _ubool	Read( WStringPtr name, SafeQword& value ) override;
	virtual _ubool	Read( WStringPtr x_name, WStringPtr y_name, Vector2& vector ) override;
	virtual _ubool	Read( WStringPtr x_name, WStringPtr y_name, WStringPtr z_name, Vector3& vector ) override;
	virtual _ubool	Read( WStringPtr x_name, WStringPtr y_name, WStringPtr z_name, WStringPtr w_name, Vector4& vec4 ) override;
	virtual _ubool	Read( WStringPtr x_name, WStringPtr y_name, WStringPtr z_name, WStringPtr w_name, Quaternion& quaternion ) override;
	virtual _ubool	Read( WStringPtr px_name, WStringPtr py_name, WStringPtr sx_name, WStringPtr sy_name, WStringPtr rotation_name, Transform2D& transform ) override;
	virtual _ubool	Read( WStringPtr min_name, WStringPtr max_name, DwordRange& bounds ) override;
	virtual _ubool	Read( WStringPtr min_name, WStringPtr max_name, FloatRange& bounds ) override;
	virtual _ubool	Read( WStringPtr r, WStringPtr g, WStringPtr b, WStringPtr a, Color& color ) override;
	virtual _ubool	ReadTime( WStringPtr name, _time_t& value ) override;
	virtual _ubool	ReadFlag( WStringPtr name, _dword flag_value_to_combine, FlagsObject& flags ) override;
	virtual _ubool	ReadFlags( WStringPtr name, FlagsObject& flags ) override;
	virtual _ubool 	ReadFlags( WStringPtr name, FlagsObject& flags, ISerializableNode::OnQueryEnumValue funcpointer ) override;

	virtual _ubool	Write( WStringPtr name, _int value ) override;
	virtual _ubool	Write( WStringPtr name, _dword value ) override;
	virtual _ubool	Write( WStringPtr name, _large value ) override;
	virtual _ubool	Write( WStringPtr name, _qword value ) override;
	virtual _ubool	Write( WStringPtr name, _boolean value ) override;
	virtual _ubool	Write( WStringPtr name, _float value ) override;
	virtual _ubool	Write( WStringPtr name, _double value ) override;
	virtual _ubool	Write( WStringPtr name, _charw value ) override;
	virtual _ubool	Write( WStringPtr name, const _chara* value ) override;
	virtual _ubool	Write( WStringPtr name, const _charw* value ) override;
	virtual _ubool	Write( WStringPtr name, AStringPtr value ) override;
	virtual _ubool	Write( WStringPtr name, UStringPtr value ) override;
	virtual _ubool	Write( WStringPtr name, WStringPtr value ) override;
	virtual _ubool	Write( WStringPtr name, const AStringR& value ) override;
	virtual _ubool	Write( WStringPtr name, const UStringR& value ) override;
	virtual _ubool	Write( WStringPtr name, const WStringR& value ) override;
	virtual _ubool	Write( WStringPtr name, const AStringObj& value ) override;
	virtual _ubool	Write( WStringPtr name, const UStringObj& value ) override;
	virtual _ubool	Write( WStringPtr name, const WStringObj& value ) override;
	virtual _ubool	Write( WStringPtr name, const Time& value ) override;
	virtual _ubool	Write( WStringPtr name, const MD5Code& value ) override;
	virtual _ubool	Write( WStringPtr name, const Version& value ) override;
	virtual _ubool	Write( WStringPtr name, const Color& value ) override;
	virtual _ubool	Write( WStringPtr x_name, WStringPtr y_name, const Vector2& vector ) override;
	virtual _ubool	Write( WStringPtr x_name, WStringPtr y_name, WStringPtr z_name, const Vector3& vector ) override;
	virtual _ubool	Write( WStringPtr x_name, WStringPtr y_name, WStringPtr z_name, WStringPtr w_name, const Vector4& vec4 ) override;
	virtual _ubool	Write( WStringPtr x_name, WStringPtr y_name, WStringPtr z_name, WStringPtr w_name, const Quaternion& quaternion ) override;
	virtual _ubool	Write( WStringPtr px_name, WStringPtr py_name, WStringPtr sx_name, WStringPtr sy_name, WStringPtr rotation_name, const Transform2D& transform ) override;
	virtual _ubool	Write( WStringPtr min_name, WStringPtr max_name, const DwordRange& bounds ) override;
	virtual _ubool	Write( WStringPtr min_name, WStringPtr max_name, const FloatRange& bounds ) override;
	virtual _ubool	Write( WStringPtr r, WStringPtr g, WStringPtr b, WStringPtr a, const Color& color ) override;
	virtual _ubool	WriteTime( WStringPtr name, _time_t value ) override;
	virtual _ubool	WriteFlag( WStringPtr name, _dword flag_value_to_check, const FlagsObject& flags ) override;
	virtual _ubool	WriteFlags( WStringPtr name, const FlagsObject& flags ) override;
	virtual _ubool 	WriteFlags( WStringPtr name, const FlagsObject& flags, ISerializableNode::OnQueryEnumName funcpointer ) override;
};

//----------------------------------------------------------------------------
// TSerializableNode Implementation
//----------------------------------------------------------------------------

template< typename Type >
TSerializableNode< Type >::TSerializableNode( )
{

}

template< typename Type >
TSerializableNode< Type >::~TSerializableNode( )
{

}

template< typename Type >
_ubool TSerializableNode< Type >::IsHex( UStringPtr string ) const
{
	return string.StartsWith( "0x", _true );
}

template< typename Type >
_ubool TSerializableNode< Type >::IsHex( WStringPtr string ) const
{
	return string.StartsWith( L"0x", _true );
}

template< typename Type >
template< typename StringPtrType >
_dword TSerializableNode< Type >::GetRadix( StringPtrType string ) const
{
	return IsHex( string ) ? 16 : 10;
}

template< typename Type >
template< typename StringPtrType >
_int TSerializableNode< Type >::String2Long( StringPtrType string ) const
{
	_dword radix = GetRadix( string );
	if ( radix == 16 )
		string = string.SubString( 2 ); // Jump the "0x" prefix string

	return string.ToLong( radix );
}

template< typename Type >
template< typename StringPtrType >
_dword TSerializableNode< Type >::String2Dword( StringPtrType string ) const
{
	_dword radix = GetRadix( string );
	if ( radix == 16 )
		string = string.SubString( 2 ); // Jump the "0x" prefix string

	return string.ToDword( radix );
}

template< typename Type >
template< typename StringPtrType >
_large TSerializableNode< Type >::String2Large( StringPtrType string ) const
{
	_dword radix = GetRadix( string );
	if ( radix == 16 )
		string = string.SubString( 2 ); // Jump the "0x" prefix string

	return string.ToLarge( radix );
}

template< typename Type >
template< typename StringPtrType >
_qword TSerializableNode< Type >::String2Qword( StringPtrType string ) const
{
	_dword radix = GetRadix( string );
	if ( radix == 16 )
		string = string.SubString( 2 ); // Jump the "0x" prefix string

	return string.ToQword( radix );
}

template< typename Type >
_ubool TSerializableNode< Type >::Read( WStringPtr name, _byte& value )
{
	_int content_value = 0;
	if ( OnGetPropertyValue( name, content_value ) )
	{
		value = content_value;
	}
	else
	{
		UString content;
		if ( OnGetPropertyValue( name, content ) == _false )
			return _false;

		value = (_byte) String2Dword( content );
	}

	return _true;
}

template< typename Type >
_ubool TSerializableNode< Type >::Read( WStringPtr name, _word& value )
{
	_int content_value = 0;
	if ( OnGetPropertyValue( name, content_value ) )
	{
		value = content_value;
	}
	else
	{
		UString content;
		if ( OnGetPropertyValue( name, content ) == _false )
			return _false;

		value = (_word) String2Dword( content );
	}

	return _true;
}

template< typename Type >
_ubool TSerializableNode< Type >::Read( WStringPtr name, _int& value )
{
	_int content_value = 0;
	if ( OnGetPropertyValue( name, content_value ) )
	{
		value = content_value;
	}
	else
	{
		UString content;
		if ( OnGetPropertyValue( name, content ) == _false )
			return _false;

		value = String2Long( content );
	}

	return _true;
}

template< typename Type >
_ubool TSerializableNode< Type >::Read( WStringPtr name, _dword& value )
{
	_dword content_value = 0;
	if ( OnGetPropertyValue( name, content_value ) )
	{
		value = content_value;
	}
	else
	{
		UString content;
		if ( OnGetPropertyValue( name, content ) == _false )
			return _false;

		value = String2Dword( content );
	}

	return _true;
}

template< typename Type >
_ubool TSerializableNode< Type >::Read( WStringPtr name, _large& value )
{
	_large content_value = 0;
	if ( OnGetPropertyValue( name, content_value ) )
	{
		value = content_value;
	}
	else
	{
		UString content;
		if ( OnGetPropertyValue( name, content ) == _false )
			return _false;

		value = String2Large( content );
	}

	return _true;
}

template< typename Type >
_ubool TSerializableNode< Type >::Read( WStringPtr name, _qword& value )
{
	_qword content_value = 0;
	if ( OnGetPropertyValue( name, content_value ) )
	{
		value = content_value;
	}
	else
	{
		UString content;
		if ( OnGetPropertyValue( name, content ) == _false )
			return _false;

		value = String2Qword( content );
	}

	return _true;
}

template< typename Type >
_ubool TSerializableNode< Type >::Read( WStringPtr name, _ubool& value )
{
	_ubool content_value = _false;
	if ( OnGetPropertyValue( name, content_value ) )
	{
		value = content_value;
	}
	else
	{
		UString content;
		if ( OnGetPropertyValue( name, content ) == _false )
			return _false;

		if ( content.IsEqual( "true", _true ) || Platform::ConvertStringToDword( content.Str( ), 10 ) != 0 )
			value = _true;
		else if ( content.IsEqual( "false", _true ) || Platform::ConvertStringToDword( content.Str( ), 10 ) == 0 )
			value = _false;
	}

	return _true;
}

template< typename Type >
_ubool TSerializableNode< Type >::Read( WStringPtr name, _float& value )
{
	_double content_value = 0;
	if ( OnGetPropertyValue( name, content_value ) )
	{
		value = (_float) content_value;
	}
	else
	{
		UString content;
		if ( OnGetPropertyValue( name, content ) == _false )
			return _false;

		value = content.ToFloat( );
	}

	return _true;
}

template< typename Type >
_ubool TSerializableNode< Type >::Read( WStringPtr name, _double& value )
{
	_double content_value = 0;
	if ( OnGetPropertyValue( name, content_value ) )
	{
		value = content_value;
	}
	else
	{
		UString content;
		if ( OnGetPropertyValue( name, content ) == _false )
			return _false;

		value = content.ToDouble( );
	}

	return _true;
}

template< typename Type >
_ubool TSerializableNode< Type >::Read( WStringPtr name, _charw& value )
{
	WString string;
	if ( OnGetPropertyValue( name, string ) == _false )
		return _false;

	if ( string.GetLength( ) != 1 )
		return _false;

	value = string[0];

	return _true;
}

template< typename Type >
_ubool TSerializableNode< Type >::Read( WStringPtr name, AString& value )
{
	return OnGetPropertyValue( name, value );
}

template< typename Type >
_ubool TSerializableNode< Type >::Read( WStringPtr name, UString& value )
{
	return OnGetPropertyValue( name, value );
}

template< typename Type >
_ubool TSerializableNode< Type >::Read( WStringPtr name, WString& value )
{
	return OnGetPropertyValue( name, value );
}

template< typename Type >
_ubool TSerializableNode< Type >::Read( WStringPtr name, AStringObj& value )
{
	AString content;
	if ( OnGetPropertyValue( name, content ) == _false )
		return _false;

	value = content;

	return _true;
}

template< typename Type >
_ubool TSerializableNode< Type >::Read( WStringPtr name, UStringObj& value )
{
	UString content;
	if ( OnGetPropertyValue( name, content ) == _false )
		return _false;

	value = content;

	return _true;
}

template< typename Type >
_ubool TSerializableNode< Type >::Read( WStringPtr name, WStringObj& value )
{
	WString content;
	if ( OnGetPropertyValue( name, content ) == _false )
		return _false;

	value = content;

	return _true;
}

template< typename Type >
_ubool TSerializableNode< Type >::Read( WStringPtr name, Time& value )
{
	UString content;
	if ( OnGetPropertyValue( name, content ) == _false )
		return _false;

	value = Time( content );

	return _true;
}

template< typename Type >
_ubool TSerializableNode< Type >::Read( WStringPtr name, MD5Code& value )
{
	UString content;
	if ( OnGetPropertyValue( name, content ) == _false )
		return _false;

	MD5Code md5_code;
	if ( md5_code.ParseFromString( content ) == _false )
		return _false;

	value = md5_code;

	return _true;
}

template< typename Type >
_ubool TSerializableNode< Type >::Read( WStringPtr name, Version& value )
{
	UString content;
	if ( OnGetPropertyValue( name, content ) == _false )
		return _false;

	value = Version( content );

	return _true;
}

template< typename Type >
_ubool TSerializableNode< Type >::Read( WStringPtr name, Color& value )
{
	_dword color = 0;
	if ( Read( name, color ) == _false )
		return _false;

	value = Color( color );

	return _true;
}

template< typename Type >
template< typename SafeValueType >
_ubool TSerializableNode< Type >::ReadSafeValueType( WStringPtr name, SafeValueType& value )
{
	typename SafeValueType::SafeValueFromValueType _value = 0;
	if ( Read( name, _value ) == _false )
		return _false;

	value = _value;
	return _true;
}

template< typename Type >
_ubool TSerializableNode< Type >::Read( WStringPtr name, SafeInt& value )
{
	return ReadSafeValueType( name, value );
}

template< typename Type >
_ubool TSerializableNode< Type >::Read( WStringPtr name, SafeDword& value )
{
	return ReadSafeValueType( name, value );
}

template< typename Type >
_ubool TSerializableNode< Type >::Read( WStringPtr name, SafeFloat& value )
{
	return ReadSafeValueType( name, value );
}

template< typename Type >
_ubool TSerializableNode< Type >::Read( WStringPtr name, SafeBool& value )
{
	return ReadSafeValueType( name, value );
}

template< typename Type >
_ubool TSerializableNode< Type >::Read( WStringPtr name, SafeDouble& value )
{
	return ReadSafeValueType( name, value );
}

template< typename Type >
_ubool TSerializableNode< Type >::Read( WStringPtr name, SafeLarge& value )
{
	return ReadSafeValueType( name, value );
}

template< typename Type >
_ubool TSerializableNode< Type >::Read( WStringPtr name, SafeQword& value )
{
	return ReadSafeValueType( name, value );
}

template< typename Type >
_ubool TSerializableNode< Type >::Read( WStringPtr x_name, WStringPtr y_name, Vector2& vector )
{
	Vector2 value = Vector2::cOrigin;

	if ( Read( x_name, value.x ) == _false )
		return _false;

	if ( Read( y_name, value.y ) == _false )
		return _false;

	vector = value;

	return _true;
}

template< typename Type >
_ubool TSerializableNode< Type >::Read( WStringPtr x_name, WStringPtr y_name, WStringPtr z_name, Vector3& vector )
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

template< typename Type >
_ubool TSerializableNode< Type >::Read( WStringPtr x_name, WStringPtr y_name, WStringPtr z_name, WStringPtr w_name, Vector4& vec4 )
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

template< typename Type >
_ubool TSerializableNode< Type >::Read( WStringPtr x_name, WStringPtr y_name, WStringPtr z_name, WStringPtr w_name, Quaternion& quaternion )
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

template< typename Type >
_ubool TSerializableNode< Type >::Read( WStringPtr px_name, WStringPtr py_name, WStringPtr sx_name, WStringPtr sy_name, WStringPtr rotation_name, Transform2D& transform )
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

template< typename Type >
_ubool TSerializableNode< Type >::Read( WStringPtr min_name, WStringPtr max_name, DwordRange& bounds )
{
	DwordRange value = DwordRange::cNull;

	if ( Read( min_name, value.mMinValue ) == _false )
		return _false;

	if ( Read( max_name, value.mMaxValue ) == _false )
		return _false;

	bounds = value;

	return _true;
}

template< typename Type >
_ubool TSerializableNode< Type >::Read( WStringPtr min_name, WStringPtr max_name, FloatRange& bounds )
{
	FloatRange value = FloatRange::cNull;

	if ( Read( min_name, value.mMinValue ) == _false )
		return _false;

	if ( Read( max_name, value.mMaxValue ) == _false )
		return _false;

	bounds = value;

	return _true;
}

template< typename Type >
_ubool TSerializableNode< Type >::Read( WStringPtr r, WStringPtr g, WStringPtr b, WStringPtr a, Color& color )
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

template< typename Type >
_ubool TSerializableNode< Type >::ReadTime( WStringPtr name, _time_t& value )
{
	_int content_value = 0;
	if ( OnGetPropertyValue( name, content_value ) )
	{
		value = content_value;
	}
	else
	{
		UString content;
		if ( OnGetPropertyValue( name, content ) == _false )
			return _false;

		value = (_time_t)content.ToLarge( 10 );
	}

	return _true;
}

template< typename Type >
_ubool TSerializableNode< Type >::ReadFlag( WStringPtr name, _dword flag_value_to_combine, FlagsObject& flags )
{
	_ubool status	= _false;
	_ubool ret		= Read( name, status );

	flags.EnableFlags( flag_value_to_combine, status );

	return ret;
}

template< typename Type >
_ubool TSerializableNode< Type >::ReadFlags( WStringPtr name, FlagsObject& flags )
{
	_dword value = 0;
	if ( Read( name, value ) )
	{
		flags = value;
		return _false;
	}

	return _true;
}

template< typename Type >
_ubool TSerializableNode< Type >::ReadFlags( WStringPtr name, FlagsObject& flags, ISerializableNode::OnQueryEnumValue funcpointer )
{
	// Read the flags as bit mode
	_dword value = 0;
	if ( ReadEnum( name, value, _true, funcpointer ) == _false )
		return _false;

	// Update the flags
	flags.SetFlags( value );

	return _true;
}

template< typename Type >
_ubool TSerializableNode< Type >::Write( WStringPtr name, _int value )
{
	return OnSetPropertyValue( name, value );
}

template< typename Type >
_ubool TSerializableNode< Type >::Write( WStringPtr name, _dword value )
{
	return OnSetPropertyValue( name, value );
}

template< typename Type >
_ubool TSerializableNode< Type >::Write( WStringPtr name, _large value )
{
	return OnSetPropertyValue( name, value );
}

template< typename Type >
_ubool TSerializableNode< Type >::Write( WStringPtr name, _qword value )
{
	return OnSetPropertyValue( name, value );
}

template< typename Type >
_ubool TSerializableNode< Type >::Write( WStringPtr name, _boolean value )
{
	return OnSetPropertyValue( name, value );
}

template< typename Type >
_ubool TSerializableNode< Type >::Write( WStringPtr name, _float value )
{
	return OnSetPropertyValue( name, value );
}

template< typename Type >
_ubool TSerializableNode< Type >::Write( WStringPtr name, _double value )
{
	return OnSetPropertyValue( name, value );
}

template< typename Type >
_ubool TSerializableNode< Type >::Write( WStringPtr name, _charw value )
{
	return OnSetPropertyValue( name, WString( value ) );
}

template< typename Type >
_ubool TSerializableNode< Type >::Write( WStringPtr name, const _chara* value )
{
	return OnSetPropertyValue( name, AStringPtr( value ) );
}

template< typename Type >
_ubool TSerializableNode< Type >::Write( WStringPtr name, const _charw* value )
{
	return OnSetPropertyValue( name, WStringPtr( value ) );
}

template< typename Type >
_ubool TSerializableNode< Type >::Write( WStringPtr name, AStringPtr value )
{
	return OnSetPropertyValue( name, value );
}

template< typename Type >
_ubool TSerializableNode< Type >::Write( WStringPtr name, UStringPtr value )
{
	return OnSetPropertyValue( name, value );
}

template< typename Type >
_ubool TSerializableNode< Type >::Write( WStringPtr name, WStringPtr value )
{
	return OnSetPropertyValue( name, value );
}

template< typename Type >
_ubool TSerializableNode< Type >::Write( WStringPtr name, const AStringR& value )
{
	return OnSetPropertyValue( name, (const AString&)value );
}

template< typename Type >
_ubool TSerializableNode< Type >::Write( WStringPtr name, const UStringR& value )
{
	return OnSetPropertyValue( name, (const UString&)value );
}

template< typename Type >
_ubool TSerializableNode< Type >::Write( WStringPtr name, const WStringR& value )
{
	return OnSetPropertyValue( name, (const WString&)value );
}

template< typename Type >
_ubool TSerializableNode< Type >::Write( WStringPtr name, const AStringObj& value )
{
	return OnSetPropertyValue( name, value );
}

template< typename Type >
_ubool TSerializableNode< Type >::Write( WStringPtr name, const UStringObj& value )
{
	return OnSetPropertyValue( name, value );
}

template< typename Type >
_ubool TSerializableNode< Type >::Write( WStringPtr name, const WStringObj& value )
{
	return OnSetPropertyValue( name, value );
}

template< typename Type >
_ubool TSerializableNode< Type >::Write( WStringPtr name, const Time& value )
{
	return OnSetPropertyValue( name, value.ToWString( ) );
}

template< typename Type >
_ubool TSerializableNode< Type >::Write( WStringPtr name, const MD5Code& value )
{
	return OnSetPropertyValue( name, value.ToWString( _true ) );
}

template< typename Type >
_ubool TSerializableNode< Type >::Write( WStringPtr name, const Version& value )
{
	return OnSetPropertyValue( name, value.ToWString( ) );
}

template< typename Type >
_ubool TSerializableNode< Type >::Write( WStringPtr name, const Color& value )
{
	// Convert color to hex value mode
	WString string = WString( ).FromValue( (_dword)value, 16 );
	string.Uppercase( );
	string = L"0x" + string;

	return Write( name, string );
}

template< typename Type >
_ubool TSerializableNode< Type >::Write( WStringPtr x_name, WStringPtr y_name, const Vector2& vector )
{
	if ( Write( x_name, vector.x ) == _false )
		return _false;

	if ( Write( y_name, vector.y ) == _false )
		return _false;

	return _true;
}

template< typename Type >
_ubool TSerializableNode< Type >::Write( WStringPtr x_name, WStringPtr y_name, WStringPtr z_name, const Vector3& vector )
{
	if ( Write( x_name, vector.x ) == _false )
		return _false;

	if ( Write( y_name, vector.y ) == _false )
		return _false;

	if ( Write( z_name, vector.z ) == _false )
		return _false;

	return _true;
}

template< typename Type >
_ubool TSerializableNode< Type >::Write( WStringPtr x_name, WStringPtr y_name, WStringPtr z_name, WStringPtr w_name, const Vector4& vec4 )
{
	if ( Write( x_name, vec4.x ) == _false )
		return _false;

	if ( Write( y_name, vec4.y ) == _false )
		return _false;

	if ( Write( z_name, vec4.z ) == _false )
		return _false;

	if ( Write( w_name, vec4.w ) == _false )
		return _false;

	return _true;
}

template< typename Type >
_ubool TSerializableNode< Type >::Write( WStringPtr x_name, WStringPtr y_name, WStringPtr z_name, WStringPtr w_name, const Quaternion& quaternion )
{
	if ( Write( x_name, quaternion.x ) == _false )
		return _false;

	if ( Write( y_name, quaternion.y ) == _false )
		return _false;

	if ( Write( z_name, quaternion.z ) == _false )
		return _false;

	if ( Write( w_name, quaternion.w ) == _false )
		return _false;

	return _true;
}

template< typename Type >
_ubool TSerializableNode< Type >::Write( WStringPtr px_name, WStringPtr py_name, WStringPtr sx_name, WStringPtr sy_name, WStringPtr rotation_name, const Transform2D& transform )
{
	if ( Write( px_name, py_name, transform.mPosition ) == _false )
		return _false;

	if ( Write( sx_name, sy_name, transform.mScale ) == _false )
		return _false;

	if ( Write( rotation_name, transform.mRadian ) == _false )
		return _false;

	return _true;
}

template< typename Type >
_ubool TSerializableNode< Type >::Write( WStringPtr min_name, WStringPtr max_name, const DwordRange& bounds )
{
	if ( Write( min_name, bounds.mMinValue ) == _false )
		return _false;

	if ( Write( max_name, bounds.mMaxValue ) == _false )
		return _false;

	return _true;
}

template< typename Type >
_ubool TSerializableNode< Type >::Write( WStringPtr min_name, WStringPtr max_name, const FloatRange& bounds )
{
	if ( Write( min_name, bounds.mMinValue ) == _false )
		return _false;

	if ( Write( max_name, bounds.mMaxValue ) == _false )
		return _false;

	return _true;
}

template< typename Type >
_ubool TSerializableNode< Type >::Write( WStringPtr r, WStringPtr g, WStringPtr b, WStringPtr a, const Color& color )
{
	if ( Write( r, color.r ) == _false )
		return _false;

	if ( Write( g, color.g ) == _false )
		return _false;

	if ( Write( b, color.b ) == _false )
		return _false;

	if ( Write( a, color.a ) == _false )
		return _false;

	return _true;
}

template< typename Type >
_ubool TSerializableNode< Type >::WriteTime( WStringPtr name, _time_t value )
{
	return OnSetPropertyValue( name, WString( ).FromValue( (_large)value, 10 ) );
}

template< typename Type >
_ubool TSerializableNode< Type >::WriteFlag( WStringPtr name, _dword flag_value_to_check, const FlagsObject& flags )
{
	if ( Write( name, flags.HasFlags( flag_value_to_check ) ) == _false )
		return _false;

	return _true;
}

template< typename Type >
_ubool TSerializableNode< Type >::WriteFlags( WStringPtr name, const FlagsObject& flags )
{
	return Write( name, flags.GetFlags( ) );
}

template< typename Type >
_ubool TSerializableNode< Type >::WriteFlags( WStringPtr name, const FlagsObject& flags, ISerializableNode::OnQueryEnumName funcpointer ) 
{
	// Write flags as bits mode
	return WriteEnum( name, flags.GetFlags( ), _true, funcpointer );
}

}
