//! @file     TScriptType.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TScriptType
//----------------------------------------------------------------------------

template< typename Type >
class TScriptType : public Type
{
protected:
	//!	The script entity type ID
	_SCRIPT_TYPE_ID	mScriptEntityTypeID;

protected:
	TScriptType( _SCRIPT_TYPE_ID type_id );
	virtual ~TScriptType( );

// IScriptType Interface
public:
	virtual _SCRIPT_TYPE_ID GetTypeID( ) const override;
	virtual WStringPtr	GetTypeIDString( ) const override;
};

//----------------------------------------------------------------------------
// TScriptType Implementation
//----------------------------------------------------------------------------

template< typename Type >
TScriptType< Type >::TScriptType( _SCRIPT_TYPE_ID type_id )
{
	mScriptEntityTypeID = type_id;
}

template< typename Type >
TScriptType< Type >::~TScriptType( )
{
}

template< typename Type >
_SCRIPT_TYPE_ID TScriptType< Type >::GetTypeID( ) const 
{
	return mScriptEntityTypeID;
}

template< typename Type >
WStringPtr TScriptType< Type >::GetTypeIDString( ) const
{
	switch ( mScriptEntityTypeID )
	{
		case _SCRIPT_TYPE_CLASS:	return L"Class";
		case _SCRIPT_TYPE_FUNCTION:	return L"Function";
		case _SCRIPT_TYPE_VM:		return L"VM";
		default:
			return L"Unknown";
	}
}

}