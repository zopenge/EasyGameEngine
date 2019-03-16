//! @file     TSoundFileWriter.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TSoundFileWriter
//----------------------------------------------------------------------------

template< typename Type >
class TSoundFileWriter : public TFileWriter< Type >
{
protected:

protected:
	TSoundFileWriter( );
	virtual ~TSoundFileWriter( );

// IFileWriter Interface
public:
	virtual IBaseFilePassRef	SaveToBaseFile( ) const override;
};

//----------------------------------------------------------------------------
// TSoundFileWriter Implementation
//----------------------------------------------------------------------------

template< typename Type >
TSoundFileWriter< Type >::TSoundFileWriter( )
{
}

template< typename Type >
TSoundFileWriter< Type >::~TSoundFileWriter( )
{

}

template< typename Type >
IBaseFilePassRef TSoundFileWriter< Type >::SaveToBaseFile( ) const
{
	IStreamWriterRef stream_writer = GetInterfaceFactory( )->CreateMemStreamWriter( );
	if ( stream_writer.IsNull( ) )
		return _null;

	if ( this->SaveToStream( stream_writer ) == _false )
		return _null;

	IStreamReaderRef stream_reader = GetInterfaceFactory( )->CreateMemStreamReader( stream_writer->GetBuffer( ), stream_writer->GetOffset( ), _STREAM_SHARE_MODE_NONE );
	if ( stream_reader.IsNull( ) )
		return _null;

	return GetInterfaceFactory( )->ParseSoundFile( stream_reader );
}

}