//! @file     ITGUISubResourceObject.h
//! @author   Foreven
//! @version  
//! @date     2012/11/15  
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// ITGUISubResourceObject
//----------------------------------------------------------------------------

template< typename Type >
class ITGUISubResourceObject : public Type
{
public:
	virtual _void				LoadDelaySubResourceInBackground( IObject* ui_app_entity, ISerializableNode* node ) const PURE;
};


}