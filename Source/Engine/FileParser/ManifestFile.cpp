//! @file     ManifestFile.cpp
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright ...

#include "EGEEngine.h"

WStringPtr ManifestDir::sDirElementTypeName		= L"Dir";
WStringPtr ManifestDir::sFileElementTypeName	= L"File";

//----------------------------------------------------------------------------
// ManifestDir Implementation
//----------------------------------------------------------------------------

ManifestDir::ManifestDir( ) : BaseClass( _null )
{
	mFastAccessItems = _null;
}

ManifestDir::ManifestDir( WStringPtr name, ManifestDir* parent ) : BaseClass( parent )
{
	mName				= name;
	mFastAccessItems	= _null;
}

ManifestDir::~ManifestDir( )
{
	EGE_DELETE( mFastAccessItems );
}

_ubool ManifestDir::ImportSubDir( ISerializableNode* node )
{
	// Read the element name
	WString name;
	if ( node->Read( L"name", name ) == _false )
	{
		WLOG_ERROR( L"The sub-dir's name is missing" );
		return _false;
	}

	// Create and import a sub-dir
	ManifestDir* sub_dir = new ManifestDir( name, this );
	if ( sub_dir->Import( node ) == _false )
	{
		WLOG_ERROR_1( L"The '%'s sub-dir import failed", name.Str( ) );
		return _false;
	}

	return _true;
}

_ubool ManifestDir::ImportSubItem( ISerializableNode* node )
{
	_ubool ret = _true;

	// Read item info
	ManifestItemInfo item;
	ret &= node->Read( L"name", item.mName );
	ret &= node->Read( L"md5", item.mMD5Code );

	if ( ret == _false )
	{
		WLOG_ERROR( L"Import sub item failed, some attributes are missing" );
		return _false;
	}

	// Insert item
	return InsertSubItem( item );
}

_ubool ManifestDir::ExportSubItem( const ManifestItemInfo& item, ISerializableNode* node ) const
{
	_ubool ret = _true;

	// Write item info
	ret &= node->Write( L"name", item.mName );
	ret &= node->Write( L"md5", item.mMD5Code );

	return ret;
}

_ubool ManifestDir::BuildFastAccessItems( ManifestItemWithParentDirInfoMap& access_items )
{
	for ( ManifestDir* child_dir = static_cast< ManifestDir* >( mFirstChildObject ); child_dir != _null; child_dir = static_cast< ManifestDir* >( child_dir->NextObject( ) ) )
	{
		if ( child_dir->BuildFastAccessItems( access_items ) == _false )
			return _false;
	}

	for ( _dword i = 0; i < mSubItems.Number( ); i ++ )
	{
		ManifestItemWithParentDirInfo& info = access_items[ mSubItems[i].mName ];
		info.mItemInfo						= &mSubItems[i];
		info.mParentDir						= this;
	}

	return _true;
}

_void ManifestDir::Clone( IManifestDir* dir )
{
	mName		= dir->GetName( );
	mSubItems	= dir->GetSubItems( );
}

_ubool ManifestDir::Import( ISerializableNode* node )
{
	if ( node == _null )
		return _false;

	// Get the sub item number, we will pre-allocate the memory to fit the best size
	_dword sub_items_number = 0;
	if ( node->Read( L"items_number", sub_items_number ) && sub_items_number != 0 )
		mSubItems.Resize( sub_items_number );

	// Import all children items
	ISerializableNodeRef child_node = node->GetFirstChildNode( ); 
	if ( child_node.IsValid( ) )
	{
		do
		{
			// Read the element type
			WString type = child_node->GetNodeName( );
		
			// It's directory
			if ( type == sDirElementTypeName )
			{
				if ( ImportSubDir( child_node ) == _false )
					return _false;
			}
			// It's file
			else if ( type == sFileElementTypeName )
			{
				if ( ImportSubItem( child_node ) == _false )
					return _false;
			}
			// Invalid type
			else
			{
				return _false;
			}
		}
		while ( child_node->MoveNext( ) );
	}

	return _true;
}

_ubool ManifestDir::Export( ISerializableNode* node ) const
{
	if ( node == _null )
		return _false;

	// Write the element name
	if ( node->Write( L"name", GetName( ) ) == _false )
		return _false;

	// Write the item's number
	if ( node->Write( L"items_number", mSubItems.Number( ) ) == _false )
		return _false;

	// Export the sub-dir
	ManifestDir* child_object = static_cast< ManifestDir* >( mFirstChildObject );
	if ( child_object != _null )
	{
		ISerializableNodeRef dir_node = node->InsertChildNode( sDirElementTypeName, L"", _false );
		if ( child_object->Export( dir_node ) == _false )
			return _false;
	}

	// Export the brother dir
	ManifestDir* next_object = static_cast< ManifestDir* >( mNextObject );
	if ( next_object != _null )
	{
		ISerializableNodeRef dir_node = node->InsertBrotherNode( sDirElementTypeName, L"", _false );
		if ( next_object->Export( dir_node ) == _false )
			return _false;
	}

	// Export all items
	for ( _dword i = 0; i < mSubItems.Number( ); i ++ )
	{
		ISerializableNodeRef file_node = node->InsertChildNode( sFileElementTypeName, L"", _false );
		if ( ExportSubItem( mSubItems[i], file_node ) == _false )
			return _false;
	}

	return _true;
}

_ubool ManifestDir::BuildFastAccessItems( )
{
	EGE_DELETE( mFastAccessItems );
	mFastAccessItems = new ManifestItemWithParentDirInfoMap( );

	if ( BuildFastAccessItems( *mFastAccessItems ) == _false )
		return _false;

	return _true;
}

WStringR ManifestDir::GetPath( ) const
{
	if ( mParentObject == _null )
		return mName;

	WString path = mParentObject->GetPath( );
	if ( path.IsEmpty( ) )
		return mName;
	else
		return path + L"/" + mName;
}

_dword ManifestDir::GetNumberOfSubItems( ) const
{
	return mSubItems.Number( );
}

const ManifestItemInfo* ManifestDir::GetSubItemByIndex( _dword index ) const
{
	if ( index >= mSubItems.Number( ) )
		return _null;

	return &mSubItems[ index ];
}

const ManifestItemInfo* ManifestDir::GetSubItem( WStringPtr name, _ubool ignorecase ) const
{
	// Try to use the fast access items
	if ( mFastAccessItems != _null && ignorecase == _false )
	{
		const ManifestItemWithParentDirInfo* info = mFastAccessItems->Search( name );
		if ( info != _null )
			return info->mItemInfo;
	}

	for ( _dword i = 0; i < mSubItems.Number( ); i ++ )
	{
		// Compare file name
		if ( mSubItems[i].mName.IsEqual( name, ignorecase ) == _false )
			continue;

		return &mSubItems[i];
	}

	return _null;
}

_ubool ManifestDir::GetSubItem( WStringPtr name, _ubool ignorecase, ManifestItemNodeInfo& item_node ) const
{
	// Try to use the fast access items
	if ( mFastAccessItems != _null && ignorecase == _false )
	{
		const ManifestItemWithParentDirInfo* info = mFastAccessItems->Search( name );
		if ( info != _null )
		{
			item_node = ManifestItemNodeInfo( *info->mItemInfo, (ManifestDir*) info->mParentDir );
			return _true;
		}
	}

	// Walk self and brother dir
	for ( const ManifestDir* brother_dir = this; brother_dir != _null; brother_dir = static_cast< const ManifestDir* >( brother_dir->NextObject( ) ) )
	{
		// Walk child dir recursively 
		const IManifestDir* child_dir = brother_dir->FirstChildObject( );
		if ( child_dir != _null )
		{
			if ( child_dir->GetSubItem( name, ignorecase, item_node ) )
				return _true;
		}

		// Search for all sub items
		for ( _dword i = 0; i < brother_dir->mSubItems.Number( ); i ++ )
		{
			const ManifestItemInfo& item = brother_dir->mSubItems[i];

			// Compare file name
			if ( item.mName.IsEqual( name, ignorecase ) == _false )
				continue;

			item_node = ManifestItemNodeInfo( item, (ManifestDir*) brother_dir );

			return _true;
		}
	}

	// If no any items then we assume failure
	return _false;
}

_ubool ManifestDir::GetSubItems( WStringPtr name, _ubool ignorecase, ManifestItemNodeInfoArray& item_nodes ) const
{
	// Walk self and brother dir
	for ( const ManifestDir* brother_dir = this; brother_dir != _null; brother_dir = static_cast< const ManifestDir* >( brother_dir->NextObject( ) ) )
	{
		// Walk child dir recursively 
		const IManifestDir* child_dir = brother_dir->FirstChildObject( );
		if ( child_dir != _null )
			child_dir->GetSubItems( name, ignorecase, item_nodes );

		// Search for all sub items
		for ( _dword i = 0; i < brother_dir->mSubItems.Number( ); i ++ )
		{
			const ManifestItemInfo& item = brother_dir->mSubItems[i];

			// Compare file name
			if ( item.mName.IsEqual( name, ignorecase ) == _false )
				continue;

			item_nodes.Append( ManifestItemNodeInfo( item, (ManifestDir*) brother_dir ) );
		}
	}

	// If no any items then we assume failure
	if ( item_nodes.Number( ) == 0 )
		return _false;

	return _true;
}

_ubool ManifestDir::GetSubItems( ManifestItemNodeInfoArray& items ) const
{
	// Walk self and brother dir
	for ( const ManifestDir* brother_dir = this; brother_dir != _null; brother_dir = static_cast< const ManifestDir* >( brother_dir->NextObject( ) ) )
	{
		// Walk child dir recursively 
		const IManifestDir* child_dir = brother_dir->FirstChildObject( );
		if ( child_dir != _null )
			child_dir->GetSubItems( items );

		// Search for all sub items
		for ( _dword i = 0; i < brother_dir->mSubItems.Number( ); i ++ )
		{
			const ManifestItemInfo& item = brother_dir->mSubItems[i];

			items.Append( ManifestItemNodeInfo( item, (ManifestDir*) brother_dir ) );
		}
	}

	// If no any items then we assume failure
	if ( items.Number( ) == 0 )
		return _false;

	return _true;
}

const ManifestItemArray& ManifestDir::GetSubItems( ) const
{
	return mSubItems;
}

_ubool ManifestDir::HasSubItem( WStringPtr filename ) const
{
	return mSubItems.SearchAscending( filename ).IsValid( );
}

_void ManifestDir::RemoveSubItem( WStringPtr filename )
{
	mSubItems.RemoveAscending( filename );
}

_ubool ManifestDir::InsertSubItem( const ManifestItemInfo& item )
{
	if ( item.mName.IsEmpty( ) )
	{
		WLOG_ERROR( L"You must provide the item's name in order to insert into manifest file" );
		return _false;
	}

	// Here we will check the duplicate item on debug mode
#ifdef _DEBUG
	for ( _dword i = 0; i < mSubItems.Number( ); i ++ )
	{
		if ( mSubItems[i].mName != item.mName )
			continue;

		// It's duplicate item
		WLOG_ERROR_1( L"'%s' is duplicate itemskip to insert it", item.mName.Str( ) );
		return _false;
	}
#endif

	mSubItems.InsertAscending< WStringPtr >( item );
	return _true;
}

_ubool ManifestDir::ReplaceSubItem( const ManifestItemInfo& item )
{
	if ( item.mName.IsEmpty( ) )
		return _false;

	// Search for the existing item
	ManifestItemArray::Iterator it = mSubItems.SearchAscending( item.mName );
	if ( it.IsValid( ) )
	{
		// Update existing item
		( (ManifestItemInfo&) it ) = item;
	}
	// Insert a new item
	else
	{
		mSubItems.InsertAscending< WStringPtr >( item );
	}

	return _true;
}

_ubool ManifestDir::InsertSubItemByPath( WStringPtr path, const ManifestItemInfo& item )
{
	// Insert the parent directory 
	IManifestDir* root_dir = InsertSubDirByPath( path );
	if ( root_dir == _null )
		return _false;

	// Build the item without path directory
	ManifestItemInfo item_temp	= item;
	item_temp.mName				= Path::GetFileName( item.mName );

	// Insert sub-item
	return root_dir->InsertSubItem( item_temp );
}

IManifestDir* ManifestDir::SearchSubItemByPath( WStringPtr filename, const ManifestItemInfo*& item ) const
{
	// Get the parent directory path
	WString path = Path::GetDirectoryName( filename );

	// Search the parent directory 
	IManifestDirRef root_dir = SearchSubDirByPath( path );
	if ( root_dir.IsNull( ) )
		return _null;

	// Build the item without path directory
	WString item_name = Path::GetFileName( filename );

	// Search sub-item
	if ( item != _null )
		item = root_dir->GetSubItem( item_name, _false );

	return root_dir;
}

const ManifestItemInfo* ManifestDir::SearchSubItemByPath( WStringPtr filename ) const
{
	// Get the parent directory path
	WString path = Path::GetDirectoryName( filename );

	// Search the parent directory 
	IManifestDirRef root_dir = SearchSubDirByPath( path );
	if ( root_dir.IsNull( ) )
		return _null;

	// Build the item without path directory
	WString item_name = Path::GetFileName( filename );

	// Search sub-item
	return root_dir->GetSubItem( item_name, _false );
}

_ubool ManifestDir::HasSubItemByPath( WStringPtr filename ) const
{
	// Get the parent directory path
	WString path = Path::GetDirectoryName( filename );

	// Search the parent directory 
	const IManifestDir* root_dir = SearchSubDirByPath( path );
	if ( root_dir == _null )
		return _false;

	// Get the file name without parent directory
	WString item_name = Path::GetFileName( filename );

	// Search sub-item
	return root_dir->HasSubItem( item_name );
}

_void ManifestDir::RemoveSubItemByPath( WStringPtr filename )
{
	// Get the parent directory path
	WString path = Path::GetDirectoryName( filename );

	// Search the parent directory 
	IManifestDirRef parent_dir = SearchSubDirByPath( path );
	if ( parent_dir.IsNull( ) )
		return;

	// Remove it
	parent_dir->RemoveSubItem( Path::GetFileName( filename ) );
}

_ubool ManifestDir::GetSubDirs( WStringPtr name, Array< IManifestDirRef >& dirs ) const
{
	for ( IManifestDir* child = mFirstChildObject; child != _null; child = child->NextObject( ) )
	{
		IManifestDir* dir = child->FirstChildObject( );
		if ( dir != _null )
			dir->GetSubDirs( name, dirs );

		// Check sub directory name
		if ( child->GetName( ) == name )
			dirs.Append( child );
	}

	return dirs.Number( ) != 0;
}

IManifestDir* ManifestDir::GetSubDirByName( WStringPtr name )
{
	// Self
	if ( name == L"." )
		return this;

	// Back to the parent directory
	if ( name == L".." )
		return ParentObject( );

	for ( IManifestDir* child = mFirstChildObject; child != _null; child = child->NextObject( ) )
	{
		if ( child->GetName( ).IsEqual( name, _false ) )
			return child;
	}

	return _null;
}

IManifestDir* ManifestDir::InsertSubDir( WStringPtr name )
{
	// Search for the existing sub-dir
	IManifestDir* dir = GetSubDirByName( name );
	if ( dir != _null )
		return dir;

	// Create and insert it as child
	return new ManifestDir( name, this );
}

_ubool ManifestDir::InsertSubDir( IManifestDir* dir )
{
	if ( dir == _null )
		return _false;

	// Copy dir
	IManifestDirRef sub_dir = InsertSubDir( dir->GetName( ) );
	if ( sub_dir.IsNull( ) )
		return _false;

	// Copy sub-dirs
	for ( IManifestDir* child_dir = dir->FirstChildObject( ); child_dir != _null; child_dir = child_dir->NextObject( ) )
	{
		if ( sub_dir->InsertSubDir( child_dir ) == _false )
			return _false;
	}

	// Copy sub-items
	for ( _dword i = 0; i < dir->GetNumberOfSubItems( ); i ++ )
	{
		const ManifestItemInfo* item = dir->GetSubItemByIndex( i );
		if ( item == _null )
			return _false;

		if ( sub_dir->InsertSubItem( *item ) == _false )
			return _false;
	}

	return _true;
}

_void ManifestDir::RemoveSubDir( WStringPtr name )
{
	for ( IManifestDir* child = mFirstChildObject; child != _null; child = child->NextObject( ) )
	{
		if ( child->GetName( ).IsEqual( name, _false ) )
		{
			RemoveChildObject( child );
			EGE_RELEASE( child );
			return;
		}
	}
}

IManifestDir* ManifestDir::InsertSubDirByPath( WStringPtr path )
{
	// Get the root directory
	IManifestDir* root_dir = this;

	// Insert sub-directories
	Path sub_path( path );
	for ( _dword i = 0; i < sub_path.Number( ); i ++ )
	{
		IManifestDir* sub_dir = root_dir->GetSubDirByName( sub_path[i] );
		if ( sub_dir == _null )
		{
			// Add a new sub-dir
			sub_dir = root_dir->InsertSubDir( sub_path[i] );
			if ( sub_dir == _null )
				return _null;
		}

		root_dir = sub_dir;
	}

	return root_dir;
}

IManifestDir* ManifestDir::SearchSubDirByPath( WStringPtr path ) const
{
	// Get the root directory
	IManifestDir* root_dir = (IManifestDir*) this;

	// Search sub-directories
	Path sub_path( path );
	for ( _dword i = 0; i < sub_path.Number( ); i ++ )
	{
		IManifestDir* sub_dir = root_dir->GetSubDirByName( sub_path[i] );
		if ( sub_dir == _null )
			return _null;

		root_dir = sub_dir;
	}

	return root_dir;
}

_void ManifestDir::RemoveSubDirByPath( WStringPtr path )
{
	IManifestDirRef sub_dir = SearchSubDirByPath( path );
	if ( sub_dir.IsNull( ) )
		return;

	IManifestDirRef parent_dir = sub_dir->ParentObject( );
	if ( parent_dir.IsNull( ) )
		return;

	parent_dir->RemoveSubDir( sub_dir->GetName( ) );
}

//----------------------------------------------------------------------------
// ManifestWalker Implementation
//----------------------------------------------------------------------------

ManifestWalker::ManifestWalker( IManifestDir* root_dir )
{
	mItemNumber	= 0;

	PushDir( root_dir );
}

ManifestWalker::~ManifestWalker( )
{

}

WString ManifestWalker::BuildPath( const IManifestDir* dir, WStringPtr item_name ) const
{
	// We must have the root directory
	EGE_ASSERT( mDirStack.Number( ) > 0 );

	// Get the root directory
	const IManifestDir* root_dir = ( (const FolderData&) mDirStack.GetHeadIterator( ) ).mDir;
	EGE_ASSERT( root_dir != _null );

	// The file path from root directory
	WString file_path = item_name;

	// Build the file path
	for ( const IManifestDir* dir_it = dir; dir_it != root_dir; dir_it = dir_it->ParentObject( ) )
		file_path = Path::BuildFilePath( dir_it->GetName( ), file_path );

	return file_path;
}

_void ManifestWalker::PushDir( IManifestDir* dir )
{
	EGE_ASSERT( dir != _null );

	FolderData folder_data;
	folder_data.mDir		= dir;
	folder_data.mSubDir		= dir->FirstChildObject( );
	folder_data.mItemIndex	= 0;

	mDirStack.Push( folder_data );
}

_void ManifestWalker::PopDir( )
{
	mDirStack.Pop( );
}

_ubool ManifestWalker::ReadDir( FolderData& folder_data, ManifestWalkerItemInfo& item_info, WStringPtr filter, _dword flags, _dword depth )
{
	// Skip for directory only mode
	if ( ( flags & _FILE_FINDER_ENUMERATION_DIRECTORY_ONLY ) == 0 )
	{
		// Walk sub-item
		for ( ; folder_data.mItemIndex < folder_data.mDir->GetNumberOfSubItems( ); folder_data.mItemIndex ++ )
		{
			// Get the file info
			const ManifestItemInfo* item = folder_data.mDir->GetSubItemByIndex( folder_data.mItemIndex );
			if ( item == _null )
				return _false;

			// Update the item info
			mItem = *item;

			// Check the extension name
			if ( ( filter.IsEmpty( ) == _false ) && ( Path::DoesMatchExtension( mItem.mName, filter ) == _false ) )
				continue;

			// Jump to the next item
			mItemNumber ++;

			// Feedback the item info
			item_info.mDirectory	= _null;
			item_info.mItem			= &mItem;

			// Jump to the next item
			folder_data.mItemIndex ++;

			return _true;
		}
	}

	// Walk sub-directory
	if ( folder_data.mSubDir.IsValid( ) )
	{
		// Feedback the sub-directory
		item_info.mDirectory	= folder_data.mSubDir;
		item_info.mItem			= _null;

		// Jump to the next sub-directory
		folder_data.mSubDir = folder_data.mSubDir->NextObject( );

		return _true;
	}

	// No any more files or directories what we can find
	return _false;
}

_ubool ManifestWalker::Walk( ManifestWalkerItemInfo& item_info, WStringPtr filter, _dword flags, _dword depth ) 
{
	// Walk the directories and items
	while ( mDirStack.Number( ) > 0 )
	{
		// Get the current directory
		FolderData& folder_data = mDirStack.Top( );

		// Read the current directory
		if ( ReadDir( folder_data, item_info, filter, flags, depth ) == _false )
		{
			// Complete the directory walk, pop it
			PopDir( );
			continue;
		}

		// Build the file info
		item_info.mDepth		= mDirStack.Number( );
		item_info.mItemNumber	= mItemNumber;

		// Build the absolute path
		if ( item_info.mItem )
		{
			WString path = folder_data.mDir->GetPath( );

			item_info.mRelativePath = BuildPath( folder_data.mDir, item_info.mItem->mName );
			item_info.mAbsolutePath	= Path::BuildFilePath( path, item_info.mItem->mName );
		}
		else
		{
			item_info.mRelativePath = BuildPath( folder_data.mDir, L"" );
			item_info.mAbsolutePath = item_info.mDirectory->GetPath( );
		}

		// Walk for the sub-directory
		if ( ( item_info.mDirectory.IsValid( ) ) && ( depth == -1 || depth < item_info.mDepth ) )
		{
			// Push the sub-directory
			PushDir( item_info.mDirectory );

			// Enumerate file only
			if ( flags & _FILE_FINDER_ENUMERATION_FILE_ONLY )
				continue; // Continue to enumerate
		}

		// We found file or directory
		return _true;
	}

	// Walk finished
	return _false;
}

//----------------------------------------------------------------------------
// ManifestFile Implementation
//----------------------------------------------------------------------------

ManifestFile::ManifestFile( )
{
	mRootDir = new ManifestDir( L"", _null );
}

ManifestFile::~ManifestFile( )
{
	Unload( );
}

IObject* ManifestFile::CloneTo( _ubool standalone ) const
{
	ManifestFile* manifest_file = new ManifestFile( );

	manifest_file->mVersion	= mVersion;
	manifest_file->mRootDir	= new ManifestDir( );
	manifest_file->mRootDir->Clone( mRootDir );

	return manifest_file;
}

_FILE_FORMAT ManifestFile::GetFileID( ) const
{
	return _FF_MANIFEST;
}

_ubool ManifestFile::LoadFromStream( IStreamReader* stream_reader )
{
	if ( stream_reader == _null )
		return _false;

	Unload( );

	// Create serializable node
	ISerializableNodeRef node = GetInterfaceFactory( )->CreateMarkupLangSerializableNode( stream_reader );
	if ( node.IsNull( ) )
	{
		WLOG_ERROR( L"Create markup language node of manifest file failed" );
		return _false;
	}

	// Read the version
	if ( node->Read( L"version", mVersion ) == _false )
	{
		WLOG_ERROR( L"The manifest file must has 'version' attribute" );
		return _false;
	}

	// Import from serializable node
	mRootDir = new ManifestDir( L"", _null );
	if ( mRootDir->Import( node ) == _false )
	{
		WLOG_ERROR( L"The manifest file import root directory failed" );
		return _false;
	}

	// Build the fast access items for root directory
	if ( mRootDir->BuildFastAccessItems( ) == _false )
		return _false;

	return _true;
}

_void ManifestFile::Unload( )
{
	mVersion = Version::cZero;

	EGE_RELEASE( mRootDir );
}

_ubool ManifestFile::SaveToStream( IStreamWriter* stream_writer, _dword flags ) const
{
	// Create xml file
	IMarkupLangFileRef xml_file = GetInterfaceFactory( )->CreateXMLFile( );
	if ( xml_file.IsNull( ) )
		return _false;

	// Build the root node
	IMarkupLangElement* xml_root_node = xml_file->GetRootElement( );
	if ( xml_root_node == _null )
		return _false;

	// Set the root name
	if ( xml_root_node->SetName( L"Manifest" ) == _false )
		return _false;

	// Create serializable node
	ISerializableNodeRef node = GetInterfaceFactory( )->CreateMarkupLangSerializableNode( xml_file );
	if ( node.IsNull( ) )
		return _false;

	// Write the version
	if ( node->Write( L"version", mVersion ) == _false )
		return _false;

	// Export to serializable node
	if ( mRootDir->Export( node ) == _false )
		return _false;

	// Save the manifest file
	return xml_file->SaveToStream( stream_writer );
}

IManifestDir* ManifestFile::GetRootDir( ) const
{
	return mRootDir;
}

IManifestWalkerPassRef ManifestFile::CreateWalker( IManifestDir* root_dir ) const
{
	return new ManifestWalker( root_dir );
}

IManifestWalkerPassRef ManifestFile::CreateWalker( WStringPtr path ) const
{
	// Search for the directory
	IManifestDir* root_dir = mRootDir->SearchSubDirByPath( path );
	if ( root_dir == _null )
		return _null;

	// Create walker
	return CreateWalker( root_dir );
}
