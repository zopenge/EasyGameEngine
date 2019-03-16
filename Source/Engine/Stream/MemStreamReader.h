//! @file     MemStreamReader.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// MemStreamReader
//----------------------------------------------------------------------------

class MemStreamReader : public TMemStream< TStreamReader< IStreamReader > >
{
private:
	typedef TMemStream< TStreamReader< IStreamReader > > BaseClass;

private:
	//!	Read the value data.
	//!	@param		data	The value data.
	//! @return		True indicates success, false indicates failure.
	template< typename DataType >
	_dword ReadValue( DataType& data );

public:
	MemStreamReader( const _byte* buffer, _dword size, _STREAM_SHARE_MODE share_mode );
	virtual ~MemStreamReader( );

// IObject Interface
public:
	virtual IObject*		CloneTo( _ubool standalone ) const override;

// IStreamReader Interface
public:
	virtual _dword			GetRemainBytes( ) const override;

	virtual const _byte*	GetBuffer( ) override;

	virtual _ubool 			ReachEnd( ) const override;

	virtual _dword 			PeekBuffer( _void* buffer, _dword size ) override;
	virtual _dword			PeekBuffer( _void* buffer, _dword size, _dword offset ) override;

	virtual _dword 			ReadBuffer( _void* buffer, _dword size ) override;
	virtual _dword 			ReadTiny( _tiny& data ) override;
	virtual _dword 			ReadShort( _short& data ) override;
	virtual _dword 			ReadLong( _int& data ) override;
	virtual _dword 			ReadByte( _byte& data ) override;
	virtual _dword 			ReadWord( _word& data ) override;
	virtual _dword 			ReadDword( _dword& data ) override;
	virtual _dword 			ReadQword( _qword& data ) override;
	virtual _dword 			ReadFloat( _float& data ) override;
	virtual _dword 			ReadDouble( _double& data ) override;
};

//----------------------------------------------------------------------------
// MemStreamReader Implementation
//----------------------------------------------------------------------------

template< typename DataType >
_dword MemStreamReader::ReadValue( DataType& data )
{
	if ( GetRemainBytes( ) < sizeof( DataType ) )
		return 0;

	data = *( (DataType*) mPointer );
	mPointer += sizeof( DataType );

	return sizeof( DataType );
}

}