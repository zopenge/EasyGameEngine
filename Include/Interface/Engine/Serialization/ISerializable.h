//! @file     ISerializable.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ITSerializable
//----------------------------------------------------------------------------

template< typename Type >
class ITSerializable : public Type
{
public:
	//!	Import properties.
	//!	@param		node	The serializable node.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool Import( ISerializableNode* node ) PURE;
	//!	Export properties.
	//!	@param		node	The serializable node.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool Export( ISerializableNode* node ) const PURE;

	//!	Import properties from file.
	//!	@param		filename	The file name.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool ImportFromFile( WStringPtr filename ) PURE;
	//!	Import properties from XML string.
	//!	@param		xml_string	The XML string.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool ImportFromXMLString( WStringPtr xml_string ) PURE;
	//!	Export properties to file.
	//!	@param		filename	The file name.
	//!	@param		root_name	The root name.
	//!	@param		tag_name	The tag name.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool ExportToFile( WStringPtr filename, WStringPtr root_name, WStringPtr tag_name ) PURE;
	//!	Export properties to XML string.
	//!	@param		root_name	The root name.
	//!	@param		tag_name	The tag name.
	//!	@param		xml_string	The XML string.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool ExportToXMLString( WStringPtr root_name, WStringPtr tag_name, WString& xml_string ) PURE;

	//!	Import properties.
	//!	@param		node	The serializable node.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool ImportFromStream( IStreamReader* stream_reader ) PURE;
	//!	Export properties.
	//!	@param		node	The serializable node.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool ExportToStream( IStreamWriter* stream_writer ) const PURE;
};

//----------------------------------------------------------------------------
// ISerializable
//----------------------------------------------------------------------------

class ISerializable : public ITSerializable< IObject >
{
};

}