#pragma once

namespace EGE {

/// <summary>
/// The object tree.
/// </summary>
template <typename Type, typename NodeInterface>
class ITObjectTree : public Type {
public:
	typedef _void (*OnObjectCallback)(NodeInterface* object);

public:
	//!	Get the root object.
	//!	@param		none.
	//!	@return		The root object.
	virtual NodeInterface* GetRootObject() PURE;

	//!	Set the parent object.
	//!	@param		node		The node interface.
	//!	@return		The parent object.
	virtual _void SetParent(NodeInterface* node) PURE;
	//!	Get the parent object.
	//!	@param		none.
	//!	@return		The parent object.
	virtual NodeInterface* GetParent() PURE;
	//!	Get the parent objects.
	//!	@param		none.
	//!	@return		The parent objects.
	virtual Array<NodeInterface*> GetParents() PURE;

	//!	Get the children objects.
	//!	@param		none.
	//!	@return		The children objects.
	virtual Array<NodeInterface*> GetChildren() PURE;

	//!	Add children.
	//!	@param		object		The node object.
	//! @return		none.
	virtual _void Add(NodeInterface* object) PURE;
	//!	Insert children.
	//!	@param		index		The children index.
	//!	@param		object		The node object.
	//!	@return		none.
	virtual _void Insert(_dword index, NodeInterface* object) PURE;
	//!	Remove children.
	//!	@param		object		The node object.
	//!	@return		none.
	virtual _void Remove(NodeInterface* object) PURE;

	/// <summary>
	/// Check whether it's child of it.
	/// </summary>
	/// <param name="node"></param>
	/// <returns>True indicates it's child of it</returns>
	virtual _ubool IsChildOf(const NodeInterface* node) const PURE;

	/// <summary>
	/// Traverse children.
	/// </summary>
	/// <param name="func"></param>
	/// <param name="recursive"></param>
	/// <returns></returns>
	virtual _void Traverse(OnObjectCallback func, _ubool recursive = _true) PURE;
};

} // namespace EGE