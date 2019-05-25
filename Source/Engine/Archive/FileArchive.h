//! @file     FileArchive.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright 2009-2011 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// FileArchive
//----------------------------------------------------------------------------

class FileArchive : public INTERFACE_ARCHIVE_IMPL( IArchive )
{
private:
	typedef INTERFACE_ARCHIVE_IMPL( IArchive ) BaseClass;

private:
	WString	mPath;

public:
	FileArchive( WStringPtr path );
	virtual ~FileArchive( );

// IArchive Interface
public:
	virtual WStringPtr				GetPath( ) const override;

	virtual _ubool					HasResourceByPath( WStringPtr file_name ) const override;
	virtual IStreamReaderPassRef	LoadResourceByPath( WStringPtr file_name ) override;

	virtual _ubool					EnumResources( OnWalkItem walk_item_func, WStringPtr path, WStringPtr filter = L"", _dword flags = 0, _dword depth = -1, const QwordParameters2& params = QwordParameters2::cNull ) const override;
};

}