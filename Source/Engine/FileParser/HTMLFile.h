//! @file     HTMLFile.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright ...

#pragma once

#ifndef _EGE_DISABLE_HTML_FILE_

namespace EGE
{

//----------------------------------------------------------------------------
// HTMLAttribute
//----------------------------------------------------------------------------

class HTMLAttribute : public INTERFACE_MARKUP_LANG_ATTRIBUTE_IMPL( IHTMLAttribute )
{
private:
	typedef INTERFACE_MARKUP_LANG_ATTRIBUTE_IMPL( IHTMLAttribute ) BaseClass;

private:
	//!	The HTML attribute
	GumboAttribute*	mGumboAttribute;

// TMarkupLangAttribute Interface
private:
	virtual _ubool		OnSetContentU( UStringPtr content ) override;
	virtual _ubool		OnSetContentW( WStringPtr content ) override;
	virtual UStringPtr	OnGetContentU( ) const override;

	virtual _ubool		OnGetValue( _ubool& value ) const override;
	virtual _ubool		OnGetValue( _int& value ) const override;
	virtual _ubool		OnGetValue( _dword& value ) const override;
	virtual _ubool		OnGetValue( _double& value ) const override;

public:
	HTMLAttribute( GumboAttribute* gumbo_attribute );
	virtual ~HTMLAttribute( );
	
// IMarkupLangAttribute Interface
public:
	virtual WStringR	GetName( _ubool with_prefix = _false ) const override;
};

//----------------------------------------------------------------------------
// HTMLElement
//----------------------------------------------------------------------------

class HTMLElement : public INTERFACE_MARKUP_LANG_ELEMENT_IMPL( IHTMLElement )
{
private:
	typedef INTERFACE_MARKUP_LANG_ELEMENT_IMPL( IHTMLElement ) BaseClass;

private:
	typedef Map< IHTMLAttribute*, WStringObj > HTMLAttributesMap;

private:
	//!	The HTML element
	GumboElement*		mGumboElement;

	//! The attributes
	HTMLAttributesMap	mHTMLAttributes;

// TMarkupLangElement Interface
private:
    virtual IMarkupLangElementIteratorPassRef OnCreateElementIterator( IMarkupLangElement* element ) override;

public:
	HTMLElement( GumboElement* gumbo_element, HTMLElement* parent, HTMLElement* prev, HTMLElement* next );
	virtual ~HTMLElement( );

// IMarkupLangElement Interface
public:
	virtual _ubool								SetName( WStringPtr name ) override;
	virtual WStringR							GetName( ) const override;

	virtual IMarkupLangElement*					InsertChildElementU( WStringPtr name, UStringPtr text, _ubool is_array_obj ) override;
	virtual IMarkupLangElement*					InsertNextElementU( WStringPtr name, UStringPtr text, _ubool is_array_obj ) override;

	virtual _void								RemoveElement( IMarkupLangElement* element ) override;
	virtual IMarkupLangElementIteratorPassRef	RemoveElement( IMarkupLangElementIterator* it ) override;

	virtual _ubool								HasAttribute( WStringPtr name, _ubool ignorecase = _false ) const override;
	virtual IMarkupLangAttribute*				SearchAttribute( WStringPtr name, _ubool ignorecase = _false ) const override;

	virtual _dword								GetValueU( ) const override;
	virtual _int								GetValueI( ) const override;
	virtual _float								GetValueF( ) const override;
	virtual _double								GetValueD( ) const override;

	virtual _ubool								GetText( UString& text ) const override;
	virtual _ubool								GetText( WString& text ) const override;
	virtual UStringR							GetTextU( ) const override;
	virtual WStringR							GetTextW( ) const override;
	virtual _ubool								SetText( UStringPtr text ) override;
	virtual _ubool								SetText( WStringPtr text ) override;

	virtual _ubool 								SetAttributeString( WStringPtr name, UStringPtr string ) override;
	virtual _ubool 								SetAttributeString( WStringPtr name, WStringPtr string ) override;

	virtual WStringR							DumpToString( ) const override;
	virtual WStringR							DumpToSchemaString( ) const override;
};

//----------------------------------------------------------------------------
// HTMLFile
//----------------------------------------------------------------------------

class HTMLFile : public TBaseFile< IHTMLFile >
{
private:
	typedef TBaseFile< IHTMLFile > BaseClass;

private:
	static const GumboOptions sGumboDefaultOptions;

private:
	//!	The HTML output data ( as file )
	GumboOutput*	mGumboOutput;

private:
	//!	The allocate/free hooker.
	static _void* OnGumboAlloc( _void* userdata, size_t size );
	static _void OnGumboFree( _void* userdata, _void* ptr );

public:
	HTMLFile( );
	virtual ~HTMLFile( );

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

#endif