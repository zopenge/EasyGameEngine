//! @file     TNetworkStreamReader.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TNetworkStreamReader
//----------------------------------------------------------------------------

template< typename Type >
class TNetworkStreamReader : public TStreamReader< TObject< Type > >
{
protected:
	typedef TStreamReader< TObject< Type > > TBaseClass;

protected:
	//!	The thread lock
	Lock							mLocker;
	//!	The notifier
	INetworkStreamReaderNotifierRef	mNotifier;

	//!	The remote file name
	AString							mRemoteFileName;
	//!	The MIME content type
	_NETWORK_MIME_CONTENT_TYPE		mMIMEContentType;
	//!	The MIME content size in bytes
	_dword							mMIMEContentSize;
	//!	The MIME content MD5 code
	MD5Code							mMIMEContentMD5Code;

	//!	The stream to read from stream writer's buffer data
	IStreamReaderRef				mStreamReader;
	//!	The stream to receive remote buffer data
	IStreamWriterRef				mStreamWriter;

protected:

protected:
	TNetworkStreamReader( INetworkStreamReaderNotifier* notifier );
	virtual ~TNetworkStreamReader( );

// IStreamReader Interface
public:
	virtual _dword							GetSize( ) const override;
	virtual _dword							GetOffset( ) const override;

	virtual const _byte*					GetBuffer( ) override;

	virtual _dword							Seek( _SEEK flag, _int distance ) override;
	virtual _dword							SeekByArrangedValueFromBegin( _dword value ) override;

// IStreamReader Interface
public:
	virtual _dword							GetRemainBytes( ) const override;

	virtual _ubool 							ReachEnd( ) const override;

	virtual _dword 							PeekBuffer( _void* buffer, _dword size ) override;
	virtual _dword							PeekBuffer( _void* buffer, _dword size, _dword offset ) override;

	virtual _dword 							ReadBuffer( _void* buffer, _dword size ) override;
	virtual _dword 							ReadTiny( _tiny& data ) override;
	virtual _dword 							ReadShort( _short& data ) override;
	virtual _dword 							ReadLong( _int& data ) override;
	virtual _dword 							ReadByte( _byte& data ) override;
	virtual _dword 							ReadWord( _word& data ) override;
	virtual _dword 							ReadDword( _dword& data ) override;
	virtual _dword 							ReadQword( _qword& data ) override;
	virtual _dword 							ReadFloat( _float& data ) override;
	virtual _dword 							ReadDouble( _double& data ) override;

// INetworkStreamReader Interface
public:
	virtual _void							SetNotifier( INetworkStreamReaderNotifier* notifier ) override;
	virtual INetworkStreamReaderNotifier*	GetNotifier( ) override;

	virtual _NETWORK_MIME_CONTENT_TYPE		GetMIMEContentType( ) const override;
};

//----------------------------------------------------------------------------
// TNetworkStreamReader Implementation
//----------------------------------------------------------------------------

template< typename Type >
TNetworkStreamReader< Type >::TNetworkStreamReader( INetworkStreamReaderNotifier* notifier )
{
	mMIMEContentType	= _MIME_CONTENT_TYPE_UNKNOWN;
	mMIMEContentSize	= 0;
	mMIMEContentMD5Code	= MD5Code::cNull;

	SetNotifier( notifier );
}

template< typename Type >
TNetworkStreamReader< Type >::~TNetworkStreamReader( )
{
}

template< typename Type >
_dword TNetworkStreamReader< Type >::GetSize( ) const
{
	return mMIMEContentSize;
}

template< typename Type >
_dword TNetworkStreamReader< Type >::GetOffset( ) const
{
	return mStreamReader->GetOffset( );
}

template< typename Type >
const _byte* TNetworkStreamReader< Type >::GetBuffer( )
{
	return mStreamReader->GetBuffer( );
}

template< typename Type >
_dword TNetworkStreamReader< Type >::Seek( _SEEK flag, _int distance )
{
	return mStreamReader->Seek( flag, distance );
}

template< typename Type >
_dword TNetworkStreamReader< Type >::SeekByArrangedValueFromBegin( _dword value )
{
	return mStreamReader->SeekByArrangedValueFromBegin( value );
}

template< typename Type >
_dword TNetworkStreamReader< Type >::GetRemainBytes( ) const
{
	return mStreamReader->GetRemainBytes( );
}

template< typename Type >
_ubool TNetworkStreamReader< Type >::ReachEnd( ) const
{
	return mStreamReader->ReachEnd( );
}

template< typename Type >
_dword TNetworkStreamReader< Type >::PeekBuffer( _void* buffer, _dword size )
{
	return mStreamReader->PeekBuffer( buffer, size );
}

template< typename Type >
_dword TNetworkStreamReader< Type >::PeekBuffer( _void* buffer, _dword size, _dword offset )
{
	return mStreamReader->PeekBuffer( buffer, size, offset );
}

template< typename Type >
_dword TNetworkStreamReader< Type >::ReadBuffer( _void* buffer, _dword size )
{
	return mStreamReader->ReadBuffer( buffer, size );
}

template< typename Type >
_dword TNetworkStreamReader< Type >::ReadTiny( _tiny& data )
{
	return mStreamReader->ReadTiny( data );
}

template< typename Type >
_dword TNetworkStreamReader< Type >::ReadShort( _short& data )
{
	return mStreamReader->ReadShort( data );
}

template< typename Type >
_dword TNetworkStreamReader< Type >::ReadLong( _int& data )
{
	return mStreamReader->ReadLong( data );
}

template< typename Type >
_dword TNetworkStreamReader< Type >::ReadByte( _byte& data )
{
	return mStreamReader->ReadByte( data );
}

template< typename Type >
_dword TNetworkStreamReader< Type >::ReadWord( _word& data )
{
	return mStreamReader->ReadWord( data );
}

template< typename Type >
_dword TNetworkStreamReader< Type >::ReadDword( _dword& data )
{
	return mStreamReader->ReadDword( data );
}

template< typename Type >
_dword TNetworkStreamReader< Type >::ReadQword( _qword& data )
{
	return mStreamReader->ReadQword( data );
}

template< typename Type >
_dword TNetworkStreamReader< Type >::ReadFloat( _float& data )
{
	return mStreamReader->ReadFloat( data );
}

template< typename Type >
_dword TNetworkStreamReader< Type >::ReadDouble( _double& data )
{
	return mStreamReader->ReadDouble( data );
}

template< typename Type >
_void TNetworkStreamReader< Type >::SetNotifier( INetworkStreamReaderNotifier* notifier ) 
{
	if ( notifier == _null )
		mNotifier = &NullNetwork::GetInstance( ).GetNetworkStreamReaderNotifier( );
	else
		mNotifier = notifier;
}

template< typename Type >
INetworkStreamReaderNotifier* TNetworkStreamReader< Type >::GetNotifier( )
{
	return mNotifier;
}

template< typename Type >
_NETWORK_MIME_CONTENT_TYPE TNetworkStreamReader< Type >::GetMIMEContentType( ) const
{
	return mMIMEContentType;
}

}