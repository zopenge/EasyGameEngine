//! @file     IStorageModule.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IStorageModule
//----------------------------------------------------------------------------

class IStorageModule : public IModule
{
public:
	//!	Get the working directory.
	//!	@param		none.
	//!	@return		The working directory.
	virtual WStringPtr GetWorkingDirectory( ) const PURE;
	//!	Set the working directory.
	//!	@param		working_dir		The working directory.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool SetWorkingDirectory( WStringPtr working_dir ) PURE;

	//!	Add the patch directory.
	//!	@param		patch_dir	The patch directory.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool AddPatchDirectory( WStringPtr patch_dir ) PURE;
	//!	Remove the patch directory.
	//!	@param		patch_dir	The patch directory.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool RemovePatchDirectory( WStringPtr patch_dir ) PURE;

	//!	Get the working archive.
	//!	@param		none.
	//!	@return		The working archive.
	virtual IArchive* GetWorkingArchive( ) PURE;
};

}