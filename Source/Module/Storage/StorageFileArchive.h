//! @file     StorageFileArchive.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// StorageFileArchive
//----------------------------------------------------------------------------

class StorageFileArchive : public TArchive< IArchive >
{
private:
	typedef TArchive< IArchive > BaseClass;

// TArchive Interface
private:
	virtual IStreamReaderPassRef	OnLoadResource( WStringPtr filename ) override;
	virtual IStreamWriterPassRef	OnCreateResource( WStringPtr filename, _dword size ) override;

public:
	StorageFileArchive( WStringPtr path );
	virtual ~StorageFileArchive( );

public:
	//!	Initialize.
	_ubool Initialize( WStringPtr password, WStringPtr module_name );

// IArchive Interface
public:
	virtual _ubool EnumResources( OnWalkItem walk_item_func, WStringPtr path, WStringPtr filter = L"", _dword flags = 0, _dword depth = -1, const QwordParameters2& parameters = QwordParameters2::cNull ) override;
};

//----------------------------------------------------------------------------
// StorageFileArchive Implementation
//----------------------------------------------------------------------------

}