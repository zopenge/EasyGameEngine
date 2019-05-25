//! @file     BinaryXMLFile.h
//! @author   foreven
//! @version  1.0
//! @date     2013/07/11

#pragma once

namespace EGE
{

class BinaryXMLFile;

//----------------------------------------------------------------------------
// BinaryXMLStringTableReader
//----------------------------------------------------------------------------

class BinaryXMLStringTableReader
{
private:
	typedef Array< WStringPtr > WStringPtrArray;

private:
	WStringPtrArray	mReadOnlyStrings;
	_charw*			mStringPool;

public:
	BinaryXMLStringTableReader( );
	~BinaryXMLStringTableReader( );

public:
	//!	Get the string by index.
	WStringPtr GetString( _dword index ) const
	{
		return mReadOnlyStrings[index];
	}
	//!	Get the string number.
	_dword GetStringNumber( ) const
	{
		return mReadOnlyStrings.Number( );
	}

public:
	//!	Load from stream.
	_ubool LoadFromStream( _ENCODING encoding, IStreamReader* stream_reader );
};

//----------------------------------------------------------------------------
// BinaryXMLStringTableWriter
//----------------------------------------------------------------------------

class BinaryXMLStringTableWriter
{
private:
	WStringArray	mStrings;

public:
	BinaryXMLStringTableWriter( );
	BinaryXMLStringTableWriter( const BinaryXMLStringTableReader& reader );
	~BinaryXMLStringTableWriter( );

public:
	//!	Add string and get its index of table.
	_dword AddString( WStringPtr string );
	//!	Search string and get its index of table.
	_dword SearchString( WStringPtr string ) const;
	//!	Get the total string number.
	_dword GetStringNumber( ) const;

	// Write to stream.
	_ubool Write2Stream( _ENCODING encoding, IStreamWriter* stream_writer ) const;
};

//----------------------------------------------------------------------------
// BinaryXMLAttribute
//----------------------------------------------------------------------------

class BinaryXMLAttribute : public IMarkupAttribute
{
private:
	//!	The XML name
	WStringPtr	mAttributeName;
	//!	The XML attribute
	Variable	mAttributeValue;

private:
	//!	Read attribute.
	_ubool ReadAttribute( IStreamReader* stream_reader, BinaryXMLFile* xml_file );

public:
	BinaryXMLAttribute( );
	virtual ~BinaryXMLAttribute( );

public:
	//!	Load from stream.
	_ubool LoadFromStream( IStreamReader* stream_reader, BinaryXMLFile* xml_file );

	//!	Get the value type.
	_dword GetValueType( ) const;

// IMarkupAttribute Interface
public:
	virtual WString	GetName( _ubool with_prefix = _false ) const override;

	virtual _ubool		SetBool( _ubool value ) override;
	virtual _ubool		SetLong( _int value ) override;
	virtual _ubool		SetDword( _dword value ) override;
	virtual _ubool 		SetLarge( _large value ) override;
	virtual _ubool 		SetQword( _qword value ) override;
	virtual _ubool		SetDouble( _double value ) override;
	virtual _ubool		SetOword( const MD5Code& value ) override;
	virtual _ubool		SetString( WStringPtr string ) override;
	virtual _ubool		SetColor( const Color& color ) override;
	virtual _ubool		SetVersion( const Version& version ) override;

	virtual _ubool		GetBool( ) const override;
	virtual _int		GetLong( ) const override;
	virtual _dword		GetDword( ) const override;
	virtual _large		GetLarge( ) const override;
	virtual _qword		GetQword( ) const override;
	virtual _float		GetFloat( ) const override;
	virtual _double		GetDouble( ) const override;
	virtual UString	GetStringU( ) const override;
	virtual WString	GetStringW( ) const override;
	virtual MD5Code		GetMD5Code( ) const override;
	virtual Color		GetColor( ) const override;
	virtual Version		GetVersion( ) const override;
};

//----------------------------------------------------------------------------
// BinaryXMLElement
//----------------------------------------------------------------------------

class BinaryXMLElement : public IMarkupElement
{
public:
	//!	The attribute info
	struct XMLAttributeInfo
	{
		BinaryXMLAttribute*	mAttribute;

		operator WString( ) const
			{ return mAttribute->GetName( ); }

		XMLAttributeInfo( )
		{
			mAttribute = _null;
		}
		XMLAttributeInfo( BinaryXMLAttribute* attribute )
		{
			mAttribute = attribute;
		}
	};
	typedef Array< XMLAttributeInfo > XMLAttributeInfoArray;

private:
	//!	The XML element name
	WStringPtr				mElementName;
	//!	The XML element text
	WStringPtr				mElementText;

	//!	The attributes
	XMLAttributeInfoArray	mAttributes;

	//!	The parent element
	BinaryXMLElement*		mParentElement;
	//!	The previous element
	BinaryXMLElement*		mPrevElement;
	//!	The next element
	BinaryXMLElement*		mNextElement;
	//!	The first child element
	BinaryXMLElement*		mFirstChildElement;
	//!	The last child element
	BinaryXMLElement*		mLastChildElement;

	//!	The XML file 
	BinaryXMLFile*			mMarkupFile;

private:
	//!	Read the element string.
	_ubool ReadElementString( BinaryXMLFile* xml_file, IStreamReader* stream_reader, WStringPtr& string );

	//!	Read attribute nodes.
	_ubool ReadAttributeNodes( BinaryXMLFile* xml_file, IStreamReader* stream_reader );

	//!	Read element nodes.
	_ubool ReadElementNode( BinaryXMLFile* xml_file, IStreamReader* stream_reader, BinaryXMLElement*& element );

	//!	Dump element's depth to string.
	_ubool DumpElementDepthToString( const BinaryXMLElement* element, WStringPtr depth_string, WString& string ) const;
	//!	Dump element's attributes to string.
	_ubool DumpAttributesToString( const BinaryXMLElement* element, WString& string ) const;
	//!	Dump to string.
	_ubool DumpToString( const BinaryXMLElement* root, WString& string ) const;

public:
	BinaryXMLElement( );
	virtual ~BinaryXMLElement( );

public:
	EGE_GETR_ACCESSOR_CONST( XMLAttributeInfoArray, Attributes )

public:
	//!	Load from stream.
	_ubool LoadFromStream( IStreamReader* stream_reader, BinaryXMLFile* xml_file );

// IMarkupElement Interface
public:
	virtual _ubool								IsArrayObject( ) const override;

	virtual _dword								GetDepth( ) const override;

	virtual _ubool								SetName( WStringPtr name ) override;
	virtual WString							GetName( ) const override;

	virtual _dword								GetChildElementNumber( ) const override;
	virtual IMarkupElement*					GetChildElementByIndex( _dword index ) const override;
	virtual IMarkupElement*					GetChildElementByName( WStringPtr name, _ubool ignorecase = _false ) const override;
	virtual IMarkupElement*					GetChildElementByText( WStringPtr text, _ubool ignorecase = _false ) const override;

	virtual _ubool								HasChildElement( WStringPtr name, _ubool ignorecase = _false ) const override;
	virtual _ubool								GetChildElementTextByName( WStringPtr name, UString& text, _ubool ignorecase = _false ) const override;
	virtual _ubool								GetChildElementTextByName( WStringPtr name, WString& text, _ubool ignorecase = _false ) const override;
	virtual UString							GetChildElementTextByNameU( WStringPtr name, _ubool ignorecase = _false ) const override;
	virtual WString							GetChildElementTextByNameW( WStringPtr name, _ubool ignorecase = _false ) const override;

	virtual IMarkupElement*					GetFirstChildElement( ) const override;
	virtual IMarkupElement*					GetLastChildElement( ) const override;
	virtual IMarkupElement*					GetParentElement( ) const override;
	virtual IMarkupElement*					GetPrevElement( ) const override;
	virtual IMarkupElement*					GetNextElement( ) const override;
	virtual IMarkupElement*					GetHeadElement( ) const override;
	virtual IMarkupElement*					GetTailElement( ) const override;

	virtual IMarkupElement*					GetPrevElementByName( WStringPtr name, _ubool ignorecase = _false ) const override;
	virtual IMarkupElement*					GetNextElementByName( WStringPtr name, _ubool ignorecase = _false ) const override;

	virtual IMarkupElement*					InsertChildElementU( WStringPtr name, UStringPtr text, _ubool is_array_obj ) override;
	virtual IMarkupElement*					InsertChildElementW( WStringPtr name, WStringPtr text, _ubool is_array_obj ) override;
	virtual IMarkupElement*					InsertChildElement( const IMarkupElement* element, _ubool all_child ) override;
	virtual IMarkupElement*					InsertNextElementU( WStringPtr name, UStringPtr text, _ubool is_array_obj ) override;
	virtual IMarkupElement*					InsertNextElementW( WStringPtr name, WStringPtr text, _ubool is_array_obj ) override;
	virtual IMarkupElement*					InsertNextElement( const IMarkupElement* element, _ubool all_child ) override;

	virtual IMarkupElement*					InsertChildArrayObj( WStringPtr name ) override;
	virtual IMarkupElement*					AppendElementOfArrayObj( ) override;
	virtual _dword								AppendElementOfArrayObj( IMarkupElement* element ) override;
	virtual _dword								AppendValueUOfArrayObj( _dword value ) override;
	virtual _dword								AppendValueIOfArrayObj( _int value ) override;
	virtual _dword								AppendValueFOfArrayObj( _float value ) override;
	virtual _dword								AppendValueDOfArrayObj( _double value ) override;
	virtual _dword								GetSubElementsNumber( ) const override;
	virtual IMarkupElement*					GetSubElementByIndex( _dword index ) const override;

	virtual _void								Remove( ) override;
	virtual _void								RemoveElement( IMarkupElement* element ) override;
	virtual IMarkupLangElementIteratorPassRef	RemoveElement( IMarkupLangElementIterator* it ) override;

	virtual IMarkupLangElementIteratorPassRef	CreateSelfElementIterator( ) override;
	virtual IMarkupLangElementIteratorPassRef	CreateChildElementIterator( WStringPtr name, _ubool recursive = _false ) override;

	virtual _dword								GetAttributesNumber( ) const override;
	virtual IMarkupAttribute*				GetAttributeByIndex( _dword index ) const override;

	virtual _ubool								HasAttribute( WStringPtr name, _ubool ignorecase = _false ) const override;
	virtual IMarkupAttribute*				SearchAttribute( WStringPtr name, _ubool ignorecase = _false ) const override;

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
	virtual AString							GetTextA( ) const override;
	virtual UString							GetTextU( ) const override;
	virtual WString							GetTextW( ) const override;
	virtual _ubool								SetText( AStringPtr text ) override;
	virtual _ubool								SetText( UStringPtr text ) override;
	virtual _ubool								SetText( WStringPtr text ) override;

	virtual _ubool								GetAttributeBool( WStringPtr name, _ubool& value, _ubool ignorecase = _false ) const override;
	virtual _ubool								GetAttributeLong( WStringPtr name, _int& value, _ubool ignorecase = _false ) const override;
	virtual _ubool								GetAttributeDword( WStringPtr name, _dword& value, _ubool ignorecase = _false ) const override;
	virtual _ubool								GetAttributeLarge( WStringPtr name, _large& value, _ubool ignorecase = _false ) const override;
	virtual _ubool								GetAttributeQword( WStringPtr name, _qword& value, _ubool ignorecase = _false ) const override;
	virtual _ubool								GetAttributeDouble( WStringPtr name, _double& value, _ubool ignorecase = _false ) const override;
	virtual _ubool								GetAttributeString( WStringPtr name, UString& string, _ubool ignorecase = _false ) const override;
	virtual _ubool								GetAttributeString( WStringPtr name, WString& string, _ubool ignorecase = _false ) const override;
	virtual _ubool								GetAttributeMD5Code( WStringPtr name, MD5Code& value, _ubool ignorecase = _false ) const override;
	virtual _ubool								GetAttributeColor( WStringPtr name, Color& color, _ubool ignorecase = _false ) const override;
	virtual _ubool								GetAttributeVersion( WStringPtr name, Version& version, _ubool ignorecase = _false ) const override;

	virtual _ubool								SetAttributeBool( WStringPtr name, _ubool value ) override;
	virtual _ubool								SetAttributeLong( WStringPtr name, _int value ) override;
	virtual _ubool								SetAttributeDword( WStringPtr name, _dword value ) override;
	virtual _ubool								SetAttributeLarge( WStringPtr name, _large value ) override;
	virtual _ubool								SetAttributeQword( WStringPtr name, _qword value ) override;
	virtual _ubool								SetAttributeDouble( WStringPtr name, _double value ) override;
	virtual _ubool								SetAttributeString( WStringPtr name, UStringPtr string ) override;
	virtual _ubool								SetAttributeString( WStringPtr name, WStringPtr string ) override;
	virtual _ubool								SetAttributeMD5Code( WStringPtr name, const MD5Code& value ) override;
	virtual _ubool								SetAttributeColor( WStringPtr name, const Color& color ) override;
	virtual _ubool								SetAttributeVersion( WStringPtr name, const Version& version ) override;

	virtual WString							DumpToString( ) const override;
	virtual WString							DumpToSchemaString( ) const override;
};

//----------------------------------------------------------------------------
// BinaryXMLFileDeclaration
//----------------------------------------------------------------------------

class BinaryXMLFileDeclaration : public IMarkupDeclaration
{
public:
	BinaryXMLFileDeclaration( );
	virtual ~BinaryXMLFileDeclaration( );

// IMarkupDeclaration Interface
public:
	virtual _void			SetVersion( const Version& version ) override;
	virtual const Version&	GetVersion( ) const override;

	virtual _void			SetEncoding( _ENCODING encoding ) override;
	virtual _ENCODING		GetEncoding( ) const override;
};

//----------------------------------------------------------------------------
// BinaryXMLFile
//----------------------------------------------------------------------------

class BinaryXMLFile : public TBaseFile< IMarkupFile >
{
public:
	//!	The binary xml file ID
	enum { _FILE_ID = EGE_ID( 'B', 'x', 'm', 'l' ) };

private:
	//!	The regular expression type
	enum _REGULAR_EXPRESSION_TYPE
	{
		_RET_STRING = -2,
		_RET_BOOLEAN = -1,
		_RET_POSITIVE_NUMERIC,
		_RET_NEGATIVE_NUMERIC,
		_RET_DOUBLE,
		_RET_COLOR,
		_RET_MD5,

		_RET_MAXNUMBER,
	};

	//!	The index mode
	enum _INDEX_MODE
	{
		_INDEX_8_BITS,
		_INDEX_16_BITS,
		_INDEX_32_BITS,
	};

	//!	The value mode
	enum _VALUE_MODE
	{
		_VALUE_MODE_NORMAL,
		_VALUE_MODE_DYNAMIC,
	};

private:
	typedef TBaseFile< IMarkupFile > BaseClass;

private:
	//!	The header info
	struct HeaderInfo
	{
		_byte	mValueMode;
		_byte	mEncodingType;

		_byte	mStringTableIndexMode;
		_byte	mAttributeIndexMode;
		_byte	mElementIndexMode;

		_byte	mReserved[3];

		HeaderInfo( )
		{
			mValueMode				= _VALUE_MODE_NORMAL;
			mEncodingType			= _ENCODING_ANSI;

			mStringTableIndexMode	= _INDEX_8_BITS;
			mAttributeIndexMode		= _INDEX_8_BITS;
			mElementIndexMode		= _INDEX_8_BITS;

			EGE_INIT_ARRAY( mReserved );
		}
	};

	//!	The attribute info
	struct AttributeInfo
	{
		_REGULAR_EXPRESSION_TYPE	mType;
		IMarkupAttribute*		mAttribute;

		operator IMarkupAttribute* ( ) const
			{ return mAttribute; }

		AttributeInfo( )
		{
			mType		= _RET_STRING;
			mAttribute	= _null;
		}
		AttributeInfo( _REGULAR_EXPRESSION_TYPE type, IMarkupAttribute* attribute )
		{
			mType		= type;
			mAttribute	= attribute;
		}
	};
	typedef Array< AttributeInfo > AttributeArray;

	//!	The element info
	struct ElementInfo
	{
		IMarkupElement*	mElement;

		operator IMarkupElement* ( ) const
			{ return mElement; }

		ElementInfo( )
		{
			mElement = _null;
		}
		ElementInfo( IMarkupElement* element )
		{
			mElement = element;
		}
	};
	typedef Array< ElementInfo > ElementArray;

private:
	//!	The header info
	HeaderInfo					mHeaderInfo;

	//!	The root element of XML
	BinaryXMLElement*			mRootElement;
	//!	The declaration of XML
	BinaryXMLFileDeclaration	mDeclaration;

	//!	The string table reader
	BinaryXMLStringTableReader*	mStringTable;

	//!	The XML attributes pool
	_dword						mXMLAttributesNumber;
	BinaryXMLAttribute*			mXMLAttributes;

	//!	The XML elements pool
	_dword						mXMLElementsNumber;
	BinaryXMLElement*			mXMLElements;

private:
	//!	Create regular expressions.
	_ubool CreateRegularExpressions( IRegularExpressionRef regular_expressions[] ) const;

	//!	Load header info.
	_ubool LoadHeaderInfo( IStreamReader* stream_reader );

	//!	Load string table.
	_ubool LoadStringTable( IStreamReader* stream_reader );

	//!	Load XML attributes.
	_ubool LoadXMLAttributes( IStreamReader* stream_reader );
	//!	Load XML elements.
	_ubool LoadXMLElements( IStreamReader* stream_reader );

	//!	Get the value type.
	_REGULAR_EXPRESSION_TYPE GetValueType( WStringPtr value, IRegularExpressionRef regular_expressions[] ) const;
	_REGULAR_EXPRESSION_TYPE GetValueType( const BinaryXMLAttribute& attribute ) const;

	//!	Write index into stream.
	_ubool WriteIndex2Stream( IStreamWriter* stream_writer, _INDEX_MODE index_mode, _int index ) const;
	//!	Write attribute index into stream.
	_ubool WriteAttributeIndex2Stream( IStreamWriter* stream_writer, const HeaderInfo& header_info, IMarkupAttribute* attribute, const AttributeArray& xml_attributes ) const;
	//!	Write element index into stream.
	_ubool WriteElementIndex2Stream( IStreamWriter* stream_writer, const HeaderInfo& header_info, IMarkupElement* element, const ElementArray& xml_elements ) const;
	//!	Write string index into stream.
	_ubool WriteStringIndexIntoStream( IStreamWriter* stream_writer, const HeaderInfo& header_info, const BinaryXMLStringTableWriter& string_table, WStringPtr string ) const;

	//!	Write attribute to stream.
	_ubool WriteAttribute2Stream( IStreamWriter* stream_writer, const HeaderInfo& header_info, const BinaryXMLStringTableWriter& string_table, const AttributeInfo& attribute ) const;
	//!	Write attributes to stream.
	_ubool WriteAttributes2Stream( IStreamWriter* stream_writer, const HeaderInfo& header_info, const BinaryXMLStringTableWriter& string_table, const AttributeArray& xml_attributes ) const;
	//!	Write elements to stream.
	_ubool WriteElements2Stream( IStreamWriter* stream_writer, const HeaderInfo& header_info, const BinaryXMLStringTableWriter& string_table, const ElementArray& xml_elements, const AttributeArray& xml_attributes ) const;
	//!	Write binary XML file to stream.
	_ubool WriteBXML2Stream( IStreamWriter* stream_writer, const HeaderInfo& header_info, const BinaryXMLStringTableWriter& string_table, const ElementArray& xml_elements, const AttributeArray& xml_attributes ) const;

	//!	Get the index mode.
	_INDEX_MODE GetIndexMode( _dword number ) const;

	//!	Build pools from markup file.
	_ubool BuildPoolsFromMarkupFile( IMarkupElement* element, BinaryXMLStringTableWriter& string_table, ElementArray& xml_elements, AttributeArray& xml_attributes, IRegularExpressionRef regular_expressions[] );
	//!	Build header info.
	_ubool BuildHeaderInfo( HeaderInfo& header_info, const BinaryXMLStringTableWriter& string_table, const ElementArray& xml_elements, const AttributeArray& xml_attributes ) const;

	//!	Read the index from stream.
	_int ReadIndexFromStream( _INDEX_MODE index_mode, IStreamReader* stream_reader ) const;

public:
	BinaryXMLFile( );
	virtual ~BinaryXMLFile( );

public:
	//!	Load from markup file.
	_ubool LoadFromMarkupFile( IMarkupFile* markup_file );

	//!	Read the attribute index from stream.
	_int ReadAttributeIndexFromStream( IStreamReader* stream_reader );
	//!	Read the element index from stream.
	_int ReadElementIndexFromStream( IStreamReader* stream_reader );
	//!	Read the string index from stream.
	_int ReadStringIndexFromStream( IStreamReader* stream_reader );

public:
	//!	Get string.
	inline WStringPtr GetString( _int index ) const;
	//!	Get xml attribute.
	inline BinaryXMLAttribute* GetXMLAttribute( _int index );
	//!	Get xml element.
	inline BinaryXMLElement* GetXMLElement( _int index );

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

//----------------------------------------------------------------------------
// BinaryXMLFile Implementation
//----------------------------------------------------------------------------

WStringPtr BinaryXMLFile::GetString( _int index ) const
{
	return mStringTable->GetString( index );
}

BinaryXMLAttribute* BinaryXMLFile::GetXMLAttribute( _int index )
{
	EGE_ASSERT( index < (_int)mXMLAttributesNumber );

	return &mXMLAttributes[index];
}

BinaryXMLElement* BinaryXMLFile::GetXMLElement( _int index )
{
	EGE_ASSERT( index < (_int)mXMLElementsNumber );

	return &mXMLElements[index];
}

}