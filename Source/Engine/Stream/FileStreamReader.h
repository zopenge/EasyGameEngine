//! @file     FileStreamReader.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// FileStreamReader
//----------------------------------------------------------------------------

class FileStreamReader : public INTERFACE_FILESTREAM_READER_IMPL( IFileStreamReader )
{
private:
	typedef INTERFACE_FILESTREAM_READER_IMPL( IFileStreamReader ) BaseClass;

protected:
	//!	The file size
	_dword	mFileSize;

	//!	The temporary buffer
	_byte*	mTempBuffer;

public:
	FileStreamReader( );
	virtual ~FileStreamReader( );

public:
	//!	Initialize.
	_ubool Initialize( WStringPtr root_path, WStringPtr relative_file_name );

// IObject Interface
public:
	virtual IObject*		CloneTo( _ubool standalone ) const override;

// IStream Interface
public:
	virtual _dword			GetSize( ) const override;

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

}