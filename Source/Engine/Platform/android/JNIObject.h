//! @file     JNIObject.h
//! @author   LiCode
//! @version  1.1.0.621
//! @date     2011/01/17
//! Copyright 2009-2010 LiCode's Union.

#pragma once

namespace EGE
{

//----------------------------------------------------------------------------
// JNIObject
//----------------------------------------------------------------------------

class JNIObject : public TObject< IInvoker >
{
	NO_COPY_OPERATIONS( JNIObject )

private:
	AString	mPath;
	jobject	mJSObject;
	jclass	mJSClass;

public:
	JNIObject( );
	virtual ~JNIObject( );

public:
	EGE_GET_ACCESSOR( jclass, JSClass )

public:
	//!	Initialize.
	_ubool Initialize( AStringPtr path, _ubool static_only );
	_ubool Initialize( _ubool local, AStringPtr path, jobject js_object );
	//!	Finalize.
	_void Finalize( );

// IInvoker Interface
public:
	virtual AStringPtr	GetPath( ) const override;

	virtual _void		CallVoidMethod( AStringPtr func_name, AStringPtr parameters_decl, ... ) const override;
	virtual _ubool		CallBooleanMethod( AStringPtr func_name, AStringPtr parameters_decl, ... ) const override;
	virtual _int		CallIntMethod( AStringPtr func_name, AStringPtr parameters_decl, ... ) const override;
	virtual _large		CallLongMethod( AStringPtr func_name, AStringPtr parameters_decl, ... ) const override;
	virtual _void*		CallObjectMethod( AStringPtr func_name, AStringPtr parameters_decl, ... ) const override;

	virtual _void		CallStaticVoidMethod( AStringPtr func_name, AStringPtr parameters_decl, ... ) const override;
	virtual _ubool		CallStaticBooleanMethod( AStringPtr func_name, AStringPtr parameters_decl, ... ) const override;
	virtual _int		CallStaticIntMethod( AStringPtr func_name, AStringPtr parameters_decl, ... ) const override;
	virtual _void*		CallStaticObjectMethod( AStringPtr func_name, AStringPtr parameters_decl, ... ) const override;
};

//----------------------------------------------------------------------------
// JNIObject Implementation
//----------------------------------------------------------------------------

}