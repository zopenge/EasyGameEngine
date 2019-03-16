//! @file     TObject.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TObject
//----------------------------------------------------------------------------

template< typename Type >
class TObject : public Type
{
protected:
	_dword	mRefCount;

protected:
	template< typename ToType >
	const ToType* GetObjPtr( const IObject* obj );

protected:
	TObject( );
	virtual ~TObject( );

// IObject Interface
public:
	virtual _dword				GetInterfaceTypeID( ) const override;
	virtual const AStringObj&	GetInterfaceTypeNameA( ) const override;
	virtual const WStringObj&	GetInterfaceTypeNameW( ) const override;
	virtual _dword				GetClassTypeID( ) const override;
	virtual const AStringObj&	GetClassTypeNameA( ) const override;
	virtual const WStringObj&	GetClassTypeNameW( ) const override;

	virtual IObject*			CloneTo( _ubool standalone ) const override;
	virtual IObject*			CloneTo( _void* arguments, _ubool standalone ) const override;

	virtual _ubool				CopyFrom( const IObject* obj ) override;

	virtual _void				Tick( _dword limited_elapse, _dword elapse ) override;
	virtual _void				FrameTick( _dword frame ) override;

	virtual _void				DeleteThis( ) override;
	virtual _void				Uninitialize( ) override;

	virtual _dword 				GetRefCount( ) const override;
	virtual _dword 				AddRef( ) override;
	virtual _dword 				Release( ) override;
};

//----------------------------------------------------------------------------
// TObject Implementation
//----------------------------------------------------------------------------

template< typename Type >
TObject< Type >::TObject( ) : mRefCount( 1 )
{
}

template< typename Type >
TObject< Type >::~TObject( )
{
	EGE_ASSERT( mRefCount == 1 || mRefCount == 0 );
}

template< typename Type >
template< typename ToType >
const ToType* TObject< Type >::GetObjPtr( const IObject* obj )
{
	if ( obj == _null )
		return _null;

	if ( ToType::RTTI_InterfaceTypeID( ) != obj->GetInterfaceTypeID( ) )
		return _null;

	return static_cast<const ToType*>(obj);
}

template< typename Type >
_dword TObject< Type >::GetInterfaceTypeID( ) const
{
	return GetInterfaceTypeNameA( ).GetID( );
}

template< typename Type >
const AStringObj& TObject< Type >::GetInterfaceTypeNameA( ) const
{
	EGE_ASSERT2( 0, L"Please use the RTTI_CLASS_DECL( )/RTTI_CLASS_WITH_ARGUMENTS_DECL( ) macro for inherit class for using this interface" );

	return GetStringTable( )->GetNullAString( );
}

template< typename Type >
const WStringObj& TObject< Type >::GetInterfaceTypeNameW( ) const
{
	EGE_ASSERT2( 0, L"Please use the RTTI_CLASS_DECL( )/RTTI_CLASS_WITH_ARGUMENTS_DECL( ) macro for inherit class for using this interface" );

	return GetStringTable( )->GetNullWString( );
}

template< typename Type >
_dword TObject< Type >::GetClassTypeID( ) const
{
	return GetClassTypeNameA( ).GetID( );
}

template< typename Type >
const AStringObj& TObject< Type >::GetClassTypeNameA( ) const
{
	EGE_ASSERT2( 0, L"Please use the RTTI_CLASS_DECL( )/RTTI_CLASS_WITH_ARGUMENTS_DECL( ) macro for inherit class for using this interface" );

	return GetStringTable( )->GetNullAString( );
}

template< typename Type >
const WStringObj& TObject< Type >::GetClassTypeNameW( ) const
{
	EGE_ASSERT2( 0, L"Please use the RTTI_CLASS_DECL( )/RTTI_CLASS_WITH_ARGUMENTS_DECL( ) macro for inherit class for using this interface" );

	return GetStringTable( )->GetNullWString( );
}

template< typename Type >
IObject* TObject< Type >::CloneTo( _ubool standalone ) const
{
	EGE_ASSERT2( 0, L"Please implement it in the inherit class" );

	return _null;
}

template< typename Type >
IObject* TObject< Type >::CloneTo( _void* arguments, _ubool standalone ) const
{
	EGE_ASSERT2( 0, L"Please implement it in the inherit class" );

	return _null;
}

template< typename Type >
_ubool TObject< Type >::CopyFrom( const IObject* obj )
{
	EGE_ASSERT2( 0, L"Please implement it in the inherit class" );

	return _false;
}

template< typename Type >
_void TObject< Type >::Tick( _dword limited_elapse, _dword elapse )
{

}

template< typename Type >
_void TObject< Type >::FrameTick( _dword frame )
{

}

template< typename Type >
_void TObject< Type >::DeleteThis( )
{
	delete this;
}

template< typename Type >
_void TObject< Type >::Uninitialize( )
{
}

template< typename Type >
_dword TObject< Type >::GetRefCount( ) const
{
	return mRefCount;
}

template< typename Type >
_dword TObject< Type >::AddRef( )
{
	return INTERLOCKED_INC( mRefCount );
}

template< typename Type >
_dword TObject< Type >::Release( )
{
	if ( INTERLOCKED_DEC( mRefCount ) == 0 )
	{
		GetGarbageCollector( )->AddObject( static_cast< IObject* >( this ) );
		return 0;
	}
	else
	{
		return mRefCount;
	}
}

}