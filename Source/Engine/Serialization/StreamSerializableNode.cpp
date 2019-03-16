//! @file     StreamSerializableNode.cpp
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright 2009-2011 LiCode's Union.

#include "EGEEngine.h"

//----------------------------------------------------------------------------
// StreamSerializableNode Implementation
//----------------------------------------------------------------------------

StreamSerializableNode::StreamSerializableNode( IStreamReader* stream_reader, IStreamWriter* stream_writer )
{
	mStreamReader	= stream_reader;
	mStreamWriter	= stream_writer;
}

StreamSerializableNode::~StreamSerializableNode( )
{

}

WString StreamSerializableNode::GetNodeName( ) const
{
	return WString( L"" );
}

_ubool StreamSerializableNode::HasProperty( WStringPtr name ) const
{
	return _true;
}

ISerializableNodePassRef StreamSerializableNode::GetFirstChildNode( )
{
	return _null;
}

ISerializableNodePassRef StreamSerializableNode::GetChildNode( WStringPtr name )
{
	return _null;
}

ISerializableNodePassRef StreamSerializableNode::InsertChildNode( WStringPtr name )
{
	return _null;
}

ISerializableNodePassRef StreamSerializableNode::InsertBrotherNode( WStringPtr name )
{
	return _null;
}

_ubool StreamSerializableNode::IsValid( ) const
{
	return mStreamReader.IsValid( );
}

_ubool StreamSerializableNode::MoveNext( )
{
	return _true;
}

_ubool StreamSerializableNode::MoveNext( WStringPtr name )
{
	return _true;
}

_ubool StreamSerializableNode::Read( WStringPtr name, _byte& value )
{
	if ( mStreamReader.IsNull( ) )
		return _false;

	return mStreamReader->ReadByte( value );
}

_ubool StreamSerializableNode::Read( WStringPtr name, _word& value )
{
	if ( mStreamReader.IsNull( ) )
		return _false;

	return mStreamReader->ReadWord( value );
}

_ubool StreamSerializableNode::Read( WStringPtr name, _long& value )
{
	if ( mStreamReader.IsNull( ) )
		return _false;

	return mStreamReader->ReadDword( value );
}

_ubool StreamSerializableNode::Read( WStringPtr name, _dword& value )
{
	if ( mStreamReader.IsNull( ) )
		return _false;

	return mStreamReader->ReadDword( value );
}

_ubool StreamSerializableNode::Read( WStringPtr name, _float& value )
{
	if ( mStreamReader.IsNull( ) )
		return _false;

	return mStreamReader->ReadFloat( value );
}

_ubool StreamSerializableNode::Read( WStringPtr name, _double& value )
{
	if ( mStreamReader.IsNull( ) )
		return _false;

	return mStreamReader->ReadDouble( value );
}

_ubool StreamSerializableNode::Read( WStringPtr name, WString& value )
{
	if ( mStreamReader.IsNull( ) )
		return _false;

	return mStreamReader->ReadString( value );
}

_ubool StreamSerializableNode::Read( WStringPtr name, Time& value )
{
	return mStreamReader->ReadBuffer( &value, sizeof( Time ) );
}

_ubool StreamSerializableNode::Read( WStringPtr name, MD5Code& value )
{
	if ( mStreamReader.IsNull( ) )
		return _false;

	return mStreamReader->ReadBuffer( &value, sizeof( MD5Code ) );
}

_ubool StreamSerializableNode::Read( WStringPtr name, Version& value )
{
	if ( mStreamReader.IsNull( ) )
		return _false;

	return mStreamReader->ReadBuffer( &value, sizeof( Version ) );
}

_ubool StreamSerializableNode::Read( WString& text )
{
	if ( mStreamReader.IsNull( ) )
		return _false;

	return mStreamReader->ReadString( text );
}

_ubool StreamSerializableNode::Write( WStringPtr name, _long value )
{
	if ( mStreamWriter.IsNull( ) )
		return _false;

	return mStreamWriter->WriteDword( value );
}

_ubool StreamSerializableNode::Write( WStringPtr name, _dword value )
{
	if ( mStreamWriter.IsNull( ) )
		return _false;

	return mStreamWriter->WriteDword( value );
}

_ubool StreamSerializableNode::Write( WStringPtr name, _float value )
{
	if ( mStreamWriter.IsNull( ) )
		return _false;

	return mStreamWriter->WriteFloat( value );
}

_ubool StreamSerializableNode::Write( WStringPtr name, _double value )
{
	if ( mStreamWriter.IsNull( ) )
		return _false;

	return mStreamWriter->WriteDouble( value );
}

_ubool StreamSerializableNode::Write( WStringPtr name, WStringPtr value )
{
	if ( mStreamWriter.IsNull( ) )
		return _false;

	return mStreamWriter->WriteString( value );
}

_ubool StreamSerializableNode::Write( WStringPtr name, const Time& value )
{
	if ( mStreamWriter.IsNull( ) )
		return _false;

	return mStreamWriter->WriteBuffer( &value, sizeof( Time ) );
}

_ubool StreamSerializableNode::Write( WStringPtr name, const MD5Code& value )
{
	if ( mStreamWriter.IsNull( ) )
		return _false;

	return mStreamWriter->WriteBuffer( &value, sizeof( MD5Code ) );
}

_ubool StreamSerializableNode::Write( WStringPtr name, const Version& value )
{
	if ( mStreamWriter.IsNull( ) )
		return _false;

	return mStreamWriter->WriteBuffer( &value, sizeof( Version ) );
}