//! @file     WStringStreamReader.h
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// WStringStreamReader
//----------------------------------------------------------------------------

class WStringStreamReader : public INTERFACE_STRINGSTREAM_READER_IMPL( IStreamReader, _charw, _ENCODING_UTF16 )
{
private:
	typedef INTERFACE_STRINGSTREAM_READER_IMPL( IStreamReader, _charw, _ENCODING_UTF16 ) BaseClass;

public:
	WStringStreamReader( WStringPtr string );
	virtual ~WStringStreamReader( );

// IObject Interface
public:
	virtual IObject* CloneTo( _ubool standalone ) const override;
};

//----------------------------------------------------------------------------
// WStringStreamReader Implementation
//----------------------------------------------------------------------------

}