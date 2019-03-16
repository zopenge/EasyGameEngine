//! @file     ManifestFile.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ManifestDir
//----------------------------------------------------------------------------

class ManifestDir : public INTERFACE_OBJECT_TREE_IMPL( TNameObject< TObject< IManifestDir > >, IManifestDir )
{
private:
	typedef INTERFACE_OBJECT_TREE_IMPL( TNameObject< TObject< IManifestDir > >, IManifestDir ) BaseClass;

private:
	//!	The manifest item and parent directory info.
	struct ManifestItemWithParentDirInfo
	{
		const ManifestItemInfo* mItemInfo;
		const ManifestDir*		mParentDir;

		ManifestItemWithParentDirInfo( )
		{
			mItemInfo	= _null;
			mParentDir	= _null;
		}
	};
	//!	Use the resource name as key.
	typedef Map< ManifestItemWithParentDirInfo, WString > ManifestItemWithParentDirInfoMap;

private:
	//!	The element type string
	static WStringPtr sDirElementTypeName;
	static WStringPtr sFileElementTypeName;

private:
	//!	The sub-items
	ManifestItemArray					mSubItems;

	//!	The fast access map
	ManifestItemWithParentDirInfoMap*	mFastAccessItems;

private:
	//!	Import sub-dir.
	_ubool ImportSubDir( ISerializableNode* node );
	//!	Import sub-item.
	_ubool ImportSubItem( ISerializableNode* node );

	//!	Export sub-item.
	_ubool ExportSubItem( const ManifestItemInfo& item, ISerializableNode* node ) const;

	//!	Build fast access items.
	_ubool BuildFastAccessItems( ManifestItemWithParentDirInfoMap& access_items );

public:
	ManifestDir( );
	ManifestDir( WStringPtr name, ManifestDir* parent );
	virtual ~ManifestDir( );

public:
	//!	Clone.
	_void Clone( IManifestDir* dir );

	//!	Import from serializable node.
	_ubool Import( ISerializableNode* node );
	//!	Export to serializable node.
	_ubool Export( ISerializableNode* node ) const;

	//!	Build fast access items.
	_ubool BuildFastAccessItems( );

// IManifestDir Interface
public:
	virtual WStringR					GetPath( ) const override;

	virtual _dword						GetNumberOfSubItems( ) const override;
	virtual const ManifestItemInfo*		GetSubItemByIndex( _dword index ) const override;
	virtual const ManifestItemInfo*		GetSubItem( WStringPtr name, _ubool ignorecase ) const override;
	virtual _ubool						GetSubItem( WStringPtr name, _ubool ignorecase, ManifestItemNodeInfo& item_node ) const override;
	virtual _ubool						GetSubItems( WStringPtr name, _ubool ignorecase, ManifestItemNodeInfoArray& item_nodes ) const override;
	virtual _ubool						GetSubItems( ManifestItemNodeInfoArray& items ) const override;
	virtual const ManifestItemArray&	GetSubItems( ) const override;
	virtual _ubool						HasSubItem( WStringPtr filename ) const override;
	virtual _void						RemoveSubItem( WStringPtr filename ) override;
	virtual _ubool						InsertSubItem( const ManifestItemInfo& item ) override;
	virtual _ubool						ReplaceSubItem( const ManifestItemInfo& item ) override;
	virtual _ubool						InsertSubItemByPath( WStringPtr path, const ManifestItemInfo& item ) override;
	virtual IManifestDir*				SearchSubItemByPath( WStringPtr filename, const ManifestItemInfo*& item ) const override;
	virtual const ManifestItemInfo*		SearchSubItemByPath( WStringPtr filename ) const override;
	virtual _ubool						HasSubItemByPath( WStringPtr filename ) const override;
	virtual _void						RemoveSubItemByPath( WStringPtr filename ) override;

	virtual _ubool						GetSubDirs( WStringPtr name, Array< IManifestDirRef >& dirs ) const override;
	virtual IManifestDir*				GetSubDirByName( WStringPtr name ) override;
	virtual IManifestDir*				InsertSubDir( WStringPtr name ) override;
	virtual _ubool						InsertSubDir( IManifestDir* dir ) override;
	virtual _void						RemoveSubDir( WStringPtr name ) override;
	virtual IManifestDir*				InsertSubDirByPath( WStringPtr path ) override;
	virtual IManifestDir*				SearchSubDirByPath( WStringPtr path ) const override;
	virtual _void						RemoveSubDirByPath( WStringPtr path ) override;
};

//----------------------------------------------------------------------------
// ManifestWalker
//----------------------------------------------------------------------------

class ManifestWalker : public INTERFACE_OBJECT_IMPL( IManifestWalker )
{
private:
	//!	The folder data
	struct FolderData
	{
		//!	The current directory
		IManifestDirRef	mDir;
		//!	The current sub-directory
		IManifestDirRef	mSubDir;

		//!	The item index of current directory
		_dword			mItemIndex;
	};

private:
	typedef Stack< FolderData > ManifestDirStack;

private:
	//!	The total item number
	_dword				mItemNumber;
	//!	The item info ( for feedback to caller )
	ManifestItemInfo	mItem;

	//!	The directory stack
	ManifestDirStack	mDirStack;

private:
	//!	Build the path from directory to root directory with item name.
	WString BuildPath( const IManifestDir* dir, WStringPtr item_name ) const;

	//!	Push the directory.
	_void PushDir( IManifestDir* dir );
	//!	Pop the directory.
	_void PopDir( );

	//!	Read the directory to get sub-directory or sub-item info.
	_ubool ReadDir( FolderData& folder_data, ManifestWalkerItemInfo& item_info, WStringPtr filter, _dword flags, _dword depth );

public:
	ManifestWalker( IManifestDir* root_dir );
	virtual ~ManifestWalker( );

// IManifestWalker Interface
public:
	virtual _ubool Walk( ManifestWalkerItemInfo& item_info, WStringPtr filter = L"", _dword flags = 0, _dword depth = -1 ) override;
};

//----------------------------------------------------------------------------
// ManifestFile
//----------------------------------------------------------------------------

class ManifestFile : public INTERFACE_BASEFILE_IMPL( TVersionable< IManifestFile > )
{
private:
	typedef INTERFACE_BASEFILE_IMPL( TVersionable< IManifestFile > ) BaseClass;

private:
	//!	The root dir
	ManifestDir*	mRootDir;

public:
	ManifestFile( );
	virtual ~ManifestFile( );

// IObject Interface
public:
	virtual IObject*				CloneTo( _ubool standalone ) const override;

// IBaseFile Interface
public:
	virtual _FILE_FORMAT			GetFileID( ) const override;

	virtual _ubool 					LoadFromStream( IStreamReader* stream_reader ) override;
	virtual _void 					Unload( ) override;

	virtual _ubool					SaveToStream( IStreamWriter* stream_writer, _dword flags ) const override;

// IManifestFile Interface
public:
	virtual IManifestDir*			GetRootDir( ) const override;

	virtual IManifestWalkerPassRef	CreateWalker( IManifestDir* root_dir ) const override;
	virtual IManifestWalkerPassRef	CreateWalker( WStringPtr path ) const override;
};

}