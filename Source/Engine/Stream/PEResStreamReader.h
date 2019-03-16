//! @file     PEResStreamReader.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// PEResStreamReader
//----------------------------------------------------------------------------

class PEResStreamReader : public INTERFACE_STREAM_READER_IMPL( IStreamReader )
{
private:
	typedef INTERFACE_STREAM_READER_IMPL( IStreamReader ) BaseClass;

private:
	//!	The resource handle
	_handle				mResource;
	//!	The resource data
	_byte*				mBuffer;
	//!	The resource size
	_dword				mSize;

	//!	The stream reader
	IStreamReaderRef	mStreamReader;

public:
	PEResStreamReader( );
	virtual ~PEResStreamReader( );

public:
	//!	Initialize.
	//!	@param		resource	The resource handle.
	//!	@param		size		The resource size.
	//! @return		True indicates success, false indicates failure.
	_ubool Initialize( _handle resource, _dword size );

// IObject Interface
public:
	virtual IObject*			CloneTo( _ubool standalone ) const override;

// IStream Interface
public:
	virtual _STREAM_TYPE		GetType( ) const override;
	virtual _STREAM_SHARE_MODE	GetShareMode( ) const override;

	virtual _dword				GetSize( ) const override;
	virtual _dword 				GetOffset( ) const override;

	virtual const _byte*		GetBuffer( ) override;

	virtual _dword 				Seek( _SEEK flag, _int distance ) override;
	virtual _dword				SeekByArrangedValueFromBegin( _dword value ) override;

	virtual _void				SetEndian( _ENDIAN endian ) override;
	virtual _ENDIAN 			GetEndian( ) const override;

// IStreamReader Interface
public:
	virtual _dword				GetRemainBytes( ) const override;

	virtual _ubool 				ReachEnd( ) const override;

	virtual _dword 				PeekBuffer( _void* buffer, _dword size ) override;
	virtual _dword				PeekBuffer( _void* buffer, _dword size, _dword offset ) override;

	virtual _dword 				ReadBuffer( _void* buffer, _dword size ) override;
	virtual _dword 				ReadTiny( _tiny& data ) override;
	virtual _dword 				ReadShort( _short& data ) override;
	virtual _dword 				ReadLong( _int& data ) override;
	virtual _dword 				ReadByte( _byte& data ) override;
	virtual _dword 				ReadWord( _word& data ) override;
	virtual _dword 				ReadDword( _dword& data ) override;
	virtual _dword 				ReadQword( _qword& data ) override;
	virtual _dword 				ReadFloat( _float& data ) override;
	virtual _dword 				ReadDouble( _double& data ) override;

	virtual _dword				ReadString( AString& string ) override;
	virtual _dword				ReadString( UString& string ) override;
	virtual _dword				ReadString( WString& string ) override;
};

//----------------------------------------------------------------------------
// PEResStreamReader Implementation
//----------------------------------------------------------------------------

}