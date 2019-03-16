//! @file     TStreamProcessor.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TStreamProcessor
//----------------------------------------------------------------------------

template< typename Type >
class TStreamProcessor : public Type
{
protected:
	//!	The thread locker
	Lock						mLocker;

	//!	The notifier
	IStreamProcessorNotifierRef	mNotifier;

protected:
	//!	When begin to process buffer.
	//!	@param		none.
	//! @return		True indicates success false indicates failure.
	virtual _ubool OnBeginProcessBuffer( ) PURE;
	//!	When process buffer.
	//!	@param		input_buf				The input buffer data.
	//!	@param		input_size				The input buffer size.	
	//!	@param		stream_writer			The stream writer.
	//!	@param		chunk_size				The chunk size.
	//!	@param		output_size				The output buffer size.	
	//! @return		True indicates success, false indicates failure.
	virtual _ubool OnProcessBuffer( const _byte* input_buf, _dword input_size, IStreamWriter* stream_writer, _dword chunk_size, _dword& output_size ) PURE;
	//!	When End to process buffer.
	//!	@param		none.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool OnEndProcessBuffer( ) PURE;

protected:
	TStreamProcessor( );
	virtual ~TStreamProcessor( );

// IStreamProcessor Interface
public:
	virtual _void						SetNotifier( IStreamProcessorNotifier* notifier ) override;
	virtual IStreamProcessorNotifier*	GetNotifier( ) override;

	virtual _ubool						Process( const _byte* buffer, _dword size, IStreamWriter* stream_writer, _dword chunk_size, _dword& output_size ) override;
	virtual _ubool						Process( IStreamReader* stream_reader, _dword size, IStreamWriter* stream_writer, _dword chunk_size, _dword& output_size ) override;
};

//----------------------------------------------------------------------------
// TStreamProcessor Implementation
//----------------------------------------------------------------------------

template< typename Type >
TStreamProcessor< Type >::TStreamProcessor( )
{
}

template< typename Type >
TStreamProcessor< Type >::~TStreamProcessor( )
{
}

template< typename Type >
_void TStreamProcessor< Type >::SetNotifier( IStreamProcessorNotifier* notifier )
{
	mNotifier = notifier;
}

template< typename Type >
IStreamProcessorNotifier* TStreamProcessor< Type >::GetNotifier( )
{
	return mNotifier;
}

template< typename Type >
_ubool TStreamProcessor< Type >::Process( const _byte* buffer, _dword size, IStreamWriter* stream_writer, _dword chunk_size, _dword& output_size )
{
	if ( buffer == _null || size == 0 || stream_writer == _null || chunk_size == 0 )
		return _false;

	if ( OnBeginProcessBuffer( ) == _false )
		return _false;

	_ubool ret = OnProcessBuffer( buffer, size, stream_writer, chunk_size, output_size );

	if ( OnEndProcessBuffer( ) == _false )
		return _false;

	return ret;
}

template< typename Type >
_ubool TStreamProcessor< Type >::Process( IStreamReader* stream_reader, _dword size, IStreamWriter* stream_writer, _dword chunk_size, _dword& output_size )
{
	if ( stream_reader == _null || stream_writer == _null || chunk_size == 0 )
		return _false;

	return Process( stream_reader->GetBuffer( ), stream_reader->GetSize( ), stream_writer, chunk_size, output_size );
}

}