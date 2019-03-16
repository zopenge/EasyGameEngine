//! @file     uuid_of.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

struct UID128;

//----------------------------------------------------------------------------
// Helpful Macros
//----------------------------------------------------------------------------

#define _UUID_OF( x ) uuid_of_impl< x >::sUID128

#define _DEFINE_UUID( x, d, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8 )	\
	template<>															\
	const UID128 uuid_of_impl< x >::sUID128 =							\
		{ d, w1, w2, { b1, b2, b3, b4, b5, b6, b7, b8 } };

//----------------------------------------------------------------------------
// uuid_of_impl
//----------------------------------------------------------------------------

template< typename T >
class uuid_of_impl
{
public:
	static const UID128 sUID128;
};

}