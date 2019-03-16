//! @file     AStringStreamReader.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// AStringStreamReader
//----------------------------------------------------------------------------

class AStringStreamReader : public INTERFACE_STRINGSTREAM_READER_IMPL( IStreamReader, _chara, _ENCODING_ANSI )
{
private:
	typedef INTERFACE_STRINGSTREAM_READER_IMPL( IStreamReader, _chara, _ENCODING_ANSI ) BaseClass;

public:
	AStringStreamReader( AStringPtr string );
	virtual ~AStringStreamReader( );

// IObject Interface
public:
	virtual IObject* CloneTo( _ubool standalone ) const override;
};

//----------------------------------------------------------------------------
// AStringStreamReader Implementation
//----------------------------------------------------------------------------

}