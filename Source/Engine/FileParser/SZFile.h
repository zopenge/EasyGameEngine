//! @file     SZFile.h
//! @author   fukun.yang
//! @version  1.1
//! @date     2014.05
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// SZFile
//----------------------------------------------------------------------------

class SZFile : public INTERFACE_BASEFILE_IMPL( IZIPFile )
{
private:
	typedef INTERFACE_BASEFILE_IMPL( IZIPFile ) BaseClass;

public:
	enum { _FILE_ID = 0xAFBC7A37 };

private:
	//!	The file info
	struct FileInfo
	{
		_dword				mIndex;
		WString				mFileName;
		IStreamReaderRef	mStream;

		operator WStringPtr ( ) const
			{ return mFileName; }

		FileInfo( )
		{
			mIndex = -1;
		}
	};
	typedef Array< FileInfo > FileInfoArray;

	struct SZStreamReader
	{
		ISeekInStream		mSZReader;
		IStreamReaderRef	mStreamReader;
	};
private:
	//!	The thread locker
	Lock			mLocker;

	//!	The default password
	AString			mPassword;
	//!	The compression ratio
	_float			mCompressionRatio;

	//!	The 7z file handle
	SZStreamReader	mArchiveStream;	// 7z file stream
	CLookToRead		mLookStream;	// 7z file look stream
	CSzArEx			mArchive;		// 7z archive

	//!	The decompression buffer data
	_byte*			mDecompressionBufferData;

	//!	The files
	FileInfoArray	mFileItems;

private:
	static ISzAlloc	sAllocImp;
	static ISzAlloc	sAllocImpTemp;

private:
	//!	When alloc/free memory.
	static _void* OnMemAlloc( _void*, size_t size );
	static _void OnMemFree( _void*, _void* address );

private:
	//!	Initialize archive.
	_ubool InitArchive( );

	//!	Fix the file name.
	WString FixFileName( WStringPtr file_name ) const;

	//!	Load file item.
	_ubool LoadFileItem( FileInfo& file_info, _byte*& out_buffer, size_t out_buffer_size );

public:
	SZFile( WStringPtr password );
	virtual ~SZFile( );

public:
	//!	Initialize.
	static _ubool Initialize( );
	//!	Finalize.
	static _void Finalize( );

public:
	//!	Create zip file.
	_ubool CreateFile( WStringPtr filename );

	static SRes FileInStream_Read( void *pp, void *buf, size_t *size );
	static SRes FileInStream_Seek( void *pp, Int64 *pos, ESzSeek origin );

// IBaseFile Interface
public:
	virtual _FILE_FORMAT			GetFileID( ) const override;

	virtual _ubool 					LoadFromStream( IStreamReader* stream_reader ) override;
	virtual _void 					Unload( ) override;

// IZIPFile Interface
public:
	virtual _float					GetCompressionRatio( ) const override;

	virtual _ubool					AddFile( WStringPtr filename ) override;
	virtual _ubool					AddFile( WStringPtr filename, WStringPtr filename_in_zip ) override;
	virtual _ubool					HasFile( WStringPtr filename ) const override;
	virtual IStreamReaderPassRef	GetFile( WStringPtr filename ) override;

	virtual _ubool					AddFolder( WStringPtr dir_path, WStringPtr filter = L"", _dword flags = 0, _dword depth = -1 ) override;
	virtual _ubool					AddFolder( WStringPtr dir_path, WStringPtr dir_path_in_zip, WStringPtr filter = L"", _dword flags = 0, _dword depth = -1 ) override;

	virtual _dword					GetFileNumber( ) const override;
	virtual WStringPtr				GetFileNameByIndex( _dword index ) override;
	virtual IStreamReaderPassRef	GetFileStreamByIndex( _dword index ) override;
};

}