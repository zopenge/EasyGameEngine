//! @file     TSerializable.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TSerializable
//----------------------------------------------------------------------------

template< typename Type >
class TSerializable : public Type
{
protected:
	TSerializable( );
	virtual ~TSerializable( );

// ISerializable Interface
public:
	virtual _ubool ImportFromFile( WStringPtr filename ) override;
	virtual _ubool ImportFromXMLString( WStringPtr xml_string ) override;
	virtual _ubool ExportToFile( WStringPtr filename, WStringPtr root_name, WStringPtr tag_name ) override;
	virtual _ubool ExportToXMLString( WStringPtr root_name, WStringPtr tag_name, WString& xml_string ) override;

	virtual _ubool ImportFromStream( IStreamReader* stream_reader ) override;
	virtual _ubool ExportToStream( IStreamWriter* stream_writer ) const override;
};

//----------------------------------------------------------------------------
// TSerializable Implementation
//----------------------------------------------------------------------------

template< typename Type >
TSerializable< Type >::TSerializable( )
{

}

template< typename Type >
TSerializable< Type >::~TSerializable( )
{

}

template< typename Type >
_ubool TSerializable< Type >::ImportFromFile( WStringPtr filename )
{
	IFileStreamReaderRef stream_reader = GetInterfaceFactory( )->CreateFileStreamReader( filename );
	if ( stream_reader.IsNull( ) )
		return _false;

	ISerializableNodeRef res_node = GetInterfaceFactory( )->CreateMarkupLangSerializableNode( stream_reader );
	if ( res_node.IsNull( ) )
		return _false;

	if ( this->Import( res_node ) == _false )
		return _false;

	return _true;
}

template< typename Type >
_ubool TSerializable< Type >::ImportFromXMLString( WStringPtr xml_string )
{
	UString string_utf8; string_utf8.FromString( xml_string );

	IStreamReaderRef stream_reader = GetInterfaceFactory( )->CreateMemStreamReader( (const _byte*) string_utf8.Str( ), string_utf8.GetLength( ), _STREAM_SHARE_MODE_READ_ONLY );
	if ( stream_reader.IsNull( ) )
		return _false;

	ISerializableNodeRef res_node = GetInterfaceFactory( )->CreateMarkupLangSerializableNode( stream_reader );
	if ( res_node.IsNull( ) )
		return _false;

	if ( this->Import( res_node ) == _false )
		return _false;

	return _true;
}

template< typename Type >
_ubool TSerializable< Type >::ExportToFile( WStringPtr filename, WStringPtr root_name, WStringPtr tag_name )
{
	IMarkupLangFileRef xml_file = GetInterfaceFactory()->CreateXMLFile( root_name );
	if ( xml_file.IsNull( ) )
		return _false;

	ISerializableNodeRef node = GetInterfaceFactory( )->CreateMarkupLangSerializableNode( xml_file );
	if ( node.IsNull( ) )
		return _false;

	if ( tag_name.IsEmpty( ) == _false )
	{
		node = node->InsertChildNode( tag_name, L"", _false );
		if ( node.IsNull( ) )
			return _false;
	}

	if ( this->Export( node ) == _false )
		return _false;

	if ( xml_file->SaveToFile( filename ) == _false )
		return _false;

	return _true;
}

template< typename Type >
_ubool TSerializable< Type >::ExportToXMLString( WStringPtr root_name, WStringPtr tag_name, WString& xml_string )
{
	IMarkupLangFileRef xml_file = GetInterfaceFactory()->CreateXMLFile( root_name );
	if ( xml_file.IsNull( ) )
		return _false;

	ISerializableNodeRef node = GetInterfaceFactory( )->CreateMarkupLangSerializableNode( xml_file );
	if ( node.IsNull( ) )
		return _false;

	if ( tag_name.IsEmpty( ) == _false )
	{
		node = node->InsertChildNode( tag_name, L"", _false );
		if ( node.IsNull( ) )
			return _false;
	}

	if ( this->Export( node ) == _false )
		return _false;

	xml_string = xml_file->GetRootElement( )->DumpToString( );

	return _true;
}

template< typename Type >
_ubool TSerializable< Type >::ImportFromStream( IStreamReader* stream_reader )
{
	EGE_ASSERT2( 0, L"Please implement it in the inherit class" );

	return _false;
}

template< typename Type >
_ubool TSerializable< Type >::ExportToStream( IStreamWriter* stream_writer ) const
{
	EGE_ASSERT2( 0, L"Please implement it in the inherit class" );

	return _false;
}

}