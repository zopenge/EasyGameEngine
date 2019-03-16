//! @file     StoragePEResArchive.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// StoragePEResArchive
//----------------------------------------------------------------------------

class StoragePEResArchive : public INTERFACE_ARCHIVE_IMPL( IArchive )
{
private:
	typedef INTERFACE_ARCHIVE_IMPL( IArchive ) BaseClass;

private:
	//!	The resource module handle
	_handle	mModule;

private:
	//!	Get resource info.
	//!	@param		name		The resource name
	//!	@param		size		The resource size.
	//!	@return		The resource info handle.
	_handle GetResourceInfo( WStringPtr name, _dword* size ) const;

// TArchive Interface
private:
	virtual IStreamReaderPassRef	OnLoadResource( WStringPtr filename ) override;
	virtual IStreamWriterPassRef	OnCreateResource( WStringPtr filename, _dword size ) override;

public:
	StoragePEResArchive( WStringPtr path );
	virtual ~StoragePEResArchive( );

public:
	//!	Initialize.
	_ubool Initialize( WStringPtr password, WStringPtr module_name );

// IArchive Interface
public:
	virtual _ubool EnumResources( OnWalkItem walk_item_func, WStringPtr path, WStringPtr filter = L"", _dword flags = 0, _dword depth = -1, const QwordParameters2& parameters = QwordParameters2::cNull ) override;
};

//----------------------------------------------------------------------------
// StoragePEResArchive Implementation
//----------------------------------------------------------------------------

}