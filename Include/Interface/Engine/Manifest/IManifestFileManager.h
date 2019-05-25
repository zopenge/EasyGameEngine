//! @file     IManifestFileManager.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IManifestFileManager
//----------------------------------------------------------------------------

class IManifestFileManager : public IObject
{
public:
	//!	Get manifest version.
	//!	@param		none.
	//!	@return		The latest manifest version.
	virtual const Version& GetManifestVersion( ) const PURE;

	//!	Clear manifest file.
	//!	@param		none.
	//!	@return		none.
	virtual _void ClearManifestFile( ) PURE;
	//!	Check whether has load manifest file or not.
	//!	@param		none.
	//!	@return		True indicates loaded manifest file successful.
	virtual _ubool HasManifestFile( ) const PURE;
	//!	Load the manifest file.
	//!	@param		manifest_file	The manifest file.
	//!	@return		The manifest file ID, -1 indicates failure.
	virtual _dword LoadManifestFile( const IManifestFile* manifest_file ) PURE;
	//!	Unload the manifest file.
	//!	@param		id			The manifest file ID.
	//!	@return		none.
	virtual _void UnloadManifestFile( _dword id ) PURE;

	//!	Check whether has resource.
	//!	@param		res_name	The resource name.
	//!	@return		True indicates it's existing.
	virtual _ubool HasResource( WStringPtr res_name ) const PURE;

	//!	Get the resource relative path in manifest file.
	//!	@param		res_name	The resource name.
	//!	@param		version		The resource for manifest version.
	//!	@return		The relative path in manifest file.
	virtual WString GetRelativePath( WStringPtr res_name ) const PURE;
	//!	Get the resource relative path in manifest file.
	//!	@param		res_name	The resource name.
	//!	@param		version		The resource for manifest version.
	//!	@return		The relative path in manifest file.
	virtual WString GetRelativePath( WStringPtr res_name, Version& version ) const PURE;
	//!	Get the resource relative path in manifest file.
	//!	@param		res_name	The resource name.
	//!	@param		version		The resource for manifest version.
	//!	@param		md5_code	The resource MD5 code.
	//!	@return		The relative path in manifest file.
	virtual WString GetRelativePath( WStringPtr res_name, Version& version, MD5Code& md5_code ) const PURE;

	//!	Get the MD5 code by resource name.
	//!	@param		res_name	The resource name.
	//!	@return		The MD5 code.
	virtual const MD5Code& GetMD5Code( WStringPtr res_name ) const PURE;
};

}