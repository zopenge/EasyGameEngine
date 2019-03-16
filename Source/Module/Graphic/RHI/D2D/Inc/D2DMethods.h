//! @file     D2DMethods.h
//! @author   LiCode
//! @version  1.1
//! @date     2007.10
//! Copyright ...

#ifndef DEFINE_FUNC_PTR
#define DEFINE_FUNC_PTR( Ret, FuncName, Args ) Ret FuncName Args;
#endif

DEFINE_FUNC_PTR( 
	HRESULT, 
	D2D1CreateFactory, 
	(D2D1_FACTORY_TYPE, REFIID, CONST D2D1_FACTORY_OPTIONS*, void**)
	)
