//! @file     MarkupLangSerializableNode.cpp
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// MarkupLangSerializableNode Implementation
//----------------------------------------------------------------------------

MarkupLangSerializableNode::MarkupLangSerializableNode( IMarkupLangElement* node, IMarkupLangFile* file ) 
{
	EGE_ASSERT( node != _null );
	EGE_ASSERT( file != _null );

	mInitialElement	= node;
	mCurElement		= node;
	mMarkupFile		= file;
}

MarkupLangSerializableNode::~MarkupLangSerializableNode( )
{

}

_ubool MarkupLangSerializableNode::OnGetPropertyValue( WStringPtr name, AString& content )
{
	UString content_utf8;
	if ( OnGetPropertyValue( name, content_utf8 ) == _false )
		return _false;

	content.FromString( content_utf8 );

	return _true;
}

_ubool MarkupLangSerializableNode::OnGetPropertyValue( WStringPtr name, UString& content )
{
	// First we try to get the attribute
	if ( mCurElement->GetAttributeString( name, content, _false ) )
		return _true;

	return _false;
}

_ubool MarkupLangSerializableNode::OnGetPropertyValue( WStringPtr name, WString& content )
{
	// First we try to get the attribute
	if ( mCurElement->GetAttributeString( name, content, _false ) )
		return _true;

	return _false;
}

_ubool MarkupLangSerializableNode::OnGetPropertyValue( WStringPtr name, _ubool& value )
{
	return mCurElement->GetAttributeBool( name, value, _false );
}

_ubool MarkupLangSerializableNode::OnGetPropertyValue( WStringPtr name, _int& value )
{
	return mCurElement->GetAttributeLong( name, value, _false );
}

_ubool MarkupLangSerializableNode::OnGetPropertyValue( WStringPtr name, _dword& value )
{
	return mCurElement->GetAttributeDword( name, value, _false );
}

_ubool MarkupLangSerializableNode::OnGetPropertyValue( WStringPtr name, _large& value )
{
	return mCurElement->GetAttributeLarge( name, value, _false );
}

_ubool MarkupLangSerializableNode::OnGetPropertyValue( WStringPtr name, _qword& value )
{
	return mCurElement->GetAttributeQword( name, value, _false );
}

_ubool MarkupLangSerializableNode::OnGetPropertyValue( WStringPtr name, _double& value )
{
	return mCurElement->GetAttributeDouble( name, value, _false );
}

_ubool MarkupLangSerializableNode::OnSetPropertyValue( WStringPtr name, AStringPtr content )
{
	// Set as attribute
	return mCurElement->SetAttributeString( name, UString( ).FromString( content ) );
}

_ubool MarkupLangSerializableNode::OnSetPropertyValue( WStringPtr name, UStringPtr content )
{
	// Set as attribute
	return mCurElement->SetAttributeString( name, content );
}

_ubool MarkupLangSerializableNode::OnSetPropertyValue( WStringPtr name, WStringPtr content )
{
	// Set as attribute
	return mCurElement->SetAttributeString( name, content );
}

_ubool MarkupLangSerializableNode::OnSetPropertyValue( WStringPtr name, _ubool value )
{
	return mCurElement->SetAttributeBool( name, value );
}

_ubool MarkupLangSerializableNode::OnSetPropertyValue( WStringPtr name, _int value )
{
	return mCurElement->SetAttributeLong( name, value );
}

_ubool MarkupLangSerializableNode::OnSetPropertyValue( WStringPtr name, _dword value )
{
	return mCurElement->SetAttributeDword( name, value );
}

_ubool MarkupLangSerializableNode::OnSetPropertyValue( WStringPtr name, _large value )
{
	return mCurElement->SetAttributeLarge( name, value );
}

_ubool MarkupLangSerializableNode::OnSetPropertyValue( WStringPtr name, _qword value )
{
	return mCurElement->SetAttributeQword( name, value );
}

_ubool MarkupLangSerializableNode::OnSetPropertyValue( WStringPtr name, _double value )
{
	return mCurElement->SetAttributeDouble( name, value );
}

IObject* MarkupLangSerializableNode::CloneTo( _ubool standalone ) const
{
	return new MarkupLangSerializableNode( mInitialElement, mMarkupFile );
}

_ubool MarkupLangSerializableNode::IsArrayObject( ) const
{
	return mCurElement->IsArrayObject( );
}

IMarkupLangElement* MarkupLangSerializableNode::GetMarkupLangElement( )
{
	return mCurElement;
}

const IMarkupLangElement* MarkupLangSerializableNode::GetMarkupLangElement( ) const
{
	return mCurElement;
}

IMarkupLangFile* MarkupLangSerializableNode::GetMarkupLangFile( )
{
	return mMarkupFile;
}

const IMarkupLangFile* MarkupLangSerializableNode::GetMarkupLangFile( ) const
{
	return mMarkupFile;
}

WStringR MarkupLangSerializableNode::GetNodeName( ) const
{
	return mCurElement->GetName( );
}

_ubool MarkupLangSerializableNode::SetNodeName( WStringPtr name )
{
	return mCurElement->SetName( name );
}

_ubool MarkupLangSerializableNode::HasObject( ) const
{
	return mCurElement != _null;
}

_ubool MarkupLangSerializableNode::HasProperty( WStringPtr name ) const
{
	return mCurElement->HasAttribute( name, _false );
}

_dword MarkupLangSerializableNode::GetChildNodesNumber( ) const
{
	return mCurElement->GetChildElementNumber( );
}

_dword MarkupLangSerializableNode::GetChildNodesNumber( WStringPtr name ) const
{
	_dword number = 0;

	IMarkupLangElement* element = mCurElement->GetChildElementByName( name, _false );
	for ( ; element != _null; element = element->GetNextElementByName( name, _false ) )
		number ++;

	return number;
}

_dword MarkupLangSerializableNode::AppendElementOfArrayObj( ISerializableNode* node )
{
	if ( node == _null )
		return -1;

	return mCurElement->AppendElementOfArrayObj( node->GetMarkupLangElement( ) );
}

_dword MarkupLangSerializableNode::AppendValueUOfArrayObj( _dword value )
{
	return mCurElement->AppendValueUOfArrayObj( value );
}

_dword MarkupLangSerializableNode::AppendValueIOfArrayObj( _int value )
{
	return mCurElement->AppendValueIOfArrayObj( value );
}

_dword MarkupLangSerializableNode::AppendValueFOfArrayObj( _float value )
{
	return mCurElement->AppendValueFOfArrayObj( value );
}

_dword MarkupLangSerializableNode::AppendValueDOfArrayObj( _double value )
{
	return mCurElement->AppendValueDOfArrayObj( value );
}

_dword MarkupLangSerializableNode::GetSubElementsNumber( ) const
{
	return mCurElement->GetSubElementsNumber( );
}

ISerializableNodePassRef MarkupLangSerializableNode::GetSubElementByIndex( _dword index )
{
	IMarkupLangElement* element = mCurElement->GetSubElementByIndex( index );
	if ( element == _null )
		return _null;

	return new MarkupLangSerializableNode( element, mMarkupFile );
}

ISerializableNodePassRef MarkupLangSerializableNode::GetParentNode( )
{
	IMarkupLangElement* element = mCurElement->GetParentElement( );
	if ( element == _null )
		return _null;

	return new MarkupLangSerializableNode( element, mMarkupFile );
}

ISerializableNodePassRef MarkupLangSerializableNode::GetFirstChildNode( )
{
	IMarkupLangElement* element = mCurElement->GetFirstChildElement( );
	if ( element == _null )
		return _null;

	return new MarkupLangSerializableNode( element, mMarkupFile );
}

ISerializableNodePassRef MarkupLangSerializableNode::GetLastChildNode( )
{
	IMarkupLangElement* element = mCurElement->GetLastChildElement( );
	if ( element == _null )
		return _null;

	return new MarkupLangSerializableNode( element, mMarkupFile );
}

ISerializableNodePassRef MarkupLangSerializableNode::GetPrevNode( )
{
	IMarkupLangElement* element = mCurElement->GetPrevElement( );
	if ( element == _null )
		return _null;

	return new MarkupLangSerializableNode( element, mMarkupFile );
}

ISerializableNodePassRef MarkupLangSerializableNode::GetPrevNode( WStringPtr name, _ubool ignorecase )
{
	IMarkupLangElement* element = mCurElement->GetPrevElementByName( name, ignorecase );
	if ( element == _null )
		return _null;

	return new MarkupLangSerializableNode( element, mMarkupFile );
}

ISerializableNodePassRef MarkupLangSerializableNode::GetNextNode( )
{
	IMarkupLangElement* element = mCurElement->GetNextElement( );
	if ( element == _null )
		return _null;

	return new MarkupLangSerializableNode( element, mMarkupFile );
}

ISerializableNodePassRef MarkupLangSerializableNode::GetNextNode( WStringPtr name, _ubool ignorecase )
{
	IMarkupLangElement* element = mCurElement->GetNextElementByName( name, ignorecase );
	if ( element == _null )
		return _null;

	return new MarkupLangSerializableNode( element, mMarkupFile );
}

ISerializableNodePassRef MarkupLangSerializableNode::GetHeadNode( )
{
	IMarkupLangElement* element = mCurElement->GetHeadElement( );
	if ( element == _null )
		return _null;

	return new MarkupLangSerializableNode( element, mMarkupFile );
}

ISerializableNodePassRef MarkupLangSerializableNode::GetTailNode( )
{
	IMarkupLangElement* element = mCurElement->GetTailElement( );
	if ( element == _null )
		return _null;

	return new MarkupLangSerializableNode( element, mMarkupFile );
}

WStringR MarkupLangSerializableNode::GetChildTextByNameW( WStringPtr name )
{
	ISerializableNodeRef node = GetChildNodeByName( name );
	if ( node.IsNull( ) )
		return WString( L"" );

	return node->GetTextW( );
}

WStringR MarkupLangSerializableNode::GetChildValueByNameW( WStringPtr name, WStringPtr attribute_name )
{
	ISerializableNodeRef node = GetChildNodeByName( name );
	if ( node.IsNull( ) )
		return WString( L"" );

	WString value;
	if ( node->Read( attribute_name, value ) == _false )
		return WString( L"" );

	return value;
}

ISerializableNodePassRef MarkupLangSerializableNode::GetChildNodeByName( WStringPtr name )
{
	EGE_ASSERT( mCurElement != _null );

	IMarkupLangElement* element = mCurElement->GetChildElementByName( name, _false );
	if ( element == _null )
		return _null;

	return new MarkupLangSerializableNode( element, mMarkupFile );
}

ISerializableNodePassRef MarkupLangSerializableNode::GetChildNodeByIndex( _dword index )
{
	IMarkupLangElement* element = mCurElement->GetChildElementByIndex( index );
	if ( element == _null )
		return _null;

	return new MarkupLangSerializableNode( element, mMarkupFile );
}

ISerializableNodePassRef MarkupLangSerializableNode::InsertChildNode( WStringPtr name )
{
	return InsertChildNode( name, L"", _false );
}

ISerializableNodePassRef MarkupLangSerializableNode::InsertChildNode( WStringPtr name, WStringPtr text, _ubool is_array_obj )
{
	IMarkupLangElement* element = mCurElement->InsertChildElementW( name, text, is_array_obj );
	if ( element == _null )
		return _null;

	return new MarkupLangSerializableNode( element, mMarkupFile );
}

ISerializableNodePassRef MarkupLangSerializableNode::InsertBrotherNode( WStringPtr name )
{
	return InsertBrotherNode( name, L"", _false );
}

ISerializableNodePassRef MarkupLangSerializableNode::InsertBrotherNode( WStringPtr name, WStringPtr text, _ubool is_array_obj )
{
	IMarkupLangElement* element = mCurElement->InsertNextElementW( name, text, is_array_obj );
	if ( element == _null )
		return _null;

	return new MarkupLangSerializableNode( element, mMarkupFile );
}

ISerializableNodePassRef MarkupLangSerializableNode::InsertChildNode( ISerializableNode* node, _ubool recursive )
{
	if ( node == _null )
		return _null;

	IMarkupLangElement* element = mCurElement->InsertChildElement( node->GetMarkupLangElement( ), recursive );
	if ( element == _null )
		return _null;

	return new MarkupLangSerializableNode( element, mMarkupFile );
}

ISerializableNodePassRef MarkupLangSerializableNode::InsertBrotherNode( ISerializableNode* node, _ubool recursive )
{
	if ( node == _null )
		return _null;

	IMarkupLangElement* element = mCurElement->InsertNextElement( node->GetMarkupLangElement( ), recursive );
	if ( element == _null )
		return _null;

	return new MarkupLangSerializableNode( element, mMarkupFile );
}

ISerializableNodeWalkerPassRef MarkupLangSerializableNode::CreateWalker( )
{
	return new MarkupLangSerializableNodeWalker( this );
}

_dword MarkupLangSerializableNode::GetValueU( ) const
{
	return mCurElement->GetValueU( );
}

_int MarkupLangSerializableNode::GetValueI( ) const
{
	return mCurElement->GetValueI( );
}

_float MarkupLangSerializableNode::GetValueF( ) const
{
	return mCurElement->GetValueF( );
}

_double MarkupLangSerializableNode::GetValueD( ) const
{
	return mCurElement->GetValueD( );
}

AStringR MarkupLangSerializableNode::GetTextA( ) const
{
	return mCurElement->GetTextA( );
}

UStringR MarkupLangSerializableNode::GetTextU( ) const
{
	return mCurElement->GetTextU( );
}

WStringR MarkupLangSerializableNode::GetTextW( ) const
{
	return mCurElement->GetTextW( );
}

_void MarkupLangSerializableNode::SetText( AStringPtr text )
{
	mCurElement->SetText( text );
}

_void MarkupLangSerializableNode::SetText( UStringPtr text )
{
	mCurElement->SetText( text );
}

_void MarkupLangSerializableNode::SetText( WStringPtr text )
{
	mCurElement->SetText( text );
}

_ubool MarkupLangSerializableNode::HasPrev( ) const
{
	return mCurElement->GetPrevElement( ) != _null;
}

_ubool MarkupLangSerializableNode::HasPrev( WStringPtr name ) const
{
	return mCurElement->GetPrevElementByName( name, _false ) != _null;
}

_ubool MarkupLangSerializableNode::MovePrev( )
{
	mCurElement = mCurElement->GetPrevElement( );
	if ( mCurElement == _null )
		return _false;

	return _true;
}

_ubool MarkupLangSerializableNode::MovePrev( WStringPtr name )
{
	mCurElement = mCurElement->GetPrevElementByName( name, _false );
	if ( mCurElement == _null )
		return _false;

	return _true;
}

_ubool MarkupLangSerializableNode::HasNext( ) const
{
	return mCurElement->GetNextElement( ) != _null;
}

_ubool MarkupLangSerializableNode::HasNext( WStringPtr name ) const
{
	return mCurElement->GetNextElementByName( name, _false ) != _null;
}

_ubool MarkupLangSerializableNode::MoveNext( )
{
	mCurElement = mCurElement->GetNextElement( );
	if ( mCurElement == _null )
		return _false;

	return _true;
}

_ubool MarkupLangSerializableNode::MoveNext( WStringPtr name )
{
	mCurElement = mCurElement->GetNextElementByName( name, _false );
	if ( mCurElement == _null )
		return _false;

	return _true;
}

WStringR MarkupLangSerializableNode::DumpToString( ) const
{
	return mCurElement->DumpToString( );
}

WStringR MarkupLangSerializableNode::DumpToSchemaString( ) const
{
	return mCurElement->DumpToSchemaString( );
}
