//! @file     XMLFile.cpp
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// BinaryXMLStringTableReaderReader Implementation
//----------------------------------------------------------------------------

BinaryXMLStringTableReader::BinaryXMLStringTableReader( )
{
	mStringPool = _null;
}

BinaryXMLStringTableReader::~BinaryXMLStringTableReader( )
{
	EGE_DELETE_ARRAY( mStringPool );
}

_ubool BinaryXMLStringTableReader::LoadFromStream( _ENCODING encoding, IStreamReader* stream_reader )
{
	// Clear the previous info
	EGE_DELETE_ARRAY( mStringPool );
	mReadOnlyStrings.Clear( );

	// Read the total UTF-16 characters number
	_dword total_utf16_chars_number = 0;
	stream_reader->ReadDword( total_utf16_chars_number );

	// Create string pool
	mStringPool = new _charw[total_utf16_chars_number];

	// Read string table
	switch ( encoding )
	{
		case _ENCODING_ANSI:
		{
			// Read the total characters number
			_dword total_ansi_chars_number = 0;
			stream_reader->ReadDword( total_ansi_chars_number );

			// Read string pool by ANSI mode
			_chara* string_pool_ansi = new _chara[total_ansi_chars_number];
			stream_reader->ReadBuffer( string_pool_ansi, total_ansi_chars_number );

			// Get the address
			_charw*			to			= mStringPool;
			const _chara*	from_begin	= string_pool_ansi;

			// Start to parse string pool
			while ( _true )
			{
				// The remain character number of UTF-16
				_dword remain_utf16_characters_number = total_utf16_chars_number - (to - mStringPool);
				if ( remain_utf16_characters_number == 0 )
					break;

				// Convert ANSI to UTF16
				_dword string_utf16_length = Platform::AnsiToUtf16( to, remain_utf16_characters_number, from_begin );
				mReadOnlyStrings.Append( to );

				// Jump to the next string
				while ( *from_begin != 0 )
					from_begin ++;

				// Jump the '\0' character
				from_begin ++;

				// Update target address (with '\0' character)
				to += (string_utf16_length / sizeof( _charw )) + 1;
			}

			delete[] string_pool_ansi;
		}
		break;

		case _ENCODING_UTF16:
		{
			mStringPool = new _charw[total_utf16_chars_number];
			stream_reader->ReadBuffer( mStringPool, total_utf16_chars_number * sizeof( _charw ) );

			const _charw* to	= mStringPool;
			const _charw* end	= mStringPool + total_utf16_chars_number;

			while ( to < end )
			{
				mReadOnlyStrings.Append( to );

				while ( *to != 0 )
					to ++;

				to ++;
			}
		}
		break;

		default:
			return _false;
	}

	// Seek current pointer to make sure it's 4 bytes align
	stream_reader->SeekByArrangedValueFromBegin( 4 );

	return _true;
}

//----------------------------------------------------------------------------
// BinaryXMLStringTableWriter Implementation
//----------------------------------------------------------------------------

BinaryXMLStringTableWriter::BinaryXMLStringTableWriter( )
{
}

BinaryXMLStringTableWriter::BinaryXMLStringTableWriter( const BinaryXMLStringTableReader& reader )
{
	for ( _dword i = 0; i < reader.GetStringNumber( ); i ++ )
		mStrings.Append( reader.GetString( i ) );
}

BinaryXMLStringTableWriter::~BinaryXMLStringTableWriter( )
{
}

_dword BinaryXMLStringTableWriter::AddString( WStringPtr string )
{
	WStringArray::Iterator it = mStrings.SearchAscending( string );
	if ( it.IsValid( ) )
		return it.mIndex;

	return mStrings.InsertAscending( string );
}

_dword BinaryXMLStringTableWriter::SearchString( WStringPtr string ) const
{
	return mStrings.SearchAscending( string ).mIndex;
}

_dword BinaryXMLStringTableWriter::GetStringNumber( ) const
{
	return mStrings.Number( );
}

_ubool BinaryXMLStringTableWriter::Write2Stream( _ENCODING encoding, IStreamWriter* stream_writer ) const
{
	// Write the total UTF-16 characters number
	_dword total_utf16_chars_number = 0;
	for ( _dword i = 0; i < mStrings.Number( ); i ++ )
		total_utf16_chars_number += mStrings[i].GetLength( ) + 1;

	// Write the total UTF-16 characters number
	stream_writer->WriteDword( total_utf16_chars_number );

	// It's ANSI encoding type
	switch ( encoding )
	{
		case _ENCODING_ANSI:
		{
			// Convert UTF-16 -> ANSI string
			AStringArray ansi_strings;
			for ( _dword i = 0; i < mStrings.Number( ); i ++ )
				ansi_strings.Append( AString( ).FromString( mStrings[i] ) );

			// Get the total characters number in ANSI mode
			_dword total_ansi_chars_number = 0;
			for ( _dword i = 0; i < ansi_strings.Number( ); i ++ )
				total_ansi_chars_number += ansi_strings[i].GetLength( ) + 1;

			// Write ANSI strings into buffer
			_dword  index = 0;
			_chara* string_pool = new _chara[total_ansi_chars_number];
			for ( _dword i = 0; i < ansi_strings.Number( ); i ++ )
			{
				EGE_MEM_CPY( string_pool + index, ansi_strings[i].Str( ), ansi_strings[i].SizeOfBytes( ) );

				index += ansi_strings[i].SizeOfBytes( );
			}

			// Dump ANSI strings into stream
			stream_writer->WriteDword( total_ansi_chars_number );
			stream_writer->WriteBuffer( string_pool, total_ansi_chars_number );

			delete[] string_pool;
		}
		break;

		case _ENCODING_UTF16:
		{
			_dword  index = 0;
			_charw* string_pool = new _charw[total_utf16_chars_number];
			for ( _dword i = 0; i < mStrings.Number( ); i ++ )
			{
				EGE_MEM_CPY( string_pool + index, mStrings[i].Str( ), mStrings[i].SizeOfBytes( ) );

				index += mStrings[i].GetLength( ) + 1;
			}

			stream_writer->WriteBuffer( string_pool, total_utf16_chars_number * sizeof( _charw ) );

			delete[] string_pool;
		}
		break;

		default:
			return _false;
	}

	// Seek current pointer to make sure it's 4 bytes align
	stream_writer->SeekByArrangedValueFromBegin( 4 );

	return _true;
}

//----------------------------------------------------------------------------
// BinaryXMLAttribute Implementation
//----------------------------------------------------------------------------

BinaryXMLAttribute::BinaryXMLAttribute( )
{
}

BinaryXMLAttribute::~BinaryXMLAttribute( )
{
}

_ubool BinaryXMLAttribute::ReadAttribute( IStreamReader* stream_reader, BinaryXMLFile* xml_file )
{
	EGE_ASSERT( stream_reader != _null );
	EGE_ASSERT( xml_file != _null );

	// Read the attribute name index
	_int attribute_name_index = xml_file->ReadStringIndexFromStream( stream_reader );
	mAttributeName = xml_file->GetString( attribute_name_index );

	// Read the attribute type
	_dword attribute_type = 0;
	stream_reader->ReadDword( attribute_type );

	// Read the attribute value
	switch ( attribute_type )
	{
		case Variable::_TYPE_ID_BOOLEAN:
		{
			_byte value = 0;
			stream_reader->ReadByte( value );

			mAttributeValue = (_boolean)EGE_BOOLEAN( value );
		}
		break;

		case Variable::_TYPE_ID_INT8:
		{
			_tiny value = 0;
			stream_reader->ReadTiny( value );

			mAttributeValue = value;
		}
		break;

		case Variable::_TYPE_ID_INT16:
		{
			_short value = 0;
			stream_reader->ReadShort( value );

			mAttributeValue = value;
		}
		break;

		case Variable::_TYPE_ID_INT32:
		{
			_int value = 0;
			stream_reader->ReadLong( value );

			mAttributeValue = value;
		}
		break;

		case Variable::_TYPE_ID_UINT8:
		{
			_byte value = 0;
			stream_reader->ReadByte( value );

			mAttributeValue = value;
		}
		break;

		case Variable::_TYPE_ID_UINT16:
		{
			_word value = 0;
			stream_reader->ReadWord( value );

			mAttributeValue = value;
		}
		break;

		case Variable::_TYPE_ID_UINT32:
		{
			_dword value = 0;
			stream_reader->ReadDword( value );

			mAttributeValue = value;
		}
		break;

		case Variable::_TYPE_ID_FLOAT:
		{
			_float value = 0.0f;
			stream_reader->ReadFloat( value );

			mAttributeValue = value;
		}
		break;

		case Variable::_TYPE_ID_DOUBLE:
		{
			_double value = 0.0;
			stream_reader->ReadDouble( value );

			mAttributeValue = value;
		}
		break;

		case Variable::_TYPE_ID_WSTRING:
		{
			_int value_string_index = xml_file->ReadStringIndexFromStream( stream_reader );

			WStringPtr string = xml_file->GetString( value_string_index );
			mAttributeValue.SetString( string );
		}
		break;

		default:
			return _false;
	}

	return _true;
}

_ubool BinaryXMLAttribute::LoadFromStream( IStreamReader* stream_reader, BinaryXMLFile* xml_file )
{
	EGE_ASSERT( stream_reader != _null );
	EGE_ASSERT( xml_file != _null );

	// Read attribute
	if ( ReadAttribute( stream_reader, xml_file ) == _false )
		return _false;

	return _true;
}

_dword BinaryXMLAttribute::GetValueType( ) const
{
	return mAttributeValue.GetTypeID( );
}

WString BinaryXMLAttribute::GetName( _ubool with_prefix ) const
{
	return mAttributeName;
}

_ubool BinaryXMLAttribute::SetBool( _ubool value )
{
	return _false;
}

_ubool BinaryXMLAttribute::SetLong( _int value )
{
	return _false;
}

_ubool BinaryXMLAttribute::SetDword( _dword value )
{
	return _false;
}

_ubool BinaryXMLAttribute::SetLarge( _large value )
{
	return _false;
}

_ubool BinaryXMLAttribute::SetQword( _qword value )
{
	return _false;
}

_ubool BinaryXMLAttribute::SetDouble( _double value ) 
{
	return _false;
}

_ubool BinaryXMLAttribute::SetOword( const MD5Code& value )
{
	return _false;
}

_ubool BinaryXMLAttribute::SetString( WStringPtr string )
{
	return _false;
}

_ubool BinaryXMLAttribute::SetColor( const Color& color )
{
	return _false;
}

_ubool BinaryXMLAttribute::SetVersion( const Version& version )
{
	return _false;
}

_ubool BinaryXMLAttribute::GetBool( ) const
{
	return (_boolean)mAttributeValue;
}

_int BinaryXMLAttribute::GetLong( ) const
{
	return (_int)mAttributeValue;
}

_dword BinaryXMLAttribute::GetDword( ) const
{
	return (_dword)mAttributeValue;
}

_large BinaryXMLAttribute::GetLarge( ) const
{
	return (_large)mAttributeValue;
}

_qword BinaryXMLAttribute::GetQword( ) const
{
	return (_qword)mAttributeValue;
}

_float BinaryXMLAttribute::GetFloat( ) const
{
	return (_float)mAttributeValue;
}

_double BinaryXMLAttribute::GetDouble( ) const
{
	return (_double)mAttributeValue;
}

UString BinaryXMLAttribute::GetStringU( ) const
{
	WString string = mAttributeValue.ToString( );
	return UString( ).FromString( string );
}

WString BinaryXMLAttribute::GetStringW( ) const
{
	WString string = mAttributeValue.ToString( );
	return string;
}

MD5Code BinaryXMLAttribute::GetMD5Code( ) const
{
	WStringPtr string = mAttributeValue;
	
	MD5Code md5_code;
	md5_code.ParseFromString( string );

	return md5_code;
}

Color BinaryXMLAttribute::GetColor( ) const
{
	return Color( (_dword)mAttributeValue );
}

Version	BinaryXMLAttribute::GetVersion( ) const
{
	if ( mAttributeValue.IsNumber( ) )
	{
		return Version( (_word)mAttributeValue, 0, 0, 0 );
	}
	else if ( mAttributeValue.IsString( ) )
	{
		WStringPtr string = mAttributeValue;
		return Version( string );
	}
	else
	{
		return Version::cZero;
	}
}

//----------------------------------------------------------------------------
// BinaryXMLElement Implementation
//----------------------------------------------------------------------------

BinaryXMLElement::BinaryXMLElement( )
{
	mParentElement		= _null;
	mPrevElement		= _null;
	mNextElement		= _null;
	mFirstChildElement	= _null;
	mLastChildElement	= _null;

	mMarkupFile			= _null;
}

BinaryXMLElement::~BinaryXMLElement( )
{
}

_ubool BinaryXMLElement::ReadElementString( BinaryXMLFile* xml_file, IStreamReader* stream_reader, WStringPtr& string )
{
	_int string_index = xml_file->ReadStringIndexFromStream( stream_reader );
	string = mMarkupFile->GetString( string_index );

	return _true;
}

_ubool BinaryXMLElement::ReadAttributeNodes( BinaryXMLFile* xml_file, IStreamReader* stream_reader )
{
	EGE_ASSERT( stream_reader != _null );

	// Read attributes number
	_dword attributes_number = 0;
	stream_reader->ReadDword( attributes_number );

	// Read attributes index and get it
	for ( _dword i = 0; i < attributes_number; i ++ )
	{
		_int attribute_index = xml_file->ReadAttributeIndexFromStream( stream_reader );
		if ( attribute_index == -1 )
			return _false;

		BinaryXMLAttribute* attribute = mMarkupFile->GetXMLAttribute( attribute_index );
		if ( attribute == _null )
			return _false;

		mAttributes.InsertAscending< WStringPtr >( XMLAttributeInfo( attribute ) );
	}

	return _true;
}

_ubool BinaryXMLElement::ReadElementNode( BinaryXMLFile* xml_file, IStreamReader* stream_reader, BinaryXMLElement*& element )
{
	EGE_ASSERT( stream_reader != _null );

	_int element_index = xml_file->ReadElementIndexFromStream( stream_reader );

	if ( element_index != -1 )
		element = mMarkupFile->GetXMLElement( element_index );

	return _true;
}

_ubool BinaryXMLElement::DumpElementDepthToString( const BinaryXMLElement* element, WStringPtr depth_string, WString& string ) const
{
	_dword depth = element->GetDepth( );
	for ( _dword i = 0; i < depth; i ++ )
		string += depth_string;

	return _true;
}

_ubool BinaryXMLElement::DumpAttributesToString( const BinaryXMLElement* element, WString& string ) const
{
	for ( _dword i = 0; i < element->mAttributes.Number( ); i ++ )
	{
		const BinaryXMLAttribute* attribute = element->mAttributes[i].mAttribute;

		string += L" " + attribute->GetName( ) + L"=\"";

		switch ( attribute->GetValueType( ) )
		{
			case Variable::_TYPE_ID_BOOLEAN:
			{
				_boolean value = attribute->GetBool( );
				string += value ? L"true" : L"false";
			}
			break;

			case Variable::_TYPE_ID_INT8:
			case Variable::_TYPE_ID_INT16:
			case Variable::_TYPE_ID_INT32:
			{
				_int value = attribute->GetLong( );
				string += WString( ).FromValue( value, 10 );
			}
			break;

			case Variable::_TYPE_ID_UINT8:
			case Variable::_TYPE_ID_UINT16:
			case Variable::_TYPE_ID_UINT32:
			{
				_dword value = attribute->GetDword( );
				string += WString( ).FromValue( value, 10 );
			}
			break;

			case Variable::_TYPE_ID_FLOAT:
			{
				_float value = attribute->GetFloat( );
				string += WString( ).FromValue( value );
			}
			break;

			case Variable::_TYPE_ID_DOUBLE:
			{
				_double value = attribute->GetDouble( );
				string += WString( ).FromValue( value );
			}
			break;

			case Variable::_TYPE_ID_WSTRING:
			{
				WString value_string = attribute->GetStringW( );
				string += value_string;
			}
			break;

			default:
				break;
		}

		string += L"\"";
	}

	return _true;
}

_ubool BinaryXMLElement::DumpToString( const BinaryXMLElement* root, WString& string ) const
{
	EGE_ASSERT( root != _null );

	// Begin to write element begin section
	DumpElementDepthToString( root, L"\t", string );
	string += L"<" + root->GetName( );

	// Dump element's attributes
	if ( DumpAttributesToString( root, string ) == _false )
		return _false;

	// Finish to write element begin section
	string += L">";

	// Dump element's text
	string += root->mElementText;
	string += L"\n";

	// Continue to dump child of element
	const BinaryXMLElement* first_child = root->mFirstChildElement;
	if ( first_child != _null )
	{
		if ( DumpToString( first_child, string ) == _false )
			return _false;
	}

	// Finish to write element section
	DumpElementDepthToString( root, L"\t", string );
	string += L"</" + root->GetName( ) + L">\n";

	// Continue to dump brothers of element
	const BinaryXMLElement* brother = root->mNextElement; 
	if ( brother != _null )
	{
		if ( DumpToString( brother, string ) == _false )
			return _false;
	}

	return _true;
}

_ubool BinaryXMLElement::LoadFromStream( IStreamReader* stream_reader, BinaryXMLFile* xml_file )
{
	EGE_ASSERT( stream_reader != _null );
	EGE_ASSERT( xml_file != _null );

	// Save the XML file
	mMarkupFile = xml_file;

	// Read the element name
	if ( ReadElementString( xml_file, stream_reader, mElementName ) == _false )
		return _false;

	// Read the element text
	if ( ReadElementString( xml_file, stream_reader, mElementText ) == _false )
		return _false;

	// Read the attribute nodes
	if ( ReadAttributeNodes( xml_file, stream_reader ) == _false )
		return _false;

	// Read the parent element node
	if ( ReadElementNode( xml_file, stream_reader, mParentElement ) == _false )
		return _false;

	// Read the previous element node
	if ( ReadElementNode( xml_file, stream_reader, mPrevElement ) == _false )
		return _false;

	// Read the next element node
	if ( ReadElementNode( xml_file, stream_reader, mNextElement ) == _false )
		return _false;

	// Read the first child element node
	if ( ReadElementNode( xml_file, stream_reader, mFirstChildElement ) == _false )
		return _false;

	// Set the last child element
	if ( mFirstChildElement != _null )
	{
		mLastChildElement = mFirstChildElement;
		while ( mLastChildElement->mNextElement != _null )
			mLastChildElement = mLastChildElement->mNextElement;
	}

	return _true;
}

_ubool BinaryXMLElement::IsArrayObject( ) const
{
	return _false;
}

_dword BinaryXMLElement::GetDepth( ) const
{
	_dword depth = 0;

	const IMarkupElement* parent = mParentElement;
	while ( parent != _null )
	{
		depth ++;

		parent = parent->GetParentElement( );
	}
	
	return depth;
}

_ubool BinaryXMLElement::SetName( WStringPtr name )
{
	return _false;
}

WString BinaryXMLElement::GetName( ) const
{
	return mElementName;
}

_dword BinaryXMLElement::GetChildElementNumber( ) const
{
	_dword number = 0;
	for ( IMarkupElement* child = mFirstChildElement; child != _null; child = child->GetNextElement( ) )
		number ++;

	return number;
}

IMarkupElement* BinaryXMLElement::GetChildElementByIndex( _dword index ) const
{
	for ( IMarkupElement* child = mFirstChildElement; child != _null; child = child->GetNextElement( ), index -- )
	{
		if ( index == 0 )
			return child;
	}

	return _null;
}

IMarkupElement* BinaryXMLElement::GetChildElementByName( WStringPtr name, _ubool ignorecase ) const
{
	for ( IMarkupElement* child = mFirstChildElement; child != _null; child = child->GetNextElement( ) )
	{
		WString child_name = child->GetName( );

		if ( child_name.IsEqual( name, ignorecase ) )
			return child;
	}
	
	return _null;
}

IMarkupElement* BinaryXMLElement::GetChildElementByText( WStringPtr text, _ubool ignorecase ) const
{
	for ( IMarkupElement* child = mFirstChildElement; child != _null; child = child->GetNextElement( ) )
	{
		WString child_text = child->GetTextW( );

		if ( child_text.IsEqual( text, ignorecase ) )
			return child;
	}

	return _null;
}

_ubool BinaryXMLElement::HasChildElement( WStringPtr name, _ubool ignorecase ) const
{
	for ( IMarkupElement* child = mFirstChildElement; child != _null; child = child->GetNextElement( ) )
	{
		WString child_name = child->GetName( );

		if ( child_name.IsEqual( name, ignorecase ) )
			return _true;
	}

	return _false;
}

_ubool BinaryXMLElement::GetChildElementTextByName( WStringPtr name, UString& text, _ubool ignorecase ) const
{
	for ( IMarkupElement* child = mFirstChildElement; child != _null; child = child->GetNextElement( ) )
	{
		WString child_name = child->GetName( );

		if ( child_name.IsEqual( name, ignorecase ) == _false )
			continue;

		text = child->GetTextU( );

		return _true;
	}

	return _false;
}

_ubool BinaryXMLElement::GetChildElementTextByName( WStringPtr name, WString& text, _ubool ignorecase ) const
{
	for ( IMarkupElement* child = mFirstChildElement; child != _null; child = child->GetNextElement( ) )
	{
		WString child_name = child->GetName( );

		if ( child_name.IsEqual( name, ignorecase ) == _false )
			continue;

		text = child->GetTextW( );

		return _true;
	}

	return _false;
}

UString BinaryXMLElement::GetChildElementTextByNameU( WStringPtr name, _ubool ignorecase ) const
{
	for ( const IMarkupElement* child = mFirstChildElement; child != _null; child = child->GetNextElement( ) )
	{
		WString child_name = child->GetName( );

		if ( child_name.IsEqual( name, ignorecase ) == _false )
			continue;

		return child->GetTextU( );
	}

	return UString( "" );
}

WString BinaryXMLElement::GetChildElementTextByNameW( WStringPtr name, _ubool ignorecase ) const
{
	for ( IMarkupElement* child = mFirstChildElement; child != _null; child = child->GetNextElement( ) )
	{
		WString child_name = child->GetName( );

		if ( child_name.IsEqual( name, ignorecase ) == _false )
			continue;

		return child->GetTextW( );
	}

	return WString( L"" );
}

IMarkupElement* BinaryXMLElement::GetFirstChildElement( ) const
{
	return mFirstChildElement;
}

IMarkupElement* BinaryXMLElement::GetLastChildElement( ) const
{
	return mLastChildElement;
}

IMarkupElement* BinaryXMLElement::GetParentElement( ) const
{
	return mParentElement;
}

IMarkupElement* BinaryXMLElement::GetPrevElement( ) const
{
	return mPrevElement;
}

IMarkupElement* BinaryXMLElement::GetNextElement( ) const
{
	return mNextElement;
}

IMarkupElement* BinaryXMLElement::GetHeadElement( ) const
{
	BinaryXMLElement* head_element = mPrevElement;
	if ( head_element == _null )
		return _null;

	while ( head_element->mPrevElement != _null )
		head_element = head_element->mPrevElement;

	return head_element;
}

IMarkupElement* BinaryXMLElement::GetTailElement( ) const
{
	BinaryXMLElement* tail_element = mNextElement;
	if ( tail_element == _null )
		return _null;

	while ( tail_element->mNextElement != _null )
		tail_element = tail_element->mNextElement;

	return tail_element;
}

IMarkupElement* BinaryXMLElement::GetPrevElementByName( WStringPtr name, _ubool ignorecase ) const
{
	for ( IMarkupElement* prev = mPrevElement; prev != _null; prev = prev->GetPrevElement( ) )
	{
		WString prev_name = prev->GetName( );

		if ( prev_name.IsEqual( name, ignorecase ) == _false )
			continue;

		return prev;
	}

	return _null;
}

IMarkupElement* BinaryXMLElement::GetNextElementByName( WStringPtr name, _ubool ignorecase ) const
{
	for ( IMarkupElement* next = mNextElement; next != _null; next = next->GetNextElement( ) )
	{
		WString next_name = next->GetName( );

		if ( next_name.IsEqual( name, ignorecase ) == _false )
			continue;

		return next;
	}

	return _null;
}

IMarkupElement* BinaryXMLElement::InsertChildElementU( WStringPtr name, UStringPtr text, _ubool is_array_obj )
{
	return _null;
}

IMarkupElement* BinaryXMLElement::InsertChildElementW( WStringPtr name, WStringPtr text, _ubool is_array_obj )
{
	return _null;
}

IMarkupElement* BinaryXMLElement::InsertChildElement( const IMarkupElement* element, _ubool all_child )
{
	return _null;
}

IMarkupElement* BinaryXMLElement::InsertNextElementU( WStringPtr name, UStringPtr text, _ubool is_array_obj )
{
	return _null;
}

IMarkupElement* BinaryXMLElement::InsertNextElementW( WStringPtr name, WStringPtr text, _ubool is_array_obj )
{
	return _null;
}

IMarkupElement* BinaryXMLElement::InsertNextElement( const IMarkupElement* element, _ubool all_child )
{
	return _null;
}

IMarkupElement* BinaryXMLElement::InsertChildArrayObj( WStringPtr name )
{
	return _null;
}

IMarkupElement* BinaryXMLElement::AppendElementOfArrayObj( )
{
	return _null;
}

_dword BinaryXMLElement::AppendElementOfArrayObj( IMarkupElement* element )
{
	return -1;
}

_dword BinaryXMLElement::AppendValueUOfArrayObj( _dword value )
{
	return -1;
}

_dword BinaryXMLElement::AppendValueIOfArrayObj( _int value )
{
	return -1;
}

_dword BinaryXMLElement::AppendValueFOfArrayObj( _float value )
{
	return -1;
}

_dword BinaryXMLElement::AppendValueDOfArrayObj( _double value )
{
	return -1;
}

_dword BinaryXMLElement::GetSubElementsNumber( ) const
{
	return 0;
}

IMarkupElement* BinaryXMLElement::GetSubElementByIndex( _dword index ) const
{
	return _null;
}

_void BinaryXMLElement::Remove( )
{

}

_void BinaryXMLElement::RemoveElement( IMarkupElement* element )
{

}

IMarkupLangElementIteratorPassRef BinaryXMLElement::RemoveElement( IMarkupLangElementIterator* it )
{
	return _null;
}

IMarkupLangElementIteratorPassRef BinaryXMLElement::CreateSelfElementIterator( )
{
	return _null;
}

IMarkupLangElementIteratorPassRef BinaryXMLElement::CreateChildElementIterator( WStringPtr name, _ubool recursive )
{
	return _null;
}

_dword BinaryXMLElement::GetAttributesNumber( ) const
{
	return mAttributes.Number( );
}

IMarkupAttribute* BinaryXMLElement::GetAttributeByIndex( _dword index ) const
{
	if ( index >= mAttributes.Number( ) )
		return _null;

	return mAttributes[ index ].mAttribute;
}

_ubool BinaryXMLElement::HasAttribute( WStringPtr name, _ubool ignorecase ) const
{
	if ( ignorecase )
	{
		for ( _dword i = 0; i < mAttributes.Number( ); i ++ )
		{
			WString attribute_name = mAttributes[i].mAttribute->GetName( );

			if ( attribute_name.IsEqual( name, ignorecase ) )
				return _true;
		}
	}
	else
	{
		if ( mAttributes.SearchAscending( name ).IsValid( ) )
			return _true;
	}

	return _false;
}

IMarkupAttribute* BinaryXMLElement::SearchAttribute( WStringPtr name, _ubool ignorecase ) const
{
	if ( ignorecase )
	{
		for ( _dword i = 0; i < mAttributes.Number( ); i ++ )
		{
			BinaryXMLAttribute* attribute = mAttributes[i].mAttribute;
			
			WString attribute_name = attribute->GetName( );

			if ( attribute_name.IsEqual( name, ignorecase ) )
				return attribute;
		}
	}
	else
	{
		XMLAttributeInfoArray::Iterator it = mAttributes.SearchAscending( name );
		if ( it.IsValid( ) )
			return it.GetObject( ).mAttribute;
	}

	return _null;
}

_dword BinaryXMLElement::GetValueU( ) const
{
	return mElementText.ToDword( 10 );
}

_int BinaryXMLElement::GetValueI( ) const
{
	return mElementText.ToLong( 10 );
}

_float BinaryXMLElement::GetValueF( ) const
{
	return mElementText.ToFloat( );
}

_double BinaryXMLElement::GetValueD( ) const
{
	return mElementText.ToDouble( );
}

_ubool BinaryXMLElement::SetValueU( _dword value )
{
	return _false;
}

_ubool BinaryXMLElement::SetValueI( _int value )
{
	return _false;
}

_ubool BinaryXMLElement::SetValueF( _float value )
{
	return _false;
}

_ubool BinaryXMLElement::SetValueD( _double value )
{
	return _false;
}

_ubool BinaryXMLElement::GetText( AString& text ) const
{
	text.FromString( mElementText );

	return _true;
}

_ubool BinaryXMLElement::GetText( UString& text ) const
{
	text.FromString( mElementText );

	return _true;
}

_ubool BinaryXMLElement::GetText( WString& text ) const
{
	text = mElementText;

	return _true;
}

AString BinaryXMLElement::GetTextA( ) const
{
	return AString( ).FromString( mElementText );
}

UString BinaryXMLElement::GetTextU( ) const
{
	return UString( ).FromString( mElementText );
}

WString BinaryXMLElement::GetTextW( ) const
{
	return mElementText;
}

_ubool BinaryXMLElement::SetText( AStringPtr text )
{
	return _false;
}

_ubool BinaryXMLElement::SetText( UStringPtr text )
{
	return _false;
}

_ubool BinaryXMLElement::SetText( WStringPtr text )
{
	return _false;
}

_ubool BinaryXMLElement::GetAttributeBool( WStringPtr name, _ubool& value, _ubool ignorecase ) const
{
	IMarkupAttribute* attribute = SearchAttribute( name, ignorecase );
	if ( attribute == _null )
		return _false;

	value = attribute->GetBool( );

	return _true;
}

_ubool BinaryXMLElement::GetAttributeLong( WStringPtr name, _int& value, _ubool ignorecase ) const
{
	IMarkupAttribute* attribute = SearchAttribute( name, ignorecase );
	if ( attribute == _null )
		return _false;

	value = attribute->GetLong( );

	return _true;
}

_ubool BinaryXMLElement::GetAttributeDword( WStringPtr name, _dword& value, _ubool ignorecase ) const
{
	IMarkupAttribute* attribute = SearchAttribute( name, ignorecase );
	if ( attribute == _null )
		return _false;

	value = attribute->GetDword( );

	return _true;
}

_ubool BinaryXMLElement::GetAttributeLarge( WStringPtr name, _large& value, _ubool ignorecase ) const
{
	IMarkupAttribute* attribute = SearchAttribute( name, ignorecase );
	if ( attribute == _null )
		return _false;

	value = attribute->GetLarge( );

	return _true;
}

_ubool BinaryXMLElement::GetAttributeQword( WStringPtr name, _qword& value, _ubool ignorecase ) const
{
	IMarkupAttribute* attribute = SearchAttribute( name, ignorecase );
	if ( attribute == _null )
		return _false;

	value = attribute->GetQword( );

	return _true;
}

_ubool BinaryXMLElement::GetAttributeDouble( WStringPtr name, _double& value, _ubool ignorecase ) const
{
	IMarkupAttribute* attribute = SearchAttribute( name, ignorecase );
	if ( attribute == _null )
		return _false;

	value = attribute->GetDouble( );

	return _true;
}

_ubool BinaryXMLElement::GetAttributeString( WStringPtr name, UString& string, _ubool ignorecase ) const
{
	IMarkupAttribute* attribute = SearchAttribute( name, ignorecase );
	if ( attribute == _null )
		return _false;

	string = attribute->GetStringU( );

	return _true;
}

_ubool BinaryXMLElement::GetAttributeString( WStringPtr name, WString& string, _ubool ignorecase ) const
{
	IMarkupAttribute* attribute = SearchAttribute( name, ignorecase );
	if ( attribute == _null )
		return _false;

	string = attribute->GetStringW( );

	return _true;
}

_ubool BinaryXMLElement::GetAttributeMD5Code( WStringPtr name, MD5Code& value, _ubool ignorecase ) const
{
	IMarkupAttribute* attribute = SearchAttribute( name, ignorecase );
	if ( attribute == _null )
		return _false;

	value = attribute->GetMD5Code( );

	return _true;
}

_ubool BinaryXMLElement::GetAttributeColor( WStringPtr name, Color& color, _ubool ignorecase ) const
{
	IMarkupAttribute* attribute = SearchAttribute( name, ignorecase );
	if ( attribute == _null )
		return _false;

	color = attribute->GetColor( );

	return _true;
}

_ubool BinaryXMLElement::GetAttributeVersion( WStringPtr name, Version& version, _ubool ignorecase ) const
{
	IMarkupAttribute* attribute = SearchAttribute( name, ignorecase );
	if ( attribute == _null )
		return _false;

	version = attribute->GetVersion( );

	return _true;
}

_ubool BinaryXMLElement::SetAttributeBool( WStringPtr name, _ubool value )
{
	return _false;
}

_ubool BinaryXMLElement::SetAttributeLong( WStringPtr name, _int value )
{
	return _false;
}

_ubool BinaryXMLElement::SetAttributeDword( WStringPtr name, _dword value )
{
	return _false;
}

_ubool BinaryXMLElement::SetAttributeLarge( WStringPtr name, _large value )
{
	return _false;
}

_ubool BinaryXMLElement::SetAttributeQword( WStringPtr name, _qword value )
{
	return _false;
}

_ubool BinaryXMLElement::SetAttributeDouble( WStringPtr name, _double value )
{
	return _false;
}

_ubool BinaryXMLElement::SetAttributeString( WStringPtr name, UStringPtr string )
{
	return _false;
}

_ubool BinaryXMLElement::SetAttributeString( WStringPtr name, WStringPtr string )
{
	return _false;
}

_ubool BinaryXMLElement::SetAttributeMD5Code( WStringPtr name, const MD5Code& value )
{
	return _false;
}

_ubool BinaryXMLElement::SetAttributeColor( WStringPtr name, const Color& color )
{
	return _false;
}

_ubool BinaryXMLElement::SetAttributeVersion( WStringPtr name, const Version& version )
{
	return _false;
}

WString BinaryXMLElement::DumpToString( ) const
{
	WString string;
	if ( DumpToString( this, string ) == _false )
		return WString( L"" );

	return string;
}

WString BinaryXMLElement::DumpToSchemaString( ) const
{
	return WString( L"" );
}

//----------------------------------------------------------------------------
// BinaryXMLFileDeclaration Implementation
//----------------------------------------------------------------------------

BinaryXMLFileDeclaration::BinaryXMLFileDeclaration( )
{
}

BinaryXMLFileDeclaration::~BinaryXMLFileDeclaration( )
{
}

_void BinaryXMLFileDeclaration::SetVersion( const Version& version )
{
}

const Version& BinaryXMLFileDeclaration::GetVersion( ) const
{
	return Version::cZero;
}

_void BinaryXMLFileDeclaration::SetEncoding( _ENCODING encoding )
{
}

_ENCODING BinaryXMLFileDeclaration::GetEncoding( ) const
{
	return _ENCODING_ANSI;
}

//----------------------------------------------------------------------------
// BinaryXMLFile Implementation
//----------------------------------------------------------------------------

BinaryXMLFile::BinaryXMLFile( )
{
	mRootElement			= _null;

	mStringTable			= _null;

	mXMLAttributesNumber	= 0;
	mXMLAttributes			= _null;

	mXMLElementsNumber		= 0;
	mXMLElements			= _null;
}

BinaryXMLFile::~BinaryXMLFile( )
{
	Unload( );
}

_ubool BinaryXMLFile::CreateRegularExpressions( IRegularExpressionRef regular_expressions[] ) const
{
	regular_expressions[_RET_POSITIVE_NUMERIC]	= GetInterfaceFactory( )->CreateRegularExpression( L"^\\+?(0|[1-9][0-9]*)$" );
	regular_expressions[_RET_NEGATIVE_NUMERIC]	= GetInterfaceFactory( )->CreateRegularExpression( L"^(-)?[1-9][0-9]*$" );
	regular_expressions[_RET_DOUBLE]			= GetInterfaceFactory( )->CreateRegularExpression( L"^[+-]?([0-9]*\\.?[0-9]+|[0-9]+\\.?[0-9]*)([eE][+-]?[0-9]+)?$" );
	regular_expressions[_RET_COLOR]				= GetInterfaceFactory( )->CreateRegularExpression( L"\\b0[xX][0-9a-fA-F]+\\b" );
	regular_expressions[_RET_MD5]				= GetInterfaceFactory( )->CreateRegularExpression( L"/^[a-z0-9]{32}$/" );

	return _true;
}

_ubool BinaryXMLFile::LoadHeaderInfo( IStreamReader* stream_reader )
{
	stream_reader->ReadBuffer( &mHeaderInfo, sizeof( mHeaderInfo ) );

	return _true;
}

_ubool BinaryXMLFile::LoadStringTable( IStreamReader* stream_reader )
{
	mStringTable = new BinaryXMLStringTableReader( );
	if ( mStringTable->LoadFromStream( (_ENCODING)mHeaderInfo.mEncodingType, stream_reader ) == _false )
		return _false;

	return _true;
}

_ubool BinaryXMLFile::LoadXMLAttributes( IStreamReader* stream_reader )
{
	// Read XML attributes number
	stream_reader->ReadDword( mXMLAttributesNumber );
	if ( mXMLAttributesNumber == 0 )
		return _false;

	// Create and read XML attributes
	mXMLAttributes = new BinaryXMLAttribute[ mXMLAttributesNumber ];
	for ( _dword i = 0; i < mXMLAttributesNumber; i ++ )
	{
		if ( mXMLAttributes[i].LoadFromStream( stream_reader, this ) == _false )
			return _false;
	}
	
	return _true;
}

_ubool BinaryXMLFile::LoadXMLElements( IStreamReader* stream_reader )
{
	// Read XML elements number
	stream_reader->ReadDword( mXMLElementsNumber );
	if ( mXMLElementsNumber == 0 )
		return _false;

	// Create and read XML elements
	mXMLElements = new BinaryXMLElement[mXMLElementsNumber];
	for ( _dword i = 0; i < mXMLElementsNumber; i ++ )
	{
		if ( mXMLElements[i].LoadFromStream( stream_reader, this ) == _false )
			return _false;
	}

	return _true;
}

BinaryXMLFile::_REGULAR_EXPRESSION_TYPE BinaryXMLFile::GetValueType( WStringPtr value, IRegularExpressionRef regular_expressions[] ) const
{
	if ( value.IsEqual( L"true", _true ) || value.IsEqual( L"false", _true ) )
		return _RET_BOOLEAN;

	for ( _dword i = 0; i < _RET_MAXNUMBER; i ++ )
	{
		if ( regular_expressions[i]->Match( value ) )
			return (_REGULAR_EXPRESSION_TYPE)i;
	}

	return _RET_STRING;
}

BinaryXMLFile::_REGULAR_EXPRESSION_TYPE BinaryXMLFile::GetValueType( const BinaryXMLAttribute& attribute ) const
{
	switch ( attribute.GetValueType( ) )
	{
		case Variable::_TYPE_ID_BOOLEAN:
			return BinaryXMLFile::_RET_BOOLEAN;

		case Variable::_TYPE_ID_INT8:
		case Variable::_TYPE_ID_INT16:
		case Variable::_TYPE_ID_INT32:
		case Variable::_TYPE_ID_INT64:
			return BinaryXMLFile::_RET_NEGATIVE_NUMERIC;

		case Variable::_TYPE_ID_UINT8:
		case Variable::_TYPE_ID_UINT16:
		case Variable::_TYPE_ID_UINT32:
		case Variable::_TYPE_ID_UINT64:
			return BinaryXMLFile::_RET_POSITIVE_NUMERIC;

		case Variable::_TYPE_ID_FLOAT:
		case Variable::_TYPE_ID_DOUBLE:
			return BinaryXMLFile::_RET_DOUBLE;

		case Variable::_TYPE_ID_WSTRING:
			return BinaryXMLFile::_RET_STRING;

		default:
			return BinaryXMLFile::_RET_STRING;
	}
}

_ubool BinaryXMLFile::WriteIndex2Stream( IStreamWriter* stream_writer, _INDEX_MODE index_mode, _int index ) const
{
	switch ( index_mode )
	{
		case _INDEX_8_BITS:		stream_writer->WriteTiny( index ); break;
		case _INDEX_16_BITS:	stream_writer->WriteShort( index ); break;
		case _INDEX_32_BITS:	stream_writer->WriteLong( index ); break;
		default:
			break;
	}

	return _true;
}

_ubool BinaryXMLFile::WriteAttributeIndex2Stream( IStreamWriter* stream_writer, const HeaderInfo& header_info, IMarkupAttribute* attribute, const AttributeArray& xml_attributes ) const
{
	_int index = -1;

	if ( attribute != _null )
	{
		AttributeArray::Iterator it = xml_attributes.SearchAscending( attribute );
		if ( it.IsValid( ) == _false )
			return _false;

		index = it.mIndex;
	}

	if ( WriteIndex2Stream( stream_writer, (_INDEX_MODE)header_info.mAttributeIndexMode, index ) == _false )
		return _false;

	return _true;
}

_ubool BinaryXMLFile::WriteElementIndex2Stream( IStreamWriter* stream_writer, const HeaderInfo& header_info, IMarkupElement* element, const ElementArray& xml_elements ) const
{
	_int index = -1;

	if ( element != _null )
	{
		ElementArray::Iterator it = xml_elements.SearchAscending( element );
		if ( it.IsValid( ) == _false )
			return _false;

		index = it.mIndex;
	}

	if ( WriteIndex2Stream( stream_writer, (_INDEX_MODE)header_info.mElementIndexMode, index ) == _false )
		return _false;

	return _true;
}

_ubool BinaryXMLFile::WriteStringIndexIntoStream( IStreamWriter* stream_writer, const HeaderInfo& header_info, const BinaryXMLStringTableWriter& string_table, WStringPtr string ) const
{
	_int index = string_table.SearchString( string );
	EGE_ASSERT( index != -1 );

	if ( WriteIndex2Stream( stream_writer, (_INDEX_MODE)header_info.mStringTableIndexMode, index ) == _false )
		return _false;

	return _true;
}

_ubool BinaryXMLFile::WriteAttribute2Stream( IStreamWriter* stream_writer, const HeaderInfo& header_info, const BinaryXMLStringTableWriter& string_table, const AttributeInfo& attribute ) const
{
	// Get the attribute name
	WString attribute_name = attribute.mAttribute->GetName( );

	// Write the attribute name index
	if ( WriteStringIndexIntoStream( stream_writer, header_info, string_table, attribute_name ) == _false )
		return _false;

	// Write the value and its type
	switch ( attribute.mType )
	{
		case _RET_BOOLEAN:
		{
			_boolean value = attribute.mAttribute->GetBool( );

			// In dynamic value mode
			if ( header_info.mValueMode == _VALUE_MODE_DYNAMIC )
			{
				stream_writer->WriteDword( Variable::_TYPE_ID_BOOLEAN );
				stream_writer->WriteByte( value );
			}
			// In normal value mode
			else
			{
				stream_writer->WriteDword( Variable::_TYPE_ID_UINT32 );
				stream_writer->WriteDword( value );
			}
		}
		break;

		case _RET_STRING:
		{
			stream_writer->WriteDword( Variable::_TYPE_ID_WSTRING );

			WString attribute_value = attribute.mAttribute->GetStringW( );
			if ( WriteStringIndexIntoStream( stream_writer, header_info, string_table, attribute_value ) == _false )
				return _false;
		}
		break;

		case _RET_POSITIVE_NUMERIC:
		{
			_dword value = attribute.mAttribute->GetDword( );

			// In dynamic value mode
			if ( header_info.mValueMode == _VALUE_MODE_DYNAMIC )
			{
				// 8 bits
				if ( value <= 127 )
				{
					stream_writer->WriteDword( Variable::_TYPE_ID_UINT8 );
					stream_writer->WriteByte( (_byte)value );
				}
				// 16 bits
				else if ( value <= 32767 )
				{
					stream_writer->WriteDword( Variable::_TYPE_ID_UINT16 );
					stream_writer->WriteWord( (_word)value );
				}
				// 32 bits
				else
				{
					stream_writer->WriteDword( Variable::_TYPE_ID_UINT32 );
					stream_writer->WriteDword( value );
				}
			}
			// In normal value mode
			else
			{
				stream_writer->WriteDword( Variable::_TYPE_ID_UINT32 );
				stream_writer->WriteDword( value );
			}
		}
		break;

		case _RET_NEGATIVE_NUMERIC:
		{
			_int value = attribute.mAttribute->GetLong( );

			// In dynamic value mode
			if ( header_info.mValueMode == _VALUE_MODE_DYNAMIC )
			{
				// 8 bits
				if ( value >= -128 )
				{
					stream_writer->WriteDword( Variable::_TYPE_ID_INT8 );
					stream_writer->WriteTiny( (_tiny)value );
				}
				// 16 bits
				else if ( value >= -32768 )
				{
					stream_writer->WriteDword( Variable::_TYPE_ID_INT16 );
					stream_writer->WriteShort( (_short)value );
				}
				// 32 bits
				else
				{
					stream_writer->WriteDword( Variable::_TYPE_ID_INT32 );
					stream_writer->WriteLong( value );
				}
			}
			// In normal value mode
			else
			{
				stream_writer->WriteDword( Variable::_TYPE_ID_INT32 );
				stream_writer->WriteLong( value );
			}
		}
		break;

		case _RET_DOUBLE:
		{
			_double value = attribute.mAttribute->GetDouble( );
			if ( value >= Math::cMinFloat && value <= Math::cMaxFloat )
			{
				stream_writer->WriteDword( Variable::_TYPE_ID_FLOAT );
				stream_writer->WriteFloat( (_float)value );
			}
			else
			{
				stream_writer->WriteDword( Variable::_TYPE_ID_DOUBLE );
				stream_writer->WriteDouble( value );
			}
		}
		break;

		case _RET_COLOR:
		{
			_dword value = attribute.mAttribute->GetDword( );

			stream_writer->WriteDword( Variable::_TYPE_ID_UINT32 );
			stream_writer->WriteDword( value );
		}
		break;

		case _RET_MD5:
		{
			MD5Code value = attribute.mAttribute->GetMD5Code( );

			stream_writer->WriteDword( Variable::_TYPE_ID_WSTRING );
			if ( WriteStringIndexIntoStream( stream_writer, header_info, string_table, value.ToWString( _true ) ) == _false )
				return _false;
		}
		break;

		default:
			break;
	}

	return _true;
}

_ubool BinaryXMLFile::WriteAttributes2Stream( IStreamWriter* stream_writer, const HeaderInfo& header_info, const BinaryXMLStringTableWriter& string_table, const AttributeArray& xml_attributes ) const
{
	stream_writer->WriteDword( xml_attributes.Number( ) );

	for ( _dword i = 0; i < xml_attributes.Number( ); i ++ )
	{
		const AttributeInfo& attribute = xml_attributes[i];

		if ( WriteAttribute2Stream( stream_writer, header_info, string_table, attribute ) == _false )
			return _false;
	}

	return _true;
}

_ubool BinaryXMLFile::WriteElements2Stream( IStreamWriter* stream_writer, const HeaderInfo& header_info, const BinaryXMLStringTableWriter& string_table, const ElementArray& xml_elements, const AttributeArray& xml_attributes ) const
{
	stream_writer->WriteDword( xml_elements.Number( ) );

	for ( _dword i = 0; i < xml_elements.Number( ); i ++ )
	{
		const IMarkupElement* element = xml_elements[i].mElement;
		EGE_ASSERT( element != _null );

		// Write the element name index
		WString element_name = element->GetName( );
		if ( WriteStringIndexIntoStream( stream_writer, header_info, string_table, element_name ) == _false )
			return _false;

		// Write the element text index
		WString element_text = element->GetTextW( );
		if ( WriteStringIndexIntoStream( stream_writer, header_info, string_table, element_text ) == _false )
			return _false;

		// Write the number of attributes
		_dword attributes_number = element->GetAttributesNumber( );
		stream_writer->WriteDword( attributes_number );

		// Write the attribute nodes
		for ( _dword i = 0; i < attributes_number; i ++ )
			WriteAttributeIndex2Stream( stream_writer, header_info, element->GetAttributeByIndex( i ), xml_attributes );

		// Write the parent, previous, next and first child element node
		WriteElementIndex2Stream( stream_writer, header_info, element->GetParentElement( ), xml_elements );
		WriteElementIndex2Stream( stream_writer, header_info, element->GetPrevElement( ), xml_elements );
		WriteElementIndex2Stream( stream_writer, header_info, element->GetNextElement( ), xml_elements );
		WriteElementIndex2Stream( stream_writer, header_info, element->GetFirstChildElement( ), xml_elements );
	}

	return _true;
}

_ubool BinaryXMLFile::WriteBXML2Stream( IStreamWriter* stream_writer, const HeaderInfo& header_info, const BinaryXMLStringTableWriter& string_table, const ElementArray& xml_elements, const AttributeArray& xml_attributes ) const
{
	// Write the file ID
	stream_writer->WriteDword( _FILE_ID );

	// Write header info into stream
	if ( stream_writer->WriteBuffer( &header_info, sizeof( HeaderInfo ) ) == _false )
		return _false;

	// Write string table into stream
	if ( string_table.Write2Stream( (_ENCODING)header_info.mEncodingType, stream_writer ) == _false )
		return _false;

	// Build stream from attributes
	if ( WriteAttributes2Stream( stream_writer, header_info, string_table, xml_attributes ) == _false )
		return _false;

	// Build stream from elements
	if ( WriteElements2Stream( stream_writer, header_info, string_table, xml_elements, xml_attributes ) == _false )
		return _false;

	return _true;
}

BinaryXMLFile::_INDEX_MODE BinaryXMLFile::GetIndexMode( _dword number ) const
{
	if ( number <= 127 )
		return _INDEX_8_BITS;
	else if ( number <= 32767 )
		return _INDEX_16_BITS;
	else
		return _INDEX_32_BITS;
}

_ubool BinaryXMLFile::BuildPoolsFromMarkupFile( IMarkupElement* element, BinaryXMLStringTableWriter& string_table, ElementArray& xml_elements, AttributeArray& xml_attributes, IRegularExpressionRef regular_expressions[] )
{
	while ( element != _null )
	{
		WString element_name = element->GetName( );
		WString element_text = element->GetTextW( );

		// Update string table
		string_table.AddString( element_name );
		string_table.AddString( element_text );

		// Update attributes
		for ( _dword i = 0; i < element->GetAttributesNumber( ); i ++ )
		{
			IMarkupAttribute* attribute = element->GetAttributeByIndex( i );
			EGE_ASSERT( attribute != _null );

			// Get the attribute name
			WString attribute_name = attribute->GetName( );

			// Update string table
			string_table.AddString( attribute_name );

			// Get the value string and its type
			WString						value_string = attribute->GetStringW( );
			_REGULAR_EXPRESSION_TYPE	value_type = GetValueType( value_string, regular_expressions );

			// Update string table
			if ( value_type == _RET_STRING )
			{
				WString attribute_value = attribute->GetStringW( );
				string_table.AddString( attribute_value );
			}

			// Update attributes pool
			xml_attributes.InsertAscending( AttributeInfo( value_type, attribute ) );
		}

		// Update elements pool
		xml_elements.InsertAscending( ElementInfo( element ) );

		// Continue to walk child elements
		IMarkupElement* child_element = element->GetFirstChildElement( );
		if ( child_element != _null )
		{
			if ( BuildPoolsFromMarkupFile( child_element, string_table, xml_elements, xml_attributes, regular_expressions ) == _false )
				return _false;
		}

		// Jump to the next element
		element = element->GetNextElement( );
	}

	return _true;
}

_ubool BinaryXMLFile::BuildHeaderInfo( HeaderInfo& header_info, const BinaryXMLStringTableWriter& string_table, const ElementArray& xml_elements, const AttributeArray& xml_attributes ) const
{
	header_info.mValueMode		= _VALUE_MODE_NORMAL;
	header_info.mEncodingType	= _ENCODING_UTF16;

	// It's dynamic value mode
	if ( header_info.mValueMode == _VALUE_MODE_DYNAMIC )
	{
		header_info.mAttributeIndexMode		= GetIndexMode( xml_attributes.Number( ) );
		header_info.mElementIndexMode		= GetIndexMode( xml_elements.Number( ) );
		header_info.mStringTableIndexMode	= GetIndexMode( string_table.GetStringNumber( ) );
	}
	// It's normal value mode
	else
	{
		header_info.mAttributeIndexMode		= _INDEX_32_BITS;
		header_info.mElementIndexMode		= _INDEX_32_BITS;
		header_info.mStringTableIndexMode	= _INDEX_32_BITS;
	}

	return _true;
}

_int BinaryXMLFile::ReadIndexFromStream( _INDEX_MODE index_mode, IStreamReader* stream_reader ) const
{
	_int feedback_index = -1;

	switch ( index_mode )
	{
		case BinaryXMLFile::_INDEX_8_BITS:
		{
			_tiny index = -1;
			stream_reader->ReadTiny( index );

			feedback_index = index;
		}
		break;

		case BinaryXMLFile::_INDEX_16_BITS:
		{
			_short index = -1;
			stream_reader->ReadShort( index );

			feedback_index = index;
		}
		break;

		case BinaryXMLFile::_INDEX_32_BITS:
		{
			_int index = -1;
			stream_reader->ReadLong( index );

			feedback_index = index;
		}
		break;

		default:
			break;
	}

	return feedback_index;
}

_ubool BinaryXMLFile::LoadFromMarkupFile( IMarkupFile* markup_file )
{
	if ( markup_file == _null )
		return _false;

	// The string table
	BinaryXMLStringTableWriter string_table;

	// Create regular expressions
	IRegularExpressionRef regular_expressions[_RET_MAXNUMBER];
	if ( CreateRegularExpressions( regular_expressions ) == _false )
		return _false;

	// The XML elements and attributes pool
	ElementArray xml_elements;
	AttributeArray xml_attributes;

	// Build pools form markup file
	if ( BuildPoolsFromMarkupFile( markup_file->GetRootElement( ), string_table, xml_elements, xml_attributes, regular_expressions ) == _false )
		return _false;

	// Build header info
	HeaderInfo header_info;
	if ( BuildHeaderInfo( header_info, string_table, xml_elements, xml_attributes ) == _false )
		return _false;

	// Create stream writer
	IStreamWriterRef stream_writer = GetInterfaceFactory( )->CreateMemStreamWriter( 4 MB, 4 MB );
	if ( stream_writer.IsNull( ) )
		return _false;

	// Build stream for binary XML file
	if ( WriteBXML2Stream( stream_writer, header_info, string_table, xml_elements, xml_attributes ) == _false )
		return _false;

	// Create stream reader
	IStreamReaderRef stream_reader = GetInterfaceFactory( )->CreateMemStreamReader( stream_writer->GetBuffer( ), stream_writer->GetOffset( ), _STREAM_SHARE_MODE_READ_ONLY );
	if ( stream_reader.IsNull( ) )
		return _false;

	// Load from stream
	if ( LoadFromStream( stream_reader ) == _false )
		return _false;

	return _true;
}

_int BinaryXMLFile::ReadAttributeIndexFromStream( IStreamReader* stream_reader )
{
	return ReadIndexFromStream( (_INDEX_MODE)mHeaderInfo.mAttributeIndexMode, stream_reader );
}

_int BinaryXMLFile::ReadElementIndexFromStream( IStreamReader* stream_reader )
{
	return ReadIndexFromStream( (_INDEX_MODE)mHeaderInfo.mElementIndexMode, stream_reader );
}

_int BinaryXMLFile::ReadStringIndexFromStream( IStreamReader* stream_reader )
{
	return ReadIndexFromStream( (_INDEX_MODE)mHeaderInfo.mStringTableIndexMode, stream_reader );
}

_FILE_FORMAT BinaryXMLFile::GetFileID( ) const
{
	return _FF_BXML;
}

_ubool BinaryXMLFile::LoadFromStream( IStreamReader* stream_reader )
{
	if ( stream_reader == _null )
		return _false;

	Unload( );

	// Load the file ID
	_dword file_id = 0;
	stream_reader->ReadDword( file_id );

	// Check file ID
	if ( file_id != _FILE_ID )
		return _false;

	// Load header info
	if ( LoadHeaderInfo( stream_reader ) == _false )
		return _false;

	// Load string table
	if ( LoadStringTable( stream_reader ) == _false )
		return _false;

	// Load XML attributes
	if ( LoadXMLAttributes( stream_reader ) == _false )
		return _false;

	// Load XML elements
	if ( LoadXMLElements( stream_reader ) == _false )
		return _false;

	// Get the root element
	mRootElement = &mXMLElements[0];
	EGE_ASSERT( mRootElement != _null );
	while ( mRootElement->GetParentElement( ) != _null )
		mRootElement = (BinaryXMLElement*) mRootElement->GetParentElement( );

	return _true;
}

_void BinaryXMLFile::Unload( )
{
	mRootElement = _null;

	EGE_DELETE( mStringTable );

	mXMLAttributesNumber = 0;
	EGE_DELETE_ARRAY( mXMLAttributes );

	mXMLElementsNumber = 0;
	EGE_DELETE_ARRAY( mXMLElements );
}

_ubool BinaryXMLFile::SaveToStream( IStreamWriter* stream_writer, _dword flags ) const
{
	// Create string table writer
	BinaryXMLStringTableWriter string_table( *mStringTable );

	// Create elements pool
	ElementArray elements;
	elements.Resize( mXMLElementsNumber );
	for ( _dword i = 0; i < mXMLElementsNumber; i ++ )
		elements.Append( ElementInfo( &mXMLElements[i] ) );

	// Create attributes pool
	AttributeArray attributes;
	attributes.Resize( mXMLAttributesNumber );
	for ( _dword i = 0; i < mXMLAttributesNumber; i ++ )
	{
		_REGULAR_EXPRESSION_TYPE value_type = GetValueType( mXMLAttributes[i] );

		attributes.Append( AttributeInfo( value_type, &mXMLAttributes[i] ) );
	}

	// Build stream for binary XML file
	if ( WriteBXML2Stream( stream_writer, mHeaderInfo, string_table, elements, attributes ) == _false )
		return _false;

	return _true;
}

IMarkupDeclaration* BinaryXMLFile::GetDeclaration( )
{
	return &mDeclaration;
}

IMarkupElement* BinaryXMLFile::GetRootElement( )
{
	return mRootElement;
}

_ubool BinaryXMLFile::SchemaValidate( WStringPtr filename )
{
	return _false;
}

_ubool BinaryXMLFile::SchemaValidate( IStreamReader* stream_reader )
{
	return _false;
}