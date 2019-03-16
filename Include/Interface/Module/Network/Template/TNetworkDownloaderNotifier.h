//! @file     TNetworkDownloaderNotifier.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TNetworkDownloaderNotifier
//----------------------------------------------------------------------------

template< typename Type >
class TNetworkDownloaderNotifier : public Type
{
protected:
	INetworkDownloaderNotifier::_ERROR	mLastErrID;

	QwordRange							mCurItemSizeRange;
	DwordRange							mCurItemsRange;

protected:
	TNetworkDownloaderNotifier( );
	virtual ~TNetworkDownloaderNotifier( );

// INetworkDownloaderNotifier Interface
public:
	virtual const DwordRange&	GetItemRange( ) const override;
	virtual _float				GetPercentage( ) const override;

	virtual _void				OnError( INetworkDownloaderNotifier::_ERROR err_id, const QwordParameters2& parameters ) override;

	virtual MD5Code				OnQueryMD5Code( WStringPtr res_file_name, const QwordParameters2& parameters ) override;
	virtual _void				OnDownloading( _qword cur_dl_size, _qword total_dl_size, _dword cur_item_number, _dword total_item_number, const QwordParameters2& parameters ) override;
	virtual _void				OnReplacing( _qword cur_size, _qword total_size, _dword cur_item_number, _dword total_item_number, const QwordParameters2& parameters ) override;
	virtual _void				OnFinishFile( WStringPtr remote_relative_filename, WStringPtr local_relative_filename, const QwordParameters2& parameters ) override;
	virtual _void				OnFinishAll( ) override;

	virtual _ubool				OnReplaceManifestFile( IStreamReader* stream_reader, _ENCRYPTION encryption_type, AStringPtr encryption_key, WStringPtr manifest_filename ) override;
};

//----------------------------------------------------------------------------
// TNetworkDownloaderNotifier Implementation
//----------------------------------------------------------------------------

template< typename Type >
TNetworkDownloaderNotifier< Type >::TNetworkDownloaderNotifier( )
{
	mLastErrID			= INetworkDownloaderNotifier::_ERROR_NO;

	mCurItemSizeRange	= QwordRange::cNull;
	mCurItemsRange		= DwordRange::cNull;
}

template< typename Type >
TNetworkDownloaderNotifier< Type >::~TNetworkDownloaderNotifier( )
{
}

template< typename Type >
const DwordRange& TNetworkDownloaderNotifier< Type >::GetItemRange( ) const
{
	return mCurItemsRange;
}

template< typename Type >
_float TNetworkDownloaderNotifier< Type >::GetPercentage( ) const
{
	return mCurItemsRange.GetPercentage( );
}

template< typename Type >
_void TNetworkDownloaderNotifier< Type >::OnError( INetworkDownloaderNotifier::_ERROR err_id, const QwordParameters2& parameters )
{
	mLastErrID = err_id;
}

template< typename Type >
MD5Code TNetworkDownloaderNotifier< Type >::OnQueryMD5Code( WStringPtr res_file_name, const QwordParameters2& parameters )
{
	return MD5Code::cNull;
}

template< typename Type >
_void TNetworkDownloaderNotifier< Type >::OnDownloading( _qword cur_dl_size, _qword total_dl_size, _dword cur_item_number, _dword total_item_number, const QwordParameters2& parameters )
{
	mCurItemSizeRange	= QwordRange( cur_dl_size, total_dl_size );
	mCurItemsRange		= DwordRange( cur_item_number, total_item_number );
}

template< typename Type >
_void TNetworkDownloaderNotifier< Type >::OnReplacing( _qword cur_size, _qword total_size, _dword cur_item_number, _dword total_item_number, const QwordParameters2& parameters )
{
	mCurItemSizeRange	= QwordRange( cur_size, total_size );
	mCurItemsRange		= DwordRange( cur_item_number, total_item_number );
}

template< typename Type >
_void TNetworkDownloaderNotifier< Type >::OnFinishFile( WStringPtr remote_relative_filename, WStringPtr local_relative_filename, const QwordParameters2& parameters )
{
}

template< typename Type >
_void TNetworkDownloaderNotifier< Type >::OnFinishAll( )
{
	mCurItemSizeRange	= QwordRange::cNull;
	mCurItemsRange		= DwordRange( mCurItemsRange.mMaxValue, mCurItemsRange.mMaxValue );
}

template< typename Type >
_ubool TNetworkDownloaderNotifier< Type >::OnReplaceManifestFile( IStreamReader* stream_reader, _ENCRYPTION encryption_type, AStringPtr encryption_key, WStringPtr manifest_filename )
{
	return _false;
}

}