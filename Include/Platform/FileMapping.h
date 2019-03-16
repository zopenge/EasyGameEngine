//! @file     FileMapping.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// FileMapping
//----------------------------------------------------------------------------

class FileMapping : public KernelObject
{
private:
 //! The mapping file handle
 _handle mFileHandle;

 //! The mapping buffer size
 _dword mSize;
 //! The mapping buffer data
 _byte* mBuffer;

private:
 //! Initialize.
 //! @param none.
 //! @return True indicates success false indicates failure.
 _ubool Initialize( );

public:
 FileMapping( );
 ~FileMapping( );

public:
 //! Get the mapping buffer size, in bytes.
 //! @param none.
 //! @return The mapping buffer size, in bytes.
 _dword GetSize( ) const;
 //! Get the mapping buffer data.
 //! @param none.
 //! @return The mapping buffer data pointer.
 _byte* GetBuffer( ) const;

 //! Open the file mapping.
 //! @param filename The file name.
 //! @return True indicates success false indicates failure.
 _ubool Open( WStringPtr filename );
 //! Close the file mapping.
 //! @param none.
 //! @return none.
 _void Close( );
};

//----------------------------------------------------------------------------
// FileMapping Implementation
//----------------------------------------------------------------------------

}