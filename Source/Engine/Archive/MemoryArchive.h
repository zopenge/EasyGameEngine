//! @file     MemoryArchive.h
//! @author   fukun.yang
//! @version  1.1.0.613
//! @date     2014/05/22
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// MemoryArchive
//----------------------------------------------------------------------------

class MemoryArchive : public INTERFACE_ARCHIVE_IMPL( IArchive )
{
private:
	typedef INTERFACE_ARCHIVE_IMPL( IArchive ) BaseClass;

private:
	//!	The MD5 Code
	MD5Code				mMD5Code;

	//!	The ZIP file
	IZIPFileRef			mZIPFile;

	//!	The manifest file
	IManifestFileRef	mManifestFile;

	//!	The file copier for copying archive
	IFileCopierRef		mFileCopier;

private:
	//!	Get the archive file name from document.
	WString GetArchiveFileNameFromDocument( WStringPtr name );
	//!	Get the archive stream reader.
	IStreamReaderRef GetArchiveStreamReader( WStringPtr name, IStreamReader* stream_reader );
	
	//! Load manifest file.
	_ubool LoadManifestFile( WStringPtr manifest_filename, _ENCRYPTION manifest_encryption_type, WStringPtr manifest_encryption_key );

public:
	MemoryArchive( );
	virtual ~MemoryArchive( );

public:
	//!	Initialize.
	_ubool Initialize( WStringPtr name, IStreamReader* stream_reader, WStringPtr password, _ENCRYPTION manifest_encryption_type, WStringPtr manifest_encryption_key );

// IArchive Interface
public:
	virtual WStringPtr				GetPath( ) const override;
	virtual const MD5Code&			GetMD5Code( ) const override;

	virtual const IManifestFile*	GetManifestFile( ) const override;

	virtual _ubool					HasResourceByPath( WStringPtr file_name ) const override;
	virtual IStreamReaderPassRef	LoadResourceByPath( WStringPtr file_name ) override;
};

//----------------------------------------------------------------------------
// MemoryArchive Implementation
//----------------------------------------------------------------------------

}