//! @file     IEncryptor.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IEncryptor
//----------------------------------------------------------------------------

class IEncryptor : public ICrypto
{
public:
	//!	Process string.
	//!	@param		src_string	The source string.
	//! @return		True indicates success, false indicates failure.
	virtual _ubool ProcessString( AStringPtr src_string ) PURE;
};

}