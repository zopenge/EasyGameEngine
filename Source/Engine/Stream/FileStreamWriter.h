//! @file     FileStreamWriter.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// FileStreamWriter
//----------------------------------------------------------------------------

class FileStreamWriter : public INTERFACE_FILESTREAM_WRITER_IMPL( IFileStreamWriter )
{
private:
	typedef INTERFACE_FILESTREAM_WRITER_IMPL( IFileStreamWriter ) BaseClass;

public:
	FileStreamWriter( );
	virtual ~FileStreamWriter( );

public:
	//!	Initialize.
	_ubool Initialize( WStringPtr root_path, WStringPtr relative_file_name );

// IStream Interface
public:
	virtual _dword	GetSize( ) const override;

// IStreamWriter Interface
public:
	virtual _dword	RemoveBuffer( _dword size ) override;
	virtual _ubool	SetCurOffsetAsEndPos( ) override;

	virtual _byte*	GetBuffer( ) override;

	virtual _dword 	WriteBuffer( const _void* buffer, _dword size ) override;
	virtual _dword 	WriteTiny( _tiny data ) override;
	virtual _dword 	WriteShort( _short data ) override;
	virtual _dword 	WriteLong( _int data ) override;
	virtual _dword 	WriteByte( _byte data ) override;
	virtual _dword 	WriteWord( _word data ) override;
	virtual _dword 	WriteDword( _dword data ) override;
	virtual _dword	WriteQword( _qword data ) override;
	virtual _dword 	WriteFloat( _float data ) override;
	virtual _dword 	WriteDouble( _double data ) override;
};

}