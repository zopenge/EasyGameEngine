//! @file     PackageFile.h
//! @author   fukun.yang
//! @version  1.1
//! @date     2014.05
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// PackageFile
//----------------------------------------------------------------------------

class PackageFile : public INTERFACE_BASEFILE_IMPL( IZIPFile )
{
private:
	typedef INTERFACE_BASEFILE_IMPL( IZIPFile ) BaseClass;

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

private:
	//!	The thread locker
	Lock					mLocker;

	//!	The files
	FileInfoArray			mFileItems;

	//!	The file stream writer.
	IFileStreamWriterRef	mStreamWriter;

public:
	PackageFile( );
	virtual ~PackageFile( );

public:
	//!	Create file.
	_ubool CreateFile( WStringPtr filename );

// IBaseFile Interface
public:
	virtual _FILE_FORMAT			GetFileID( ) const override;

	virtual _ubool 					LoadFromStream( IStreamReader* stream_reader ) override;
	virtual _void 					Unload( ) override;

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