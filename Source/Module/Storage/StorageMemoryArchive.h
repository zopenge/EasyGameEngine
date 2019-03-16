//! @file     StorageMemoryArchive.h
//! @author   fukun.yang
//! @version  1.1.0.613
//! @date     2014/05/22
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// StorageMemoryArchive
//----------------------------------------------------------------------------

class StorageMemoryArchive : public INTERFACE_ARCHIVE_IMPL( IArchive )
{
private:
	typedef INTERFACE_ARCHIVE_IMPL( IArchive ) BaseClass;

private:
	//!	The ZIP file
	IZIPFileRef	mZIPFile;

private:
	//!	Load compressed file from document.
	IFileStreamReaderRef LoadCompressedFileFromDocument( WStringPtr filename, const MD5Code& md5_code, IStreamReader* stream_reader );

// TArchive Interface
private:
	virtual IStreamReaderPassRef	OnLoadResource( WStringPtr filename ) override;
	virtual IStreamWriterPassRef	OnCreateResource( WStringPtr filename, _dword size ) override;

public:
	StorageMemoryArchive( WStringPtr path );
	virtual ~StorageMemoryArchive( );

public:
	//!	Initialize.
	_ubool Initialize( WStringPtr password, WStringPtr module_name );

// IArchive Interface
public:
	virtual _ubool					EnumResources( OnWalkItem walk_item_func, WStringPtr path, WStringPtr filter = L"", _dword flags = 0, _dword depth = -1, const QwordParameters2& parameters = QwordParameters2::cNull ) override;

	virtual IManifestFilePassRef	LoadManifestFile( _ENCRYPTION manifest_encryption_type, WStringPtr manifest_encryption_key ) override;
};

//----------------------------------------------------------------------------
// StorageMemoryArchive Implementation
//----------------------------------------------------------------------------

}