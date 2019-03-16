//! @file     IManifestFile.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IManifestDir
//----------------------------------------------------------------------------

class IManifestDir : public ITObjectTree< ITNameObject< IObject >, IManifestDir >
{
public:
	//!	Get the path.
	//!	@param		none.
	//!	@return		The path.
	virtual WStringR GetPath( ) const PURE;

	//!	Get the number of sub-items.
	//!	@param		none.
	//!	@return		The number of sub-items.
	virtual _dword GetNumberOfSubItems( ) const PURE;
	//!	Get the sub-item by index.
	//!	@param		index		The index of sub-item.
	//! @return		True indicates success, false indicates failure.
	virtual const ManifestItemInfo* GetSubItemByIndex( _dword index ) const PURE;
	//!	Get the sub-item.
	//!	@param		name		The file name.
	//!	@param		ignorecase	True indicates case insensitive.
	//! @return		The item info.
	virtual const ManifestItemInfo* GetSubItem( WStringPtr name, _ubool ignorecase ) const PURE;
	//!	Get the sub-item node.
	//!	@param		name		The file name.
	//!	@param		ignorecase	True indicates case insensitive.
	//!	@param		item		The item node info.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool GetSubItem( WStringPtr name, _ubool ignorecase, ManifestItemNodeInfo& item ) const PURE;
	//!	Get all sub-items by name with md5 code.
	//!	@param		name		The item name.
	//!	@param		ignorecase	True indicates case insensitive.
	//!	@param		items		The items what matched all conditions.
	//! @return		True indicates success, false indicates failure or no any matched items.
	virtual _ubool GetSubItems( WStringPtr name, _ubool ignorecase, ManifestItemNodeInfoArray& items ) const PURE;
	//!	Get all sub-items by md5 code only.
	//!	@param		items		The items what matched all conditions.
	//! @return		True indicates success, false indicates failure or no any matched items.
	virtual _ubool GetSubItems( ManifestItemNodeInfoArray& items ) const PURE;
	//!	Get all sub-items.
	//!	@param		none.
	//!	@return		The sub-items.
	virtual const ManifestItemArray& GetSubItems( ) const PURE;
	//!	Check whether has the sub-item or not.
	//!	@param		name		The file name.
	//! @return		True indicates it's existing item.
	virtual _ubool HasSubItem( WStringPtr filename ) const PURE;
	//!	Remove sub-item.
	//!	@param		name		The file name.
	//! @return		none.
	virtual _void RemoveSubItem( WStringPtr filename ) PURE;
	//!	Insert sub-item.
	//!	@param		item		The item info.
	//! @return		True indicates success, false indicates failure or it's duplicate item.
	virtual _ubool InsertSubItem( const ManifestItemInfo& item ) PURE;
	//!	Replace sub-item.
	//!	@param		item		The item info.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool ReplaceSubItem( const ManifestItemInfo& item ) PURE;
	//!	Insert sub-item by path.
	//!	@param		path		The item path.
	//!	@param		item		The item info.
	//! @return		True indicates success, false indicates failure or it's duplicate item.
	virtual _ubool InsertSubItemByPath( WStringPtr path, const ManifestItemInfo& item ) PURE;
	//!	Get the sub-item by file name.
	//!	@param		filename	The file name.
	//!	@param		item		The item info.
	//! @return		The parent directory interface, null indicates the sub-item is not existing.
	virtual IManifestDir* SearchSubItemByPath( WStringPtr filename, const ManifestItemInfo*& item ) const PURE;
	//!	Get the sub-item by file name.
	//!	@param		filename	The file name.
	//! @return		The item info.
	virtual const ManifestItemInfo* SearchSubItemByPath( WStringPtr filename ) const PURE;
	//!	Check whether has the sub-item or not.
	//!	@param		name		The file name.
	//! @return		True indicates it's existing item.
	virtual _ubool HasSubItemByPath( WStringPtr filename ) const PURE;
	//!	Remove sub-item.
	//!	@param		name		The file name.
	//! @return		none.
	virtual _void RemoveSubItemByPath( WStringPtr filename ) PURE;

	//!	Get the all sub-directories by name.
	//!	@param		name		The name of sub-directory.
	//!	@param		dirs		The sub directories.
	//! @return		True indicates success, false indicates failure or no any matched items.
	virtual _ubool GetSubDirs( WStringPtr name, Array< IManifestDirRef >& dirs ) const PURE;
	//!	Get the sub-directory by name.
	//!	@param		name		The name of sub-directory.
	//!	@return		The sub-directory.
	virtual IManifestDir* GetSubDirByName( WStringPtr name ) PURE;
	//!	Insert sub-directory.
	//!	@param		name		The directory name.
	//! @return		The sub-directory interface.
	virtual IManifestDir* InsertSubDir( WStringPtr name ) PURE;
	//!	Insert sub-directory with all childs.
	//!	@param		dir			The directory what will insert.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool InsertSubDir( IManifestDir* dir ) PURE;
	//!	Remove sub-directory.
	//!	@param		name		The directory name.
	//! @return		none.
	virtual _void RemoveSubDir( WStringPtr name ) PURE;
	//!	Insert sub-directory by path.
	//!	@param		path		The directory path.
	//! @return		The sub-directory interface.
	virtual IManifestDir* InsertSubDirByPath( WStringPtr path ) PURE;
	//!	Search sub-directory by path.
	//!	@param		path		The directory path.
	//! @return		The sub-directory interface.
	virtual IManifestDir* SearchSubDirByPath( WStringPtr path ) const PURE;
	//!	Remove sub-directory by path.
	//!	@param		path		The directory path.
	//! @return		none.
	virtual _void RemoveSubDirByPath( WStringPtr path ) PURE;
};

//----------------------------------------------------------------------------
// IManifestWalker
//----------------------------------------------------------------------------

class IManifestWalker : public IObject
{
public:
	//!	Start to walk.
	//!	@param		item_info	The item info.
	//! @param		filter		The extension name filter.
	//! @param		flags		The enumeration flags, @see _FILE_FINDER_ENUMERATION.
	//!	@param		depth		The enumeration depth.
	//! @return		True indicates there are some files or directories what need to walk, otherwise indicates walk finished.
	virtual _ubool Walk( ManifestWalkerItemInfo& item_info, WStringPtr filter = L"", _dword flags = 0, _dword depth = -1 ) PURE;
};

//----------------------------------------------------------------------------
// IManifestFile
//----------------------------------------------------------------------------

class IManifestFile : public ITVersionable< IBaseFile >
{
public:
	//!	Get the root directory.
	//!	@param		none.
	//!	@return		The root directory.
	virtual IManifestDir* GetRootDir( ) const PURE;

	//!	Create walker.
	//!	@param		root_dir	The root directory.
	//!	@return		The walker interface.
	virtual IManifestWalkerPassRef CreateWalker( IManifestDir* root_dir ) const PURE;
	//!	Create walker.
	//!	@param		path		The directory path.
	//!	@return		The walker interface.
	virtual IManifestWalkerPassRef CreateWalker( WStringPtr path ) const PURE;
};

}