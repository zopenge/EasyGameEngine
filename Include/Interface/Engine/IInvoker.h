//! @file     IInvoker.h
//! @author   LiCode
//! @version  1.0.0.547
//! @date     2011/01/07
//! Copyright ...

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// IInvoker
//----------------------------------------------------------------------------

class IInvoker : public IObject
{
public:
	virtual AStringPtr GetPath( ) const PURE;

	virtual _void	CallVoidMethod( AStringPtr func_name, AStringPtr parameters_decl, ... ) const PURE;
	virtual _ubool	CallBooleanMethod( AStringPtr func_name, AStringPtr parameters_decl, ... ) const PURE;
	virtual _int	CallIntMethod( AStringPtr func_name, AStringPtr parameters_decl, ... ) const PURE;
	virtual _large	CallLongMethod( AStringPtr func_name, AStringPtr parameters_decl, ... ) const PURE;
	virtual _void*	CallObjectMethod( AStringPtr func_name, AStringPtr parameters_decl, ... ) const PURE;

	virtual _void	CallStaticVoidMethod( AStringPtr func_name, AStringPtr parameters_decl, ... ) const PURE;
	virtual _ubool	CallStaticBooleanMethod( AStringPtr func_name, AStringPtr parameters_decl, ... ) const PURE;
	virtual _int	CallStaticIntMethod( AStringPtr func_name, AStringPtr parameters_decl, ... ) const PURE;
	virtual _void*	CallStaticObjectMethod( AStringPtr func_name, AStringPtr parameters_decl, ... ) const PURE;
};

}
