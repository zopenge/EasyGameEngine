//! @file     XMLFile.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

#ifdef _USE_TINY_XML2_
typedef tinyxml2::XMLAttribute*	xmlAttrPtr;
typedef tinyxml2::XMLElement*	xmlNodePtr;
typedef tinyxml2::XMLDocument*	xmlDocPtr;
#endif

//----------------------------------------------------------------------------
// XMLAttribute
//----------------------------------------------------------------------------

class XMLAttribute : public INTERFACE_MARKUP_LANG_ATTRIBUTE_IMPL( IMarkupLangAttribute )
{
private:
	typedef INTERFACE_MARKUP_LANG_ATTRIBUTE_IMPL( IMarkupLangAttribute ) BaseClass;

private:
	//!	The XML attribute
	xmlAttrPtr	mXMLAttribute;

// TMarkupLangAttribute Interface
private:
	virtual _ubool		OnSetContentU( UStringPtr content ) override;
	virtual _ubool		OnSetContentW( WStringPtr content ) override;
	virtual UStringPtr	OnGetContentU( ) const override;

	virtual _ubool		OnGetValue( _ubool& value ) const override;
	virtual _ubool		OnGetValue( _int& value ) const override;
	virtual _ubool		OnGetValue( _dword& value ) const override;
	virtual _ubool		OnGetValue( _large& value ) const override;
	virtual _ubool		OnGetValue( _qword& value ) const override;
	virtual _ubool		OnGetValue( _float& value ) const override;
	virtual _ubool		OnGetValue( _double& value ) const override;

public:
	XMLAttribute( xmlAttrPtr xml_attribute );
	virtual ~XMLAttribute( );
	
// IMarkupLangAttribute Interface
public:
	virtual WStringR	GetName( _ubool with_prefix = _false ) const override;
};

//----------------------------------------------------------------------------
// XMLElement
//----------------------------------------------------------------------------

class XMLElement : public INTERFACE_MARKUP_LANG_ELEMENT_IMPL( IMarkupLangElement )
{
private:
	typedef INTERFACE_MARKUP_LANG_ELEMENT_IMPL( IMarkupLangElement ) BaseClass;

private:
	typedef Map< XMLAttribute*, WString > XMLAttributesMap;

private:
	//!	The XML document
	xmlDocPtr			mXMLDocument;

	//!	The XML element
	xmlNodePtr			mXMLElement;

	//! The attributes
	XMLAttributesMap	mXMLAttributes;

private:
	//!	The output buffer write callback function.
	static _int OnXMLOutputWriteFunc( _void* context, const _chara* buffer, _int len );

// TMarkupLangElement Interface
private:
    virtual IMarkupLangElementIteratorPassRef OnCreateElementIterator( IMarkupLangElement* element ) override;

public:
	XMLElement( xmlDocPtr xml_doc, xmlNodePtr xml_element, XMLElement* parent, XMLElement* prev, XMLElement* next );
	virtual ~XMLElement( );

// IMarkupLangElement Interface
public:
	virtual _ubool								SetName( WStringPtr name ) override;
	virtual WStringR							GetName( ) const override;

	virtual IMarkupLangElement*					InsertChildElementU( WStringPtr name, UStringPtr text, _ubool is_array_obj ) override;
	virtual IMarkupLangElement*					InsertNextElementU( WStringPtr name, UStringPtr text, _ubool is_array_obj ) override;

	virtual _void								RemoveElement( IMarkupLangElement* element ) override;
	virtual IMarkupLangElementIteratorPassRef	RemoveElement( IMarkupLangElementIterator* it ) override;

	virtual _dword								GetAttributesNumber( ) const override;
	virtual IMarkupLangAttribute*				GetAttributeByIndex( _dword index ) const override;

	virtual _ubool								HasAttribute( WStringPtr name, _ubool ignorecase = _false ) const override;
	virtual IMarkupLangAttribute*				SearchAttribute( WStringPtr name, _ubool ignorecase = _false ) const override;

	virtual _dword								GetValueU( ) const override;
	virtual _int								GetValueI( ) const override;
	virtual _float								GetValueF( ) const override;
	virtual _double								GetValueD( ) const override;

	virtual _ubool								SetValueU( _dword value ) override;
	virtual _ubool								SetValueI( _int value ) override;
	virtual _ubool								SetValueF( _float value ) override;
	virtual _ubool								SetValueD( _double value ) override;

	virtual _ubool								GetText( AString& text ) const override;
	virtual _ubool								GetText( UString& text ) const override;
	virtual _ubool								GetText( WString& text ) const override;
	virtual AStringR							GetTextA( ) const override;
	virtual UStringR							GetTextU( ) const override;
	virtual WStringR							GetTextW( ) const override;
	virtual _ubool								SetText( AStringPtr text ) override;
	virtual _ubool								SetText( UStringPtr text ) override;
	virtual _ubool								SetText( WStringPtr text ) override;

	virtual _ubool 								SetAttributeString( WStringPtr name, UStringPtr string ) override;
	virtual _ubool 								SetAttributeString( WStringPtr name, WStringPtr string ) override;

	virtual WStringR							DumpToString( ) const override;
	virtual WStringR							DumpToSchemaString( ) const override;
};

//----------------------------------------------------------------------------
// XMLFileDeclaration
//----------------------------------------------------------------------------

class XMLFileDeclaration : public INTERFACE_MARKUP_LANG_DECLARATION_IMPL( IMarkupLangDeclaration )
{
private:
	typedef INTERFACE_MARKUP_LANG_DECLARATION_IMPL( IMarkupLangDeclaration ) BaseClass;

private:
	//!	The XML document
	xmlDocPtr	mXmlDocument;

private:
	//!	Set XML document version.
	_void SetDocVersion( UStringPtr version );
	//!	Set XML document encoding.
	_void SetDocEncoding( UStringPtr encoding );

public:
	XMLFileDeclaration( xmlDocPtr document );
	virtual ~XMLFileDeclaration( );

// IMarkupLangDeclaration Interface
public:
	virtual _void	SetVersion( const Version& version ) override;

	virtual _void	SetEncoding( _ENCODING encoding ) override;
};

//----------------------------------------------------------------------------
// XMLFile
//----------------------------------------------------------------------------

class XMLFile : public TBaseFile< IMarkupLangFile >
{
private:
	typedef TBaseFile< IMarkupLangFile > BaseClass;

private:
	//!	The XML document
	xmlDocPtr			mXmlDocument;

	//!	The declaration of XML
	XMLFileDeclaration*	mDeclaration;
	//!	The root element of XML
	XMLElement*			mRootElement;

private:
	//!	The memory operation callback function.
	static void OnXMLFreeFunc( void* mem );
	static void* OnXMLMallocFunc( size_t size );
	static void* OnXMLReallocFunc( void* mem, size_t size );
	static char* OnXMLStrdupFunc( const char* str );

	//!	The generic XML error callback function.
#ifndef _USE_TINY_XML2_
	static _void OnXMLGenericErrorFunc( _void* ctx, const _chara* msg, ... );
	//!	The structure XML error callback function.
	static _void OnXMLStructuredErrorFunc( _void* userdata, xmlErrorPtr error );
	//!	The output buffer write callback function.
	static _int OnXMLOutputWriteFunc( _void* context, const _chara* buffer, _int len );
#endif

private:
#ifndef _USE_TINY_XML2_
	//!	The XSD validation.
	_ubool SchemaValidate( xmlSchemaParserCtxtPtr parser_context );
#endif

	//! Parse XML document.
	_ubool ParseXMLDocument( const _chara* string, _dword size );

public:
	XMLFile( );
	virtual ~XMLFile( );

public:
	//!	Initialize.
	static _ubool Initialize( );
	//!	Finalize.
	static _void Finalize( );

public:
	//!	Initialize XML document.
	_void InitXMLDocument( );

// IBaseFile Interface
public:
	virtual _FILE_FORMAT			GetFileID( ) const override;

	virtual _ubool 					LoadFromStream( IStreamReader* stream_reader ) override;
	virtual _void 					Unload( ) override;

	virtual _ubool					SaveToStream( IStreamWriter* stream_writer, _dword flags ) const override;

// IMarkupLangFile Interface
public:
	virtual IMarkupLangDeclaration*	GetDeclaration( ) override;

	virtual IMarkupLangElement*		GetRootElement( ) override;

	virtual _ubool					SchemaValidate( WStringPtr filename ) override;
	virtual _ubool					SchemaValidate( IStreamReader* stream_reader ) override;
};

}