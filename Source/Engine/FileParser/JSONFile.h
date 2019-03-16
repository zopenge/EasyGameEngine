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

class JSONAttribute : public INTERFACE_MARKUP_LANG_ATTRIBUTE_IMPL( IMarkupLangAttribute )
{
private:
	typedef INTERFACE_MARKUP_LANG_ATTRIBUTE_IMPL( IMarkupLangAttribute ) BaseClass;

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
	
// IMarkupLangAttribute Interface
public:
	virtual WStringR	GetName( _ubool with_prefix = _false ) const override;
};

//----------------------------------------------------------------------------
// JSONElement
//----------------------------------------------------------------------------

class JSONElement : public INTERFACE_MARKUP_LANG_ELEMENT_IMPL( IMarkupLangElement )
{
private:
	typedef INTERFACE_MARKUP_LANG_ELEMENT_IMPL( IMarkupLangElement ) BaseClass;

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
    virtual IMarkupLangElementIteratorPassRef OnCreateElementIterator( IMarkupLangElement* element ) override;

public:
	JSONElement( cJSON* json_element, JSONElement* parent, JSONElement* prev, JSONElement* next );
	virtual ~JSONElement( );

public:
	//!	Free JSON element.
	_void FreeJSONElement( );

// IMarkupLangElement Interface
public:
	virtual _ubool					IsArrayObject( ) const override;

	virtual _ubool					SetName( WStringPtr name ) override;
	virtual WStringR				GetName( ) const override;

	virtual IMarkupLangElement*		InsertChildElementU( WStringPtr name, UStringPtr text, _ubool is_array_obj ) override;
	virtual IMarkupLangElement*		InsertChildElementW( WStringPtr name, WStringPtr text, _ubool is_array_obj ) override;

	virtual IMarkupLangElement*		InsertChildArrayObj( WStringPtr name ) override;
	virtual IMarkupLangElement*		AppendElementOfArrayObj( ) override;
	virtual _dword					AppendElementOfArrayObj( IMarkupLangElement* element ) override;
	virtual _dword					AppendValueUOfArrayObj( _dword value ) override;
	virtual _dword					AppendValueIOfArrayObj( _int value ) override;
	virtual _dword					AppendValueFOfArrayObj( _float value ) override;
	virtual _dword					AppendValueDOfArrayObj( _double value ) override;
	virtual _dword					GetSubElementsNumber( ) const override;
	virtual IMarkupLangElement*		GetSubElementByIndex( _dword index ) const override;

	virtual _dword					GetAttributesNumber( ) const override;
	virtual IMarkupLangAttribute*	GetAttributeByIndex( _dword index ) const override;

	virtual _ubool					HasAttribute( WStringPtr name, _ubool ignorecase = _false ) const override;
	virtual IMarkupLangAttribute*	SearchAttribute( WStringPtr name, _ubool ignorecase = _false ) const override;

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
	virtual AStringR				GetTextA( ) const override;
	virtual UStringR				GetTextU( ) const override;
	virtual WStringR				GetTextW( ) const override;
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

	virtual WStringR				DumpToString( ) const override;
	virtual WStringR				DumpToSchemaString( ) const override;
};

//----------------------------------------------------------------------------
// JSONFile
//----------------------------------------------------------------------------

class JSONFile : public TBaseFile< IMarkupLangFile >
{
private:
	typedef TBaseFile< IMarkupLangFile > BaseClass;

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

// IMarkupLangFile Interface
public:
	virtual IMarkupLangDeclaration*	GetDeclaration( ) override;

	virtual IMarkupLangElement*		GetRootElement( ) override;

	virtual _ubool					SchemaValidate( WStringPtr filename ) override;
	virtual _ubool					SchemaValidate( IStreamReader* stream_reader ) override;
};

}