//! @file     StreamingPCMFile.cpp
//! @author   LiCode
//! @version  1.1.0.689
//! @date     2011/02/13
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// StreamingPCMFile Implementation
//----------------------------------------------------------------------------

StreamingPCMFile::StreamingPCMFile( )
{
}

StreamingPCMFile::~StreamingPCMFile( )
{
}

_ubool StreamingPCMFile::Initialize( const SoundHeaderInfo& info )
{
	mHeaderInfo = info;

	mStreamWriter = GetInterfaceFactory( )->CreateMemStreamWriter( );
	if ( mStreamWriter.IsNull( ) )
		return _false;

	return _true;
}

_FILE_FORMAT StreamingPCMFile::GetFileID( ) const
{
	return _FF_STREAMING_PCM;
}

_ubool StreamingPCMFile::LoadFromStream( IStreamReader* stream_reader )
{
	if ( stream_reader == _null )
		return _false;

	Unload( );

	return _true;
}

_void StreamingPCMFile::Unload( )
{
	BaseClass::Unload( );
}

_ubool StreamingPCMFile::SaveToStream( IStreamWriter* stream_writer, _dword flags ) const
{
	if ( stream_writer == _null )
		return _false;

	return _true;
}

_ubool StreamingPCMFile::IsStreaming( ) const
{
	return _true;
}

_double StreamingPCMFile::TimeSeek( _SEEK flag, _double time )
{
	return 0.0;
}

_double StreamingPCMFile::GetCurTime( ) const
{
	return 0.0;
}

_dword StreamingPCMFile::Decode( _byte* buffer, _dword size )
{
	if ( buffer == _null || size == 0 )
		return 0;

	LockOwner lock_owner( mLock );

	_dword remain_size = mStreamWriter->GetOffset( );
	_dword decode_size = Math::Min( remain_size, size );
	EGE_MEM_CPY( buffer, mStreamWriter->GetBuffer( ), decode_size );

	mStreamWriter->RemoveBuffer( decode_size );

	return decode_size;
}

_void StreamingPCMFile::WriteBuffer( _dword size, const _byte* buffer )
{
	LockOwner lock_owner( mLock );

	mStreamWriter->WriteBuffer( buffer, size );
}
