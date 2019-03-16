//! @file     MarkupLangSerializableNode.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// MarkupLangSerializableNode
//----------------------------------------------------------------------------

class MarkupLangSerializableNode : public INTERFACE_SERIALIZABLE_NODE_IMPL( ISerializableNode )
{
private:
	//!	The initial markup element
	IMarkupLangElement*	mInitialElement;
	//!	The current markup element
	IMarkupLangElement*	mCurElement;
	//!	The markup file
	IMarkupLangFileRef	mMarkupFile;

// TSerializableNode Interface
private:
	virtual _ubool 	OnGetPropertyValue( WStringPtr name, AString& content ) override;
	virtual _ubool 	OnGetPropertyValue( WStringPtr name, UString& content ) override;
	virtual _ubool 	OnGetPropertyValue( WStringPtr name, WString& content ) override;
	virtual _ubool	OnGetPropertyValue( WStringPtr name, _ubool& value ) override;
	virtual _ubool	OnGetPropertyValue( WStringPtr name, _int& value ) override;
	virtual _ubool	OnGetPropertyValue( WStringPtr name, _dword& value ) override;
	virtual _ubool	OnGetPropertyValue( WStringPtr name, _large& value ) override;
	virtual _ubool	OnGetPropertyValue( WStringPtr name, _qword& value ) override;
	virtual _ubool	OnGetPropertyValue( WStringPtr name, _double& value ) override;

	virtual _ubool 	OnSetPropertyValue( WStringPtr name, AStringPtr content ) override;
	virtual _ubool 	OnSetPropertyValue( WStringPtr name, UStringPtr content ) override;
	virtual _ubool 	OnSetPropertyValue( WStringPtr name, WStringPtr content ) override;
	virtual _ubool	OnSetPropertyValue( WStringPtr name, _ubool value ) override;
	virtual _ubool	OnSetPropertyValue( WStringPtr name, _int value ) override;
	virtual _ubool	OnSetPropertyValue( WStringPtr name, _dword value ) override;
	virtual _ubool	OnSetPropertyValue( WStringPtr name, _large value ) override;
	virtual _ubool	OnSetPropertyValue( WStringPtr name, _qword value ) override;
	virtual _ubool	OnSetPropertyValue( WStringPtr name, _double value ) override;

public:
	MarkupLangSerializableNode( IMarkupLangElement* node, IMarkupLangFile* file );
	virtual ~MarkupLangSerializableNode( );

// IObject Interface
public:
	virtual IObject*						CloneTo( _ubool standalone ) const override;

// ISerializableNode Interface
public:
	virtual _ubool							IsArrayObject( ) const override;

	virtual IMarkupLangElement*				GetMarkupLangElement( ) override;
	virtual const IMarkupLangElement*		GetMarkupLangElement( ) const override;

	virtual IMarkupLangFile*				GetMarkupLangFile( ) override;
	virtual const IMarkupLangFile*			GetMarkupLangFile( ) const override;

	virtual WStringR						GetNodeName( ) const override;
	virtual _ubool							SetNodeName( WStringPtr name ) override;

	virtual _ubool							HasObject( ) const override;
	virtual _ubool							HasProperty( WStringPtr name ) const override;

	virtual _dword							GetChildNodesNumber( ) const override;
	virtual _dword							GetChildNodesNumber( WStringPtr name ) const override;

	virtual _dword							AppendElementOfArrayObj( ISerializableNode* node ) override;
	virtual _dword							AppendValueUOfArrayObj( _dword value ) override;
	virtual _dword							AppendValueIOfArrayObj( _int value ) override;
	virtual _dword							AppendValueFOfArrayObj( _float value ) override;
	virtual _dword							AppendValueDOfArrayObj( _double value ) override;
	virtual _dword							GetSubElementsNumber( ) const override;
	virtual ISerializableNodePassRef		GetSubElementByIndex( _dword index ) override;

	virtual ISerializableNodePassRef		GetParentNode( ) override;
	virtual ISerializableNodePassRef		GetFirstChildNode( ) override;
	virtual ISerializableNodePassRef		GetLastChildNode( ) override;
	virtual ISerializableNodePassRef		GetPrevNode( ) override;
	virtual ISerializableNodePassRef		GetPrevNode( WStringPtr name, _ubool ignorecase = _false ) override;
	virtual ISerializableNodePassRef		GetNextNode( ) override;
	virtual ISerializableNodePassRef		GetNextNode( WStringPtr name, _ubool ignorecase = _false ) override;
	virtual ISerializableNodePassRef		GetHeadNode( ) override;
	virtual ISerializableNodePassRef		GetTailNode( ) override;

	virtual WStringR						GetChildTextByNameW( WStringPtr name ) override;
	virtual WStringR						GetChildValueByNameW( WStringPtr name, WStringPtr attribute_name ) override;
	virtual ISerializableNodePassRef		GetChildNodeByName( WStringPtr name ) override;
	virtual ISerializableNodePassRef		GetChildNodeByIndex( _dword index ) override;

	virtual ISerializableNodePassRef		InsertChildNode( WStringPtr name ) override;
	virtual ISerializableNodePassRef		InsertChildNode( WStringPtr name, WStringPtr text, _ubool is_array_obj ) override;
	virtual ISerializableNodePassRef		InsertBrotherNode( WStringPtr name ) override;
	virtual ISerializableNodePassRef		InsertBrotherNode( WStringPtr name, WStringPtr text, _ubool is_array_obj ) override;

	virtual ISerializableNodePassRef		InsertChildNode( ISerializableNode* node, _ubool recursive ) override;
	virtual ISerializableNodePassRef		InsertBrotherNode( ISerializableNode* node, _ubool recursive ) override;

	virtual ISerializableNodeWalkerPassRef	CreateWalker( ) override;

	virtual _dword							GetValueU( ) const override;
	virtual _int							GetValueI( ) const override;
	virtual _float							GetValueF( ) const override;
	virtual _double							GetValueD( ) const override;

	virtual AStringR						GetTextA( ) const override;
	virtual UStringR						GetTextU( ) const override;
	virtual WStringR						GetTextW( ) const override;
	virtual _void							SetText( AStringPtr text ) override;
	virtual _void							SetText( UStringPtr text ) override;
	virtual _void							SetText( WStringPtr text ) override;

	virtual _ubool							HasPrev( ) const override;
	virtual _ubool							HasPrev( WStringPtr name ) const override;
	virtual _ubool							MovePrev( ) override;
	virtual _ubool							MovePrev( WStringPtr name ) override;

	virtual _ubool							HasNext( ) const override;
	virtual _ubool							HasNext( WStringPtr name ) const override;
	virtual _ubool							MoveNext( ) override;
	virtual _ubool							MoveNext( WStringPtr name ) override;

	virtual WStringR						DumpToString( ) const override;
	virtual WStringR						DumpToSchemaString( ) const override;
};

}