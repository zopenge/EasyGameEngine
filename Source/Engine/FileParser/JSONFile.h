//! @file     JSONFile.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// JSONAttribute
//----------------------------------------------------------------------------

class JSONAttribute : public INTERFACE_MARKUP_LANG_ATTRIBUTE_IMPL( IMarkupAttribute )
{
private:
	typedef INTERFACE_MARKUP_LANG_ATTRIBUTE_IMPL( IMarkupAttribute ) BaseClass;

private:
	//!	The JSON attribute
	cJSON*	mJSONAttribute;

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
	JSONAttribute( cJSON* json_attribute );
	virtual ~JSONAttribute( );
	
// IMarkupAttribute Interface
public:
	virtual WString	GetName( _ubool with_prefix = _false ) const override;
};

//----------------------------------------------------------------------------
// JSONElement
//----------------------------------------------------------------------------

class JSONElement : public INTERFACE_MARKUP_LANG_ELEMENT_IMPL( IMarkupElement )
{
private:
	typedef INTERFACE_MARKUP_LANG_ELEMENT_IMPL( IMarkupElement ) BaseClass;

private:
	typedef Map< JSONAttribute*, WString > JSONAttributesMap;

	//!	The element declaration
	typedef Array< JSONElement* > JSONElementArray;

private:
	//!	The JSON element
	cJSON*				mJSONElement;

	//!	The attributes
	JSONAttributesMap	mJSONAttributes;

	//!	The elements
	JSONElementArray	mJSONSubElements;

private:
	_void UpdateAttribute( WStringPtr name, cJSON* json_value );

// TMarkupLangElement Interface
private:
    virtual IMarkupLangElementIteratorPassRef OnCreateElementIterator( IMarkupElement* element ) override;

public:
	JSONElement( cJSON* json_element, JSONElement* parent, JSONElement* prev, JSONElement* next );
	virtual ~JSONElement( );

public:
	//!	Free JSON element.
	_void FreeJSONElement( );

// IMarkupElement Interface
public:
	virtual _ubool					IsArrayObject( ) const override;

	virtual _ubool					SetName( WStringPtr name ) override;
	virtual WString				GetName( ) const override;

	virtual IMarkupElement*		InsertChildElementU( WStringPtr name, UStringPtr text, _ubool is_array_obj ) override;
	virtual IMarkupElement*		InsertChildElementW( WStringPtr name, WStringPtr text, _ubool is_array_obj ) override;

	virtual IMarkupElement*		InsertChildArrayObj( WStringPtr name ) override;
	virtual IMarkupElement*		AppendElementOfArrayObj( ) override;
	virtual _dword					AppendElementOfArrayObj( IMarkupElement* element ) override;
	virtual _dword					AppendValueUOfArrayObj( _dword value ) override;
	virtual _dword					AppendValueIOfArrayObj( _int value ) override;
	virtual _dword					AppendValueFOfArrayObj( _float value ) override;
	virtual _dword					AppendValueDOfArrayObj( _double value ) override;
	virtual _dword					GetSubElementsNumber( ) const override;
	virtual IMarkupElement*		GetSubElementByIndex( _dword index ) const override;

	virtual _dword					GetAttributesNumber( ) const override;
	virtual IMarkupAttribute*	GetAttributeByIndex( _dword index ) const override;

	virtual _ubool					HasAttribute( WStringPtr name, _ubool ignorecase = _false ) const override;
	virtual IMarkupAttribute*	SearchAttribute( WStringPtr name, _ubool ignorecase = _false ) const override;

	virtual _dword					GetValueU( ) const override;
	virtual _int					GetValueI( ) const override;
	virtual _float					GetValueF( ) const override;
	virtual _double					GetValueD( ) const override;

	virtual _ubool					SetValueU( _dword value ) override;
	virtual _ubool					SetValueI( _int value ) override;
	virtual _ubool					SetValueF( _float value ) override;
	virtual _ubool					SetValueD( _double value ) override;

	virtual _ubool					GetText( AString& text ) const override;
	virtual _ubool					GetText( UString& text ) const override;
	virtual _ubool					GetText( WString& text ) const override;
	virtual AString				GetTextA( ) const override;
	virtual UString				GetTextU( ) const override;
	virtual WString				GetTextW( ) const override;
	virtual _ubool					SetText( AStringPtr text ) override;
	virtual _ubool					SetText( UStringPtr text ) override;
	virtual _ubool					SetText( WStringPtr text ) override;

	virtual _ubool 					SetAttributeBool( WStringPtr name, _ubool value ) override;
	virtual _ubool 					SetAttributeLong( WStringPtr name, _int value ) override;
	virtual _ubool 					SetAttributeDword( WStringPtr name, _dword value ) override;
	virtual _ubool 					SetAttributeQword( WStringPtr name, _qword value ) override;
	virtual _ubool 					SetAttributeDouble( WStringPtr name, _double value ) override;
	virtual _ubool 					SetAttributeString( WStringPtr name, UStringPtr string ) override;
	virtual _ubool 					SetAttributeString( WStringPtr name, WStringPtr string ) override;

	virtual WString				DumpToString( ) const override;
	virtual WString				DumpToSchemaString( ) const override;
};

//----------------------------------------------------------------------------
// JSONFile
//----------------------------------------------------------------------------

class JSONFile : public TBaseFile< IMarkupFile >
{
private:
	typedef TBaseFile< IMarkupFile > BaseClass;

private:
	//!	The JSON root element
	JSONElement*	mRootElement;

public:
	//!	The memory allocation hooker function.
	static void* OnMallocFunc( size_t size );
	//!	The memory free hooker function.
	static void OnFreeFunc( void* pointer );

public:
	JSONFile( );
	virtual ~JSONFile( );

public:
	//!	Initialize.
	static _ubool Initialize( );
	//!	Finalize.
	static _void Finalize( );

// IBaseFile Interface
public:
	virtual _FILE_FORMAT			GetFileID( ) const override;

	virtual _ubool 					LoadFromStream( IStreamReader* stream_reader ) override;
	virtual _void 					Unload( ) override;

	virtual _ubool					SaveToStream( IStreamWriter* stream_writer, _dword flags ) const override;

// IMarkupFile Interface
public:
	virtual IMarkupDeclaration*	GetDeclaration( ) override;

	virtual IMarkupElement*		GetRootElement( ) override;

	virtual _ubool					SchemaValidate( WStringPtr filename ) override;
	virtual _ubool					SchemaValidate( IStreamReader* stream_reader ) override;
};

}