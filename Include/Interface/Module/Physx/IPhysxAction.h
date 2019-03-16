//! @file     IPhysxAction.h
//! @author   LiCode
//! @version  1.0
//! @date     2007.10
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IPhysxAction
//----------------------------------------------------------------------------

class IPhysxAction : public IClonableObject< IPhysxAction, IObject >
{
public:
	//!	The shape type
	enum _TYPE
	{
		_TYPE_UNKNOWN,
		_TYPE_CHARACTER_CONTROLLER,
	};

public:
	//!	Get the shape type.
	//!	@param		none.
	//!	@return		The shape type.
	virtual _TYPE GetType( ) const PURE;
	//!	Get the action resource.
	//!	@param		none.
	//!	@return		The action type.
	virtual ActionPHIRef GetActionResource( ) PURE;
};

//----------------------------------------------------------------------------
// IPhysxCharacterControllerAction
//----------------------------------------------------------------------------

class IPhysxCharacterControllerAction : public IPhysxAction
{
public:
};

}