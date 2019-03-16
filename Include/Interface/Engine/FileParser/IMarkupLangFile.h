//! @file     IMarkupLangFile.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

class IMarkupLangElement;

//----------------------------------------------------------------------------
// IMarkupLangElementIterator
//----------------------------------------------------------------------------

class IMarkupLangElementIterator : public ITIterator< IMarkupLangElement*, IObject >
{
public:
};

//----------------------------------------------------------------------------
// IMarkupLangAttribute
//----------------------------------------------------------------------------

class IMarkupLangAttribute
{
public:
	//!	Get name.
	//!	@param		with_prefix		True indicates with prefix name.
	//!	@return		The name.
	virtual WStringR GetName( _ubool with_prefix = _false ) const PURE;

	//!	Set attribute value.
	//!	@param		value	The attribute value.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetBool( _ubool value ) PURE;
	//!	Set attribute value.
	//!	@param		value	The attribute value.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetLong( _int value ) PURE;
	//!	Set attribute value.
	//!	@param		value	The attribute value.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetDword( _dword value ) PURE;
	//!	Set attribute value.
	//!	@param		value	The attribute value.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetLarge( _large value ) PURE;
	//!	Set attribute value.
	//!	@param		value	The attribute value.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetQword( _qword value ) PURE;
	//!	Set attribute value.
	//!	@param		value	The attribute value.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetDouble( _double value ) PURE;
	//!	Set attribute value.
	//!	@param		value	The attribute value.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetOword( const MD5Code& value ) PURE;
	//!	Set attribute value.
	//!	@param		string	The value string.
	//! @return		none.
	virtual _ubool SetString( WStringPtr string ) PURE;
	//!	Set attribute color.
	//!	@param		color	The attribute color.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetColor( const Color& color ) PURE;
	//!	Set attribute version.
	//!	@param		version	The attribute version.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetVersion( const Version& version ) PURE;

	//!	Get attribute value.
	//!	@param		none.
	//! @return		The value info.
	virtual _ubool GetBool( ) const PURE;
	//!	Get attribute value.
	//!	@param		none.
	//! @return		The value info.
	virtual _int GetLong( ) const PURE;
	//!	Get attribute value.
	//!	@param		none.
	//! @return		The value info.
	virtual _dword GetDword( ) const PURE;
	//!	Get attribute value.
	//!	@param		none.
	//! @return		The value info.
	virtual _large GetLarge( ) const PURE;
	//!	Get attribute value.
	//!	@param		none.
	//! @return		The value info.
	virtual _qword GetQword( ) const PURE;
	//!	Get attribute value.
	//!	@param		none.
	//! @return		The value info.
	virtual _float GetFloat( ) const PURE;
	//!	Get attribute value.
	//!	@param		none.
	//! @return		The value info.
	virtual _double GetDouble( ) const PURE;
	//!	Get attribute string in UTF-8 mode.
	//!	@param		none.
	//! @return		The value info.
	virtual UStringR GetStringU( ) const PURE;
	//!	Get attribute string in UTF-16 mode.
	//!	@param		none.
	//! @return		The value info.
	virtual WStringR GetStringW( ) const PURE;
	//!	Get attribute value.
	//!	@param		none.
	//! @return		The value info.
	virtual MD5Code GetMD5Code( ) const PURE;
	//!	Get attribute color.
	//!	@param		none.
	//! @return		The value info.
	virtual Color GetColor( ) const PURE;
	//!	Get attribute version.
	//!	@param		none.
	//! @return		The value info.
	virtual Version GetVersion( ) const PURE;
};

//----------------------------------------------------------------------------
// IMarkupLangElement
//----------------------------------------------------------------------------

class IMarkupLangElement
{
public:
	//!	Check whether it's array object.
	//!	@param		none.
	//!	@return		True indicates it's array object.
	virtual _ubool IsArrayObject( ) const PURE;

	//!	Get the depth.
	//!	@param		none.
	//!	@return		The depth of element.
	virtual _dword GetDepth( ) const PURE;

	//!	Set name.
	//!	@param		name		The name.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetName( WStringPtr name ) PURE;
	//!	Get name.
	//!	@param		none.
	//!	@return		The name.
	virtual WStringR GetName( ) const PURE;

	//!	Get the total child element number.
	//!	@param		none.
	//!	@return		The total child element number.
	virtual _dword GetChildElementNumber( ) const PURE;
	//!	Get the child element by index.
	//!	@param		index		The child element index.
	//!	@return		The child element.
	virtual IMarkupLangElement* GetChildElementByIndex( _dword index ) const PURE;
	//!	Search for the child element by name.
	//!	@param		name		The child element name.
	//!	@param		ignorecase	True indicates case insensitive when parsing.
	//! @return		The child element, _null indicates not existing.
	virtual IMarkupLangElement* GetChildElementByName( WStringPtr name, _ubool ignorecase = _false ) const PURE;
	//!	Search for the child element by text.
	//!	@param		text		The child element text.
	//!	@param		ignorecase	True indicates case insensitive when parsing.
	//! @return		The child element, _null indicates not existing.
	virtual IMarkupLangElement* GetChildElementByText( WStringPtr text, _ubool ignorecase = _false ) const PURE;

	//!	Check whether has child element or not.
	//!	@param		name		The child element name.
	//!	@param		ignorecase	True indicates case insensitive when parsing.
	//!	@return		True indicates the child element with specified name is existing.
	virtual _ubool HasChildElement( WStringPtr name, _ubool ignorecase = _false ) const PURE;
	//!	Get the child element text by name.
	//!	@param		name		The child element name.
	//!	@param		text		The element text.
	//!	@param		ignorecase	True indicates case insensitive when parsing.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool GetChildElementTextByName( WStringPtr name, UString& text, _ubool ignorecase = _false ) const PURE;
	//!	Get the child element text by name.
	//!	@param		name		The child element name.
	//!	@param		text		The element text.
	//!	@param		ignorecase	True indicates case insensitive when parsing.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool GetChildElementTextByName( WStringPtr name, WString& text, _ubool ignorecase = _false ) const PURE;
	//!	Get the child element text by name.
	//!	@param		name		The child element name.
	//!	@param		ignorecase	True indicates case insensitive when parsing.
	//! @return		The element text.
	virtual UStringR GetChildElementTextByNameU( WStringPtr name, _ubool ignorecase = _false ) const PURE;
	//!	Get the child element text by name.
	//!	@param		name		The child element name.
	//!	@param		ignorecase	True indicates case insensitive when parsing.
	//! @return		The element text.
	virtual WStringR GetChildElementTextByNameW( WStringPtr name, _ubool ignorecase = _false ) const PURE;

	//!	Get the first child element.
	//! @param		none.
	//! @return		The first child element, _null indicates hasn't any child element.
	virtual IMarkupLangElement* GetFirstChildElement( ) const PURE;
	//!	Get the last child element.
	//! @param		none.
	//! @return		The last child element, _null indicates hasn't any child element.
	virtual IMarkupLangElement* GetLastChildElement( ) const PURE;
	//!	Get the parent element.
	//! @param		none.
	//! @return		The parent element, _null indicates hasn't the parent element.
	virtual IMarkupLangElement* GetParentElement( ) const PURE;
	//!	Get the previous element.
	//! @param		none.
	//! @return		The previous element, _null indicates hasn't the previous element.
	virtual IMarkupLangElement* GetPrevElement( ) const PURE;
	//!	Get the next element.
	//! @param		none.
	//! @return		The next element, _null indicates hasn't the next element.
	virtual IMarkupLangElement* GetNextElement( ) const PURE;
	//!	Get the head element.
	//! @param		none.
	//! @return		The head element.
	virtual IMarkupLangElement* GetHeadElement( ) const PURE;
	//!	Get the tail element.
	//! @param		none.
	//! @return		The tail element.
	virtual IMarkupLangElement* GetTailElement( ) const PURE;

	//!	Get the previous element text by name.
	//!	@param		name		The element name.
	//!	@param		ignorecase	True indicates case insensitive when parsing.
	//! @return		The element, _null indicates not existing.
	virtual IMarkupLangElement* GetPrevElementByName( WStringPtr name, _ubool ignorecase = _false ) const PURE;
	//!	Get the next element text by name.
	//!	@param		name		The element name.
	//!	@param		ignorecase	True indicates case insensitive when parsing.
	//! @return		The element, _null indicates not existing.
	virtual IMarkupLangElement* GetNextElementByName( WStringPtr name, _ubool ignorecase = _false ) const PURE;

	//!	Insert child element to the end.
	//!	@param		name			The child element name.
	//!	@param		text			The child element text.
	//!	@return		is_array_obj	True indicates it's array object.
	//! @return		The element, _null indicates failure.
	virtual IMarkupLangElement* InsertChildElementU( WStringPtr name, UStringPtr text, _ubool is_array_obj ) PURE;
	//!	Insert child element to the end.
	//!	@param		name			The child element name.
	//!	@param		text			The child element text.
	//!	@return		is_array_obj	True indicates it's array object.
	//! @return		The element, _null indicates failure.
	virtual IMarkupLangElement* InsertChildElementW( WStringPtr name, WStringPtr text, _ubool is_array_obj ) PURE;
	//!	Insert child element to the end.
	//!	@param		element			The child element.
	//!	@param		all_child		True indicates insert all childs too.
	//! @return		The element, _null indicates failure.
	virtual IMarkupLangElement* InsertChildElement( const IMarkupLangElement* element, _ubool all_child ) PURE;
	//!	Insert next element to the end.
	//!	@param		name			The next element name.
	//!	@param		text			The next element text.
	//!	@return		is_array_obj	True indicates it's array object.
	//! @return		The element, _null indicates failure.
	virtual IMarkupLangElement* InsertNextElementU( WStringPtr name, UStringPtr text, _ubool is_array_obj ) PURE;
	//!	Insert next element to the end.
	//!	@param		name			The next element name.
	//!	@param		text			The next element text.
	//!	@return		is_array_obj	True indicates it's array object.
	//! @return		The element, _null indicates failure.
	virtual IMarkupLangElement* InsertNextElementW( WStringPtr name, WStringPtr text, _ubool is_array_obj ) PURE;
	//!	Insert next element to the end.
	//!	@param		element			The child element.
	//!	@param		all_child		True indicates insert all childs too.
	//! @return		The element, _null indicates failure.
	virtual IMarkupLangElement* InsertNextElement( const IMarkupLangElement* element, _ubool all_child ) PURE;

	//!	Insert child element as array object to the end.
	//!	@param		name		The child element name.
	//! @return		The element, _null indicates failure.
	virtual IMarkupLangElement* InsertChildArrayObj( WStringPtr name ) PURE;
	//!	Append child element into array object to the end.
	//!	@param		none.
	//! @return		The element, _null indicates failure.
	virtual IMarkupLangElement* AppendElementOfArrayObj( ) PURE;
	//!	Append child element as array object to the end.
	//!	@param		element		The element of array.
	//! @return		The index of appended element, -1 indicates failure.
	virtual _dword AppendElementOfArrayObj( IMarkupLangElement* element ) PURE;
	//!	Append child element/value as array object to the end.
	//!	@param		value		The element's value.
	//! @return		The index of appended element, -1 indicates failure.
	virtual _dword AppendValueUOfArrayObj( _dword value ) PURE;
	//!	Append child element/value as array object to the end.
	//!	@param		value		The element's value.
	//! @return		The index of appended element, -1 indicates failure.
	virtual _dword AppendValueIOfArrayObj( _int value ) PURE;
	//!	Append child element/value as array object to the end.
	//!	@param		value		The element's value.
	//! @return		The index of appended element, -1 indicates failure.
	virtual _dword AppendValueFOfArrayObj( _float value ) PURE;
	//!	Append child element/value as array object to the end.
	//!	@param		value		The element's value.
	//! @return		The index of appended element, -1 indicates failure.
	virtual _dword AppendValueDOfArrayObj( _double value ) PURE;
	//!	Get the number of array object's sub-elements.
	//!	@param		none.
	//!	@return		The number of array object's sub-elements.
	virtual _dword GetSubElementsNumber( ) const PURE;
	//!	Get the sub-element of array object.
	//!	@param		index		The index of sub-elements.
	//!	@return		The element of array object.
	virtual IMarkupLangElement* GetSubElementByIndex( _dword index ) const PURE;

	//!	Remove self.
	//!	@param		none.
	//!	@return		none.
	virtual _void Remove( ) PURE;
	//!	Remove element.
	//!	@param		element		The element.
	//! @return		none.
	virtual _void RemoveElement( IMarkupLangElement* element ) PURE;
	//!	Remove element by iterator.
	//!	@param		iterator	The element iterator.
	//! @return		The next iterator.
	virtual IMarkupLangElementIteratorPassRef RemoveElement( IMarkupLangElementIterator* it ) PURE;

	//!	Create the self element iterator.
	//!	@param		none.
	//!	@return		The element iterator.
	virtual IMarkupLangElementIteratorPassRef CreateSelfElementIterator( ) PURE;
	//!	Create the child element iterator.
	//!	@param		name		The child element name.
	//!	@param		recursive	True indicates find the child recursively.
	//!	@return		The element iterator.
	virtual IMarkupLangElementIteratorPassRef CreateChildElementIterator( WStringPtr name, _ubool recursive = _false ) PURE;

	//!	Get attributes number.
	//!	@param		none.
	//!	@return		The attributes number.
	virtual _dword GetAttributesNumber( ) const PURE;
	//!	Get attribute by index.
	//!	@param		index		The index of attributes.
	//!	@return		The attribute.
	virtual IMarkupLangAttribute* GetAttributeByIndex( _dword index ) const PURE;

	//!	Check whether has attribute or not.
	//!	@param		name		The attribute name.
	//!	@param		ignorecase	True indicates case insensitive when parsing.
	//!	@return		True indicates the attribute with specified name is existing.
	virtual _ubool HasAttribute( WStringPtr name, _ubool ignorecase = _false ) const PURE;
	//!	Search the attribute by name.
	//!	@param		name		The attribute name.
	//!	@param		ignorecase	True indicates case insensitive when parsing.
	//!	@return		The attribute.
	virtual IMarkupLangAttribute* SearchAttribute( WStringPtr name, _ubool ignorecase = _false ) const PURE;

	//!	Get the node's value.
	//!	@param		none.
	//! @return		The value.
	virtual _dword GetValueU( ) const PURE;
	//!	Get the node's value.
	//!	@param		none.
	//! @return		The value.
	virtual _int GetValueI( ) const PURE;
	//!	Get the node's value.
	//!	@param		none.
	//! @return		The value.
	virtual _float GetValueF( ) const PURE;
	//!	Get the node's value.
	//!	@param		none.
	//! @return		The value.
	virtual _double GetValueD( ) const PURE;

	//!	Set the node's value.
	//!	@param		value		The value.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetValueU( _dword value ) PURE;
	//!	Set the node's value.
	//!	@param		value		The value.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetValueI( _int value ) PURE;
	//!	Set the node's value.
	//!	@param		value		The value.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetValueF( _float value ) PURE;
	//!	Set the node's value.
	//!	@param		value		The value.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetValueD( _double value ) PURE;

	//!	Get the element text.
	//!	@param		text		The element text.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool GetText( AString& text ) const PURE;
	//!	Get the element text.
	//!	@param		text		The element text.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool GetText( UString& text ) const PURE;
	//!	Get the element text.
	//!	@param		text		The element text.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool GetText( WString& text ) const PURE;
	//!	Get the element text.
	//!	@param		none.
	//! @return		The element text.
	virtual AStringR GetTextA( ) const PURE;
	//!	Get the element text.
	//!	@param		none.
	//! @return		The element text.
	virtual UStringR GetTextU( ) const PURE;
	//!	Get the element text.
	//!	@param		none.
	//! @return		The element text.
	virtual WStringR GetTextW( ) const PURE;
	//!	Set the element text.
	//!	@param		text		The element text.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetText( AStringPtr text ) PURE;
	//!	Set the element text.
	//!	@param		text		The element text.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetText( UStringPtr text ) PURE;
	//!	Set the element text.
	//!	@param		text		The element text.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetText( WStringPtr text ) PURE;

	//!	Get attribute value.
	//!	@param		name		The attribute name.
	//!	@param		value		The attribute value.
	//!	@param		ignorecase	True indicates case insensitive when parsing.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool GetAttributeBool( WStringPtr name, _ubool& value, _ubool ignorecase = _false ) const PURE;
	//!	Get attribute value.
	//!	@param		name		The attribute name.
	//!	@param		value		The attribute value.
	//!	@param		ignorecase	True indicates case insensitive when parsing.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool GetAttributeLong( WStringPtr name, _int& value, _ubool ignorecase = _false ) const PURE;
	//!	Get attribute value.
	//!	@param		name		The attribute name.
	//!	@param		value		The attribute value.
	//!	@param		ignorecase	True indicates case insensitive when parsing.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool GetAttributeDword( WStringPtr name, _dword& value, _ubool ignorecase = _false ) const PURE;
	//!	Get attribute value.
	//!	@param		name		The attribute name.
	//!	@param		value		The attribute value.
	//!	@param		ignorecase	True indicates case insensitive when parsing.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool GetAttributeLarge( WStringPtr name, _large& value, _ubool ignorecase = _false ) const PURE;
	//!	Get attribute value.
	//!	@param		name		The attribute name.
	//!	@param		value		The attribute value.
	//!	@param		ignorecase	True indicates case insensitive when parsing.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool GetAttributeQword( WStringPtr name, _qword& value, _ubool ignorecase = _false ) const PURE;
	//!	Get attribute value.
	//!	@param		name		The attribute name.
	//!	@param		value		The attribute value.
	//!	@param		ignorecase	True indicates case insensitive when parsing.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool GetAttributeDouble( WStringPtr name, _double& value, _ubool ignorecase = _false ) const PURE;
	//!	Get attribute string in ANSI mode.
	//!	@param		name		The attribute name.
	//!	@param		value		The attribute string.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool GetAttributeString( WStringPtr name, UString& string, _ubool ignorecase = _false ) const PURE;
	//!	Get attribute string in UNICODE mode.
	//!	@param		name		The attribute name.
	//!	@param		value		The attribute string.
	//!	@param		ignorecase	True indicates case insensitive when parsing.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool GetAttributeString( WStringPtr name, WString& string, _ubool ignorecase = _false ) const PURE;
	//!	Get attribute value.
	//!	@param		name		The attribute name.
	//!	@param		value		The attribute value.
	//!	@param		ignorecase	True indicates case insensitive when parsing.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool GetAttributeMD5Code( WStringPtr name, MD5Code& value, _ubool ignorecase = _false ) const PURE;
	//!	Get attribute color.
	//!	@param		name		The attribute name.
	//!	@param		color		The attribute color.
	//!	@param		ignorecase	True indicates case insensitive when parsing.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool GetAttributeColor( WStringPtr name, Color& color, _ubool ignorecase = _false ) const PURE;
	//!	Get attribute version.
	//!	@param		name		The attribute name.
	//!	@param		version		The attribute version.
	//!	@param		ignorecase	True indicates case insensitive when parsing.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool GetAttributeVersion( WStringPtr name, Version& version, _ubool ignorecase = _false ) const PURE;

	//!	Set attribute value.
	//!	@param		name		The attribute name.
	//!	@param		value		The attribute value.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetAttributeBool( WStringPtr name, _ubool value ) PURE;
	//!	Set attribute value.
	//!	@param		name		The attribute name.
	//!	@param		value		The attribute value.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetAttributeLong( WStringPtr name, _int value ) PURE;
	//!	Set attribute value.
	//!	@param		name		The attribute name.
	//!	@param		value		The attribute value.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetAttributeDword( WStringPtr name, _dword value ) PURE;
	//!	Set attribute value.
	//!	@param		name		The attribute name.
	//!	@param		value		The attribute value.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetAttributeLarge( WStringPtr name, _large value ) PURE;
	//!	Set attribute value.
	//!	@param		name		The attribute name.
	//!	@param		value		The attribute value.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetAttributeQword( WStringPtr name, _qword value ) PURE;
	//!	Set attribute value.
	//!	@param		name		The attribute name.
	//!	@param		value		The attribute value.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetAttributeDouble( WStringPtr name, _double value ) PURE;
	//!	Set attribute string.
	//!	@param		name		The attribute name.
	//!	@param		string		The attribute string.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetAttributeString( WStringPtr name, UStringPtr string ) PURE;
	//!	Set attribute string.
	//!	@param		name		The attribute name.
	//!	@param		string		The attribute string.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetAttributeString( WStringPtr name, WStringPtr string ) PURE;
	//!	Set attribute value.
	//!	@param		name		The attribute name.
	//!	@param		value		The attribute value.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetAttributeMD5Code( WStringPtr name, const MD5Code& value ) PURE;
	//!	Set attribute color.
	//!	@param		name		The attribute name.
	//!	@param		color		The attribute color.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetAttributeColor( WStringPtr name, const Color& color ) PURE;
	//!	Set attribute version.
	//!	@param		name		The attribute name.
	//!	@param		version		The attribute version.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SetAttributeVersion( WStringPtr name, const Version& version ) PURE;

	//!	Dump to string.
	//!	@param		none.
	//!	@return		The formatted string contains all child nodes.
	virtual WStringR DumpToString( ) const PURE;
	//!	Dump to schema string.
	//!	@param		none.
	//!	@return		The schema string contains all child nodes.
	virtual WStringR DumpToSchemaString( ) const PURE;
};

//----------------------------------------------------------------------------
// IMarkupLangDeclaration
//----------------------------------------------------------------------------

class IMarkupLangDeclaration
{
public:
	//!	Set the XML version.
	//!	@param		version		The version.
	//! @return		none.
	virtual _void SetVersion( const Version& version ) PURE;
	//!	Get the XML version.
	//!	@param		none.
	//! @return		The XML version.
	virtual const Version& GetVersion( ) const PURE;

	//!	Set the XML encoding.
	//!	@param		encoding	The encoding type.
	//! @return		none.
	virtual _void SetEncoding( _ENCODING encoding ) PURE;
	//!	Get the XML encoding.
	//!	@param		none.
	//! @return		The XML encoding type.
	virtual _ENCODING GetEncoding( ) const PURE;
};

//----------------------------------------------------------------------------
// IMarkupLangFile
//----------------------------------------------------------------------------

class IMarkupLangFile : public IBaseFile
{
public:
	//!	Get the declaration.
	//!	@param		none.
	//! @return		The declaration interface.
	virtual IMarkupLangDeclaration* GetDeclaration( ) PURE;

	//!	Get the root element.
	//!	@param		none.
	//! @return		The root element interface.
	virtual IMarkupLangElement* GetRootElement( ) PURE;

	//!	Validate with XSD file.
	//!	@param		filename		The XSD file name.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SchemaValidate( WStringPtr filename ) PURE;
	//!	Validate with XSD stream.
	//!	@param		stream_reader	The XSD stream reader.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool SchemaValidate( IStreamReader* stream_reader ) PURE;
};

}