//! @file     TBaseFile.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{
	
//----------------------------------------------------------------------------
// TBaseFile
//----------------------------------------------------------------------------

template< typename Type >
class TBaseFile : public TSerializable< TObject< TFlagsObject< Type > > >
{
protected:

protected:
	TBaseFile( );
	virtual ~TBaseFile( );

// ISerializable Interface
public:
	virtual _ubool	Import( ISerializableNode* node ) override;
	virtual _ubool	Export( ISerializableNode* node ) const override;

// IBaseFile Interface
public:
	virtual _ubool	LoadFromFile( WStringPtr filename ) override;
	virtual _ubool 	LoadFromStream( IStreamReader* stream_reader ) override;

	virtual _void	Unload( ) override;

	virtual _ubool	SaveToStream( IStreamWriter* stream_writer, _dword flags = 0 ) const override;
	virtual _ubool 	SaveToFile( WStringPtr filename, _dword flags = 0 ) const override;
};

//----------------------------------------------------------------------------
// TBaseFile Implementation
//----------------------------------------------------------------------------

template< typename Type >
TBaseFile< Type >::TBaseFile( )
{
}

template< typename Type >
TBaseFile< Type >::~TBaseFile( )
{

}

template< typename Type >
_ubool TBaseFile< Type >::Import( ISerializableNode* node )
{
	return _false;
}

template< typename Type >
_ubool TBaseFile< Type >::Export( ISerializableNode* node ) const
{
	return _false;
}

template< typename Type >
_ubool TBaseFile< Type >::LoadFromFile( WStringPtr filename )
{
	// Check the file name
	if ( filename.IsEmpty( ) )
	{
		WLOG_ERROR( L"The file name is empty" );
		return _false;
	}

	// Create the file reader
	IFileStreamReaderRef stream_reader = GetInterfaceFactory( )->CreateFileStreamReader( filename );
	if ( stream_reader.IsNull( ) )
	{
		WLOG_ERROR_1( L"Create file reader of '%s' failed", filename.Str( ) );
		return _false;
	}

	// The stream read can't be empty
	if ( stream_reader->GetSize( ) == 0 )
	{
		WLOG_ERROR_1( L"The size of '%s' is 0, we can't load it", filename.Str( ) );
		return _false;
	}

	// Load file from stream
	if ( this->LoadFromStream( stream_reader ) == _false )
	{
		WLOG_ERROR_1( L"Load from '%s' failed", filename.Str( ) );
		return _false;
	}

	return _true;
}

template< typename Type >
_ubool TBaseFile< Type >::LoadFromStream( IStreamReader* stream_reader )
{
	return _false;
}

template< typename Type >
_void TBaseFile< Type >::Unload( )
{

}

template< typename Type >
_ubool TBaseFile< Type >::SaveToStream( IStreamWriter* stream_writer, _dword flags ) const
{
	return _false;
}

template< typename Type >
_ubool TBaseFile< Type >::SaveToFile( WStringPtr filename, _dword flags ) const
{
	// Check the file name
	if ( filename.IsEmpty( ) )
	{
		WLOG_ERROR( L"The file name is empty" );
		return _false;
	}

	// Create the file writer
	IFileStreamWriterRef stream_writer = GetInterfaceFactory( )->CreateFileStreamWriter( filename );
	if ( stream_writer.IsNull( ) )
	{
		WLOG_ERROR_1( L"Create file writer of '%s' failed", filename.Str( ) );
		return _false;
	}

	// Save to stream
	if ( this->SaveToStream( stream_writer, flags ) == _false )
	{
		WLOG_ERROR_1( L"Save to '%s' failed", filename.Str( ) );
		return _false;
	}

	return _true;
}

}