//! @file     BulletSoftWorldInfo.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// BulletSoftWorldInfo
//----------------------------------------------------------------------------

class BulletSoftWorldInfo : public SoftWorldInfoPHI
{
private:
	btSoftBodyWorldInfo	mBTWorldInfo;

public:
	EGE_GETR_ACCESSOR( btSoftBodyWorldInfo, BTWorldInfo )

public:
	BulletSoftWorldInfo( );
	virtual ~BulletSoftWorldInfo( );

// IObject Interface
public:
	virtual _void	Tick( _dword limited_elapse, _dword elapse ) override;
};

}