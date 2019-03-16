//! @file     TFileWriter.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TFileWriter
//----------------------------------------------------------------------------

template< typename Type >
class TFileWriter : public TObject< Type >
{
protected:

protected:
	TFileWriter( );
	virtual ~TFileWriter( );

// IFileWriter Interface
public:
	virtual _ubool	SaveToStream( IStreamWriter* stream_writer ) const override;
	virtual _ubool	SaveToFile( WStringPtr file_name ) const override;
};

//----------------------------------------------------------------------------
// TFileWriter Implementation
//----------------------------------------------------------------------------

template< typename Type >
TFileWriter< Type >::TFileWriter( )
{
}

template< typename Type >
TFileWriter< Type >::~TFileWriter( )
{

}

template< typename Type >
_ubool TFileWriter< Type >::SaveToStream( IStreamWriter* stream_writer ) const
{
	EGE_ASSERT( 0 );
	return _false;
}

template< typename Type >
_ubool TFileWriter< Type >::SaveToFile( WStringPtr file_name ) const
{
	IFileStreamWriterRef stream_writer = GetInterfaceFactory( )->CreateFileStreamWriter( file_name );
	if ( stream_writer.IsNull( ) )
		return _false;

	return SaveToStream( stream_writer );
}

}