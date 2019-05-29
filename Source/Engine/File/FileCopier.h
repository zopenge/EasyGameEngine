//! @file     FileCopier.h
//! @author   fukun.yang
//! @version  1.1.0.613
//! @date     2014/05/22
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// FileCopierThread
//----------------------------------------------------------------------------

class FileCopierThread : public Thread
{
private:
	WString					mFileName;
	WString					mTempFileName;
	_dword					mOffset;
	_dword					mReadChunkSize;
	MD5Code					mMD5Code;
	_byte*					mBuffer;
	IStreamReaderRef		mStreamReader;
	IFileStreamWriterRef	mFileStreamWriter;

	MD5						mMD5;

// Thread Interface
private:
	virtual _dword	OnRunThread( const QwordParams2& params ) override;
	virtual _void	OnCloseThread( _dword exitcode, const QwordParams2& params ) override;

public:
	FileCopierThread( );
	virtual ~FileCopierThread( );

public:
	//!	Start.
	_ubool Start( _dword read_chunk_size, const MD5Code& md5_code, IStreamReader* stream_reader, WStringPtr filepath );
};

//----------------------------------------------------------------------------
// FileCopier
//----------------------------------------------------------------------------

class FileCopier : public TObject< IFileCopier >
{
private:
	FileCopierThread	mFileCopierThread;

public:
	FileCopier( );
	virtual ~FileCopier( );

// IFileCopier Interface
public:
	virtual _ubool	Start( _dword read_chunk_size, const MD5Code& md5_code, IStreamReader* stream_reader, WStringPtr filepath ) override;
	virtual _void	Stop( ) override;
};

//----------------------------------------------------------------------------
// FileCopier Implementation
//----------------------------------------------------------------------------

}