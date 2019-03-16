//! @file     IGraphicResourceMonitor.h
//! @author   LiCode
//! @version  1.0.0.613
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IGraphicResourceMonitor
//----------------------------------------------------------------------------

//!	The graphic resource monitor ( don't clone any resource object in notified interface )
class IGraphicResourceMonitor : public IObject
{
public:
	//!	When create 2D texture.
	//!	@param		texture_2d		The texture 2D.
	//!	@return		none.
	virtual _void OnCreateTexture2D( const IGraphicTexture2D* texture ) PURE;
	//!	When release 2D texture.
	//!	@param		texture_2d		The texture 2D.
	//!	@return		none.
	virtual _void OnReleaseTexture2D( const IGraphicTexture2D* texture ) PURE;
};

}