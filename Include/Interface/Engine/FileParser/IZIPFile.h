//! @file     IZIPFile.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IZIPFile
//----------------------------------------------------------------------------

class IZIPFile : public IBaseFile
{
public:
	//!	The flags
	enum _FLAG
	{
		//!	True indicates skip to build items
		_FLAG_SKIP_TO_BUILD_ITEMS	= 1 << 0,
		//!	True indicates use the file name without any directory
		_FLAG_USE_FILE_NAME_ONLY	= 1 << 1,
	};

public:
	//!	Get the Compression ratio.
	//!	@param		none.
	//!	@return		The compression ratio in [0.0, 1.0].
	virtual _float GetCompressionRatio( ) const PURE;

	//!	Add file into zip file.
	//!	@param		filename	The absolute file name.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool AddFile( WStringPtr filename ) PURE;
	//!	Add file into zip file with different path.
	//!	@param		filename		The absolute file name.
	//!	@param		filename_in_zip	The relative file name in ZIP file.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool AddFile( WStringPtr filename, WStringPtr filename_in_zip ) PURE;
	//!	Check whether has file or not.
	//!	@param		filename		The relative file name in ZIP file.
	//!	@return		True indicates has file.
	virtual _ubool HasFile( WStringPtr filename ) const PURE;
	//!	Get file stream.
	//!	@param		filename		The relative file name in ZIP file.
	//!	@return		The file stream.
	virtual IStreamReaderPassRef GetFile( WStringPtr filename ) PURE;

	//!	Add files in folder into zip file.
	//!	@param		dir_path	The absolute directory path.
	//! @param		filter		The extension name filter.
	//! @param		flags		The enumeration flags, @see _FILE_FINDER_ENUMERATION.
	//!	@param		depth		The enumeration depth.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool AddFolder( WStringPtr dir_path, WStringPtr filter = L"", _dword flags = 0, _dword depth = -1 ) PURE;
	//!	Add files in folder into zip file.
	//!	@param		dir_path		The absolute directory path.
	//!	@param		dir_path_in_zip	The relative directory path in ZIP file.
	//! @param		filter			The extension name filter.
	//! @param		flags			The enumeration flags, @see _FILE_FINDER_ENUMERATION.
	//!	@param		depth			The enumeration depth.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool AddFolder( WStringPtr dir_path, WStringPtr dir_path_in_zip, WStringPtr filter = L"", _dword flags = 0, _dword depth = -1 ) PURE;

	//!	Get the files number.
	//!	@param		none.
	//!	@return		The files number.
	virtual _dword GetFileNumber( ) const PURE;
	//!	Get the file name by index.
	//!	@param		index	The file index.
	//!	@return		The file name.
	virtual WStringPtr GetFileNameByIndex( _dword index ) PURE;
	//!	Get the file stream by index.
	//!	@param		index	The file index.
	//!	@return		The file stream.
	virtual IStreamReaderPassRef GetFileStreamByIndex( _dword index ) PURE;
};

}