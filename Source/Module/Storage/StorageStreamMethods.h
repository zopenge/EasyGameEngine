//! @file     StorageStreamMethods.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

//----------------------------------------------------------------------------
// Storage Stream Interface Declaration
//----------------------------------------------------------------------------

// IStream Interface
public:
	virtual _STREAM_TYPE		GetType( ) const override;
	virtual _STREAM_SHARE_MODE	GetShareMode( ) const override;

	virtual _dword				GetSize( ) const override;
	virtual _dword 				GetOffset( ) const override;

	virtual const _byte*		GetBuffer( ) override;

	virtual _dword 				Seek( _SEEK flag, _long distance ) override;
	virtual _dword				SeekByArrangedValueFromBegin( _dword value ) override;

	virtual _void				SetEndian( _ENDIAN endian ) override;
	virtual _ENDIAN 			GetEndian( ) const override;

#if defined STORAGE_STREAM_READER

// IObject Interface
public:
	virtual IObject*				CloneTo( ) const override;

// IStreamReader Interface
public:
	virtual _dword					GetRemainBytes( ) const override;

	virtual _ubool 					ReachEnd( ) const override;

	virtual _dword 					PeekBuffer( _void* buffer, _dword size ) override;
	virtual _dword					PeekBuffer( _void* buffer, _dword size, _dword offset ) override;

	virtual _dword 					ReadBuffer( _void* buffer, _dword size ) override;
	virtual _dword 					ReadTiny( _tiny& data ) override;
	virtual _dword 					ReadShort( _short& data ) override;
	virtual _dword 					ReadLong( _long& data ) override;
	virtual _dword 					ReadByte( _byte& data ) override;
	virtual _dword 					ReadWord( _word& data ) override;
	virtual _dword 					ReadDword( _dword& data ) override;
	virtual _dword 					ReadQword( _qword& data ) override;
	virtual _dword 					ReadFloat( _float& data ) override;
	virtual _dword 					ReadDouble( _double& data ) override;

	virtual _dword					ReadString( AString& string ) override;
	virtual _dword					ReadString( UString& string ) override;
	virtual _dword					ReadString( WString& string ) override;

#elif defined STORAGE_STREAM_WRITER

// IStreamWriter Interface
public:
	virtual _dword	RemoveBuffer( _dword size ) override;
	virtual _ubool	SetCurOffsetAsEndPos( ) override;

	virtual _dword 	WriteBuffer( const _void* buffer, _dword size ) override;
	virtual _dword 	WriteTiny( _tiny data ) override;
	virtual _dword 	WriteShort( _short data ) override;
	virtual _dword 	WriteLong( _long data ) override;
	virtual _dword 	WriteByte( _byte data ) override;
	virtual _dword 	WriteWord( _word data ) override;
	virtual _dword 	WriteDword( _dword data ) override;
	virtual _dword	WriteQword( _qword data ) override;
	virtual _dword 	WriteFloat( _float data ) override;
	virtual _dword 	WriteDouble( _double data ) override;

	virtual _dword	WriteString( AStringPtr string ) override;
	virtual _dword	WriteString( WStringPtr string ) override;

#endif