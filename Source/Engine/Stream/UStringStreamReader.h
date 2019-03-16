//! @file     UStringStreamReader.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// UStringStreamReader
//----------------------------------------------------------------------------

class UStringStreamReader : public INTERFACE_STRINGSTREAM_READER_IMPL( IStreamReader, _chara, _ENCODING_UTF8 )
{
private:
	typedef INTERFACE_STRINGSTREAM_READER_IMPL( IStreamReader, _chara, _ENCODING_UTF8 ) BaseClass;

public:
	UStringStreamReader( UStringPtr string );
	virtual ~UStringStreamReader( );

// IObject Interface
public:
	virtual IObject* CloneTo( _ubool standalone ) const override;
};

//----------------------------------------------------------------------------
// UStringStreamReader Implementation
//----------------------------------------------------------------------------

}