//! @file     ValueEncoder.h
//! @author   LiCode
//! @version  1.1
//! @date     2016.08
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ValueEncoder
//----------------------------------------------------------------------------

//! This class provides many common mathematics functions.
class ValueEncoder
{
private:
	template< typename Type >
	static Type EncodeFloatArray( const _float* value_ptr, const _float* bounding_min_ptr, const _float* bounding_max_ptr, _dword count, _dword precision = -1 );
	template< typename Type >
	static _void DecodeFloatArray( Type code, _float* value_ptr, const _float* bounding_min_ptr, const _float* bounding_max_ptr, _dword count, _dword precision = -1 );
	template< typename Type >
	static _dword GetMaxAbsValueIndex( const Type* value_ptr, _dword count );
public:
	template< typename Type >
	static Type EncodeVector4( const Vector4& position, const Vector4& bounding_min, const Vector4& bounding_max, _dword precision = -1 );
	template< typename Type >
	static Vector4 DecodeVector4( Type code, const Vector4& bounding_min, const Vector4& bounding_max, _dword precision = -1 );
	template< typename Type >
	static Type EncodeVector3( const Vector3& position, const Vector3& bounding_min, const Vector3& bounding_max, _dword precision = -1 );
	template< typename Type >
	static Vector3 DecodeVector3( Type code, const Vector3& bounding_min, const Vector3& bounding_max, _dword precision = -1 );
	template< typename Type >
	static Type EncodeVector2( const Vector2& uv, const Vector2& bounding_min, const Vector2& bounding_max, _dword precision = -1 );
	template< typename Type >
	static Vector2 DecodeVector2( Type code, const Vector2& bounding_min, const Vector2& bounding_max, _dword precision = -1 );

	template< typename Type >
	static Type EncodeQuaternion( const Quaternion& quat, _dword precision = -1 );
	template< typename Type >
	static Quaternion DecodeQuaternion( Type code, _dword precision = -1 );

	static _void EncodeTransform3D( const Transform3D& transform, const AxisAlignedBox& bounding_box, _qword& encode_q, _dword& encode_d );
	static Transform3D DecodeTransform3D( const AxisAlignedBox& bounding_box, _qword encode_q, _dword encode_d );

	template< typename Type >
	static Type EncodeWeight( const Vector4& weight, _dword precision = -1 );
	template< typename Type >
	static Vector4 DecodeWeight( Type code, _dword precision = -1 );
};

//----------------------------------------------------------------------------
// ValueEncoder Implementation
//----------------------------------------------------------------------------

template< typename Type >
inline Type ValueEncoder::EncodeFloatArray( const _float* value_ptr, const _float* bounding_min_ptr, const _float* bounding_max_ptr, _dword count, _dword precision )
{
	_dword size_of_bits = (_dword) ( sizeof( Type ) ) << 3;
	if ( precision == -1 )
		precision = size_of_bits / count;
	Type mask = ( (Type) ( -1 ) ) >> ( size_of_bits - precision );

	Type encode_value = 0;

	for ( _dword i = 0; i < count; ++ i )
	{
		_float bounding_size = bounding_max_ptr[i] - bounding_min_ptr[i];
		_float normalize_value = bounding_size == 0.0f ? 0.0f : ( ( value_ptr[i] - bounding_min_ptr[i] ) / bounding_size );

		Type encode_term = ( (Type) ( normalize_value * (_float) ( mask ) ) ) & mask;
		encode_value |= encode_term << ( precision * i );
	}

	return encode_value;
}

template< typename Type >
inline _void ValueEncoder::DecodeFloatArray( Type code, _float* value_ptr, const _float* bounding_min_ptr, const _float* bounding_max_ptr, _dword count, _dword precision )
{
	_dword size_of_bits = (_dword) ( sizeof( Type ) ) << 3;
	if ( precision == -1 )
		precision = size_of_bits / count;
	Type mask = ( (Type) ( -1 ) ) >> ( size_of_bits - precision );

	for ( _dword i = 0; i < count; ++ i )
	{
		Type encode_term = ( code >> ( precision * i ) ) & mask;
		_float normalize_value = (_float) encode_term / (_float) mask;
		value_ptr[i] = normalize_value * ( bounding_max_ptr[i] - bounding_min_ptr[i] ) + bounding_min_ptr[i];
	}
}

template< typename Type >
inline _dword ValueEncoder::GetMaxAbsValueIndex( const Type* value_ptr, _dword count )
{
	_dword max_term = 0;
	Type max_value = 0;

	for ( _dword i = 0; i < count; ++ i )
	{
		Type cur_value = (Type) Math::Abs( value_ptr[i] );
		if ( i == 0 || max_value < cur_value )
		{
			max_term = i;
			max_value = cur_value;
		}
	}

	return max_term;
}

template< typename Type >
inline Type ValueEncoder::EncodeVector4( const Vector4& position, const Vector4& bounding_min, const Vector4& bounding_max, _dword precision )
{
	return EncodeFloatArray< Type >( &( position.x ), &( bounding_min.x ), &( bounding_max.x ), 4, precision );
}

template< typename Type >
inline Vector4 ValueEncoder::DecodeVector4( Type code, const Vector4& bounding_min, const Vector4& bounding_max, _dword precision )
{
	Vector4 ret( Vector4::cOrigin );
	DecodeFloatArray< Type >( code, &( ret.x ), &( bounding_min.x ), &( bounding_max.x ), 4, precision );
	return ret;
}

template< typename Type >
inline Type ValueEncoder::EncodeVector3( const Vector3& position, const Vector3& bounding_min, const Vector3& bounding_max, _dword precision )
{
	return EncodeFloatArray< Type >( &( position.x ), &( bounding_min.x ), &( bounding_max.x ), 3, precision );
}

template< typename Type >
inline Vector3 ValueEncoder::DecodeVector3( Type code, const Vector3& bounding_min, const Vector3& bounding_max, _dword precision )
{
	Vector3 ret( Vector3::cOrigin );
	DecodeFloatArray< Type >( code, &( ret.x ), &( bounding_min.x ), &( bounding_max.x ), 3, precision );
	return ret;
}

template< typename Type >
inline Type ValueEncoder::EncodeVector2( const Vector2& uv, const Vector2& bounding_min, const Vector2& bounding_max, _dword precision )
{
	return EncodeFloatArray< Type >( &( uv.x ), &( bounding_min.x ), &( bounding_max.x ), 2, precision );
}

template< typename Type >
inline Vector2 ValueEncoder::DecodeVector2( Type code, const Vector2& bounding_min, const Vector2& bounding_max, _dword precision )
{
	Vector2 ret( Vector2::cOrigin );
	DecodeFloatArray< Type >( code, &( ret.x ), &( bounding_min.x ), &( bounding_max.x ), 2, precision );
	return ret;
}

template< typename Type >
inline Type ValueEncoder::EncodeQuaternion( const Quaternion& quat, _dword precision )
{
	_dword size_of_bits = (_dword) ( sizeof( Type ) ) << 3;
	if ( precision == -1 )
		precision = ( size_of_bits - 2 ) / 3;
	Type mask = ( (Type) ( -1 ) ) >> ( size_of_bits - precision );

	Quaternion rot = quat;
	rot.Normalize( );
	rot.Fix( );

	Type max_term = (Type) GetMaxAbsValueIndex<_float>( &( rot.x ), 4 );
	_float max_term_value = *( &( rot.x ) + (_dword) max_term );

	if ( max_term_value < 0.0f )
	{
		rot.x = -rot.x;
		rot.y = -rot.y;
		rot.z = -rot.z;
		rot.w = -rot.w;
	}

	Type encode_value = ( max_term & 0x3 ) << ( precision * 3 );
	_dword compress_index = 0;
	for ( _dword i = 0; i < 4; ++ i )
	{
		if ( i == max_term )
			continue;

		_float alpha = Math::Clamp( *( &( rot.x ) + i ) * 0.70710678f + 0.5f, 0.0f, 1.0f );
		Type compress_term = ( (Type) ( alpha * (_float) ( mask - 1 ) ) ) & mask;
		encode_value |= compress_term << ( precision * compress_index );

		++ compress_index;
	}

	return encode_value;
}

template< typename Type >
inline Quaternion ValueEncoder::DecodeQuaternion( Type code, _dword precision )
{
	_dword size_of_bits = (_dword) ( sizeof( Type ) ) << 3;
	if ( precision == -1 )
		precision = ( size_of_bits - 2 ) / 3;
	Type mask = ( (Type) ( -1 ) ) >> ( size_of_bits - precision );

	Quaternion quat;

	Type max_term = ( code >> ( precision * 3 ) ) & 0x3;
	_dword compress_index = 0;
	_float total = 0.0f;
	for ( _dword i = 0; i < 4; ++ i )
	{
		if ( i == max_term )
			continue;

		_float normalize_alpha = (_float) ( ( code >> ( precision * compress_index ) ) & mask ) / (_float) ( mask - 1 );
		_float decompress_value = normalize_alpha * 1.41421356f - 0.70710678f;
		*( &( quat.x ) + i ) = decompress_value;

		total += decompress_value * decompress_value;
		++ compress_index;
	}

	*( &( quat.x ) + max_term ) = 1.0f >= total ? Math::Sqrt( 1.0f - total ) : 0.0f;

	return quat;
}

template< typename Type >
inline Type ValueEncoder::EncodeWeight( const Vector4& weight, _dword precision )
{
	_dword size_of_bits = (_dword) ( sizeof( Type ) ) << 3;
	if ( precision == -1 )
		precision = ( size_of_bits - 2 ) / 3;
	Type mask = ( (Type) ( -1 ) ) >> ( size_of_bits - precision );

	Type max_term = (Type) GetMaxAbsValueIndex<_float>( &( weight.x ), 4 );

	Type encode_value = ( max_term & 0x3 ) << ( precision * 3 );
	_dword compress_index = 0;
	for ( _dword i = 0; i < 4; ++ i )
	{
		if ( i == max_term )
			continue;

		_float alpha = Math::Clamp( *( &( weight.x ) + i ) * 2.0f, 0.0f, 1.0f );
		Type compress_term = ( (Type) ( alpha * (_float) ( mask ) ) ) & mask;
		encode_value |= compress_term << ( precision * compress_index );

		++ compress_index;
	}

	return encode_value;
}

template< typename Type >
inline Vector4 ValueEncoder::DecodeWeight( Type code, _dword precision )
{
	_dword size_of_bits = (_dword) ( sizeof( Type ) ) << 3;
	if ( precision == -1 )
		precision = ( size_of_bits - 2 ) / 3;
	Type mask = ( (Type) ( -1 ) ) >> ( size_of_bits - precision );

	Vector4 weight;

	Type max_term = ( code >> ( precision * 3 ) ) & 0x3;
	_dword compress_index = 0;
	_float total = 0.0f;
	for ( _dword i = 0; i < 4; ++ i )
	{
		if ( i == max_term )
			continue;

		_float normalize_alpha = (_float) ( ( code >> ( precision * compress_index ) ) & mask ) / (_float) ( mask );
		_float decompress_value = normalize_alpha * 0.5f;
		*( &( weight.x ) + i ) = decompress_value;

		total += decompress_value;
		++ compress_index;
	}

	*( &( weight.x ) + max_term ) = 1.0f >= total ? ( 1.0f - total ) : 0.0f;

	return weight;
}

}