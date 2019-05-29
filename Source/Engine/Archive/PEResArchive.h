//! @file     PEResArchive.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// PEResArchive
//----------------------------------------------------------------------------

class PEResArchive : public INTERFACE_ARCHIVE_IMPL( IArchive )
{
private:
	typedef INTERFACE_ARCHIVE_IMPL( IArchive ) BaseClass;

private:
	//!	The PE-resource file info.
	struct PEResFileInfo
	{
		PEResArchive*		mArchive;
		OnWalkItem			mWalkItemFunc;
		QwordParams2	mParameters;
	};

private:
	//!	The module name
	WString	mModuleName;

	//!	The resource module handle
	_handle	mModule;

private:
	static _ubool OnEnumFileCallback( const _charw* type, const _charw* name, _void* parameter );

private:
	//!	Get resource info.
	//!	@param		name		The resource name
	//!	@param		size		The resource size.
	//!	@return		The resource info handle.
	_handle GetResourceInfo( WStringPtr name, _dword* size ) const;

public:
	PEResArchive( );
	virtual ~PEResArchive( );

public:
	//!	Initialize.
	_ubool Initialize( WStringPtr module_name );

// IArchive Interface
public:
	virtual WStringPtr				GetPath( ) const override;

	virtual _ubool					HasResourceByPath( WStringPtr file_name ) const override;
	virtual IStreamReaderPassRef	LoadResourceByPath( WStringPtr file_name ) override;

	virtual _ubool					EnumResources( OnWalkItem walk_item_func, WStringPtr path, WStringPtr filter = L"", _dword flags = 0, _dword depth = -1, const QwordParams2& params = QwordParams2::cNull ) const override;
};

//----------------------------------------------------------------------------
// PEResArchive Implementation
//----------------------------------------------------------------------------

}