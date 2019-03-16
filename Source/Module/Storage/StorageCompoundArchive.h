//! @file     StorageCompoundArchive.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// StorageCompoundArchive
//----------------------------------------------------------------------------

class StorageCompoundArchive : public INTERFACE_ARCHIVE_IMPL( IArchive )
{
private:
	typedef INTERFACE_ARCHIVE_IMPL( IArchive ) BaseClass;

private:
	//!	The file archive
	IArchiveRef	mFileArchive;
	//!	The PE-Res archive
	IArchiveRef	mPEResArchive;

// TArchive Interface
private:
	virtual IStreamReaderPassRef	OnLoadResource( WStringPtr filename ) override;
	virtual IStreamWriterPassRef	OnCreateResource( WStringPtr filename, _dword size ) override;

public:
	StorageCompoundArchive( WStringPtr path );
	virtual ~StorageCompoundArchive( );

public:
	//!	Initialize.
	_ubool Initialize( WStringPtr password, WStringPtr module_name );

// IArchive Interface
public:
	virtual _ubool	EnumResources( OnWalkItem walk_item_func, WStringPtr path, WStringPtr filter = L"", _dword flags = 0, _dword depth = -1, const QwordParameters2& parameters = QwordParameters2::cNull ) override;
};

//----------------------------------------------------------------------------
// StorageCompoundArchive Implementation
//----------------------------------------------------------------------------

}