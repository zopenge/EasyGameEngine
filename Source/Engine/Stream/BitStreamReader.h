//! @file     BitStreamReader.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// BitStreamReader
//----------------------------------------------------------------------------

class BitStreamReader : public TBitStream< TStreamReader< IBitStreamReader > >
{
private:
	typedef TBitStream< TStreamReader< IBitStreamReader > > BaseClass;

public:
	BitStreamReader( const _byte* buffer, _dword size, _STREAM_SHARE_MODE share_mode );
	virtual ~BitStreamReader( );

// IObject Interface
public:
	virtual IObject*		CloneTo( _ubool standalone ) const override;

// IStreamReader Interface
public:
	virtual _dword			GetRemainBytes( ) const override;

	virtual _ubool 			ReachEnd( ) const override;

	virtual const _byte*	GetBuffer( ) override;

	virtual _dword 			PeekBuffer( _void* buffer, _dword size ) override;
	virtual _dword			PeekBuffer( _void* buffer, _dword size, _dword offset ) override;

	virtual _dword 			ReadBuffer( _void* buffer, _dword size ) override;
	virtual _dword 			ReadTiny( _tiny& data ) override;
	virtual _dword 			ReadShort( _short& data ) override;
	virtual _dword 			ReadLong( _int& data ) override;
	virtual _dword 			ReadByte( _byte& data ) override;
	virtual _dword 			ReadWord( _word& data ) override;
	virtual _dword 			ReadDword( _dword& data ) override;
	virtual _dword			ReadQword( _qword& data ) override;
	virtual _dword 			ReadFloat( _float& data ) override;
	virtual _dword 			ReadDouble( _double& data ) override;

// IBitStreamReader Interface
public:
	virtual _ubool 			ReadBitsStream( _void* buffer, _dword bitsnumber ) override;
	virtual _ubool 			ReadBitsStream( _tiny& value, _dword bitsnumber ) override;
	virtual _ubool 			ReadBitsStream( _byte& value, _dword bitsnumber ) override;
	virtual _ubool 			ReadBitsStream( _word& value, _dword bitsnumber ) override;
	virtual _ubool 			ReadBitsStream( _short& value, _dword bitsnumber ) override;
	virtual _ubool 			ReadBitsStream( _int& value, _dword bitsnumber ) override;
	virtual _ubool 			ReadBitsStream( _dword& value, _dword bitsnumber ) override;
	virtual _ubool 			ReadBitsStream( _qword& value, _dword bitsnumber ) override;
	virtual _ubool 			ReadBitsStream( _float& value, _dword bitsnumber ) override;
	virtual _ubool 			ReadBitsStream( _double& value ) override;
};

}