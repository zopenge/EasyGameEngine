#pragma once

namespace EGE {

/// <summary>
/// The archive.
/// </summary>
class IArchive : public IObject {
public:
	//!	When walk directory/file.
	//!	@param		item_info	The item info.
	//!	@param		parameters	The user defined parameters.
	//!	@return		True indicates continue to enumerate, false indicates break it.
	typedef _ubool (*OnWalkItem)(const FileData& item_info, const QwordParams2& parameters);

public:
	//!	Get archive's path.
	//!	@param		none.
	//!	@return		The path.
	virtual WStringPtr GetPath() const PURE;
	//!	Get archive's MD5 code.
	//!	@param		none.
	//!	@return		The MD5 code.
	virtual const MD5Code& GetMD5Code() const PURE;
	//!	Get archive's version.
	//!	@param		none.
	//!	@return		The version.
	virtual const Version& GetVersion() const PURE;

	//!	Get archive's manifest file.
	//!	@param		none.
	//!	@return		The manifest file.
	virtual IManifestFileRef GetManifestFile() const PURE;

	//!	Load resource stream.
	//!	@param		filePath The resource file path.
	//!	@return		The resource stream reader, null indicates the resource file stream is not existing.
	virtual IStreamReaderPassRef LoadResource(WStringPtr filePath) PURE;

	//!	Load patch archive.
	//!	@param		stream	The stream reader.
	//!	@return		The patch archive ID, -1 indicates failure.
	virtual _dword AddPatchArchive(IStreamReader* stream) PURE;
	//!	Remove patch archive.
	//!	@param		id			The patch archive ID.
	//!	@return		none.
	virtual _void RemovePatchArchive(_dword id) PURE;
	//!	Get patch archive.
	//!	@param		id			The patch archive ID.
	//!	@return		The patch archive interface.
	virtual IArchive* GetPatchArchive(_dword id) PURE;

	//!	Clear caches.
	//!	@param		none.
	//!	@return		none.
	virtual _void ClearCaches() PURE;

	//! Enumerate/Walk each files/directories in recursively.
	//!	@param		walk_item_func	The walk directory/file callback function.
	//!	@param		path			The relative directory path.
	//! @param		filter			The extension name filter.
	//!	@param		depth			The enumeration depth.
	//!	@param		parameters		The user defined parameters.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool EnumResources(OnWalkItem walk_item_func, WStringPtr path, WStringPtr filter = L"", _dword depth = -1, const QwordParams2& parameters = QwordParams2::cNull) const PURE;
};

} // namespace EGE