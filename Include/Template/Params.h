//! @file     Parameters.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// Parameters
//----------------------------------------------------------------------------

template< typename Type, _dword _MAX_PARAMETERS_NUMBER >
class Parameters
{
public:
	static const Parameters	cNull;

protected:
	//!	Parameters
	Type	mParameters[ _MAX_PARAMETERS_NUMBER ];

public:
	Parameters( );
	Parameters( Type p1 );
	Parameters( Type p1, Type p2 );
	Parameters( Type p1, Type p2, Type p3 );
	Parameters( Type p1, Type p2, Type p3, Type p4 );
	Parameters( const Parameters& parameters );

public:
	//!	Copy operation function.
	Parameters& operator = ( const Parameters& parameters );

	//! Get a const element reference by index.
	//! @param		index		The index of the element in array.
	//! @return		The const element reference.
	const Type& operator [] ( _dword index ) const;
	//! Get a mutable element reference by index.
	//! @param		index		The index of the element in array.
	//! @return		The mutable element reference.
	Type& operator [] ( _dword index );

	//!	Clear.
	//!	@param		none.
	//!	@return		none.
	_void Clear( );

	//!	Get the number of parameters.
	//!	@param		none.
	//!	@return		The number of parameters.
	_dword Number( ) const;
};

//----------------------------------------------------------------------------
// Parameters Implementation
//----------------------------------------------------------------------------

template< typename Type, _dword _MAX_PARAMETERS_NUMBER >
const Type& Parameters< Type, _MAX_PARAMETERS_NUMBER >::operator [] ( _dword index ) const
{
	EGE_ASSERT( index < _MAX_PARAMETERS_NUMBER );

	return mParameters[ index ];
}

template< typename Type, _dword _MAX_PARAMETERS_NUMBER >
Type& Parameters< Type, _MAX_PARAMETERS_NUMBER >::operator [] ( _dword index )
{
	EGE_ASSERT( index < _MAX_PARAMETERS_NUMBER );

	return mParameters[ index ];
}

template< typename Type, _dword _MAX_PARAMETERS_NUMBER >
_dword Parameters< Type, _MAX_PARAMETERS_NUMBER >::Number( ) const
{
	return _MAX_PARAMETERS_NUMBER;
}

}
