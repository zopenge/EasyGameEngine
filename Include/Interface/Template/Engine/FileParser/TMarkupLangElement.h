//! @file     TMarkupLangElement.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TMarkupLangElement
//----------------------------------------------------------------------------

template< typename Type >
class TMarkupLangElement : public Type
{
protected:
	typedef TMarkupLangElement< Type > TSelfClass;

protected:
	//!	The depth of element
	_dword				mDepth;

	//!	The first child element
	IMarkupLangElement*	mFirstChildElement;
	//!	The parent element
	IMarkupLangElement*	mParentElement;
	//!	The previous element
	IMarkupLangElement*	mPrevElement;
	//!	The next element
	IMarkupLangElement*	mNextElement;

protected:
	//!	Set the first child element.
	EGE_SET_ACCESSOR( IMarkupLangElement*, FirstChildElement )
	//!	Set the next element.
	EGE_SET_ACCESSOR( IMarkupLangElement*, NextElement )

protected:
    //! When create element iterator.
    virtual IMarkupLangElementIteratorPassRef OnCreateElementIterator( IMarkupLangElement* element ) PURE;
    
protected:
	TMarkupLangElement( IMarkupLangElement* parent, IMarkupLangElement* prev, IMarkupLangElement* next );
	virtual ~TMarkupLangElement( );

// IMarkupLangElement Interface
public:
	virtual _ubool								IsArrayObject( ) const override;

	virtual _dword								GetDepth( ) const override;

	virtual _dword								GetChildElementNumber( ) const override;
	virtual IMarkupLangElement*					GetChildElementByIndex( _dword index ) const override;
	virtual IMarkupLangElement*					GetChildElementByName( WStringPtr name, _ubool ignorecase = _false ) const override;
	virtual IMarkupLangElement*					GetChildElementByText( WStringPtr text, _ubool ignorecase = _false ) const override;

	virtual _ubool								HasChildElement( WStringPtr name, _ubool ignorecase = _false ) const override;
	virtual _ubool								GetChildElementTextByName( WStringPtr name, UString& text, _ubool ignorecase = _false ) const override;
	virtual _ubool								GetChildElementTextByName( WStringPtr name, WString& text, _ubool ignorecase = _false ) const override;
	virtual UStringR							GetChildElementTextByNameU( WStringPtr name, _ubool ignorecase = _false ) const override;
	virtual WStringR							GetChildElementTextByNameW( WStringPtr name, _ubool ignorecase = _false ) const override;

	virtual IMarkupLangElement* 				GetFirstChildElement( ) const override;
	virtual IMarkupLangElement*					GetLastChildElement( ) const override;
	virtual IMarkupLangElement*					GetParentElement( ) const override;
	virtual IMarkupLangElement*					GetPrevElement( ) const override;
	virtual IMarkupLangElement* 				GetNextElement( ) const override;
	virtual IMarkupLangElement*					GetHeadElement( ) const override;
	virtual IMarkupLangElement*					GetTailElement( ) const override;

	virtual IMarkupLangElement*					GetPrevElementByName( WStringPtr name, _ubool ignorecase = _false ) const override;
	virtual IMarkupLangElement*					GetNextElementByName( WStringPtr name, _ubool ignorecase = _false ) const override;

	virtual IMarkupLangElement*					InsertChildElementU( WStringPtr name, UStringPtr text, _ubool is_array_obj ) override;
	virtual IMarkupLangElement*					InsertChildElementW( WStringPtr name, WStringPtr text, _ubool is_array_obj ) override;
	virtual IMarkupLangElement*					InsertChildElement( const IMarkupLangElement* element, _ubool all_child ) override;
	virtual IMarkupLangElement*					InsertNextElementU( WStringPtr name, UStringPtr text, _ubool is_array_obj ) override;
	virtual IMarkupLangElement*					InsertNextElementW( WStringPtr name, WStringPtr text, _ubool is_array_obj ) override;
	virtual IMarkupLangElement*					InsertNextElement( const IMarkupLangElement* element, _ubool all_child ) override;

	virtual IMarkupLangElement*					InsertChildArrayObj( WStringPtr name ) override;
	virtual IMarkupLangElement*					AppendElementOfArrayObj( ) override;
	virtual _dword								AppendElementOfArrayObj( IMarkupLangElement* element ) override;
	virtual _dword								AppendValueUOfArrayObj( _dword value ) override;
	virtual _dword								AppendValueIOfArrayObj( _int value ) override;
	virtual _dword								AppendValueFOfArrayObj( _float value ) override;
	virtual _dword								AppendValueDOfArrayObj( _double value ) override;
	virtual _dword								GetSubElementsNumber( ) const override;
	virtual IMarkupLangElement*					GetSubElementByIndex( _dword index ) const override;

	virtual _void								Remove( ) override;
	virtual _void								RemoveElement( IMarkupLangElement* element ) override;
	virtual IMarkupLangElementIteratorPassRef	RemoveElement( IMarkupLangElementIterator* it ) override;

	virtual IMarkupLangElementIteratorPassRef	CreateSelfElementIterator( ) override;
	virtual IMarkupLangElementIteratorPassRef	CreateChildElementIterator( WStringPtr name, _ubool recursive = _false ) override;

	virtual _dword								GetAttributesNumber( ) const override;
	virtual IMarkupLangAttribute*				GetAttributeByIndex( _dword index ) const override;

	virtual _ubool								HasAttribute( WStringPtr name, _ubool ignorecase = _false ) const override;
	virtual IMarkupLangAttribute*				SearchAttribute( WStringPtr name, _ubool ignorecase = _false ) const override;

	virtual _ubool								GetAttributeBool( WStringPtr name, _ubool& value, _ubool ignorecase = _false ) const override;
	virtual _ubool 								GetAttributeLong( WStringPtr name, _int& value, _ubool ignorecase = _false ) const override;
	virtual _ubool								GetAttributeDword( WStringPtr name, _dword& value, _ubool ignorecase = _false ) const override;
	virtual _ubool								GetAttributeLarge( WStringPtr name, _large& value, _ubool ignorecase = _false ) const override;
	virtual _ubool								GetAttributeQword( WStringPtr name, _qword& value, _ubool ignorecase = _false ) const override;
	virtual _ubool 								GetAttributeDouble( WStringPtr name, _double& value, _ubool ignorecase = _false ) const override;
	virtual _ubool								GetAttributeMD5Code( WStringPtr name, MD5Code& value, _ubool ignorecase = _false ) const override;
	virtual _ubool 								GetAttributeString( WStringPtr name, UString& string, _ubool ignorecase = _false ) const override;
	virtual _ubool 								GetAttributeString( WStringPtr name, WString& string, _ubool ignorecase = _false ) const override;
	virtual _ubool								GetAttributeColor( WStringPtr name, Color& color, _ubool ignorecase = _false ) const override;
	virtual _ubool								GetAttributeVersion( WStringPtr name, Version& version, _ubool ignorecase = _false ) const override;

	virtual _ubool 								SetAttributeBool( WStringPtr name, _ubool value ) override;
	virtual _ubool 								SetAttributeLong( WStringPtr name, _int value ) override;
	virtual _ubool 								SetAttributeDword( WStringPtr name, _dword value ) override;
	virtual _ubool 								SetAttributeLarge( WStringPtr name, _large value ) override;
	virtual _ubool 								SetAttributeQword( WStringPtr name, _qword value ) override;
	virtual _ubool 								SetAttributeDouble( WStringPtr name, _double value ) override;
	virtual _ubool								SetAttributeMD5Code( WStringPtr name, const MD5Code& value ) override;
	virtual _ubool								SetAttributeString( WStringPtr name, WStringPtr string ) override;
	virtual _ubool								SetAttributeColor( WStringPtr name, const Color& color ) override;
	virtual _ubool								SetAttributeVersion( WStringPtr name, const Version& version ) override;
};

//----------------------------------------------------------------------------
// TMarkupLangElement Implementation
//----------------------------------------------------------------------------

template< typename Type >
TMarkupLangElement< Type >::TMarkupLangElement( IMarkupLangElement* parent, IMarkupLangElement* prev, IMarkupLangElement* next )
	: mParentElement( parent ), mPrevElement( prev ), mNextElement( next )
{
	// Set the depth
	if ( mParentElement != _null )
		mDepth = mParentElement->GetDepth( ) + 1;
	else
		mDepth = 0;

	mFirstChildElement	= _null;
}

template< typename Type >
TMarkupLangElement< Type >::~TMarkupLangElement( )
{
	TSelfClass* parent	= static_cast< TSelfClass* >( mParentElement );
	TSelfClass* prev	= static_cast< TSelfClass* >( mPrevElement );
	TSelfClass* next	= static_cast< TSelfClass* >( mNextElement );

	// Unbind the parent link
	if ( parent != _null && parent->mFirstChildElement == this )
		parent->mFirstChildElement = next;

	// Unbind the brother link
	if ( prev != _null )
		prev->mNextElement = next;
	if ( next != _null )
		next->mPrevElement = prev;
}

template< typename Type >
_ubool TMarkupLangElement< Type >::IsArrayObject( ) const
{
	return _false;
}

template< typename Type >
_dword TMarkupLangElement< Type >::GetDepth( ) const
{
	return mDepth;
}

template< typename Type >
_dword TMarkupLangElement< Type >::GetChildElementNumber( ) const
{
	_dword number = 0;
	for ( IMarkupLangElement* childelement = GetFirstChildElement( ); childelement != _null; childelement = childelement->GetNextElement( ) )
		number ++;

	return number;
}

template< typename Type >
IMarkupLangElement* TMarkupLangElement< Type >::GetChildElementByIndex( _dword index ) const
{
	for ( IMarkupLangElement* childelement = GetFirstChildElement( ); childelement != _null; childelement = childelement->GetNextElement( ) )
	{
		if ( index -- == 0 )
			return childelement;
	}

	return _null;
}

template< typename Type >
IMarkupLangElement* TMarkupLangElement< Type >::GetChildElementByName( WStringPtr name, _ubool ignorecase ) const
{
	for ( IMarkupLangElement* childelement = GetFirstChildElement( ); childelement != _null; childelement = childelement->GetNextElement( ) )
	{
		// Get the child element name
		WString child_name = childelement->GetName( );

		// Compare the child element name
		if ( child_name.IsEqual( name.Str( ), ignorecase ) )
			return childelement;
	}

	// The child element is not existing
	return _null;
}

template< typename Type >
IMarkupLangElement* TMarkupLangElement< Type >::GetChildElementByText( WStringPtr text, _ubool ignorecase ) const
{
	for ( IMarkupLangElement* childelement = GetFirstChildElement( ); childelement != _null; childelement = childelement->GetNextElement( ) )
	{
		// Get the child element name
		WString child_text = childelement->GetTextW( );

		// Compare the child element text
		if ( child_text.IsEqual( text.Str( ), ignorecase ) )
			return childelement;
	}

	// The child element is not existing
	return _null;
}

template< typename Type >
_ubool TMarkupLangElement< Type >::HasChildElement( WStringPtr name, _ubool ignorecase ) const
{
	return GetChildElementByName( name, ignorecase ) != _null;
}

template< typename Type >
_ubool TMarkupLangElement< Type >::GetChildElementTextByName( WStringPtr name, UString& text, _ubool ignorecase ) const
{
	// Get the child element by name
	IMarkupLangElement* childelement = GetChildElementByName( name, ignorecase );
	if ( childelement == _null )
		return _false;

	// Get the child element's text
	return childelement->GetText( text );
}

template< typename Type >
_ubool TMarkupLangElement< Type >::GetChildElementTextByName( WStringPtr name, WString& text, _ubool ignorecase ) const
{
	// Get the child element by name
	IMarkupLangElement* childelement = GetChildElementByName( name, ignorecase );
	if ( childelement == _null )
		return _false;

	// Get the child element's text
	return childelement->GetText( text );
}

template< typename Type >
UStringR TMarkupLangElement< Type >::GetChildElementTextByNameU( WStringPtr name, _ubool ignorecase ) const
{
	// Get the child element by name
	IMarkupLangElement* childelement = GetChildElementByName( name, ignorecase );
	if ( childelement == _null )
		return UString( "" );

	// Get the child element's text
	return childelement->GetTextU( );
}

template< typename Type >
WStringR TMarkupLangElement< Type >::GetChildElementTextByNameW( WStringPtr name, _ubool ignorecase ) const
{
	// Get the child element by name
	IMarkupLangElement* childelement = GetChildElementByName( name, ignorecase );
	if ( childelement == _null )
		return WString( L"" );

	// Get the child element's text
	return childelement->GetTextW( );
}

template< typename Type >
IMarkupLangElement* TMarkupLangElement< Type >::GetFirstChildElement( ) const
{
	return mFirstChildElement;
}

template< typename Type >
IMarkupLangElement* TMarkupLangElement< Type >::GetLastChildElement( ) const
{
	// Get the first child element
	IMarkupLangElement* lastchildelement = GetFirstChildElement( );
	if ( lastchildelement == _null )
		return _null;

	// Find the last child element
	while ( lastchildelement->GetNextElement( ) != _null )
		lastchildelement = lastchildelement->GetNextElement( );

	return lastchildelement;
}

template< typename Type >
IMarkupLangElement* TMarkupLangElement< Type >::GetParentElement( ) const
{
	return mParentElement;
}

template< typename Type >
IMarkupLangElement* TMarkupLangElement< Type >::GetPrevElement( ) const
{
	return mPrevElement;
}

template< typename Type >
IMarkupLangElement* TMarkupLangElement< Type >::GetNextElement( ) const
{
	return mNextElement;
}

template< typename Type >
IMarkupLangElement* TMarkupLangElement< Type >::GetHeadElement( ) const
{
	if ( mParentElement != _null )
		return mParentElement->GetFirstChildElement( );
	else
		return (IMarkupLangElement*)this;
}

template< typename Type >
IMarkupLangElement* TMarkupLangElement< Type >::GetTailElement( ) const
{
	if ( mParentElement != _null )
		return mParentElement->GetLastChildElement( );
	else
		return (IMarkupLangElement*)this;
}

template< typename Type >
IMarkupLangElement* TMarkupLangElement< Type >::GetPrevElementByName( WStringPtr name, _ubool ignorecase ) const
{
	for ( IMarkupLangElement* xml_element = GetPrevElement( ); xml_element != _null; xml_element = xml_element->GetPrevElement( ) )
	{
		WString xml_element_name = xml_element->GetName( );

		if ( xml_element_name.IsEqual( name.Str( ), ignorecase ) )
			return xml_element;
	}

	return _null;
}

template< typename Type >
IMarkupLangElement* TMarkupLangElement< Type >::GetNextElementByName( WStringPtr name, _ubool ignorecase ) const
{
	for ( IMarkupLangElement* xml_element = GetNextElement( ); xml_element != _null; xml_element = xml_element->GetNextElement( ) )
	{
		WString xml_element_name = xml_element->GetName( );

		if ( xml_element_name.IsEqual( name.Str( ), ignorecase ) )
			return xml_element;
	}

	return _null;
}

template< typename Type >
IMarkupLangElement* TMarkupLangElement< Type >::InsertChildElementU( WStringPtr name, UStringPtr text, _ubool is_array_obj )
{
	EGE_ASSERT( 0 );
	return _null;
}

template< typename Type >
IMarkupLangElement* TMarkupLangElement< Type >::InsertChildElementW( WStringPtr name, WStringPtr text, _ubool is_array_obj )
{
	return InsertChildElementU( name, UString( ).FromString( text ), is_array_obj );
}

template< typename Type >
IMarkupLangElement*	TMarkupLangElement< Type >::InsertChildElement( const IMarkupLangElement* element, _ubool all_child )
{
	// Get the name and text of element
	WString element_name = element->GetName( );
	UString element_text = element->GetTextU( );

	// Insert child element
	IMarkupLangElement* child = InsertChildElementU( element_name, element_text, element->IsArrayObject( ) );
	if ( child == _null )
		return _null;

	// Clone all sub-elements
	for ( _dword i = 0; i < element->GetSubElementsNumber( ); i ++ )
		child->AppendElementOfArrayObj( element->GetSubElementByIndex( i ) );

	// Clone all attributes
	for ( _dword i = 0; i < element->GetAttributesNumber( ); i ++ )
	{
		IMarkupLangAttribute* attribute = element->GetAttributeByIndex( i );
		EGE_ASSERT( attribute != _null );

		WString attribute_name	= attribute->GetName( _true );
		WString attribute_value = attribute->GetStringW( );

		if ( child->SetAttributeString( attribute_name, attribute_value ) == _false )
			return _null;
	}

	// Insert recursively
	if ( all_child )
	{
		IMarkupLangElement* _child = element->GetFirstChildElement( );
		if ( _child != _null )
		{
			if ( child->InsertChildElement( _child, all_child ) == _null )
				return _null;

			// Insert all elements of child
			for ( IMarkupLangElement* _next = _child->GetNextElement( ); _next != _null; _next = _next->GetNextElement( ) )
			{
				if ( child->InsertChildElement( _next, all_child ) == _null )
					return _null;
			}
		}
	}

	return child;
}

template< typename Type >
IMarkupLangElement* TMarkupLangElement< Type >::InsertNextElementU( WStringPtr name, UStringPtr text, _ubool is_array_obj )
{
	EGE_ASSERT( 0 );
	return _null;
}

template< typename Type >
IMarkupLangElement* TMarkupLangElement< Type >::InsertNextElementW( WStringPtr name, WStringPtr text, _ubool is_array_obj )
{
	return InsertNextElementU( name, UString( ).FromString( text ), is_array_obj );
}

template< typename Type >
IMarkupLangElement* TMarkupLangElement< Type >::InsertNextElement( const IMarkupLangElement* element, _ubool all_child )
{
	// Get the name and text of element
	WString element_name = element->GetName( );
	UString element_text = element->GetTextU( );

	// Insert next element
	IMarkupLangElement* next = InsertNextElementU( element_name, element_text, element->IsArrayObject( ) );
	if ( next == _null )
		return _null;

	// Clone all sub-elements
	for ( _dword i = 0; i < element->GetSubElementsNumber( ); i ++ )
		next->AppendElementOfArrayObj( element->GetSubElementByIndex( i ) );

	// Clone all attributes
	for ( _dword i = 0; i < element->GetAttributesNumber( ); i ++ )
	{
		IMarkupLangAttribute* attribute = element->GetAttributeByIndex( i );
		EGE_ASSERT( attribute != _null );

		WString attribute_name	= attribute->GetName( _true );
		WString attribute_value = attribute->GetStringW( );

		if ( next->SetAttributeString( attribute_name, attribute_value ) == _false )
			return _null;
	}

	// Insert recursively
	if ( all_child )
	{
		IMarkupLangElement* _child = element->GetFirstChildElement( );
		if ( _child != _null )
		{
			if ( next->InsertChildElement( _child, all_child ) == _null )
				return _null;

			// Insert all elements of child
			for ( IMarkupLangElement* _next = _child->GetNextElement( ); _next != _null; _next = _next->GetNextElement( ) )
			{
				if ( next->InsertChildElement( _next, all_child ) == _null )
					return _null;
			}
		}
	}

	return next;
}

template< typename Type >
IMarkupLangElement* TMarkupLangElement< Type >::InsertChildArrayObj( WStringPtr name )
{
	return _null;
}

template< typename Type >
IMarkupLangElement*	TMarkupLangElement< Type >::AppendElementOfArrayObj( )
{
	return _null;
}

template< typename Type >
_dword TMarkupLangElement< Type >::AppendElementOfArrayObj( IMarkupLangElement* element )
{
	return -1;
}

template< typename Type >
_dword TMarkupLangElement< Type >::AppendValueUOfArrayObj( _dword value )
{
	return -1;
}

template< typename Type >
_dword TMarkupLangElement< Type >::AppendValueIOfArrayObj( _int value )
{
	return -1;
}

template< typename Type >
_dword TMarkupLangElement< Type >::AppendValueFOfArrayObj( _float value )
{
	return -1;
}

template< typename Type >
_dword TMarkupLangElement< Type >::AppendValueDOfArrayObj( _double value )
{
	return -1;
}

template< typename Type >
_dword TMarkupLangElement< Type >::GetSubElementsNumber( ) const
{
	return 0;
}

template< typename Type >
IMarkupLangElement* TMarkupLangElement< Type >::GetSubElementByIndex( _dword index ) const
{
	return _null;
}

template< typename Type >
_void TMarkupLangElement< Type >::Remove( )
{
	if ( this->mParentElement == _null )
		return;

	this->mParentElement->RemoveElement( this );
}

template< typename Type >
_void TMarkupLangElement< Type >::RemoveElement( IMarkupLangElement* element )
{
	EGE_ASSERT( 0 );
}

template< typename Type >
IMarkupLangElementIteratorPassRef TMarkupLangElement< Type >::RemoveElement( IMarkupLangElementIterator* it )
{
	EGE_ASSERT( 0 );
	return _null;
}

template< typename Type >
IMarkupLangElementIteratorPassRef TMarkupLangElement< Type >::CreateSelfElementIterator( )
{
	return OnCreateElementIterator( this );
}

template< typename Type >
IMarkupLangElementIteratorPassRef TMarkupLangElement< Type >::CreateChildElementIterator( WStringPtr name, _ubool recursive )
{
	for ( IMarkupLangElement* element = GetFirstChildElement( ); element != _null; element = element->GetNextElement( ) )
	{
		WString element_name = element->GetName( );

		if ( element_name == name )
			return OnCreateElementIterator( element );

		if ( recursive && element->GetFirstChildElement( ) != _null )
		{
			IMarkupLangElementIteratorPassRef walker = element->CreateChildElementIterator( name, recursive );
			if ( walker.IsValid( ) )
				return walker;
		}
	}

	return _null;
}

template< typename Type >
_dword TMarkupLangElement< Type >::GetAttributesNumber( ) const
{
	EGE_ASSERT( 0 );
	return 0;
}

template< typename Type >
IMarkupLangAttribute* TMarkupLangElement< Type >::GetAttributeByIndex( _dword index ) const
{
	EGE_ASSERT( 0 );
	return _null;
}

template< typename Type >
_ubool TMarkupLangElement< Type >::HasAttribute( WStringPtr name, _ubool ignorecase ) const
{
	EGE_ASSERT( 0 );
	return _false;
}

template< typename Type >
IMarkupLangAttribute* TMarkupLangElement< Type >::SearchAttribute( WStringPtr name, _ubool ignorecase ) const
{
	EGE_ASSERT( 0 );
	return _null;
}

template< typename Type >
_ubool TMarkupLangElement< Type >::GetAttributeBool( WStringPtr name, _ubool& value, _ubool ignorecase ) const
{
	IMarkupLangAttribute* attribute = SearchAttribute( name, ignorecase );
	if ( attribute == _null )
		return _false;

	value = attribute->GetBool( );
	return _true;
}

template< typename Type >
_ubool TMarkupLangElement< Type >::GetAttributeLong( WStringPtr name, _int& value, _ubool ignorecase ) const
{
	IMarkupLangAttribute* attribute = SearchAttribute( name, ignorecase );
	if ( attribute == _null )
		return _false;

	value = attribute->GetLong( );
	return _true;
}

template< typename Type >
_ubool TMarkupLangElement< Type >::GetAttributeDword( WStringPtr name, _dword& value, _ubool ignorecase ) const
{
	IMarkupLangAttribute* attribute = SearchAttribute( name, ignorecase );
	if ( attribute == _null )
		return _false;

	value = attribute->GetDword( );
	return _true;
}

template< typename Type >
_ubool TMarkupLangElement< Type >::GetAttributeLarge( WStringPtr name, _large& value, _ubool ignorecase ) const
{
	IMarkupLangAttribute* attribute = SearchAttribute( name, ignorecase );
	if ( attribute == _null )
		return _false;

	value = attribute->GetLarge( );
	return _true;
}

template< typename Type >
_ubool TMarkupLangElement< Type >::GetAttributeQword( WStringPtr name, _qword& value, _ubool ignorecase ) const
{
	IMarkupLangAttribute* attribute = SearchAttribute( name, ignorecase );
	if ( attribute == _null )
		return _false;

	value = attribute->GetQword( );
	return _true;
}

template< typename Type >
_ubool TMarkupLangElement< Type >::GetAttributeDouble( WStringPtr name, _double& value, _ubool ignorecase ) const
{
	IMarkupLangAttribute* attribute = SearchAttribute( name, ignorecase );
	if ( attribute == _null )
		return _false;

	value = attribute->GetDouble( );
	return _true;
}

template< typename Type >
_ubool TMarkupLangElement< Type >::GetAttributeMD5Code( WStringPtr name, MD5Code& value, _ubool ignorecase ) const
{
	IMarkupLangAttribute* attribute = SearchAttribute( name, ignorecase );
	if ( attribute == _null )
		return _false;

	value = attribute->GetMD5Code( );
	return _true;
}

template< typename Type >
_ubool TMarkupLangElement< Type >::GetAttributeString( WStringPtr name, UString& string, _ubool ignorecase ) const
{
	IMarkupLangAttribute* attribute = SearchAttribute( name, ignorecase );
	if ( attribute == _null )
		return _false;

	string = attribute->GetStringU( );
	return _true;
}

template< typename Type >
_ubool TMarkupLangElement< Type >::GetAttributeString( WStringPtr name, WString& string, _ubool ignorecase ) const
{
	IMarkupLangAttribute* attribute = SearchAttribute( name, ignorecase );
	if ( attribute == _null )
		return _false;

	string = attribute->GetStringW( );
	return _true;
}

template< typename Type >
_ubool TMarkupLangElement< Type >::GetAttributeColor( WStringPtr name, Color& color, _ubool ignorecase ) const
{
	IMarkupLangAttribute* attribute = SearchAttribute( name, ignorecase );
	if ( attribute == _null )
		return _false;

	color = attribute->GetColor( );
	return _true;
}

template< typename Type >
_ubool TMarkupLangElement< Type >::GetAttributeVersion( WStringPtr name, Version& version, _ubool ignorecase ) const
{
	IMarkupLangAttribute* attribute = SearchAttribute( name, ignorecase );
	if ( attribute == _null )
		return _false;

	version = attribute->GetVersion( );
	return _true;
}

template< typename Type >
_ubool TMarkupLangElement< Type >::SetAttributeBool( WStringPtr name, _ubool value )
{
	if ( value )
		return SetAttributeString( name, L"true" );
	else
		return SetAttributeString( name, L"false" );
}

template< typename Type >
_ubool TMarkupLangElement< Type >::SetAttributeLong( WStringPtr name, _int value )
{
	_charw string[1024];

	return SetAttributeString( name, Platform::ConvertLongToString( value, 10, string, 1024 ) );
}

template< typename Type >
_ubool TMarkupLangElement< Type >::SetAttributeDword( WStringPtr name, _dword value )
{
	_charw string[1024];

	return SetAttributeString( name, Platform::ConvertDwordToString( value, 10, string, 1024 ) );
}

template< typename Type >
_ubool TMarkupLangElement< Type >::SetAttributeLarge( WStringPtr name, _large value )
{
	_charw string[1024];

	return SetAttributeString( name, Platform::ConvertLargeToString( value, 10, string, 1024 ) );
}

template< typename Type >
_ubool TMarkupLangElement< Type >::SetAttributeQword( WStringPtr name, _qword value )
{
	_charw string[1024];

	return SetAttributeString( name, Platform::ConvertQwordToString( value, 10, string, 1024 ) );
}

template< typename Type >
_ubool TMarkupLangElement< Type >::SetAttributeDouble( WStringPtr name, _double value )
{
	_charw string[1024];

	return SetAttributeString( name, Platform::ConvertDoubleToString( value, string, 1024 ) );
}

template< typename Type >
_ubool TMarkupLangElement< Type >::SetAttributeMD5Code( WStringPtr name, const MD5Code& value )
{
	return SetAttributeString( name, value.ToWString( _true ) );
}

template< typename Type >
_ubool TMarkupLangElement< Type >::SetAttributeString( WStringPtr name, WStringPtr string )
{
    // The inherited class should be implementation this interface
    return _false;
}

template< typename Type >
_ubool TMarkupLangElement< Type >::SetAttributeColor( WStringPtr name, const Color& color )
{
	_charw colorstring[1024];
	Platform::FormatStringBuffer( colorstring, 1024, L"%.8x", (_dword) color );
	Platform::UppercaseString( colorstring );

	return SetAttributeString( name, colorstring );
}

template< typename Type >
_ubool TMarkupLangElement< Type >::SetAttributeVersion( WStringPtr name, const Version& version )
{
	return SetAttributeString( name, version.ToWString( ) );
}

}