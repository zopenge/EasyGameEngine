//! @file     File.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// File
//----------------------------------------------------------------------------

//! This class represents a system file, provides create/write/read functions.
class File
{
private:
	//! The kernel object handle.
	_handle	mObjectHandle;

public:
	File( );
	~File( );

public:
	//! Type conversion, get the kernel object handle.
	//! @param		none
	//! @return		The object handle.
	inline operator _handle ( ) const;

public:
	//! Close file.
	//! @param		none.
	//!	@return		none.
	_void Close( );
	//! Open (or create) a file.
	//! @param		filename		The name of the file to open (or to create).
	//! @param		createflag		Flag of how to create a file.
	//! @param		operateflag		Flag of how to operate a file, one of _FILE_OPERATION_FLAG.
	//! @param		shareflag		Flag of how to share the file with other processes, one of _FILE_SHARE_FLAG.
	//!	@param		attributes		The attribute of file.
	//! @return		True indicates success, false indicates failure.
	_ubool Open( WStringPtr filename, _FILE_CREATE_FLAG createflag, _dword operateflag, _dword shareflag = _FILE_SHARE_READ | _FILE_SHARE_WRITE, _dword attributes = 0 );
	//! Peek from a file.
	//! @param		buffer			Pointer to the buffer that receives the data read from the file.
	//! @param		size			Number of bytes to be read from the file.
	//! @param		bytesread		Pointer to the number of bytes read.
	//! @return		True indicates success, false indicates failure.
	_ubool PeekBuffer( _void* buffer, _dword size, _dword* bytesread = _null );
	//!	Peek the buffer data with offset.
	//!	@param		buffer			The buffer data.
	//!	@param		size			The buffer size.
	//!	@param		offset			The offset of stream in bytes from begin.
	//! @param		bytesread		Pointer to the number of bytes read.
	//! @return		True indicates success, false indicates failure.
	_ubool PeekBuffer( _void* buffer, _dword size, _dword offset, _dword* bytesread = _null );
	//! Read from a file.
	//! @param		buffer			Pointer to the buffer that receives the data read from the file.
	//! @param		size			Number of bytes to be read from the file.
	//! @param		bytesread		Pointer to the number of bytes read.
	//! @return		True indicates success, false indicates failure.
	_ubool ReadBuffer( _void* buffer, _dword size, _dword* bytesread = _null );
	//! Write into a file.
	//! @param		buffer			Pointer to the buffer containing the data to write to the file.
	//! @param		size			Number of bytes to write to the file.
	//! @param		byteswritten	Pointer to the number of bytes written.
	//! @return		True indicates success, false indicates failure.
	_ubool WriteBuffer( const _void* buffer, _dword size, _dword* byteswritten = _null );
	//! Clears the buffers of the file and causes all buffered data to be written to the file.
	//! @param		none
	//! @return		True indicates success, false indicates failure.
	_ubool Flush( );

	//!	Read the 8-bits signed value.
	//!	@param		value			The 16-bits value.
	//! @return		True indicates success, false indicates failure.
	_ubool ReadByte( _tiny& value );
	//!	Read the 16-bits signed value.
	//!	@param		value			The 16-bits value.
	//! @return		True indicates success, false indicates failure.
	_ubool ReadWord( _short& value );
	//!	Read the 32-bits signed value.
	//!	@param		value			The 32-bits value.
	//! @return		True indicates success, false indicates failure.
	_ubool ReadDword( _int& value );
	//!	Read the 8-bits unsigned value.
	//!	@param		value			The 16-bits value.
	//! @return		True indicates success, false indicates failure.
	_ubool ReadByte( _byte& value );
	//!	Read the 16-bits unsigned value.
	//!	@param		value			The 16-bits value.
	//! @return		True indicates success, false indicates failure.
	_ubool ReadWord( _word& value );
	//!	Read the 32-bits unsigned value.
	//!	@param		value			The 32-bits value.
	//! @return		True indicates success, false indicates failure.
	_ubool ReadDword( _dword& value );
	//!	Read the 64-bits unsigned value.
	//!	@param		value			The 32-bits value.
	//! @return		True indicates success, false indicates failure.
	_ubool ReadQword( _qword& value );
	//!	Read the 32-bits float value.
	//!	@param		value			The 32-bits float value.
	//! @return		True indicates success, false indicates failure.
	_ubool ReadFloat( _float& value );
	//!	Read the 64-bits float value.
	//!	@param		value			The 32-bits float value.
	//! @return		True indicates success, false indicates failure.
	_ubool ReadDouble( _double& value );

	//!	Write the 8-bits signed value.
	//!	@param		value			The 16-bits value.
	//! @return		True indicates success, false indicates failure.
	_ubool WriteByte( _tiny value );
	//!	Write the 16-bits signed value.
	//!	@param		value			The 16-bits value.
	//! @return		True indicates success, false indicates failure.
	_ubool WriteWord( _short value );
	//!	Write the 32-bits signed value.
	//!	@param		value			The 32-bits value.
	//! @return		True indicates success, false indicates failure.
	_ubool WriteDword( _int value );
	//!	Write the 8-bits unsigned value.
	//!	@param		value			The 16-bits value.
	//! @return		True indicates success, false indicates failure.
	_ubool WriteByte( _byte value );
	//!	Write the 16-bits unsigned value.
	//!	@param		value			The 16-bits value.
	//! @return		True indicates success, false indicates failure.
	_ubool WriteWord( _word value );
	//!	Write the 32-bits unsigned value.
	//!	@param		value			The 32-bits value.
	//! @return		True indicates success, false indicates failure.
	_ubool WriteDword( _dword value );
	//!	Write the 64-bits unsigned value.
	//!	@param		value			The 64-bits value.
	//! @return		True indicates success, false indicates failure.
	_ubool WriteQword( _qword value );
	//!	Write the 32-bits float value.
	//!	@param		value			The 32-bits float value.
	//! @return		True indicates success, false indicates failure.
	_ubool WriteFloat( _float value );
	//!	Write the 64-bits float value.
	//!	@param		value			The 64-bits float value.
	//! @return		True indicates success, false indicates failure.
	_ubool WriteDouble( _double value );
	//!	Write the ANSI string.
	//!	@param		string			The string what you want to write.
	//! @return		True indicates success, false indicates failure.
	_ubool WriteString( AStringPtr string );
	//!	Write the UNICODE string.
	//!	@param		string			The string what you want to write.
	//! @return		True indicates success, false indicates failure.
	_ubool WriteString( WStringPtr string );
	//!	Write the UNICODE flag.
	//!	@param		none.
	//! @return		True indicates success, false indicates failure.
	_ubool WriteUnicodeFlag( );
	//!	Write the UTF-8 flag.
	//!	@param		none.
	//! @return		True indicates success, false indicates failure.
	_ubool WriteUTF8Flag( );

	//! Move the file pointer from the begin of the file.
	//! @remarks	A positive distance moves the file pointer forward in the file,
	//!				and a negative value moves the file pointer backward.
	//!	@param		flag			The seek flag.
	//! @param		distance		Number of bytes to move.
	//! @return		The current offset of file pointer from begin.
	_dword Seek( _SEEK flag, _int distance );

	//! Get the current offset of file pointer of the file.
	//! @param		none
	//! @return		The offset of file pointer from begin of the file in number of bytes.
	_dword GetOffset( ) const;

	//! Get the size, in bytes, of the file.
	//! @param		none
	//! @return		Size of the file in bytes, or -1 indicates failure.
	_dword GetSize( ) const;
	//! Set the size of the file, maybe truncate or extend it.
	//! @param		size			Size of the file in bytes.
	//! @return		True indicates success, false indicates failure.
	_ubool SetSize( _dword size );

	//!	Sets the physical file size for the specified file to the current position of the file pointer.
	//!	@param		none.
	//! @return		True indicates success, false indicates failure.
	_ubool SetEndOfFile( );

	//! Get times of file.
	//! @param		creation		The date and time the file was created.
	//! @param		lastaccess		The date and time the file was last accessed.
	//! @param		lastwrite		The date and time the file was last written to.
	//! @return		True indicates success, false indicates failure.
	_ubool GetTimes( FileTime* creation, FileTime* lastaccess, FileTime* lastwrite ) const;
	//! Get times of file.
	//! @param		creation		The date and time the file was created.
	//! @param		lastaccess		The date and time the file was last accessed.
	//! @param		lastwrite		The date and time the file was last written to.
	//! @return		True indicates success, false indicates failure.
	_ubool GetTimes( CalendarTime* creation, CalendarTime* lastaccess, CalendarTime* lastwrite ) const;
	//! Set times of file.
	//! @param		creation		The date and time the file was created.
	//! @param		lastaccess		The date and time the file was last accessed.
	//! @param		lastwrite		The date and time the file was last written to.
	//! @return		True indicates success, false indicates failure.
	_ubool SetTimes( const CalendarTime* creation, const CalendarTime* lastaccess, const CalendarTime* lastwrite );
};

//----------------------------------------------------------------------------
// File Implementation
//----------------------------------------------------------------------------

File::operator _handle ( ) const
{
	return mObjectHandle;
}

}
