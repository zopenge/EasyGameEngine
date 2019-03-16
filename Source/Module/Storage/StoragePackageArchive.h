//! @file     StoragePackageArchive.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// StoragePackageArchive
//----------------------------------------------------------------------------

class StoragePackageArchive : public TStorageArchive< IStorageArchive >
{
private:
	typedef TStorageArchive< IStorageArchive > BaseClass;

private:
	//!	The package file
	StoragePackageFile*	mPackageFile;

// TStorageArchive Interface
private:
	virtual _ubool					OnQueryResource( WStringPtr filename ) const override;

	virtual IStreamReaderPassRef	OnLoadResource( WStringPtr filename ) override;
	virtual IStreamWriterPassRef	OnCreateResource( WStringPtr filename, _dword size ) override;

public:
	StoragePackageArchive( WStringPtr path, IManifestFile* manifest_file );
	virtual ~StoragePackageArchive( );

public:
	//!	Initialize.
	_ubool Initialize( WStringPtr module_name );

// IArchive Interface
public:
	virtual _ubool EnumResources( OnWalkItem walk_item_func, WStringPtr path, WStringPtr filter = L"", _dword flags = 0, _dword depth = -1, const VoidParameters2& parameters = VoidParameters2::cNull ) override;
};

//----------------------------------------------------------------------------
// StoragePackageArchive Implementation
//----------------------------------------------------------------------------

}