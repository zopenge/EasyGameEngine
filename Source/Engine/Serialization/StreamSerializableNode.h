//! @file     StreamSerializableNode.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// StreamSerializableNode
//----------------------------------------------------------------------------

class StreamSerializableNode : public INTERFACE_OBJECT_IMPL( ISerializableNode )
{
private:
	IStreamReaderRef	mStreamReader;
	IStreamWriterRef	mStreamWriter;

public:
	StreamSerializableNode( IStreamReader* stream_reader, IStreamWriter* stream_writer );
	virtual ~StreamSerializableNode( );

// ISerializableNode Interface
public:
	virtual WString						GetNodeName( ) const override;

	virtual _ubool						HasProperty( WStringPtr name ) const override;

	virtual ISerializableNodePassRef	GetFirstChildNode( ) override;
	virtual ISerializableNodePassRef	GetChildNode( WStringPtr name ) override;
	virtual ISerializableNodePassRef	InsertChildNode( WStringPtr name ) override;
	virtual ISerializableNodePassRef	InsertBrotherNode( WStringPtr name ) override;

	virtual _ubool						IsValid( ) const override;

	virtual _ubool						MoveNext( ) override;
	virtual _ubool						MoveNext( WStringPtr name ) override;

	virtual _ubool						Read( WStringPtr name, _byte& value ) override;
	virtual _ubool						Read( WStringPtr name, _word& value ) override;
	virtual _ubool						Read( WStringPtr name, _long& value ) override;
	virtual _ubool						Read( WStringPtr name, _dword& value ) override;
	virtual _ubool						Read( WStringPtr name, _float& value ) override;
	virtual _ubool						Read( WStringPtr name, _double& value ) override;
	virtual _ubool						Read( WStringPtr name, WString& value ) override;
	virtual _ubool						Read( WStringPtr name, Time& value ) override;
	virtual _ubool						Read( WStringPtr name, MD5Code& value ) override;
	virtual _ubool						Read( WStringPtr name, Version& value ) override;
	virtual _ubool						Read( WString& text ) override;

	virtual _ubool						Write( WStringPtr name, _long value ) override;
	virtual _ubool						Write( WStringPtr name, _dword value ) override;
	virtual _ubool						Write( WStringPtr name, _float value ) override;
	virtual _ubool						Write( WStringPtr name, _double value ) override;
	virtual _ubool						Write( WStringPtr name, WStringPtr value ) override;
	virtual _ubool						Write( WStringPtr name, const Time& value ) override;
	virtual _ubool						Write( WStringPtr name, const MD5Code& value ) override;
	virtual _ubool						Write( WStringPtr name, const Version& value ) override;
};

}