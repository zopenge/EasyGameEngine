#pragma once

namespace EGE {

/// <summary>
/// The markup attribute.
/// </summary>
class IMarkupAttribute {
public:
	//!	Get name.
	//!	@param		none.
	//!	@return		The name.
	virtual WString GetName() const PURE;

	//!	Set attribute value.
	//!	@param		value	The attribute value.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetValue(const Variable& value) PURE;
	//!	Set attribute value.
	//!	@param		string	The value string.
	//! @return		none.
	virtual _ubool SetString(WStringPtr string) PURE;

	//!	Get attribute value.
	//!	@param		none.
	//! @return		The attribute value.
	virtual const Variable& GetValue() const PURE;
	//!	Get attribute string in UTF-16 mode.
	//!	@param		none.
	//! @return		The value info.
	virtual WString GetString() const PURE;
};

/// <summary>
/// The markup element.
/// </summary>
class IMarkupElement {
public:
	//!	Set name.
	//!	@param		name		The name.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetName(WStringPtr name) PURE;
	//!	Get name.
	//!	@param		none.
	//!	@return		The name.
	virtual WString GetName() const PURE;

	//!	Set text.
	//!	@param		text		The text.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetText(WStringPtr text) PURE;
	//!	Get text.
	//!	@param		none.
	//!	@return		The text.
	virtual WString GetText() const PURE;

	//!	Get the depth.
	//!	@param		none.
	//!	@return		The depth of element.
	virtual _dword GetDepth() const PURE;

	//!	Get the parent element.
	//! @param		none.
	//! @return		The parent element, _null indicates hasn't the parent element.
	virtual IMarkupElement* GetParentElement() const PURE;

	//!	Get the child element by index.
	//!	@param		index		The child element index.
	//!	@return		The child element.
	virtual Array<IMarkupElement*> GetChildElements() const PURE;
	//!	Add child element to the end.
	//!	@param		name			The child element name.
	//! @return		The element, _null indicates failure.
	virtual IMarkupElement* AddChildElement(WStringPtr name) PURE;
	//!	Add child element with index.
	//!	@param		index			The child index, -1 indicates append it to tail.
	//! @return		The element, _null indicates failure.
	virtual IMarkupElement* AddChildElement(_dword index = -1) PURE;
	//!	Remove child element.
	//!	@param		element		The element.
	//! @return		none.
	virtual _void RemoveChildElement(IMarkupElement* element) PURE;

	//!	Get attributes.
	//!	@param		none.
	//!	@return		The attributes.
	virtual Array<IMarkupAttribute*> GetAttributes() const PURE;

	//!	Dump to string.
	//!	@param		none.
	//!	@return		The formatted string contains all child nodes.
	virtual WString DumpToString() const PURE;
};

/// <summary>
/// The markup declaration.
/// </summary>
class IMarkupDeclaration {
public:
	//!	Set the XML version.
	//!	@param		version		The version.
	//! @return		none.
	virtual _void SetVersion(const Version& version) PURE;
	//!	Get the XML version.
	//!	@param		none.
	//! @return		The XML version.
	virtual const Version& GetVersion() const PURE;

	//!	Set the XML encoding.
	//!	@param		encoding	The encoding type.
	//! @return		none.
	virtual _void SetEncoding(Encoding encoding) PURE;
	//!	Get the XML encoding.
	//!	@param		none.
	//! @return		The XML encoding type.
	virtual Encoding GetEncoding() const PURE;
};

/// <summary>
/// The markup file.
/// </summary>
class IMarkupFile : public IObject {
public:
	//!	Get the declaration.
	//!	@param		none.
	//! @return		The declaration interface.
	virtual IMarkupDeclaration* GetDeclaration() PURE;

	//!	Get the root element.
	//!	@param		none.
	//! @return		The root element interface.
	virtual IMarkupElement* GetRootElement() PURE;
};

} // namespace EGE