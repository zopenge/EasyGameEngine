#pragma once

namespace EGE {

/// <summary>
/// The directory of manifest.
/// </summary>
class IManifestDir : public ITObjectTree<IObject, IManifestDir> {
public:
	//!	Start to walk.
	//!	@param		item		The item data.
	//!	@param		params	The user defined params.
	//! @return		True indicates there are some files or directories what need to walk, otherwise indicates walk finished.
	typedef _ubool (*OnWalkItem)(const ManifestItemData& item, const QwordParams2& params);

public:
	//!	Set the name.
	//!	@param		name	The name.
	//!	@return		none.
	virtual _void SetName(WStringPtr name) PURE;
	//!	Get the name.
	//!	@param		none.
	//!	@return		The name.
	virtual WStringPtr GetName() const PURE;

	//!	Get the path.
	//!	@param		none.
	//!	@return		The path.
	virtual WString GetPath() const PURE;

	//!	Get the sub-item by index.
	//!	@param		index		The index of sub-item.
	//! @return		True indicates success, false indicates failure.
	virtual Array<const ManifestItemData*> GetItems() const PURE;
	//!	Remove sub-item.
	//!	@param		index		The index of sub-item.
	//! @return		none.
	virtual _void RemoveItem(_dword index) PURE;
	//!	Add sub-item.
	//!	@param		item		The item info.
	//! @return		True indicates success, false indicates failure or it's duplicate item.
	virtual _ubool AddItem(const ManifestItemData& item) PURE;
};

/// <summary>
/// The manifest file.
/// </summary>
class IManifestFile : public ISerializable {
public:
	//!	Set the version.
	//!	@param		version		The version.
	//!	@return		none.
	virtual _void SetVersion(const Version& version) PURE;
	//!	Get the version.
	//!	@param		none.
	//!	@return		The version.
	virtual const Version& GetVersion() const PURE;

	//!	Get the root directory.
	//!	@param		none.
	//!	@return		The root directory.
	virtual IManifestDir* GetRootDir() const PURE;
};

} // namespace EGE