//! @file     IPhysxWorldInfo.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IPhysxSoftWorldInfo
//----------------------------------------------------------------------------

class IPhysxSoftWorldInfo : public IObject
{
public:
	//!	Get the internal resource.
	//!	@param		none.
	//!	@return		The soft world info.
	virtual SoftWorldInfoPHIRef GetResource( ) const PURE;
};

}