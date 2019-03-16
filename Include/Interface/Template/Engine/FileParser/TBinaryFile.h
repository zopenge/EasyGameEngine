//! @file     TBinaryFile.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// TBinaryFile
//----------------------------------------------------------------------------

template< typename Type >
class TBinaryFile : public Type
{
protected:

protected:
	TBinaryFile( );
	virtual ~TBinaryFile( );

// IBinFile Interface
public:
};

//----------------------------------------------------------------------------
// TBinaryFile Implementation
//----------------------------------------------------------------------------

template< typename Type >
TBinaryFile< Type >::TBinaryFile( )
{

}

template< typename Type >
TBinaryFile< Type >::~TBinaryFile( )
{

}

}