//! @file     PhysxWorldInfo.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// PhysxSoftWorldInfo
//----------------------------------------------------------------------------

class PhysxSoftWorldInfo : public TObject< IPhysxSoftWorldInfo >
{
private:
	SoftWorldInfoPHIRef	mWorldInfo;

public:
	PhysxSoftWorldInfo( SoftWorldInfoPHI* world_info );
	virtual ~PhysxSoftWorldInfo( );

// IObject Interface
public:
	virtual _void				Tick( _dword limited_elapse, _dword elapse ) override;

// IPhysxSoftWorldInfo Interface
public:
	virtual SoftWorldInfoPHIRef GetResource( ) const override;
};

}