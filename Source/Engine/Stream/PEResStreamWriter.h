//! @file     PEResStreamWriter.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// PEResStreamWriter
//----------------------------------------------------------------------------

class PEResStreamWriter : public INTERFACE_STREAM_WRITER_IMPL( IStreamWriter )
{
private:
	typedef INTERFACE_STREAM_WRITER_IMPL( IStreamWriter ) BaseClass;

public:
	PEResStreamWriter( );
	virtual ~PEResStreamWriter( );

// IStream Interface
public:
	virtual _STREAM_TYPE		GetType( ) const override;
	virtual _STREAM_SHARE_MODE	GetShareMode( ) const override;

	virtual _dword				GetSize( ) const override;
	virtual _dword 				GetOffset( ) const override;

	virtual _dword 				Seek( _SEEK flag, _int distance ) override;
	virtual _dword				SeekByArrangedValueFromBegin( _dword value ) override;

	virtual _void				SetEndian( _ENDIAN endian ) override;
	virtual _ENDIAN 			GetEndian( ) const override;

// IStreamWriter Interface
public:
	virtual _dword				RemoveBuffer( _dword size ) override;
	virtual _ubool				SetCurOffsetAsEndPos( ) override;

	virtual _byte*				GetBuffer( ) override;

	virtual _dword 				WriteBuffer( const _void* buffer, _dword size ) override;
	virtual _dword 				WriteTiny( _tiny data ) override;
	virtual _dword 				WriteShort( _short data ) override;
	virtual _dword 				WriteLong( _int data ) override;
	virtual _dword 				WriteByte( _byte data ) override;
	virtual _dword 				WriteWord( _word data ) override;
	virtual _dword 				WriteDword( _dword data ) override;
	virtual _dword				WriteQword( _qword data ) override;
	virtual _dword 				WriteFloat( _float data ) override;
	virtual _dword 				WriteDouble( _double data ) override;

	virtual _dword				WriteString( AStringPtr string ) override;
	virtual _dword				WriteString( WStringPtr string ) override;
};

//----------------------------------------------------------------------------
// PEResStreamWriter Implementation
//----------------------------------------------------------------------------

}