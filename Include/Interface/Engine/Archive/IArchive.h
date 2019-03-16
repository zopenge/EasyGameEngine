//! @file     IArchive.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IArchive
//----------------------------------------------------------------------------

class IArchive : public IObject
{
public:
	//!	When walk directory/file.
	//!	@param		item_info	The item info.
	//!	@param		parameters	The user defined parameters.
	//!	@return		True indicates continue to enumerate, false indicates break it.
	typedef _ubool (*OnWalkItem)( const FileInfo& item_info, const QwordParameters2& parameters );

public:
	//!	Get archive's path.
	//!	@param		none.
	//!	@return		The path.
	virtual WStringPtr GetPath( ) const PURE;
	//!	Get archive's MD5 code.
	//!	@param		none.
	//!	@return		The MD5 code.
	virtual const MD5Code& GetMD5Code( ) const PURE;
	//!	Get archive's version.
	//!	@param		none.
	//!	@return		The version.
	virtual const Version& GetVersion( ) const PURE;

	//!	Get archive's manifest file.
	//!	@param		none.
	//!	@return		The manifest file.
	virtual const IManifestFile* GetManifestFile( ) const PURE;

	//!	Get resource's absolute path.
	//!	@param		res_name	The resource name.
	//!	@return		The absolute path.
	virtual WStringR GetResourceAbsolutePath( WStringPtr res_name ) const PURE;
	//!	Get resource's relative path.
	//!	@param		res_name	The resource name.
	//!	@return		The relative path.
	virtual WStringR GetResourceRelativePath( WStringPtr res_name ) const PURE;
	//!	Get resource's MD5 code.
	//!	@param		res_name	The resource name.
	//!	@return		The MD5 code.
	virtual const MD5Code& GetResourceMD5Code( WStringPtr res_name ) const PURE;
	
	//!	Check whether has resource.
	//!	@param		res_name	The resource name.
	//!	@return		True indicates it's existing.
	virtual _ubool HasResourceByName( WStringPtr res_name ) const PURE;
	//!	Load resource stream.
	//!	@param		res_name	The resource name.
	//!	@return		The resource stream reader, null indicates the resource file stream is not existing.
	virtual IStreamReaderPassRef LoadResourceByName( WStringPtr res_name ) PURE;
	//!	Load markup file from working archive/document by name.
	//!	@param		res_name	The resource name.
	//!	@return		The markup language file interface.
	virtual IMarkupLangFilePassRef LoadMarkupLangFileByName( WStringPtr res_name ) PURE;
	//!	Load serializable node working archive/document file by name.
	//!	@param		res_name				The resource name.
	//!	@param		locate_at_first_child	True indicates locate at first child.
	//!	@return		The serializable node interface.
	virtual ISerializableNodePassRef LoadSerializableNodeByName( WStringPtr res_name, _ubool locate_at_first_child = _false ) PURE;
	//!	Load image file from working archive/document by name.
	//!	@param		res_name	The resource name.
	//!	@param		flags		The file flags, @see IImageFile::_FLAG.
	//!	@return		The image file interface.
	virtual IImageFilePassRef LoadImageFileByName( WStringPtr res_name, _dword flags = 0 ) PURE;

	//!	Check whether has resource.
	//!	@param		file_name	The file name.
	//!	@return		True indicates it's existing.
	virtual _ubool HasResourceByPath( WStringPtr file_name ) const PURE;
	//!	Load resource stream.
	//!	@param		file_name	The file name.
	//!	@return		The resource stream reader, null indicates the resource file stream is not existing.
	virtual IStreamReaderPassRef LoadResourceByPath( WStringPtr file_name ) PURE;
	//!	Load markup file from working archive/document.
	//!	@param		res_name	The resource name.
	//!	@return		The markup language file interface.
	virtual IMarkupLangFilePassRef LoadMarkupLangFileByPath( WStringPtr file_name ) PURE;
	//!	Load serializable node working archive/document file by file name.
	//!	@param		res_name				The resource name.
	//!	@param		locate_at_first_child	True indicates locate at first child.
	//!	@return		The serializable node interface.
	virtual ISerializableNodePassRef LoadSerializableNodeByPath( WStringPtr file_name, _ubool locate_at_first_child = _false ) PURE;
	//!	Load image file from working archive/document.
	//!	@param		res_name	The resource name.
	//!	@param		flags		The file flags, @see IImageFile::_FLAG.
	//!	@return		The image file interface.
	virtual IImageFilePassRef LoadImageFileByPath( WStringPtr file_name, _dword flags = 0 ) PURE;

	//!	Load patch archive.
	//!	@param		res_name	The resource name.
	//!	@param		password	The password of archive.
	//!	@return		The patch archive ID, -1 indicates failure.
	virtual _dword AddPatchArchive( WStringPtr res_name, WStringPtr password ) PURE;
	//!	Load patch archive.
	//!	@param		res_name					The resource name.
	//!	@param		password					The password of archive.
	//!	@param		manifest_encryption_type	The manifest file encryption type.
	//!	@param		manifest_encryption_key		The manifest file encryption key.
	//!	@return		The patch archive ID, -1 indicates failure.
	virtual _dword AddPatchArchive( WStringPtr res_name, WStringPtr password, _ENCRYPTION manifest_encryption_type, WStringPtr manifest_encryption_key ) PURE;
	//! Add patch archive.
	//!	@remark		The patch archives just only work for finding/loading resource, not work for creating resource operation.
	//!	@param		archive		The archive.
	//!	@return		The patch archive ID, -1 indicates failure.
	virtual _dword AddPatchArchive( IArchive* archive ) PURE;
	//!	Remove patch archive.
	//!	@param		id			The patch archive ID.
	//!	@return		none.
	virtual _void RemovePatchArchive( _dword id ) PURE;
	//!	Remove patch archive.
	//!	@param		archive		The archive.
	//!	@return		none.
	virtual _void RemovePatchArchive( IArchive* archive ) PURE;
	//!	Remove patch archive.
	//!	@param		path		The archive path.
	//!	@return		none.
	virtual _void RemovePatchArchive( WStringPtr path ) PURE;
	//!	Get patch archive.
	//!	@param		id			The patch archive ID.
	//!	@return		The patch archive interface.
	virtual IArchive* GetPatchArchive( _dword id ) PURE;

	//!	Clear caches.
	//!	@param		none.
	//!	@return		none.
	virtual _void ClearCaches( ) PURE;

	//! Enumerate/Walk each files/directories in recursively.
	//!	@param		walk_item_func	The walk directory/file callback function.
	//!	@param		path			The relative directory path.
	//! @param		filter			The extension name filter.
	//! @param		flags			The enumeration flags, @see _FILE_FINDER_ENUMERATION.
	//!	@param		depth			The enumeration depth.
	//!	@param		parameters		The user defined parameters.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool EnumResources( OnWalkItem walk_item_func, WStringPtr path, WStringPtr filter = L"", _dword flags = 0, _dword depth = -1, const QwordParameters2& parameters = QwordParameters2::cNull ) const PURE;
};

}