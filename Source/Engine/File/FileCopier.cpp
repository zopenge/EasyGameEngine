//! @file     FileCopier.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// FileCopierThread Implementation
//----------------------------------------------------------------------------

FileCopierThread::FileCopierThread( )
{
	mOffset			= 0;
	mReadChunkSize	= 0;
	mMD5Code		= MD5Code::cNull;
	mBuffer			= _null;
}

FileCopierThread::~FileCopierThread( )
{
	EGE_DELETE_ARRAY( mBuffer );
}

_dword FileCopierThread::OnRunThread( const QwordParams2& params )
{
	while ( IsReleasing( ) == _false )
	{
		_dword read_size = mStreamReader->PeekBuffer( mBuffer, mReadChunkSize, mOffset );
		if ( read_size == 0 )
		{
			mFileStreamWriter.Clear( );

			// Check MD5 code
			mMD5.Digest( );
			if ( mMD5.GetCode( ) != mMD5Code )
			{
				WLOG_ERROR_2( L"Check '%s' -> '%s' file MD5 code failed", mTempFileName.Str( ), mFileName.Str( ) );
				return -1;
			}

			if ( FileSystem::MoveFile( mFileName, mTempFileName ) == _false )
			{
				WLOG_ERROR_2( L"Move '%s' -> '%s' file failed", mTempFileName.Str( ), mFileName.Str( ) );
				return -1;
			}
			else
			{
				WLOG_TRACE_2( L"Move '%s' -> '%s' file OK", mTempFileName.Str( ), mFileName.Str( ) );
				return 1;
			}
		}

		_dword write_size = mFileStreamWriter->WriteBuffer( mBuffer, read_size );

		_dword processed_size = Math::Min( read_size, write_size );
		mMD5.AppendBuffer( mBuffer, processed_size );

		mOffset += processed_size;

		Platform::Sleep( 10 );
	}

	return 0;
}

_void FileCopierThread::OnCloseThread( _dword exitcode, const QwordParams2& params )
{
	EGE_DELETE_ARRAY( mBuffer );

	mFileStreamWriter.Clear( );
}

_ubool FileCopierThread::Start( _dword read_chunk_size, const MD5Code& md5_code, IStreamReader* stream_reader, WStringPtr filepath )
{
	if ( read_chunk_size == 0 )
		return _false;

	if ( stream_reader == _null )
		return _false;

	if ( filepath.IsEmpty( ) )
		return _false;

	mMD5.Clear( );

	WString root_dir = Path::GetDirectoryName( filepath );
	if ( FileSystem::GetTempFileName( root_dir, L"tmp", mTempFileName ) == _false )
	{
		WLOG_ERROR_1( L"Get '%s' temp file name failed of file copier", root_dir.Str( ) );
		return _false;
	}

	mFileStreamWriter = GetInterfaceFactory( )->CreateFileStreamWriter( mTempFileName );
	if ( mFileStreamWriter.IsNull( ) )
	{
		WLOG_ERROR_1( L"Create '%s' temp file stream writer failed of file copier failed", mTempFileName.Str( ) );
		return _false;
	}

	mStreamReader	= stream_reader;
	mOffset			= 0;
	mReadChunkSize	= read_chunk_size;
	mMD5Code		= md5_code;
	EGE_DELETE_ARRAY( mBuffer );
	mBuffer			= new _byte[ read_chunk_size ];
	mFileName		= filepath;
	
	if ( Create( 0, _false, L"FileCopierThread", QwordParams2::cNull ) == _false )
	{
		WLOG_ERROR_1( L"Create '%s' thread of file copier failed", filepath.Str( ) );
		return _false;
	}

	return _true;
}

//----------------------------------------------------------------------------
// FileCopier Implementation
//----------------------------------------------------------------------------

FileCopier::FileCopier( )
{
}

FileCopier::~FileCopier( )
{
	Stop( );
}

_ubool FileCopier::Start( _dword read_chunk_size, const MD5Code& md5_code, IStreamReader* stream_reader, WStringPtr filepath )
{
	if ( mFileCopierThread.Start( read_chunk_size, md5_code, stream_reader, filepath ) == _false )
		return _false;

	return _true;
}

_void FileCopier::Stop( )
{
	mFileCopierThread.Close( );
}
